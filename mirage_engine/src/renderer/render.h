#pragma once

#ifndef RENDER_H
#define RENDER_H
#include "../texture/texture.h"
#include "../util.h"
#include "../types.h"

#include <SDL2/SDL.h>
#include <stdbool.h>

#define res_         1                     //0=160x120 1=360x240 4=640x480
#define SW          640  *res_                  //screen width
#define SH          360  *res_                  //screen height
#define SW2         (SW/2)                   //half of screen width
#define SH2         (SH/2)                   //half of screen height
#define pixelScale  2                   //OpenGL pixel scale
#define GLSW        (SW*pixelScale)          //OpenGL window width
#define GLSH        (SH*pixelScale)          //OpenGL window height

void drawPixel(int x,int y,int r,int g,int b);
void init_window();
void destroy();
void setCanvas();
SDL_Renderer*  get_renderer();

void set_string_dialogue(char new_array_string[DIALOGUE_SIZE]);
void set_string_party(char new_array_string[DIALOGUE_SIZE], int pos);
void free_menu();
bool update_button_name( int index );

void render_end();
void change_window(bool is_window);

void destroy_button_name( int new_index_button_name );
void setRender_menu();
void set_render_in_game_menu();
bool decraese_index_button_name( int index );
void set_button_name_index_value( int new_value );

#endif
