#ifndef NPC_MIND_H
#define NPC_MIND_H
#include <stdio.h>
#include <conio.h>
#include "../entity/entity.h"
#include "../array_list/array_list.h"
#include "../time/time.h"
#include "../types.h"


void init_mind_npc();

void updated_mind_npcs(f32 delta);
void updated_mind_npcs_lawful(u32 id);
void updated_mind_npcs_chaotic(u32 id);

#endif
