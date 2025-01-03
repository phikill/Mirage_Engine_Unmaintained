#ifndef H_MIRAGE
#define H_MIRAGE
#include "time/time.h"
#include "entity/item.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "physics/physics.h"

void load_next_level();
Mix_Chunk *Get_Hit();
On_Hit trigger_body_hit( Body *self, Body *other, Hit hit );
On_Hit on_table_entered_hit(Body *self, Body *other, Hit hit);

#endif
