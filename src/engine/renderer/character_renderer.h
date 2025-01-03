#ifndef RENDER_CHARACTER_H
#define RENDER_CHARACTER_H
#include "../player/player.h"
#include "../texture/texture.h"
#include "../physics/physics.h"
#include "../entity/entity.h"


void draw3D_character_at_location(Entity* npc_id, TextureMaps* textures, Body* P_view,math M, u32 id_text);

#endif
