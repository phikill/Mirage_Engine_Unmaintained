#include <assert.h>

#include "../util.h"
#include "../array_list/array_list.h"
#include "animation.h"
#include "../entity/entity.h"
#include "../texture/texture.h"
#include "../physics/physics.h"
#include "../math_utils.h"
#include "../renderer/character_renderer.h"
#include "../renderer/render.h"

Array_List *animation_definition_storage;
Array_List *animation_storage;

void animation_init(void) {
    // TODO: BUG WITH ARRAY_LIST IMPLEMENTATION CAUSES CREATED WITH 0 LENGTH TO NOT WORK
	animation_definition_storage = array_list_create(sizeof(Animation_Definition), 0);
	animation_storage = array_list_create(sizeof(Animation), 0);
}

usize animation_definition_create(Sprite_Sheet *sprite_sheet, f32 duration, u8 row, u8 *columns, u8 frame_count) {
	assert(frame_count <= MAX_FRAMES);

	Animation_Definition def = {0};

	def.sprite_sheet = sprite_sheet;
	def.frame_count = frame_count;

	for (u8 i = 0; i < frame_count; ++i) {
		def.frames[i] = (Animation_Frame){
			.column = columns[i],
			.row = row,
			.duration = duration,
		};
	}

	return array_list_append(animation_definition_storage, &def);
}

usize animation_create(usize animation_definition_id, bool does_loop) {
	usize id = animation_storage->len;
	Animation_Definition *adef = array_list_get(animation_definition_storage, animation_definition_id);
	if (adef == NULL) {
		ERROR_EXIT("Animation Definition with id %zu not found.", animation_definition_id);
	}

	// Try to find free slot first.
	for (usize i = 0; i < animation_storage->len; ++i) {
		Animation *animation = array_list_get(animation_storage, i);
		if (!animation->is_active) {
			id = i;
			break;
		}
	}

	if (id == animation_storage->len) {
		array_list_append(animation_storage, &(Animation){0});
	}

	Animation *animation = array_list_get(animation_storage, id);

	// Other fields default to 0 when using field dot syntax.
	*animation = (Animation){
		.animation_definition_id = animation_definition_id,
		.does_loop = does_loop,
		.is_active = true,
	};

	return id;
}

void animation_destroy(usize id) {
	Animation *animation = array_list_get(animation_storage, id);
	animation->is_active = false;
}

Animation *animation_get(usize id) {

	return array_list_get(animation_storage, id);

}

Array_List *animation_get_array_list() {
	return animation_storage;
}

void animated_character(u32 npc, TextureMaps* textures, Body*  P,math M, u32 id_text){

      Entity *npc_id = entity_get(npc);

}


void animation_update(f32 dt) {
	for (usize i = 0; i < animation_storage->len; ++i) {
		Animation *animation = array_list_get(animation_storage, i);
            if ( animation != NULL ){

            Animation_Definition *adef = array_list_get(animation_definition_storage, animation->animation_definition_id);
            animation->current_frame_time -= dt;
                if ( adef != NULL ){
                    if (animation->current_frame_time <= 0) {
                        animation->current_frame_index += 1;

                        // Loop or stay on last frame.
                        if (animation->current_frame_index == adef->frame_count) {
                            if (animation->does_loop) {
                                animation->current_frame_index = 0;
                            } else {
                                animation->current_frame_index -= 1;
                            }
                        }


                        animation->current_frame_time = adef->frames[animation->current_frame_index].duration;


                    }
                }
        }
}
}



void render_sprite_sheet_init(Sprite_Sheet *sprite_sheet, f32 width, f32 height, f32 cell_width, f32 cell_height) {

	sprite_sheet->width = (f32)width;
	sprite_sheet->height = (f32)height;
	sprite_sheet->cell_width = cell_width;
	sprite_sheet->cell_height = cell_height;
}


Animation_Definition* get_animation_definitiion(usize anim_id){

    Animation_Definition *adef = array_list_get(animation_definition_storage, anim_id);
	return adef;



}
