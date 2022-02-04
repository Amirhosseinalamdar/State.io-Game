
#ifndef MAIN_MENU_H
#define MAIN_MENU_H
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

//void draw_menu(Uint32 colors_array[],SDL_Renderer *sdlRenderer,int flag,int menu_map[][map_x-1]);
int main_menu(int menu_map[][map_x-1],SDL_Renderer *sdlRenderer,TTF_Font *font,TTF_Font *font2,Uint32 colors_array[]);

#endif