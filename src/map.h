
#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include<SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include<stdbool.h>
#include <time.h>
#include <string.h>
#include <math.h>

#define radius 6
#define radius2 5
#define bases 20
#define screenW 1200 //120
#define screenH 720 //72
#define chanta_harif 5
#define color_size 10
#define map_y 74
#define map_x 122
#define menu 8
#define bullet_radius 4

struct Regions{
    int id;  //  -1 default   ....players indexes
    int map[map_y][map_x];// 0 khali 1 vasta 2 border 3 centre
    int num_of_boxes;
    int center_x,center_y;
    int soldiers;
    int real_soldiers;
    char soldiers_string[4];
    int is_attacking;
    Uint32 color;
    Uint32 barracks_color;
};

struct Players{
    int Regions[bases];
    int base_size;
    Uint32 color,barrack_color;
    int rate;
};

struct Troops{
    int sum;
    int x[1024],y[1024];
    Uint32 color;
    int player_index;
    int origin_region_index;
    int destination_region_index;
    int is_empty;
    int counter;
    float Vx,Vy;
};

void set_mapsAndId(struct Regions region[],int game_map[][map_x],int region_size);
void set_regions_map(struct Regions region[],int game_map[][map_x],int region_size);
void set_regions_border(struct Regions region[],int game_map[][map_x],int region_size);
void draw_map(struct Regions region[],SDL_Renderer *sdlRenderer,int region_size,Uint32 colors_array[],int players,Uint32 barracks_colors_array[],int flag,struct Players player[]);
void organize_regions(struct Regions region[],int game_map[][map_x],int region_size);
void set_num_of_boxes(struct Regions region[],int game_map[][map_x],int region_size);
void update_game_map(struct Regions region[],int game_map[][map_x],int region_size);
void get_centre(struct Regions region[],int region_size);
void give_regions_equivalently(struct Regions region[],int region_size, int game_map[][map_x],int players);
void set_soldiers_and_rate(struct Regions region[],int region_size,struct Players player[],int players);
void soldiers_to_string(struct Regions region[],int region_size);
void print_soldiers(struct Regions region[],int region_size,SDL_Renderer *sdlRenderer);
void increase_troops(struct Regions region[],int region_size,struct Players player[],int flag);
int  is_in_center(struct Regions region[],int region_size,int x,int y);
void initialize_squad(struct Troops squad[],struct Regions region[],int key1,int key2);
int is_in_player_center(struct Regions region[],int region_size,int x,int y, struct Players player[]);
void include_map(struct Regions region[],int game_map[][map_x],int region_size,SDL_Renderer *sdlRenderer,struct Players player[],int players);
void attack_temp_func(struct Regions region[],int region_size,struct Troops squad[]);

int map(SDL_Renderer *sdlRenderer,int game_map[][map_x],int region_size,int players,Uint32 colors_array[],Uint32 barracks_colors_array[],SDL_Window *sdlWindow);



#endif