#include <stdio.h>
#include <stdlib.h>
#include <linmath\linmath.h>

#include <stdlib.h>
#include <string.h>

#include "render_internal.h"
#include "../renderer/render.h"
#include "character_renderer.h"
#include "../mirage_hengine.h"

#include <math.h>
#include <stdio.h>
#include "../texture/texture.h"

#include "../player/player.h"
#include "../math_utils.h"
#include "../array_list/array_list.h"
#include "../physics/physics.h"
#include "../entity/entity.h"
#include "../animation/animation.h"
#include "../ui/button.h"
#include "../NPC/npc_utils.h"


#include "../types.h"
#include "../collision.h"
#include "../global.h"
#include "../common.h"

walls get_wall(int i)
{
   return global.W[global.S[i].ws];
}

Entity **array_entity;

Sprite_Sheet sprite_sheet_time = {0};
Sprite_Sheet sprite_sheet_menu = {0};

Sprite_Sheet sprite_sheet_anim_attack = {0};

u32 time_anim_def_id;
u32 attack_anim_def_id;
u32 new_char_menu_id;

u32 enemy_index   = 0;
int index_text_ui = 0;

void render_add_button_load_ui()
{
   index_text_ui = index_text_ui + 1;
}

void render_remove_button_load_ui()
{
    index_text_ui = index_text_ui - 1;
}

int render_get_button_load_ui()
{
   return index_text_ui;
}

void on_npc_body_hit(Body *self, Body *other, Hit hit) 
{
    return;
}

void on_npc_body_hit_static(Body *self, 
                            Static_Body *other, 
                            Hit hit) 
{

}

u32 attack_anim_id = 0;

void clearBackground(TextureMaps* textures, Body* P, math M)
{

    for(int y=0;y<SH;y++)
    {
        for(int x=0;x<SW;x++)
        {
            int r= 153;
            int g= 153;
            int b= 163;
            drawPixel(x , y , r,g,b);
        }
    }
}

void attack_init(u32 char_id, u32 new_anim_id)
{
    if(attack_anim_id == 0)
    {
        attack_anim_id = new_anim_id;
    }
}


int index_y = (int)9;
int index_x = 0;

void draw_ui_screen(TextureMaps* textures, Body * P)
{
    int x,y,t;
    t = 21;

    for(y=0;y<textures[t].h;y++)
    {
        for(x=0;x<textures[t].w; x++)
        {
            int pixel= ((textures[t].h - y)-1)  * 3 * textures[t].w + x*3;
            int r=  textures[t].name[pixel+0] ;
            int g= textures[t].name[pixel+1];
            int b= textures[t].name[pixel+2];

            if(r + g + b > 0)
            {
                drawPixel(x + (( SW2 * .25 )), y + (SH - (SH2 * 1.8)), r,g,b);
            }
         }
    }

    for(int n = 0; n < index_text_ui; n++ )
    {
        for(y=0;y<15;y++)
        {
            for(x=0;x<15; x++)
            {

                float x1= (x * global.M.cos[155 - (30 * (n))]) - 
                   ((y - 52) * global.M.sin[155 - (30 * (n))]);

                float y1 =(x * global.M.sin[155 - (30 * (n))]) + 
                   ((y - 52) * global.M.cos[155 - (30 * (n))]);

                int pixel=((textures[25].h - y)-1)  * 3 * textures[25].w + x*3;
                int r=    textures[25].name[pixel+0];
                int g=    textures[25].name[pixel+1];
                int b=    textures[25].name[pixel+2];

                if(r + g + b > 25)
                {
                    drawPixel(x1 + (( SW2 * .31 )), y1 + (SH - (SH2 * 1.76)), r,g,b);
                }
            }
        }
    }

    for(x=20;x<103; x++)
    {
        for(y=90;y<117; y++)
        {
            float x1= (x - 60) * global.M.cos[P->a] - 
               ((y - 80) - 60) * global.M.sin[P->a];

            float y1 =(x - 60) * global.M.sin[P->a] + 
               ((y - 80) - 60) * global.M.cos[P->a];


            float xrotated = x1 + 60;
            float yrotated = y1 + 60;

            int st = 23;
            int pixel= (int)(textures[st].h -((int)yrotated%textures[st].h) -1)  
                        *3* textures[st].w + ((int)xrotated%textures[st].w)*3 ;
            
            int r= textures[st].name[pixel+0];
            int g= textures[st].name[pixel+1];
            int b= textures[st].name[pixel+2];

            if(r + g + b > 0)
            {
                drawPixel(x + (SW - (SW2 * 1.25)), y + (SH - (SH2 * 0.65)), r,g,b);
            }
       }
   }

    for(u32 i = 0; i < button_array_list_get()->len; ++i)
    {
        button_t * button = button_get(i);
        if(button )
        {
            if(button->text)
            {
                for(x=0;x<button->text->w; x++)
                {
                    for(y=0;y<button->text->h; y++)
                    {
                        int pixel= ( ( button->text->h - y)-1)  * 3 *button->text->w + x*3;
                        int r= button->text->name[pixel+0];
                        int g= button->text->name[pixel+1];
                        int b= button->text->name[pixel+2];

                        if(r + g + b > 0 && r + g + b < 762)
                        {
                           drawPixel( (int)(x+button->draw_rect.x), (int)(y+button->draw_rect.y), r,g,b );
                        }
                    }
                }
            }
        }
    }
}

int dist(int x1,int y1, int x2,int y2)
{
    int distance = sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) );
    return distance;
}

void clipBehindPlayer(int *x1,
                      int *y1,
                      int *z1, 
                      int  x2,
                      int  y2,
                      int  z2) //clip line
{
    float da=*y1;                                 //distance plane -> point a
    float db= y2;                                 //distance plane -> point b
    float d=da-db; if(d==0){ d=1;}
    float s = da/(da-db);                         //intersection factor (between 0 and 1)
    *x1 = *x1 + s*(x2-(*x1));
    *y1 = *y1 + s*(y2-(*y1)); if(*y1==0){ *y1=1;} //prevent divide by zero
    *z1 = *z1 + s*(z2-(*z1));
}


int drawWall(int x1,
             int x2, 
             int b1,
             int b2, 
             int t1,
             int t2,
             int s,
             int w, 
             int frontBack, 
             TextureMaps* textures, 
             Body* P,
             math M)
{
    int x,y;
    int wt = global.W[w].wt;
    //Hold difference in distance
    float ht = 0.f;

    int dyb  = b2-b1;                       //y distance of bottom line
    int dyt  = t2-t1;                       //y distance of top    line
    int dx   = (float)( x2-x1 ); 

    if(dx == 0)
    { 
        dx = 1;
    }    //x distance
    
    float ht_step = (((float)textures[wt].w))  / 
                     ((float) x2- ((float)x1 + 
                      (float)(x2-x1) * .5f));

    int xs=x1;//hold initial x1 starting position
    if(x1 < 0)
    {  
        ht -= ht_step * (float)( x1 ); 
        x1 = 0;
    } //clip left
    
    if(x2<0)
    {  
        x2 = 0;
    } //clip left
    
    if(x1>SW)
    { 
        x1=SW; 
    } //clip right
    
    if(x2>SW)
    { 
        x2=SW; 
    } //clip right
 
    //draw x verticle lines
    for(x = x1; x < x2; x++)
    {
        //The Y start and end point
        int y1 = dyb*(x-xs+0.5)/dx+b1; //y bottom point
        int y2 = dyt*(x-xs+0.5)/dx+t1; //y bottom point
        float vt = 0, vt_step = ( (float)textures[wt].h )  / (float)(y2-y1);

        //Clip Y
        if(y1 < 0)
        { 
            vt -= vt_step * (float)y1; 
            y1= 0;
        } //clip y
  
        if(y2 < 0)
        { 
            y2= 0;
        } //clip y
        
        if(y1 > SH)
        { 
            y1=SH;
        } //clip y
        
        if(y2 > SH)
        { 
            y2=SH;
        } //clip y
  
        int y0 = SH2;
        int x0 = SW2;
        int wo;

        //surface
        if(frontBack == 0)
        {
            if(global.S[s].surface== 1)
            { 
                global.S[s].surf[x]=y1; 
            }
            
            if(global.S[s].surface== 2)
            { 
                global.S[s].surf[x]=y2;
            }
     
            for(y = y1; y < y2; y++)
            {

                int ys = y1 - y0;
                int ye = y2 - y0;

                int xs = x2 - x0;
                int xy  =x0 -ye ;

                int pixel= (int)(textures[wt].h - ((int)vt%textures[wt].h) -1) 
                            *3* textures[wt].w + ((int)ht%textures[wt].w)* 3;

                int r = textures[wt].name[pixel+0] - (global.W[w].shade / 3); 
                if(r < 0)
                { 
                    r = 0;
                }
                
                int g = textures[wt].name[pixel+1] - (global.W[w].shade / 4); 
                if(g < 0)
                { 
                    g = 0;
                }
                int b = textures[wt].name[pixel+2] - (global.W[w].shade / 4); 
                if(b < 0)
                { 
                    b = 0;
                }

                if(r + b + g > 0)
                {
                    drawPixel(x,y, r, g, b );
                }
                vt+=vt_step;
            }
            ht += ht_step;
        }

        if(frontBack == 1)
        {
            int x0 = SW/2;
            int y0 = SH/2;
            float fov =  400.0f;
            int x2 = x-x0;
            int w0;

            float tile = global.S[s].ss * 22.f;

            if(global.S[s].surface== 1)
            { 
                y2 = global.S[s].surf[x]; 
                w0  = global.S[s].z1;
            }

            if(global.S[s].surface== 2)
            { 
                y1 = global.S[s].surf[x]; 
                w0  = global.S[s].z2;
            }

            float lookUpAnDown =  -P->l * 1.1;        
            if(lookUpAnDown > SH)
            { 
                lookUpAnDown = SH; 
            }

            float moveUpDown = (float)(P->aabb.position[2] - w0) / (float)( y0 );  
            if(moveUpDown == 0) 
            {
                moveUpDown = 0.001;
            }

            int ys  = y1 -y0,
                ye  = y2 -y0,
                xe  = x2 -ye;

            for(y=ys; y < ye; y++)
            {

                float z = y + lookUpAnDown;   
                if(z  ==0) 
                { 
                    z  = 0.0001; 
                }
                
                float fx = x2 / z * moveUpDown  * tile;
                float fy = fov / z * moveUpDown * tile;
                float fy_rgb = fov / z;

                float rx = fx * M.sin[P->a] - fy * M.cos[P->a] + (P->aabb.position[1] * .002)* (tile);
                float ry = fx * M.cos[P->a] + fy * M.sin[P->a] - (P->aabb.position[0] * .002)* (tile);

                if(rx < 0)
                { 
                    rx = -rx +1;
                }
                if(ry < 0)
                { 
                    ry = -ry +1;
                }

                int st = global.S[s].st;

                int pixel= (int)(textures[st].h - ((int)ry%textures[st].h) - 1)  
                             *3* textures[st].w + ((int)rx%textures[st].w) * 3;
                int r= textures[st].name[pixel+0];
                int g= textures[st].name[pixel+1];
                int b= textures[st].name[pixel+2];

                int fog_r = r -163;
                int fog_g = g -163;
                int fog_b = b -173;

                int xy  = (y + ys) * .6;

                int r_ = r -  (fog_r - fog_r * (y /(float) xy));
                int g_ = g  - (fog_g - fog_g * (y /(float) xy));
                int b_ = b -  (fog_b - fog_b * (y /(float) xy));

                if(r_ < r)
                { 
                    r_ = r;
                }
                if(r_ >= 255)
                { 
                    r_ = 255;
                }

                if(g_ < g)
                { 
                    g_ = g;
                }
                
                if(g_ >=255)
                { 
                    g_ = 255;
                }

                if(b_ < 0)
                { 
                    b_ = b;
                }
                
                if(b_ >= 255)
                { 
                    b_ = 255;
                }

                if(r + b + g > 2)
                {
                    drawPixel(x2 + x0, y + y0, r_ , g_ , b_);
                }
            }
        }
    }
}

void draw3D_Walls(TextureMaps* textures, Body*  P,math M)
{
    int x,
        s,
        w,
        frontBack, 
        cycles, 
        wx[4],
        wy[4],
        wz[4]; 
    float CS = M.cos[P->a], 
          SN = M.sin[P->a];

    //order sectors by distance
    for(s=0; s<global.numSect-1; s++)
    {
        for(w=0; w<global.numSect-s-1; w++)
        {
            if(global.S[w].d<global.S[w+1].d)
            {
                sectors st = global.S[w]; 
                global.S[w] = global.S[w+1]; 
                global.S[w+1] = st;
            }
        }
    }

    //draw sectors
    for(s=0;s<global.numSect;s++)
    {

        global.S[s].d=0; //clear distance
        if(P->aabb.position[2]<global.S[s].z1)
        { 
            global.S[s].surface=1;
            cycles =2;
            for(x=0;x<SW;x++)
            { 
                global.S[s].surf[x] = SH; 
            }
        }//bottom surface
        else if(P->aabb.position[2]>global.S[s].z2)
        { 
            global.S[s].surface=2;
            cycles =2;
            for(x=0; x<SW; x++)
            { 
                global.S[s].surf[x] = 0; 
            }
        }//top surface
        else
        { 
            global.S[s].surface=0;
            cycles =1;
        }//no surfaces
        for(frontBack=0;frontBack<cycles;frontBack++)
        {
            for(w=global.S[s].ws;w<global.S[s].we;w++)
            {
                //offset bottom 2 points by player
                int x1=global.W[w].x1-(P->aabb.position[0]),
                    y1=global.W[w].y1-(P->aabb.position[1]);
                
                int x2=global.W[w].x2-(P->aabb.position[0]),
                    y2=global.W[w].y2-(P->aabb.position[1]);

                //swap for surface
                if(frontBack==0)
                {
                    int swp = x1; 
                         x1 = x2; 
                         x2 = swp;
                        swp = y1; 
                         y1 = y2; 
                         y2 = swp;
                }

                //world X position
                wx[0]=x1*CS-y1*SN;
                wx[1]=x2*CS-y2*SN;
                wx[2]=wx[0];         //top line has the same x
                wx[3]=wx[1];
                
                //world Y position (depth)
                wy[0]=y1*CS+x1*SN;
                wy[1]=y2*CS+x2*SN;
                wy[2]=wy[0];        //top line has the same y
                wy[3]=wy[1];
                global.S[s].d+=dist(0,
                                    0, 
                                    (wx[0] + wx[1]) / 2,
                                    (wy[0] + wy[1]) / 2 );  //store this wall distance
                //world z height
                wz[0] = global.S[s].z1 - (P->aabb.position[2] - P->aabb.half_size[2]) + ((P->l * wy[0]) / 3.0);
                wz[1] = global.S[s].z1 - (P->aabb.position[2] - P->aabb.half_size[2]) + ((P->l * wy[1]) / 3.0);
                wz[2] = global.S[s].z2 - (P->aabb.position[2] - P->aabb.half_size[2]) + ((P->l * wy[0]) / 3.0);
                wz[3] = global.S[s].z2 - (P->aabb.position[2] - P->aabb.half_size[2]) + ((P->l * wy[1]) / 3.0);

                //dont draw if behind player
                if(wy[0] < 1 && wy[1] < 1)
                {
                    continue;
                }      //wall behind player, dont draw
                
                //point 1 behind player, clip
                if(wy[0] < 1)
                {
                    clipBehindPlayer(&wx[0],&wy[0],&wz[0], wx[1],wy[1],wz[1]); //bottom line
                    clipBehindPlayer(&wx[2],&wy[2],&wz[2], wx[3],wy[3],wz[3]); //top line
                }
    
                //point 2 behind player, clip
                if(wy[1] < 1)
                {
                    clipBehindPlayer(&wx[1],&wy[1],&wz[1], wx[0],wy[0],wz[0]); //bottom line
                    clipBehindPlayer(&wx[3],&wy[3],&wz[3], wx[2],wy[2],wz[2]); //top line
                }
    
                //screen x, screen y position
                wx[0]=wx[0]*880/wy[0]+SW2; 
                wy[0]=wz[0]*880/wy[0]+SH2;
                wx[1]=wx[1]*880/wy[1]+SW2; 
                wy[1]=wz[1]*880/wy[1]+SH2;
                wx[2]=wx[2]*880/wy[2]+SW2; 
                wy[2]=wz[2]*880/wy[2]+SH2;
                wx[3]=wx[3]*880/wy[3]+SW2; 
                wy[3]=wz[3]*880/wy[3]+SH2;

                drawWall(wx[0], wx[1], wy[0],
                         wy[1], wy[2], wy[3],
                         s, w, frontBack,
                         textures, P, M);
            }
        }
    }
}


Body *ray_cast_line_body( vec3 position, vec3 D, u8 dist)
{

	f32 X = position[0];
	f32 Y = position[1];
	f32 Z =	position[2];

	for(u32 n = 3; n < physics_body_list_array_get()->len + 1; n++) 
    {
		Body * s_other = physics_body_get(n);
		if(s_other != NULL)
        {
			Hit result = (Hit){.time = 0xBEEF};
			AABB sum_aabb = s_other->aabb;

			Body body = {0};
			body.aabb.position[0] =      X;
			body.aabb.position[1] =      Y;
			body.aabb.position[2] =      Z;

			body.aabb.half_size[0] =  4100;
			body.aabb.half_size[1] =  4100;
			body.aabb.half_size[2] =    21;

			vec3_add(sum_aabb.half_size, sum_aabb.half_size, body.aabb.half_size);
			vec3 velocity = { D[0], D[1], 0 };

			Hit hit = ray_intersect_aabb(body.aabb.position, velocity, sum_aabb);
			if(hit.is_hit)
            {
				return s_other;
			}

		}
	}
	return NULL;
}

void draw_characters(TextureMaps* textures, Body* P, math M)
{

    Entity* entity_player = entity_get(P->entity_id);
    if(entity_player != NULL)
    {
        float sin_ = (CHARACTER_DEFAULT_SIZE * .25f)*global.M.sin[P->a];
		float cos_ = (CHARACTER_DEFAULT_SIZE * .25f)*global.M.cos[P->a];
		vec3 D = 
        {
            cos_ ,
            sin_ , 
            0
        };

        Static_Body *hit_ = ray_cast_line((vec3)
                                            {
                                                P->aabb.position[0],
                                                P->aabb.position[1],
                                                P->aabb.position[2]
                                            },
                                            D,
                                            .75);

        if(hit_ != NULL)
        {
            return;
        }
        D[0] *= 12;
        D[1] *= 12;

		Body *hit = ray_cast_line_body((vec3)
                                        {
                                            P->aabb.position[0],
                                            P->aabb.position[1],
                                            P->aabb.position[2]
										},
                                        D,
										CHARACTER_DEFAULT_SIZE);

		if(hit != NULL) 
        {
			if(entity_get(hit->entity_id) != NULL) 
            {
                draw3D_character_at_location(entity_get(hit->entity_id),
                                                        textures, 
                                                        P, 
                                                        M, 
                                                        entity_get(hit->entity_id)->texture_id);
            }
        }
    }
}


