
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
#include <SDL2/SDL_image.h>

#define radius 6
#define radius2 5
#define bases 25
#define screenW 1200 //120
#define screenH 720 //72
#define chanta_harif 7
#define color_size 10
#define map_y 74
#define map_x 122
#define menu 8
#define bullet_radius 4
#define potion_radius_in 80
#define potion_radius_dif 40
#define potion_size 4
#define potion_border_distance 150
//fasele markazesh az border = 150

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
    int Vo;
    int damage;
    int khafan;
};

struct Players {
    int Regions[bases];
    int base_size;
    Uint32 color, barrack_color;
    int rate;
    int potion_effect;
};
struct Potion{
    int is_active;
    int time2;
    int center_x,center_y;
    int potion_type; //1 soorat ziad taghirban sabz //2 taghire zoor light blue //4 sarbaz ezafe she beja kam shodan taghirban sabz //3 rate abi
    int time;
    int potion_radius;
    Uint32 color;
    Uint32 border_color;
    Uint32 base_color;
    int damage;
    int player_index;
    int is_active_on_player;
    int player_time;
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
    int damage;
    int dx[3],dy[3];
};

/*void set_mapsAndId(struct Regions region[],int game_map[][map_x],int region_size);
void set_regions_map(struct Regions region[],int game_map[][map_x],int region_size);
void set_regions_border(struct Regions region[],int game_map[][map_x],int region_size);
void draw_map(struct Regions region[],SDL_Renderer *sdlRenderer,int region_size,Uint32 colors_array[],int players,Uint32 barracks_colors_array[],int flag,struct Players player[],int game_map[][map_x]);
void draw_bases(struct Regions region[],int region_size,int game_map[][map_x],SDL_Renderer *sdlRenderer);

void organize_regions(struct Regions region[],int game_map[][map_x],int region_size);
void set_num_of_boxes(struct Regions region[],int game_map[][map_x],int region_size);
void update_game_map(struct Regions region[],int game_map[][map_x],int region_size);
void get_centre(struct Regions region[],int region_size);
void give_regions_equivalently(struct Regions region[],int region_size, int game_map[][map_x],int players);
void set_soldiers_and_rate(struct Regions region[],int region_size,struct Players player[],int players);
void soldiers_to_string(struct Regions region[],int region_size);

void print_soldiers(struct Regions region[],int region_size,SDL_Renderer *sdlRenderer);
void increase_troops(struct Regions region[],int region_size,struct Players player[],int flag);
void include_map(struct Regions region[], int game_map[][map_x], int region_size, SDL_Renderer *sdlRenderer,
                 struct Players player[], int players);

void initialize_squad(struct Troops squad[],struct Regions region[],int key1,int key2);
int  is_in_center(struct Regions region[],int region_size,int x,int y);
int is_in_player_center(struct Regions region[],int region_size,int x,int y, struct Players player[]);
int distance_from_center(int x1,int y1,int x2,int y2,int a,int b);

void attack_temp_func(struct Regions region[],int region_size,struct Troops squad[],struct Potion potion[]);
void check_soldier_position(struct Troops squad[],int key,int x_pos,int y_pos,struct Potion potion[],struct Players player[]);
int check_game_state(struct Regions region[],int region_size,struct Troops squad[]);
void set_potion_struct(struct Potion potion[]);
void initialize_potion(struct Potion potion[],Uint32 potion_colors[],Uint32 potion_border_colors[]);
void update_potion(struct Potion potion[],struct Players player[]);
void draw_potions(struct Potion potion[],SDL_Renderer *sdlRenderer);
void set_regions_speed(struct Regions region[],int region_size,struct Players player[]);
void activate_potion(struct Regions region[],struct Potion potion[],int region_size,struct Players player[]);



int score(int state,int time_0);
void score_to_string(int score,char score_string[]);
*/
int map(SDL_Renderer *sdlRenderer,int game_map[][map_x],int region_size,int players,Uint32 colors_array[],Uint32 barracks_colors_array[],SDL_Window *sdlWindow,TTF_Font *font,int *myscore);



#endif