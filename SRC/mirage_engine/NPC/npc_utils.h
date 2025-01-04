#ifndef NPC_UTIL
#define NPC_UTIL
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include "../renderer/render.h"
#include "../renderer/render_internal.h"
#include "../time/time.h"
#include "../config/config.h"
#include "../input/input_internal.h"
#include "../types.h"
#include "../physics/physics.h"
#include "../entity/entity.h"
#include "../collision.h"
#include "../animation/animation.h"
#include "../NPC/mind_npc.h"
#include "../ui/button.h"

u32 init_characters(vec3 position, 
					On_Hit on_hit, 
					On_Hit_Static on_hit_static, 
					u32 index, 
					u32 dialogue_id, 
					int sector, 
					int a, 
					int l,
					int item_hoilding, 
					NPC_Alignment aligment);

#endif