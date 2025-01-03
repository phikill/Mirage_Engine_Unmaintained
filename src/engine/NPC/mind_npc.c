#include "mind_npc.h"
#include "../array_list/array_list.h"
#include "../entity/entity.h"
#include "../entity/item.h"

#include "../physics/physics.h"
#include "../renderer/render.h"
#include "../renderer/render_internal.h"

#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../util.h"
#include "../global.h"
#include "../math_utils.h"

#include "../time/time.h"
#include "../types.h"
#include "../mirage_hengine.h"



int current_size_of_turn  = 0;

int SPEED_NPC  = MOVE_SPEED;
int SIDE_SPEED_NPC  = CHARACTER_DEFAULT_SIZE * .8;

static 	Array_List *entity_npc_list;
static 	Array_List *entity_npc_id_ist;

Entity_Health_Change value_change_npc(u32 amount){


}


on_time_out_tree_delay stop_walking_coroutine(u32 id){

    Body *body = physics_body_get( id );
    body->velocity[0] = 0;
    body->velocity[1] = 0;
    Entity *entity = entity_get(body->entity_id);
	if ( entity->is_active == true )
    	entity->npc_state = IDLE;

}

on_time_out_tree_delay check_if_walking_coroutine(u32 id){

	if ( physics_body_get( id ) != NULL ){
		Body *body = physics_body_get( id );
		if (  body->velocity[0] + body->velocity[1] < MOVE_SPEED  ){
				Entity *entity = entity_get(body->entity_id);
				entity->npc_state = IDLE;
		}
	}
}

Body *ray_cast_line_entity_( vec3 position, vec3 D, u8 dist){

	f32 X = 			position[0];
	f32 Y = 			position[1];
	f32 Z =	            position[2];

	for ( u32 n = 0; n < 1; n++ ) {
		Body * s_other = physics_body_get(n);
		if ( s_other  != NULL ){
			if ( entity_get( s_other->entity_id ) != NULL ){

				Hit result = (Hit){.time = 0xBEEF};
				AABB sum_aabb = s_other->aabb;

				Body body = {0};
				body.aabb.position[0] =     X;
				body.aabb.position[1] =     Y;
				body.aabb.position[2] =     Z;

				body.aabb.half_size[0] =	555;
				body.aabb.half_size[1] = 	555;
				body.aabb.half_size[2] =     11;

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

on_time_out_tree_delay walk_ramdom_coroutine(u32 id, u32 value, f32 current_time){

    Entity *npc = entity_get(id);
	if ( npc != NULL ){
		if ( npc->is_active == true ){
				Body *body = physics_body_get( npc->body_id);
				if ( body != NULL ){
					walk_ramdom( body );
					create_time_tree_timer(stop_walking_coroutine, npc->body_id, npc->body_id, (f32)( 1.15f ));
			}
		}
	}
}

void walk_ramdom(Body *body){

    Entity* npc = entity_get(body->entity_id);
    npc->npc_state = WALK;

    int velx = random( MOVE_SPEED >> 4, MOVE_SPEED >> 3 );
    int vely = random( MOVE_SPEED >> 4, MOVE_SPEED >> 3 );

    int new_a = rand() % 372;

    body->a += clamp_int(new_a, 0, 180);
	if ( body->a > 359 )
			body->a -= 360;

	int dx=(global.M.cos[body->a]*velx)-(global.M.sin[body->a]*vely);
	int dy=(global.M.cos[body->a]*vely)+(global.M.sin[body->a]*velx);

	body->velocity[0] = dx * global.time.delta;
	body->velocity[1] += dy * global.time.delta;

}
on_time_out_tree_delay Stop_Anim(u32 npc_entity, u32 attack_id){

	Entity* entity = entity_get(npc_entity);
	if ( entity->is_active == true )
		entity->npc_state = IDLE;

}
on_time_out_tree_delay ATTACK_(u32 npc_entity, u32 attack_id){
    Entity* entity = entity_get(npc_entity);
    if ( entity != NULL ){
        if ( entity->is_active == true ){
					Body * body_npc = physics_body_get( entity->body_id );
					float sin_  = 115*global.M.sin[body_npc->a];
					float cos_  = 115*global.M.cos[body_npc->a];

					vec3 D = {   cos_ 
                         ,
                        sin_ , 0 };

					Body *hit = ray_cast_line_entity_(
									(vec3){
										body_npc->aabb.position[0],
										body_npc->aabb.position[1],
										body_npc->aabb.position[2]}
													,D, 1);
                    entity->npc_state = ATTACK;
					if (  hit != NULL ) {
							if ( entity_get( hit->entity_id ) != NULL ){
									entity_damage(hit->entity_id,
                                        2,
                                        global.time.delta
                                        );
										
                                        hit->l += CAMERA_CHANGE * .7;
								}
						}

					create_time_tree_timer(Stop_Anim, npc_entity, npc_entity, ANIMATION_DURATION * 20.f);
					audio_sound_play(Get_Hit());
                    entity->mind->can_atack = true;
			}
		}
}

void updated_mind_npcs_lawful(u32 id){

    Entity *npc = entity_get(id);
    if ( npc ){
            if ( npc->npc_state != WALK ){
                create_time_tree_timer(walk_ramdom_coroutine, id, id, 4.1f  );
        }
    }
}

void updated_mind_npcs_chaotic(u32 id){

    Entity *npc = entity_get(id);
    if ( npc ){
        if ( npc->mind->entity_id >= 1000 ){
				Body * body_npc = physics_body_get( npc->body_id );

				float sin_  = 35*global.M.sin[body_npc->a];
				float cos_	= 35*global.M.cos[body_npc->a];

				vec3 D = {  cos_,
							sin_ ,
							0 };

				Body *hit = ray_cast_line_entity_(
									(vec3){
										body_npc->aabb.position[0],
										body_npc->aabb.position[1],
										body_npc->aabb.position[2]
										}
										,D,
										CHARACTER_DEFAULT_SIZE * 35);

				if ( hit != NULL ) {
					if ( hit->entity_id != id ){
						if ( entity_get( hit->entity_id ) != NULL ){
									npc->mind->entity_id = hit->entity_id;
						}
					}
                }
        }
        else if ( (u32)npc->mind->entity_id == (u32)1 && npc->mind->can_atack == true ){
                    npc->mind->can_atack = false;
                    create_time_tree_timer(ATTACK_, id, id, ANIMATION_DURATION * 32  );

        }
    }
}

void updated_mind_npcs(f32 delta){
    for (u32 i = 2; i < entity_array_list_get()->len + (u32)1; i++){
        Entity* npc_entity = entity_get(i);
        if ( npc_entity != NULL){
            if ( npc_entity->is_active ==  true ){
                if ( npc_entity->mind->update_mind != NULL  ){
                    npc_entity->mind->update_mind(i);
                }
          	}
        }
    }
}


