#ifndef GLOBAL_H
#define GLOBAL_H
#include "math_utils.h"
#include "input/input_internal.h"
#include "player/player.h"
#include "texture/texture.h"
#include "time/time.h"
#include "config/config.h"

typedef struct global
{

math M;
Input_State input;
Time_State time;
TextureMaps textures[ 28 ];
Config_State config;
u32 body_player;
u32 player_health;

}  Global;

extern Global global;



#endif





