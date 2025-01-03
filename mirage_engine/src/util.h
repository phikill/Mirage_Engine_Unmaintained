#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>

#define ERROR_EXIT(...) { fprintf(stderr, __VA_ARGS__); exit(1); }
#define ERROR_RETURN(R, ...) { fprintf(stderr, __VA_ARGS__); return R; }
#define DIALOGUE_SIZE 55
#define INVENTORY_SIZE 5
#define PLAYER_ATTACK 25
#define TURN_START_AFTER_ANIM_TIME 1.3f
char *convert(int number, char *buff, int base, char digits[30]);

#define CHARACTER_DEFAULT_LIFE 250
#define CAMERA_CHANGE 4


#define NAME_SIZE 11

#define PLAYER_ATTACK_POWER 4

#define NPC_ATTACK 26
#define RENDER_TIME_ID 111

#define ANIMATION_DURATION .08f

#define CHARACTER_DEFAULT_SIZE 70
#define MOVE_SPEED             520 * CHARACTER_DEFAULT_SIZE


#define CHARACTER_SIZE 0
#define WHITE (vec4){1, 1, 1, 1}
#define BLACK (vec4){0, 0, 0, 1}
#define RED (vec4){1, 0, 0, 1}
#define GREEN (vec4){0, 1, 0, 1}
#define BLUE (vec4){0, 0, 1, 1}
#define YELLOW (vec3){170, 170, 170}
#define GREY (vec3){170, 170, 170}

#define CYAN (vec4){0, 1, 1, 1}
#define MAGENTA (vec4){1, 0, 1, 1}
#define ORANGE (vec4){1, 0.5, 0, 1}
#define PURPLE (vec4){0.5, 0, 1, 1}
#define TURQUOISE (vec4){0, 1, 0.5, 1}

#endif