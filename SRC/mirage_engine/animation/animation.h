#pragma once

#ifndef ANIMATION_H
#define ANIMATION_H
#include "../renderer/render.h"
#include <stdbool.h>
#include "../types.h"

#include "../entity/entity.h"
#include "../texture/texture.h"
#include "../physics/physics.h"
#include "../array_list/array_list.h"

#include "../math_utils.h"

typedef struct sprite_sheet 
{
	f32 width;
	f32 height;
	f32 cell_width;
	f32 cell_height;
	u32 texture_id;
} Sprite_Sheet;

#define MAX_FRAMES 75
typedef struct animation_frame 
{
	f32 duration;
	u8 row;
	u8 column;
} Animation_Frame;

typedef struct animation_definition 
{
	Sprite_Sheet *sprite_sheet;
	Animation_Frame frames[MAX_FRAMES];
	
	u8 frame_count;
} Animation_Definition;

typedef struct animation 
{
	usize animation_definition_id;
	f32 current_frame_time;
	u8 current_frame_index;
	bool does_loop;
	bool is_active;
	bool is_flipped;
} Animation;
void animated_character(u32 npc, 
						TextureMaps* textures, 
						Body*  P,
						math M, 
						u32 id_texture);

void animation_init(void);
usize animation_definition_create(Sprite_Sheet *sprite_sheet, 
								  f32 duration, 
								  u8 row, 
								  u8 *columns, 
								  u8 frame_count);

usize animation_create(usize animation_definition_id, bool does_loop);
void animation_destroy(usize id);
Animation *animation_get(usize id);
void animation_update(f32 dt);
Animation_Definition* get_animation_definitiion(usize anim_id);

Array_List *animation_get_array_list();

void render_sprite_sheet_init(Sprite_Sheet *sprite_sheet, 
							  f32 width, 
							  f32 height, 
							  f32 cell_width, 
							  f32 cell_height);
#endif
