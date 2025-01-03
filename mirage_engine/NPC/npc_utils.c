#include "npc_utils.h"
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include "../renderer/render.h"
#include "../renderer/render_internal.h"
#include "../time/time.h"
#include "../global.h"
#include "../player/player.h"
#include "../math_utils.h"
#include "../config/config.h"
#include "../mirage_hengine.h"
#include "../types.h"
#include "../physics/physics.h"
#include "../entity/entity.h"
#include "../collision.h"
#include "../animation/animation.h"
#include "../NPC/mind_npc.h"
#include "../ui/button.h"

Entity_Health_Change value_npc_change(u32 amount){

		global.player_health -= amount;

}

void on_npc_player_body_hit(Body *self, Body *other, Hit hit) {


}
void on_npc_player_body_entered_hit(Body *self, Body *other, Hit hit) {

}


void on_npc_player_body_hit_static(Body *self, Static_Body *other, Hit hit) {


}

Update_Mind update_mind_walk(u32 id){

		updated_mind_npcs_lawful(id);

}


Update_Mind update_mind_attack(u32 amount){

		updated_mind_npcs_chaotic(amount);

}
Entity_Delete On_Entity_Delete_NPC(u32 entity_id) {

	Entity *entity = entity_get(entity_id);
	Body  *body_npc = physics_body_get(entity->body_id);
	body_npc->velocity[0] = 0;
	body_npc->velocity[1] = 0;

}
u32 init_characters(vec3 position, On_Hit on_hit, On_Hit_Static on_hit_static, u32 index, u32 dialogue_id, int sector, int a, int l,int item_hoilding, NPC_Alignment aligment){
	u8 player_mask =
	COLLISION_LAYER_ENEMY
	| COLLISION_LAYER_TERRAIN
	| COLLISION_LAYER_ENEMY_PASSTHROUGH;

    Sprite_Sheet sprite_sheet_player = {0};
    render_sprite_sheet_init(&sprite_sheet_player, 1800, 3600, 360.f, 360.f );

    usize char_player_id = animation_definition_create(&sprite_sheet_player, ANIMATION_DURATION, 0, (u8[]){1, 2, 3, 4,5}, 5);
    usize new_char_player_id = animation_create(char_player_id, true);

   vec3 size = { 360.f, 360.f };
	Mind_NPC * mind = malloc(sizeof(Mind_NPC));

	if ( index == 17 ){
		mind->mind_alliment	=  LAWFUL;
		mind->update_mind = update_mind_walk;
	}


	else if ( index == 19 ){
		mind->mind_alliment	=  CHAOTIC;
		mind->update_mind = update_mind_attack;
		mind->entity_id = 1000;
		mind->can_atack = true;

	}
	u32 entity_npc =  entity_create( mind, RIGHT, (vec3){ position[0], position[1], position[2] }, (vec3){

	CHARACTER_DEFAULT_SIZE, CHARACTER_DEFAULT_SIZE, CHARACTER_DEFAULT_SIZE },
	(vec2){ 360.f, 360.f },(vec3){0,0,0 },  COLLISION_LAYER_PLAYER, player_mask,  false, new_char_player_id, on_npc_player_body_hit, on_npc_player_body_hit_static,  WALK, 0, CHARACTER_DEFAULT_LIFE, On_Entity_Delete_NPC, value_npc_change, false, index, 0, 0, a, a,a);

	//if ( index == 18 ){
	//	Power_Deffinition_mod  *mod = malloc( sizeof(Power_Deffinition_mod) );
	//	mod->range  = 10;
	//	mod->range  = 100;
	//	mod->damage = 100;
	//	entity_get(entity_npc)->table_mod = mod;
	//	physics_body_get(entity_get(entity_npc)->body_id)->on_hit = on_table_entered_hit;

	//}

     return entity_npc;

}
