#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>


#define ARENA_IMPLEMENTATION
#include "engine/renderer/render.h"
#include "engine/memory/arena.h"
#include "engine/renderer/render_internal.h"
#include "engine/time/time.h"
#include "engine/global.h"
#include "engine/player/player.h"
#include "engine/math_utils.h"
#include "engine/config/config.h"
#include "engine/input/input_internal.h"
#include "engine/types.h"
#include "engine/physics/physics.h"
#include "engine/entity/entity.h"
#include "engine/collision.h"
#include "engine/animation/animation.h"
#include "engine/NPC/mind_npc.h"
#include "engine/NPC/dialogue.h"
#include "engine/array_list/array_list.h"
#include "engine/mirage_hengine.h"
#include "engine/audio/audio.h"

#include "engine/ui/button.h"
#include "engine/util.h"
#include "engine/time/turn_manager.h"
#include "engine/entity/item.h"

static Mix_Music *MUSIC_STAGE_1;
static Mix_Music *MUSIC_STAGE_2;
static Mix_Music *MUSIC_STAGE_3;

static Mix_Chunk *HIT;
static Mix_Chunk *STEP;

static Arena  default_arena   =            {0};
static Arena  temporary_arena = 		   {0};
static Arena  *context_arena  = &default_arena;

Mix_Chunk *Get_Hit(){

	return HIT;

}

Mix_Chunk *Get_Step(){

	return STEP;

}
typedef enum game_states_enum {

    MAIN_MENU = 0,
    GAME,
    IN_GAME_MENU,
    TOWN_IN_GAME_MENU,

} Game_States_Enum;


Gun *gun_player;

Game_States_Enum game_state_ = GAME;
u32 sound_lower = -11;
u32 sound_up = -11;
u32 window_button = -11;

int current_volume = SDL_MIX_MAXVOLUME / 8;
int index_map = 0;
u32 button_load;
u32 button_load_two;

u32 button_screen = -1;
u32 button_left;
u32 button_right;
u32 button_back;
u32 button_interact;
u32 button_attack;
u32 button_npc_1_attack = -1;
Sprite_Sheet sprite_sheet_player = {0};
usize new_char_player_id;
bool windowmode_game = true;

void switch_song_in_sector( int next_level_index  ){

	if ( next_level_index <=  0   )
   		 audio_music_play(MUSIC_STAGE_1);

	if ( next_level_index >=  1  )
   		 audio_music_play(MUSIC_STAGE_2);


	if ( next_level_index ==  2  ){
		 audio_music_play(MUSIC_STAGE_3);
	}

}

void *context_alloc(size_t size)
{
    assert(context_arena);
    return arena_alloc(context_arena, size);
}

u32 index_in_inventory[5];
u32 current_index_in_inventory;

int current_allie = 0;
u32 npc;
bool inited = false;
u32 npc_;

u32 button_npc_name;
float delay_move  = .15f;
float delay_click = .15f;

int SPEED_PLAYER  = MOVE_SPEED ;
int SIDE_SPEED_PLAYER  = CHARACTER_DEFAULT_SIZE * .8;


bool loading = false;

bool should_show_in_menu = false;

bool make_button_in_menu = false;


void button_reset_screen(){

							button_destroy(window_button);
							button_destroy(sound_lower);
							button_destroy(sound_up - 1);

							make_button_in_menu = false;

}

u32 entity_viewer;

bool can_move = true;
u8 index_button = 0;
Array_List *inventory;


Entity_Health_Change value_change(u32 amount){

		global.player_health -= amount;

}

void on_player_body_hit(Body *self, Body *other, Hit hit) {


}


Entity_Delete On_Entity_Delete_Player(u32 entity_id) {

		Entity *Player = entity_get(entity_id);
		Player->health = 100;
		global.player_health = Player->health;
		index_map = 0;
		load_(&index_map);

}

on_time_out_tree_delay delay_load_coroutine(u32 id, u32 value, f32 current_time){

		loading = false;
}
On_Hit on_player_body_entered_hit(Body *self, Body *other, Hit hit) {

	if ( other->index_trigger == 0 ){
		index_map += 1;
		load_(&index_map);
	}
}

On_Hit on_table_entered_hit(Body *self, Body *other, Hit hit) {

		gun_player->ammo += 3;
		gun_player->gun_damage_max += 3;
		
		button_load  = button_create((vec2){ SW2 * .26, SH - ( SH2 * 1.4 )    },
		(vec2){global.textures[24].w,global.textures[24].h},
		&global.textures[24]);

		button_load_two  = button_create((vec2){ SW2 * .26, SH - ( SH2 * 1.3 )    },
		(vec2){global.textures[24].w,global.textures[24].h},
		&global.textures[24]);

		self->is_active = false;
		
}

void on_player_body_hit_static(Body *self, Static_Body *other, Hit hit) {
}

void update_camera( Body * body ){

	body->l -= normalize_int( (int)(  body->l ) );

}


int diepth_change;


Body *ray_cast_line_entity( vec3 position, vec3 D, u8 dist){

	f32 X = 			position[0];
	f32 Y = 			position[1];
	f32 Z =	            position[2];

	for ( u32 n = 2; n < physics_body_list_array_get()->len; n++ ) {
		Body * s_other = physics_body_get(n);
		if ( s_other ){
			if ( entity_get( s_other->entity_id ) != NULL ){

				Hit result = (Hit){.time = 0xBEEF};
				AABB sum_aabb = s_other->aabb;

				Body body = {0};
				body.aabb.position[0] =      X;
				body.aabb.position[1] =      Y;
				body.aabb.position[2] =      Z;

				body.aabb.half_size[0] =	530;
				body.aabb.half_size[1] = 	530;
				body.aabb.half_size[2] =     10;

				vec3_add(sum_aabb.half_size, sum_aabb.half_size, body.aabb.half_size);
				vec3 velocity = { D[0], D[1], 0 };

				Hit hit = ray_intersect_aabb(body.aabb.position, velocity, sum_aabb);

				if ( hit.is_hit){
						return s_other;
				}
			}
		}
	}

	return NULL;

}



void attack(u32 npc_entity, u32 attack_id){

        Entity* entity = entity_get(npc_entity);
        if ( entity ){

				Body * body_npc = physics_body_get( entity->body_id );

				int x_dir=global.M.sin[body_npc->a] * body_npc->aabb.half_size[1];
				int y_dir=global.M.cos[body_npc->a] * body_npc->aabb.half_size[1];
				vec3 new_pos_player = {body_npc->aabb.position[0],
												body_npc->aabb.position[1],
												body_npc->aabb.position[2]};
				vec3 *basis = calculate_basis(new_pos_player);
				normalize(*basis);
				vec3 new_basis = {**basis};
				float sin_  = 100*global.M.sin[body_npc->a];
				float cos_	= 100*global.M.cos[body_npc->a];

				vec3 D = { (

				( cos_) *  (int)body_npc->aabb.half_size[0])   ,

				((sin_ *  (int)body_npc->aabb.half_size[1] )  ), 0 };

				Body *hit = ray_cast_line_entity(
									(vec3){
										body_npc->aabb.position[0],
										body_npc->aabb.position[1],
										body_npc->aabb.position[2]
										}
										,D,
										CHARACTER_DEFAULT_SIZE * 35);

				if ( hit != NULL ) {
					if (  entity_get(hit->entity_id) ){
							entity_get(hit->entity_id)->is_active = false;
							entity_damage(hit->entity_id,
							100,
							global.time.delta);
							printf("The entity id is: %u\n",  hit->entity_id );
					}
				}
				body_npc->l		+= CAMERA_CHANGE;
		}
}

bool rotate_left = false;
bool rotate_right = false;

int last_camera_angle = 0;

f32 velx = 0;

bool just_pressed = false;
bool can_walk = true;

static void input_handle(const SDL_Event *ev, Body *cammera, math M) {

		if ( cammera != NULL ){

				can_walk = true;
				f32 vely = cammera->velocity[1];
				if (global.input.left){

					cammera->a	-= 1;
					if ( cammera->a < 0 )
							cammera->a += 360;

				}

				if (global.input.right  ){

					cammera->a	+= 1;
					if ( cammera->a > 359 )
							cammera->a -= 360;

				}

				if (global.input.up && can_walk == true ) {

					velx += MOVE_SPEED;

				 }

				if ( global.input.down && can_walk == true) {

					velx -= MOVE_SPEED;

				}

			int dx=M.sin[cammera->a]*velx;
			int dy=M.cos[cammera->a]*velx;

			cammera->velocity[0] = dx * global.time.delta;
			cammera->velocity[1] = dy * global.time.delta;

		}




}


u32 last_index = -1;
bool pressed = false;
on_time_out_tree_delay delay_load_button_reset(u32 id, u32 button_screen, f32 current_time){

	button_get(button_screen)->pressed = false;
	pressed = false;
	if ( render_get_button_load_ui() <= 0 )
		button_screen = -1;

}

 void button_update( Body *body_player, math M ) {

		if ( body_player ){
			if ( button_get(button_screen) ){
					if (
						button_get(button_screen)->pressed && pressed == false
					){
						attack( body_player->entity_id, body_player->entity_id);
						audio_sound_play(HIT);
						render_remove_button_load_ui();
						pressed = true;
						button_get(button_screen)->pressed = false;
						if ( render_get_button_load_ui() <= 0 ){
							array_list_remove( button_array_list_get(), button_screen );
							button_screen = -1;
							pressed = false;
						}
						else
						{
						create_time_tree_timer(delay_load_button_reset, button_screen, button_screen, 1.f  );
						}
						gun_player->ammo = render_get_button_load_ui();

					}
				}
				if ( button_get(button_load_two) )
					if (
						button_get(button_load_two)->pressed
					) {
						array_list_remove( button_array_list_get(), button_load_two );
						render_add_button_load_ui();
						button_load_two = -1;
				}

				if ( button_get(button_load) )
					if (
						button_get(button_load)->pressed
					) {
						array_list_remove( button_array_list_get(), button_load );
						render_add_button_load_ui();
						button_screen = button_create(
							(vec2){
								SW2 * .75,
								SH  -  ( SH2 * .75 )},
								(vec2){ SW2 * .75,
								SH2 * .75 },
								NULL);
						button_load =  -1;
					}

			}
 }

void load_( int *index ){

	Entity *viwer = entity_get(entity_viewer);
	Body* body_viwer = physics_body_get(viwer->body_id);

	load( index, &entity_viewer ,sprite_sheet_player, new_char_player_id, on_player_body_hit, on_player_body_hit_static, on_player_body_entered_hit, On_Entity_Delete_Player);

}



void init(){
 int x;
 srand(time(NULL));   // Initialization, should only be called once.
 //store sin/cos in degrees
 for(x=0;x<360;x++)                         //precalulate sin cos in degrees
 {
  global.M.cos[x]=cos(x/180.0*M_PI);
  global.M.sin[x]=sin(x/180.0*M_PI);
 }

 //load sectors
initTextures(&global.textures);

}



void display(  )
{
	Entity* player = entity_get(entity_viewer);
	Body*   body = physics_body_get(player->body_id);

	draw3D_Map(&global.textures, body,  global.M);
	setRender();
}

int main(int argc, char* argv[])
{
	init_window();
	time_init(120.0);
	config_init();
	physics_init();
	entity_init();
	init();
	init_ui();


	animation_init();
	//init_turn_manager();
	audio_init();
	audio_music_load(&MUSIC_STAGE_1, "music.wav");
	audio_music_load(&MUSIC_STAGE_2, "music_1.wav");
	audio_music_load(&MUSIC_STAGE_3, "music_2.wav");

	audio_sound_load(&HIT, "hit.mp3");
	audio_sound_load(&STEP, "step.wav");

    render_sprite_sheet_init(&sprite_sheet_player, 1500, 3000, 300.f, 300.f );

    usize char_player_id = animation_definition_create(&sprite_sheet_player, ANIMATION_DURATION, 0, (u8[]){1, 2, 3, 4, 5}, 5);
    new_char_player_id = animation_create(char_player_id, true);

	vec3 size = { 300.f, 300.f };
	u8 player_mask =
	 COLLISION_LAYER_TERRAIN
	| COLLISION_LAYER_ENEMY_PASSTHROUGH;

	entity_viewer  =  entity_create(NULL, CAMERA,  (vec3){ 40, 50, 110 }, (vec3){
	 CHARACTER_DEFAULT_SIZE,
	 CHARACTER_DEFAULT_SIZE,
	  CHARACTER_DEFAULT_SIZE },
	  (vec2){416,416},(vec3){0,0,0 },  COLLISION_LAYER_PLAYER, player_mask,  false, new_char_player_id, NULL, NULL,  WALK, 0, 100, On_Entity_Delete_Player, value_change, true, 0, 0, 0, 0,0,0);


	Entity *viwer = entity_get(entity_viewer);
	viwer->is_playble = true;
	Body* body_viwer = physics_body_get( viwer->body_id );

	entity_get(entity_viewer)->should_draw_on_scene = false;
	global.body_player = entity_viewer;
	global.player_health = 100;
    //init_mind_npc();
	int pre_load = 0;
	load_( &index_map );
	inited = true;
	bool should_quit = true;

	gun_player = malloc(sizeof(Gun));
	gun_player->ammo = 2;
	gun_player->gun_damage_max = 100;


	button_load  = button_create((vec2){ SW2 * .26, SH - ( SH2 * 1.4 )    },
	(vec2){global.textures[24].w,global.textures[24].h},
	 &global.textures[24]);

	button_load_two  = button_create((vec2){ SW2 * .26, SH - ( SH2 * 1.3 )    },
	(vec2){global.textures[24].w,global.textures[24].h},
	 &global.textures[24]);

	bool should_update_input;
    audio_music_play(MUSIC_STAGE_1);

	while (should_quit){

	Entity *viwer = entity_get(entity_viewer);
    body_viwer = physics_body_get(entity_get( entity_viewer )->body_id);
		time_update();
		SDL_Event event;
		velx = 0;
		//init player
		while (SDL_PollEvent(&event)){
		if (event.type == SDL_QUIT){
			destroy();
			should_quit = false;

			}

		button_process_event(&event);
		}
		button_update( body_viwer, global.M);

		input_update();
        input_handle( &event, body_viwer, global.M );

		updated_mind_npcs(global.time.delta);
		update_camera( body_viwer );
		animation_update(global.time.delta);

		physics_update();
		display( );
		time_update_late();
		}



	return 0;


}
