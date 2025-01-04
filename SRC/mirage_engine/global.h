#ifndef GLOBAL_H
#define GLOBAL_H
#include "math_utils.h"
#include "input/input_internal.h"
#include "renderer/render_internal.h"

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
	int numText;                         //number of textures
	int numSect;                          //number of sectors
	int numWall;                         //number of walls

	sectors S[356];	
	walls W[356];
}Global;

extern Global global;


#endif





