#include <stdio.h>
#include <stdbool.h>

#include <stdlib.h>
#include <linmath\linmath.h>
#include "character_renderer.h"

#include "render_internal.h"
#include "../renderer/render.h"

#include <math.h>
#include <stdio.h>
#include "../texture/texture.h"

#include "../player/player.h"
#include "../math_utils.h"
#include "../array_list/array_list.h"
#include "../physics/physics.h"
#include "../entity/entity.h"
#include "../animation/animation.h"

#include "../math_utils.h"

#include "../types.h"
#include "../collision.h"
#include "../global.h"
#include "../common.h"



void draw_character_at_run_time(int x1,int x2, int b1,int b2, int t1,int t2, TextureMaps* textures, Entity* npc_id, float frame_index_y,bool flipped, u32 id_text)
{

  Animation* animation = animation_get(npc_id->animation_id);
   if ( animation != NULL ){
   Animation_Definition *adef = get_animation_definitiion(animation->animation_definition_id);
    if ( adef != NULL){
     Animation_Frame *aframe = &adef->frames[animation->current_frame_index];
      if ( aframe != NULL ){
        vec4 uvs;
      vec2 offset_anim= { aframe->column, aframe->row};

      vec2 frame= {  npc_id->sprite_offset[0] * (offset_anim[0]) - 1, npc_id->sprite_offset[1]};


      int x,y;
      int wt = id_text;
      //Hold difference in distance


      float ht = frame[0], ht_step = ((float) npc_id->sprite_offset[0]) / (float)(x2-x1);

      int dyb  = b2-b1;                       //y distance of bottom line
      int dyt  = t2-t1;                       //y distance of top    line
      int dx   = x2-x1; if( dx==0){ dx=1;}    //x distance

      int xs=x1;
                                    //hold initial x1 starting position
      //CLIP X
      if(x1<   0){ ht -=ht_step *x1; x1=   0;} //clip left
      if(x2<   0){ x2=   0;} //clip left
      if(x1>SW){ x1=SW;} //clip right
      if(x2>SW){ x2=SW;} //clip right
      //draw x verticle lines

      for(x=x1;x<x2;x++)
      {

        //The Y start and end point
        int y1 = dyb*(x-xs+0.5)/dx+b1; //y bottom point
        int y2 = dyt*(x-xs+0.5)/dx+t1; //y bottom poin

        const float th = (float)(1280 / 1200);

        float vt =  (float)npc_id->sprite_offset[1] * (float) frame_index_y ;
        float vt_step = ( (float)npc_id->sprite_offset[1]) / (float)(y2-y1);



        //Clip Y
        if(y1< 0){ vt -=vt_step *y1;y1= 0;} //clip y
        if(y2< 0){ y2= 0;} //clip y
        if(y1>SH){ y1=SH;} //clip y
        if(y2>SH){ y2=SH;} //clip y

        //surface

          for(y=y1;y<y2;y++){

                      int texture_flip;

                    if ( flipped == true )

                                texture_flip = textures[wt].w  - (int)ht%textures[wt].w;

                      else
                                  texture_flip = (int)ht%textures[wt].w;




                    int pixel=  (((int)vt%textures[wt].h) ) *3* textures[wt].w + (texture_flip)* 3;
                    int r=  textures[wt].name[pixel+0] ;
                    int g= textures[wt].name[pixel+1];
                    int b= textures[wt].name[pixel+2];

                    if ( r > 0){
                            drawPixel(x, y,r,g,b);
                        }
                        vt -= vt_step;

              }

              ht += ht_step;
              }

          }
       }
    }
 }

u32 body_npc;

double clamp(double d, double min, double max) {
  const double t = d < min ? min : d;
  return t > max ? max : t;
}

void draw3D_character_at_location(Entity* entity, TextureMaps* textures, Body* P,math M, u32 id_text){
  int x,frontBack, cycles, wx[4],wy[4],wz[4]; float CS=M.cos[P->a], SN=M.sin[P->a];
  Body *body = physics_body_get(entity->body_id);
  if ( body ){
   int frame_index_y = 0;
   bool flipped = false;

   vec3 xyz  = {body->aabb.position[0], body->aabb.position[1], body->aabb.position[2]};
   vec3 size_= {body->aabb.half_size[0], body->aabb.half_size[1], body->aabb.half_size[2]};

   int x1 = xyz[0] - ( size_[0]  * .75 ),
   y1     = xyz[1] - ( size_[1] );

   int x2 = xyz[0] + ( size_[0]  * .75 ),
       y2 = xyz[1] + ( size_[1] );

	vec3 new_basis_p = {1, 1, 1};
		float sin_p  = new_basis_p[0]*global.M.cos[P->a]-new_basis_p[1]*global.M.sin[P->a];
	float cos_p    = new_basis_p[1]*global.M.cos[P->a]+new_basis_p[0]*global.M.sin[P->a];

		vec3 D_p = { ( ( ( cos_p) )

                        ) ,

                          ( sin_p  ), 1 };



		int x_dir=global.M.sin[body->a];
		int y_dir=global.M.cos[body->a];

						vec3 new_basis = {1, 1, 1};
						float sin_n = new_basis[0]*global.M.cos[body->a]+new_basis[1]*global.M.sin[body->a];
						float cos_n = new_basis[1]*global.M.cos[body->a]+new_basis[0]*global.M.sin[body->a];

						vec3 D_other = { ( ( ( cos_n)  )

                        ) ,

                           (sin_n   ), 1 };


float dot_fwd_ = dot_product_vec3( D_p, D_other);

		if (dot_fwd_ < -0.85f)
	  {
      frame_index_y = 5;
      flipped = true;
      }

		if (dot_fwd_ > 1.f){
      frame_index_y = 0;
      flipped = true;
    }

		if (abs(dot_fwd_) < .3f){
      frame_index_y = 0;
    }

		if ( dot_fwd_ < 0)
        frame_index_y = 5;


   x1=x1-(P->aabb.position[0]), y1=y1-(P->aabb.position[1]);

   x2=x2-(P->aabb.position[0]), y2=y2-(P->aabb.position[1]);


        //swap for surface
      wx[0] = x1*CS+y1*SN;

      wx[0] = (double)clamp_double((double)wx[0],
        (double)(x1*CS-y1*SN) + (double)230,
        (double)(x1*CS-y1*SN) - (double)230);

      wx[1] = x2*CS-y2*SN;


      wx[2]=wx[0];
      wx[3]=wx[1];

      //world Y position (depth)
      wy[0]=y1*CS+x1*SN;
      wy[1]=y2*CS+x2*SN;


      wy[2]=wy[0];                          //top line has the same y
      wy[3]=wy[1];

      float z1 = xyz[2] -  size_[2] * 2.95f;
      float z2 = xyz[2] +  size_[2] *  .75f;

      z1 -= (P->aabb.position[2] - P->aabb.half_size[2] * .5)+((P->l*wy[0])/32.0);
      z2 -= (P->aabb.position[2] - P->aabb.half_size[2] * .5)+((P->l*wy[0])/32.0);

      wz[0]=z1;
      wz[1]=z1;

      wz[2]=z2;
      wz[3]=z2;


      //dont draw if behind player
        //point 1 behind player, clip
        //point 1 behind player, clip

        if( wy[0]>380 && wy[1]>380 ){     //wall behind player, dont draw
        //point 1 behind player, clip
        if(wy[0]<1)
        {
        clipBehindPlayer(&wx[0],&wy[0],&wz[0], wx[1],wy[1],wz[1]); //bottom line
        clipBehindPlayer(&wx[2],&wy[2],&wz[2], wx[3],wy[3],wz[3]); //top line
        }
        //point 2 behind player, clip
        if(wy[1]<1)
        {
        clipBehindPlayer(&wx[1],&wy[1],&wz[1], wx[0],wy[0],wz[0]); //bottom line
        clipBehindPlayer(&wx[3],&wy[3],&wz[3], wx[2],wy[2],wz[2]); //top line
        }
        //screen x, screen y position
        wx[0]=wx[0]*880/wy[0]+SW2; wy[0]=wz[0]*880/wy[0]+SH2;
        wx[1]=wx[1]*880/wy[1]+SW2; wy[1]=wz[1]*880/wy[1]+SH2;
        wx[2]=wx[2]*880/wy[2]+SW2; wy[2]=wz[2]*880/wy[2]+SH2;
        wx[3]=wx[3]*880/wy[3]+SW2; wy[3]=wz[3]*880/wy[3]+SH2;

        //draw points
        if ( entity->is_active == false ){
            entity->npc_state = DEATH;
        }

        frame_index_y = frame_index_y + entity->npc_state;
        draw_character_at_run_time(wx[0],wx[1], wy[0], wy[1], wy[2],wy[3],textures,
        entity, frame_index_y, flipped, id_text);

      }
    }
  }
