#include"../array_list/array_list.h"
#include"../animation/animation.h"
#include"../mirage_hengine.h"
#include"../NPC/mind_npc.h"

#include"../util.h"
#include"entity.h"
#include"item.h"

static Array_List *entity_list;
static Array_List *attack_list;

int BACK_SPEED = CHARACTER_DEFAULT_SIZE * 1.5;

void entity_init(void) 
{
	entity_list = array_list_create(sizeof(Entity), 0);
	//0
}

usize entity_create(Mind_NPC *mind, 
					CHAR_SPACE player_index, 
					vec3 position, 
					vec3 size, 
					vec3 sprite_offset, 
					vec3 velocity, 
					u8 collision_layer, 
					u8 collision_mask, 
					bool is_kinematic, 
					usize animation_id, 
					On_Hit on_hit, 
					On_Hit_Static on_hit_static, 
					Mind_State_Enums npc_state, 
					NPC_Alignment alignment, 
					u32 health, 
					Entity_Delete entity_delete_event, 
					Entity_Health_Change health_change, 
					bool playble, 
					u32 texture_id,  
					u32 dialogue_id, 
					int sector, 
					int a, 
					int l, 
					int item_hoilding) 
{
	usize id = entity_list->len;
	usize i;
	Entity *entity;
	Entity temp_entity;
	int current_entity_value_proxy;
	u32 current_entity_value;
	Body *entity_body_set;

	// Find inactive Entity.
	for(i = 0; i < entity_list->len; ++i) 
	{
		Entity *entity = array_list_get(entity_list, i);
		if(!entity->is_active) 
		{
			id = i;
			break;
		}
	}

	if(id == entity_list->len) 
	{
    	Entity temp_entity = {0};

    	if(array_list_append(entity_list, &temp_entity) == (usize)-1) 
    	{
        	ERROR_EXIT("Could not append entity to list\n");
    	}
	}

	entity = entity_get(id);

	temp_entity.mind = mind;
	temp_entity.player_index = player_index;
	temp_entity.is_active = 1;  // Use 1 para `true` em C89
	temp_entity.animation_id = animation_id;
	temp_entity.body_id = physics_body_create(position, 
                                          	  size, 
                                          	  velocity, 
                                          	  collision_layer, 
                                          	  collision_mask, 
                                          	  is_kinematic, 
                                          	  on_hit, 
                                          	  on_hit_static, 
                                          	  id, 
                                          	  0, 
                                          	  a, 
                                          	  l);
	temp_entity.sprite_offset[0] = sprite_offset[0];
	temp_entity.sprite_offset[1] = sprite_offset[1];
	temp_entity.npc_state = IDLE;
	temp_entity.texture_id = texture_id;
	temp_entity.health = 100;
	temp_entity.entity_delete_event = entity_delete_event;
	temp_entity.dialogue_id = dialogue_id;
	temp_entity.should_draw_on_scene = 1;  // Use 1 para `true`
	temp_entity.person_of_interest_id = -1;
	temp_entity.is_turn_set = 0;  // Use 0 para `false`
	temp_entity.is_playble = playble;
	temp_entity.item_hoilding = item_hoilding;
	temp_entity.health_change = health_change;
	temp_entity.is_in_party = 0;  // Use 0 para `false`
	temp_entity.stance = NEUTRAL_STANCE;
	temp_entity.drawing_other = 0;

	*entity = temp_entity;

	entity->id = id;

	current_entity_value_proxy = -1;
	current_entity_value = (u32)current_entity_value_proxy;

	entity_body_set = physics_body_get(entity->body_id);

	if(player_index == LEFT)
	{
		entity_body_set->a = 90;
	}
	else if( player_index == RIGHT )
	{
		entity_body_set->a = 270;
	}
	return id;
}

Entity *entity_get(usize id) 
{
	return array_list_get(entity_list, id);
}

Array_List *entity_array_list_get() 
{
	return entity_list;
}


usize entity_count() 
{
	return entity_list->len;
}

void entity_reset(void) 
{
    entity_list->len = 0;
}

void entity_destroy(usize entity_id) 
{

    Entity *entity_npc = entity_get(entity_id);
	if(entity_npc == NULL)
	{
	 	return;
	}

   	entity_npc->is_active = false;
   	entity_npc->entity_delete_event(entity_id);

}

void move_back(Body *body, f32 delta_time)
{
	body->velocity[0] += (-(BACK_SPEED - (((BACK_SPEED) * 
		clamp_int(clamp_int(body->a, 0, 175), 0, 2)))) * delta_time );
}

bool entity_damage(u32 entity_id, 
				   u8 amount,
				   f32 delta_time) 
{

    Entity *entity = entity_get(entity_id);
	if(entity->health - amount <= 0) 
	{
			entity_destroy(entity_id);
			return true;
	}

	entity->health = entity->health - amount;
	return false;

}


void entity_destroy_from_memory(usize entity_id) 
{
	array_list_remove(entity_list, entity_id);
}
