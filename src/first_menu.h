

#ifndef FIRST_MENU_H
#define FIRST_MENU_H

#include <stdio.h>
#include<SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include<stdbool.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define map_y 74
#define map_x 122
#define menu 8

void include_welcome_enter(TTF_Font *font,SDL_Renderer *sdlRenderer);
void draw_menu(Uint32 colors_array[],SDL_Renderer *sdlRenderer,int flag,int menu_map[][map_x-1]);
int first_menu(TTF_Font *font,SDL_Renderer *sdlRenderer,Uint32 colors_array[],int menu_map[][map_x-1]);
#endif


