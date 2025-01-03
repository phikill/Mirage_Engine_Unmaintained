#ifndef RENDER_MAP_H
#define RENDER_MAP_H
#include "../player/player.h"
#include "../texture/texture.h"
#include "../physics/physics.h"
#include "../entity/entity.h"
#include "../animation/animation.h"

void draw3D_Map(TextureMaps* textures, Body*  P,math M);
void draw_menu(TextureMaps* textures, Body*  P,math );

void draw_ui_on_screen(TextureMaps* textures);

int get_num_sector();
void render_add_button_load_ui( );
void render_remove_button_load_ui();
int render_get_button_load_ui();

typedef struct
{
 int x1,y1;             //bottom line point 1
 int x2,y2;             //bottom line point 2
 int c;                 //wall color
int wt, u, v;
int shade;

}walls; ;

typedef struct
{
 int ws,we;             //wall number start and end
 int z1,z2;             //height of bottom and top
 int d;                 //add y distances to sort drawing order
 int c1,c2;             //bottom and top color
int st , ss;

 int surf[SW];          //to hold points for surfaces
 int surface;           //is there a surfaces to draw
 int last_sector_dist;
 int last_index;

}sectors;

walls get_wall(int index);

sectors get_sectors();
walls get_wall();


void  set_npc_sector_render( Entity *entity, int index );


void  draw_ui( TextureMaps* textures );
void init_render_internal(void);

void init_ui_time();
void attack_init( u32 char_id, u32 new_anim_id );
void draw_menu_anim( TextureMaps* textures );

#endif
