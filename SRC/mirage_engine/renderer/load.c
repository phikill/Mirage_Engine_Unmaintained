#include <stdio.h>
#include <stdlib.h>
#include <linmath\linmath.h>

#include <stdlib.h>
#include <string.h>

#include "load.h"
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

typedef struct
{
   int x,y,z,i,a,l,d; //add y distances to sort drawing order
}Next_Character;

Next_Character next_character[2];


void Calculate_3d_walls( math M, On_Hit on_trigger_hit)
{

   int index_trigger = 1;
   int x,s,w,frontBack, cycles, wx[4],wy[4],wz[4];
   u32 wall_count = 0;
   //draw sectors
   for(s=0;s<global.numSect;s++)
   {
      w = global.S[s].we;
      //offset bottom 2 points by player
      int x1 = global.W[w].x1,
      y1 = global.W[w].y1;

      int x2 = global.W[w].x2,
      y2=global.W[w].y2;


      if(x2 - x1  < 0)
      { 
         int swp=x1; 
         x1=x2; 
         x2=swp;
      }
      if(y2 - y1  < 0)
      { 
         int swp=y1; 
         y1=y2; 
         y2=swp;
      }


      //world X position
      wx[0]=x1;
      wx[1]=x2;
      wx[2]=wx[0];                          //top line has the same x
      wx[3]=wx[1];
      //world Y position (depth)
      wy[0]=y1;
      wy[1]=y2;
      wy[2]=wy[0];                          //top line has the same y
      wy[3]=wy[1];


      //world z height
      wz[0]=global.S[s].z1;
      wz[1]=global.S[s].z1;

      wz[2]= global.S[s].z2;
      wz[3]= global.S[s].z2;


      //draw points
      int x_pos = wx[1] - wx[0];
      int y_pos = wy[1] - wy[0];
      int z_pos = wz[1] - wz[0];

      if(global.W[w].wt == 5 || global.W[w].wt == 9)
      {
         u32 new_body_id = physics_static_body_create((vec3)
                                                      { 
                                                         x2 - (x_pos * .5f), 
                                                         y2 - (x_pos * .5f), 
                                                         0 
                                                      }, 
                                                      (vec3)
                                                      { 
                                                         x_pos * 1.2f, 
                                                         x_pos * 1.2f, 
                                                         x_pos * 1.2f 
                                                      }, 
                                                      COLLISION_LAYER_TERRAIN);
      }

      else if(global.W[w].wt == 10)
      {
         u8 player_mask  = COLLISION_LAYER_PLAYER;
         u32 new_body_id = physics_trigger_create((vec3)
                                                  { 
                                                      x2 - (x_pos * .5), 
                                                      y2 - (x_pos * .5f),  
                                                      60 
                                                  }, 
                                                  (vec3)
                                                  {
                                                      x_pos, 
                                                      x_pos, 
                                                      x_pos
                                                  }, 
                                                  COLLISION_LAYER_ENEMY_PASSTHROUGH, 
                                                  player_mask, 
                                                  on_trigger_hit);
         physics_body_get(new_body_id)->index_trigger = index_trigger;
         index_trigger = 0;
      }
   }
}



on_time_out_tree_delay delay_create_character(u32 id, 
                                              u32 value, 
                                              f32 current_time)
{
   for(int index_char = 0; index_char < (int)value; index_char++ )
   {
      if(next_character[index_char].x + next_character[index_char].y > 0 )
      {
         u32 entity_id = init_characters((vec3)
                                         { 
                                             next_character[index_char].x, 
                                             next_character[index_char].y, 
                                             CHARACTER_DEFAULT_SIZE
                                         },
                                         NULL, 
                                         NULL, 
                                         next_character[index_char].i,
                                         0, 
                                         0, 
                                         0, 
                                         next_character[index_char].a, 
                                         next_character[index_char].l, 
                                         0);
     }
   }
}

void load(int *index_, 
          u32 *P_viewr,
          Sprite_Sheet sprite_sheet_player,
          usize new_char_player_id,
          On_Hit on_hit, 
          On_Hit_Static on_hit_static, 
          On_Hit on_trigger_hit, 
          Entity_Delete On_Entity_Delete_Player)
{

	time_reset_observer_list();
   for(u32 index_entity = (u32)entity_array_list_get()->len;  
      index_entity > 0; --index_entity)
   {
      Entity * entity_npc = entity_get( index_entity );
      if(entity_npc != NULL)
      {
         physics_body_destroy_from_memory(entity_npc->body_id);
         entity_destroy_from_memory(index_entity);
      }
   }

   for(u32 physics_id = (u32)physics_body_list_array_get()->len;  
           physics_id > 0; --physics_id)
   {
      Body *body_din = physics_body_get(physics_id);
      if(body_din != NULL)
      {
         physics_body_destroy_from_memory(physics_id);
      }
   }

   for(u32 physics_id = (u32)physics_static_body_list_array_get()->len;  
            physics_id > 0; --physics_id)
   {
      Static_Body *body_din = physics_static_body_get(physics_id);
      if(body_din != NULL)
      {
         physics_static_body_destroy_from_memory(physics_id);
      }
   }

   int index = *index_;
   physics_reset();

	vec3 size = { 300.f, 300.f };
	u8 player_mask = COLLISION_LAYER_TERRAIN
	                 | COLLISION_LAYER_ENEMY_PASSTHROUGH;

	*P_viewr  =  entity_create(NULL, 
                              CAMERA,  
                              (vec3)
                              { 
                                 40, 
                                 50, 
                                 110 
                              }, 
                              (vec3)
                              {
                                 CHARACTER_DEFAULT_SIZE,
                                 CHARACTER_DEFAULT_SIZE,
                                 CHARACTER_DEFAULT_SIZE 
                              },
	                           (vec2)
                              {
                                 416,
                                 416
                              },
                              (vec3)
                              {
                                 0,
                                 0,
                                 0 
                              },  
                              COLLISION_LAYER_PLAYER, player_mask,  
                              false, 
                              new_char_player_id, 
                              NULL, 
                              NULL,  
                              WALK, 
                              0, 
                              100, 
                              On_Entity_Delete_Player, 
                              NULL, 
                              true, 
                              0, 
                              0, 
                              0, 
                              0,
                              0,
                              0);

	Entity *viwer = entity_get(*P_viewr);

	Body*   P_viwer = physics_body_get(viwer->body_id);

   P_viwer->aabb.position[0] =                           1430;
   P_viwer->aabb.position[1] =                           1090;
   P_viwer->aabb.position[2] =         CHARACTER_DEFAULT_SIZE;
   P_viwer->velocity[0] =                                   0;
   P_viwer->velocity[1] =                                   0;

   int s,w,x,y,z,item,i,a,aligment,l,d,size_char;


   FILE *fp;
   char level_file_name[7] = "level_";

   if(index < 10)
   {
      char c = 
      { 
         index + '0' 
      };

      strncat(level_file_name, &c, 1);
   }

   else
   {
      int a=index;
      char buffer[4];
      itoa(a,buffer,2);   // here 2 means binary

      strncat(level_file_name, buffer, 2);
   }

   strncat(level_file_name, ".h", 2);

   fp = fopen(level_file_name,"r");

   printf(level_file_name);
   fp = fopen(level_file_name,"r");

   if(fp == NULL)
   {
      fp = fopen("level_0.h","r");
      *index_ = 0;
   }

   fscanf(fp,"%i",&global.numSect);   //number of sectors
   for(s=0;s<global.numSect;s++)      //load all sectors
   {
      fscanf(fp,"%i",&global.S[s].ws);
      fscanf(fp,"%i",&global.S[s].we);
      fscanf(fp,"%i",&global.S[s].z1);
      fscanf(fp,"%i",&global.S[s].z2);
      fscanf(fp,"%i",&global.S[s].st);
      fscanf(fp,"%i",&global.S[s].ss);
   }

   fscanf(fp,"%i",&global.numWall);   //number of walls

   for(s=0;s<global.numWall;s++)      //load all walls
   {
      fscanf(fp,"%i",&global.W[s].x1);
      fscanf(fp,"%i",&global.W[s].y1);
      fscanf(fp,"%i",&global.W[s].x2);
      fscanf(fp,"%i",&global.W[s].y2);
      fscanf(fp,"%i",&global.W[s].wt);
      fscanf(fp,"%i",&global.W[s].u);
      fscanf(fp,"%i",&global.W[s].v);
      fscanf(fp,"%i",&global.W[s].shade);
   }

   fscanf(fp,"%i",&size_char);
   for(int index = 0; index < size_char; index++)
   {
      fscanf(fp,"%i",&next_character[index].x);
      fscanf(fp,"%i",&next_character[index].y);
      fscanf(fp,"%i",&next_character[index].z);
      fscanf(fp,"%i",&next_character[index].a);
      fscanf(fp,"%i",&next_character[index].l);
      fscanf(fp,"%i",&next_character[index].i);
      fscanf(fp,"%i",&next_character[index].d);
      fscanf(fp,"%i",&next_character[index].d);
      fscanf(fp,"%i",&next_character[index].d);
      fscanf(fp,"%i",&next_character[index].d);
   }

   fclose(fp);
   create_time_tree_timer(delay_create_character, 
                          (u32)size_char, 
                          (u32)size_char, 
                          2.2f);
   Calculate_3d_walls(global.M, on_trigger_hit);
}
