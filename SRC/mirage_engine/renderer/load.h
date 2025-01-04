#ifndef LOAD_H
#define LOAD_H
#include "../player/player.h"
#include "../texture/texture.h"
#include "../physics/physics.h"
#include "../entity/entity.h"
#include "../animation/animation.h"

void load(int *index_, 
		  u32 *P_viewr,
		  Sprite_Sheet sprite_sheet_player,
		  usize new_char_player_id,
 		  On_Hit on_hit, 
 		  On_Hit_Static on_hit_static, 
 		  On_Hit on_trigger_hit, 
 		  Entity_Delete On_Entity_Delete_Player);
#endif

