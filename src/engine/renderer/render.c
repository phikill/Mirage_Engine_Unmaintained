#include "../renderer/render.h"
#include "../time/time.h"

#include "../util.h"
#include "../types.h"

#include <SDL2/SDL.h>
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

TTF_Font* font;
SDL_Rect rect, dialogue_rect, char_name[5], button_rect[5], full_rect_menu_pos[9],lowe_sound_menu, up_sound_menu ;
SDL_Rect rect, dialogue_rect, char_name[5], button_rect[5], full_rect_menu_pos[9],lowe_sound_menu, up_sound_menu ;


char menu_dialogue[8][48];
bool can_print_button = true;

char button_array_string[DIALOGUE_SIZE] = { "" };
int index_button_name = 0;
u32 index_menu_pos = 9;



char name_array_string[INVENTORY_SIZE][DIALOGUE_SIZE];

bool create_button_name( char array_string[DIALOGUE_SIZE],  int new_index_button_name){

	if (  new_index_button_name < INVENTORY_SIZE ){

			char_name[new_index_button_name].w = GLSW  * .073f ;
			char_name[new_index_button_name].h = GLSH *  .0359f ;
			float index = (float)new_index_button_name;

			float pos_y = ((float)GLSH *  .049f) * index;

			char_name[new_index_button_name].y = ( GLSH + ( pos_y ) ) - ( GLSH * .83f ) ;
			char_name[new_index_button_name].x = GLSW -  (GLSW * .165f);


			button_rect[new_index_button_name].w = GLSW  * .073f;
			button_rect[new_index_button_name].h = GLSH *  .0359f;

			button_rect[new_index_button_name].y = ( GLSH + ( pos_y ) ) - ( GLSH * .83f ) ;
			button_rect[new_index_button_name].x =  + (GLSW -  (GLSW * .215f));
			set_string_party( array_string, new_index_button_name );
			index_button_name = new_index_button_name + 1;
			return true;
		}
			return false;

}


void set_button_name_index_value( int new_value ){

index_button_name = new_value;

}

void init_menu_pos(){

	for ( int i = 0; i < 8; i++ ){

			full_rect_menu_pos[ i ].w = GLSW  * .6f ;
			full_rect_menu_pos[ i ].h = GLSH *  .07f ;
			float index = (float)i ;

			float pos_y = ((float)GLSH *  .049f) * index;

			full_rect_menu_pos[ i ].y = ( GLSH + ( pos_y ) ) - ( GLSH * .83f ) ;
			full_rect_menu_pos[ i ].x = GLSW -  ( GLSW * .85 );

	}

}


void destroy_button_name( int new_index_button_name ){


	char new_array_char[DIALOGUE_SIZE] = "";
	set_string_party( new_array_char, new_index_button_name );


}





void set_string_button(char new_array_string[30]){


		for ( int i =  0; i <  DIALOGUE_SIZE; i++){

				button_array_string[i] = new_array_string [i];
		}

}

void set_string_menu(char new_array_string[DIALOGUE_SIZE], int index){

		for ( int i = 0; i <  DIALOGUE_SIZE; i++){

				menu_dialogue[index][i] = new_array_string [i];

		}

}

void set_string_party( char new_array_string[DIALOGUE_SIZE], int pos){


			for ( int i =  0; i <  DIALOGUE_SIZE; i++){

					name_array_string[pos][i] = new_array_string[i];

			}

}


SDL_Renderer*  get_renderer(){

	return renderer;

}

static void  renderPixel(){

    SDL_UpdateTexture(screen_texture, NULL, screen_buffer, SW * sizeof(unsigned int));
    SDL_RenderCopyEx(renderer, screen_texture, NULL, NULL, 0, 0, SDL_FLIP_VERTICAL);
    SDL_RenderPresent(renderer);


}

void drawPixel(int x,int y,int r,int g,int b){
 
			int offset = y * SW + x;
			Uint32  color = SDL_MapRGBA(tmpSurf->format, r, g, b, 255);
			screen_buffer[SW * y + x] = color;

}



void get_text_and_rect(SDL_Renderer *renderer, int x, int y, char *text,
	TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect){

		int text_width;
		int text_height;
		if ( text != NULL ){
			if ( (u32)strlen(text) > 1 && (u32)strlen(text) < DIALOGUE_SIZE ){

					SDL_Surface *surface = TTF_RenderText_Solid( font, text, textColor);
					*texture = SDL_CreateTextureFromSurface(renderer, surface);
					rect->w = surface->w;
					rect->h = surface->h;
					SDL_FreeSurface(surface);
					rect->x = 0;
					rect->y = 0;
					surface = NULL;

				}

		}

}


void setRender(){

	renderPixel();
	//SDL_Texture *textTexture;



   //get_text_and_rect(renderer, 0, 0, array_string, font, &textTexture, &rect);
	//DL_RenderCopy(renderer, textTexture, &rect, &dialogue_rect);

	//for ( u32 i = 0; i <= index_button_name; i++ ){

		//if ( name_array_string[i] != NULL){

		//		if ( (u32)strlen(name_array_string[i]) > 1 && (u32)strlen(name_array_string[i]) < DIALOGUE_SIZE  ){

								//get_text_and_rect(renderer, 0, 0, name_array_string[i], font, &textTexture, &rect);
								//SDL_RenderCopyEx(renderer, textTexture, &rect, &char_name[i], 0, NULL, SDL_FLIP_NONE);
								//SDL_RenderCopy(renderer, textTexture, &rect, &char_name[i]);

			//		}


		//}

	//}

	//if ( button_array_string ){

		//if ( (u32)strlen(button_array_string) > 1 && (u32)strlen(button_array_string) < DIALOGUE_SIZE  ){


					//get_text_and_rect(renderer, 0, 0, button_array_string, font, &textTexture, &rect);

					///SDL_RenderCopyEx(renderer, textTexture, &rect, &button_rect[0], 0, NULL,SDL_FLIP_NONE);
					//SDL_RenderCopy(renderer, textTexture, &rect, &button_rect[0]);

		//}

	//}
	//SDL_DestroyTexture(textTexture);

//	SDL_RenderPresent(renderer);
//	SDL_RenderClear(renderer);


}


void set_render_in_game_menu(){

	renderPixel();
	///get_text_and_rect(renderer, 0, 0, lowe_array_string_sound, font, &screen_texture, &rect);
	//SDL_RenderCopyEx(renderer, screen_texture, &rect, &lowe_sound_menu, 0, NULL,SDL_FLIP_NONE);

	//get_text_and_rect(renderer, 0, 0, up_array_string_sound, font, &screen_texture, &rect);

	//SDL_RenderCopyEx(renderer, screen_texture, &rect, &up_sound_menu, 0, NULL,SDL_FLIP_NONE);
	///SDL_RenderPresent(renderer);
	//SDL_RenderClear(renderer);


}

void setCanvas(){



}

void setRender_menu(){

	for ( int x = 0; x < SW; x++ ){
			for ( int y = 0; y < SH; y++ ){

					drawPixel(x,y,1,1,1);

			}
	}

	renderPixel();


	//Now render the texture target to our screen, but upside down
	//SDL_RenderClear(renderer);
	//SDL_RenderCopyEx(renderer, screen_texture, NULL, NULL, 0, NULL, SDL_FLIP_VERTICAL);

	//for ( int i = 0; i < 8; i++ ){

		//	get_text_and_rect(renderer, 0, 0, menu_dialogue[i], font, &screen_texture, &rect);

		//	SDL_RenderCopyEx(renderer, screen_texture, &rect, &full_rect_menu_pos[i], 0, NULL,SDL_FLIP_NONE);

	//}

	SDL_RenderPresent(renderer);
	SDL_RenderClear(renderer);



}



void init_window(){

		SDL_Init(SDL_INIT_VIDEO);

		window = SDL_CreateWindow(
			"Choujin",
			0,
			0,
			GLSW,
			GLSH,
			SDL_WINDOW_MAXIMIZED);

		if (window == NULL){
			printf("Could not create window: %s\n", SDL_GetError());
			return 1;
		}

		screen_buffer_size = sizeof(unsigned int) * SW * SH;
		screen_buffer = (unsigned int*)malloc(screen_buffer_size);
		if (screen_buffer == NULL){

				screen_buffer_size = -1;
				printf("Error initializing screen buffer!\n");
				return 1;

			}

		memset(screen_buffer, 0, screen_buffer_size);
		renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED);
		screen_texture = SDL_CreateTexture(
			renderer,
			SDL_PIXELFORMAT_RGBA32,
			SDL_TEXTUREACCESS_STREAMING,
			SW, SH
		);

    if (screen_texture == NULL)
    {
			printf("Could not create window: %s\n", SDL_GetError());
				return 1;

	}
		TTF_Init();

		font = TTF_OpenFont( "OpenSans-Bold.ttf", 9 );
		rect.w = GLSW;
		rect.h = GLSH;
		rect.y = 0;
		rect.x = 0;

		dialogue_rect.w = GLSW  * .35f ;
		dialogue_rect.h = GLSH *  .095f ;

		dialogue_rect.y = GLSH - (GLSH * .1785f);
		dialogue_rect.x = GLSW -  (GLSW * .92f);



		lowe_sound_menu.w = GLSW  * .35f ;
		lowe_sound_menu.h =  GLSH *  .095f ;

		lowe_sound_menu.x = GLSW -  (GLSW * .75f);
		lowe_sound_menu.y =  GLSH - (GLSH * .8f);


		up_sound_menu.w = GLSW  * .35f ;
		up_sound_menu.h = GLSH *  .095f ;

		up_sound_menu.x = GLSW -  (GLSW * .75f);
		up_sound_menu.y = GLSH - (GLSH * .9f);



		char_name[0].w = GLSW  * .073f ;
		char_name[0].h = GLSH *  .0359f ;

		char_name[0].y = GLSH - (GLSH * .83f);
		char_name[0].x = GLSW -  (GLSW * .165f);


		button_rect[0].w = GLSW  * .073f ;
		button_rect[0].h = GLSH *  .0359f ;

		button_rect[0].y = + (GLSH - (GLSH * .83f));
		button_rect[0].x =  + (GLSW -  (GLSW * .215f));

		tmpSurf = SDL_CreateRGBSurfaceWithFormat(0,SW, SH, 16,SDL_PIXELFORMAT_RGBA32);

}

void destroy(){

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

    if (screen_texture)
        SDL_DestroyTexture(screen_texture);

    if (screen_buffer != NULL)
        free(screen_buffer);

}

void change_window(bool is_window){

if ( is_window ){
		SDL_SetWindowFullscreen ( window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}

else{
		SDL_SetWindowFullscreen ( window, SDL_WINDOW_MAXIMIZED);
	}
}


