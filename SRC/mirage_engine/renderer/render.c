#include <stdio.h>
#include <stdlib.h>
#include <linmath\linmath.h>

#include <stdlib.h>
#include <string.h>

#include "render_internal.h"
#include "../renderer/render.h"
#include "character_renderer.h"
#include "../mirage_hengine.h"

#include <math.h>
#include <stdio.h>
#include "../texture/texture.h"

#include "../array_list/array_list.h"
#include "../physics/physics.h"
#include "../entity/entity.h"
#include "../animation/animation.h"
#include "../renderer/render.h"

#include "../types.h"
#include "../collision.h"
#include "../global.h"
#include "../common.h"
#include <SDL2/SDL_ttf.h>

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* screen_texture;
unsigned int scrnw, scrnh;
SDL_Surface *tmpSurf;


bool is_debug_mode = false;
unsigned int *screen_buffer = NULL;
int screen_buffer_size = 0;


SDL_Color textColor = {255, 255,255, 0};
Uint32 buffer[SH * SW];
SDL_Rect rect;

TTF_Font* font;

bool can_print_button = true;

char button_array_string[DIALOGUE_SIZE] = { "" };
int index_button_name = 0;
u32 index_menu_pos = 9;

void render_end()
{
    SDL_UpdateTexture(screen_texture, 
    				  NULL, 
    				  screen_buffer, 
    				  SW * sizeof(unsigned int));

    SDL_RenderCopyEx(renderer, 
    				 screen_texture, 
    				 NULL, 
    				 NULL, 
    				 0, 
    				 0, 
    				 SDL_FLIP_VERTICAL);

    SDL_RenderPresent(renderer);
}

void draw3D_Map(TextureMaps* textures, Body*  P,math M)
{
    clearBackground(textures, P, M);
    draw3D_Walls(textures, P, M);
    draw_characters(textures, P, M);
    draw_ui_screen(textures, P);
}

void drawPixel(int x,
			   int y,
			   int r,
			   int g,
			   int b)
{
	int offset = y * SW + x;
	Uint32  color = SDL_MapRGBA(tmpSurf->format, r, g, b, 255);
	screen_buffer[SW * y + x] = color;
}

void init_window()
{
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Choujin",
							  0,
							  0,
							  GLSW,
							  GLSH,
							  SDL_WINDOW_MAXIMIZED);

	if(window == NULL)
	{
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	screen_buffer_size = sizeof(unsigned int) * SW * SH;
	screen_buffer = (unsigned int*)malloc(screen_buffer_size);
	if(screen_buffer == NULL)
	{
		screen_buffer_size = -1;
		printf("Error initializing screen buffer!\n");
		return 1;
	}

	memset(screen_buffer, 0, screen_buffer_size);
	renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
	screen_texture = SDL_CreateTexture(renderer,
									   SDL_PIXELFORMAT_RGBA32,
									   SDL_TEXTUREACCESS_STREAMING,
									   SW, 
									   SH);

    if(screen_texture == NULL)
    {
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}
	
	TTF_Init();

	font = TTF_OpenFont("OpenSans-Bold.ttf", 9);
	rect.w = GLSW;
	rect.h = GLSH;
	rect.y = 0;
	rect.x = 0;
	tmpSurf = SDL_CreateRGBSurfaceWithFormat(0,SW, SH, 16,SDL_PIXELFORMAT_RGBA32);
}

void destroy()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

    if(screen_texture)
    {
        SDL_DestroyTexture(screen_texture);
    }

    if(screen_buffer != NULL)
    {
        free(screen_buffer);
    }
}

void change_window(bool is_window)
{

	if(is_window)
	{
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}
	else
	{
		SDL_SetWindowFullscreen ( window, SDL_WINDOW_MAXIMIZED);
	}
}


