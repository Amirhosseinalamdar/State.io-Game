#ifndef RANKS_H
#define RANKS_H

#include <stdio.h>
#include<SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include<stdbool.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <SDL2/SDL_image.h>

#define map_y 74
#define map_x 122


int ranks(TTF_Font *font,SDL_Renderer *sdlRenderer,Uint32 colors_array[],int menu_map[][map_x-1]);


#endif