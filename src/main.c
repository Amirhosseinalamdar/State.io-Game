#include<stdio.h>
#include<stdbool.h>
#include<SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <time.h>
#define radius 5
#define region_size 25
#define screenW 1200 //120
#define screenH 720 //72
#define map_y 74
#define map_x 122
#define chanta_harif 4
#define color_size 10

//abgr
//har region max 80 khoone

struct Regions{
    int id;  // -2 neutral  -1 default   ....players indexes
    int map[map_y][map_x];// 0 khali 1 vasta 2 border 3 centre
    int num_of_boxes;
    int center_x,center_y;
    Uint32 color;
};

struct Players{
    int Regions[region_size];
    Uint32 color;
};

struct Colors_and_symbols{
    Uint32 player_colors[color_size];
    Uint32 default_color;
    Uint32 neutral_color;
};

void set_maps(struct Regions region[],int game_map[][map_x])
{
    for(int i=0;i<region_size;i++){
        for(int j=0;j<map_y;j++){
            for(int k=0;k<map_x;k++){
                if(j==0 || k==0 || j==map_y-1 || k==map_x-1){
                    region[i].map[j][k]=-1;
                    game_map[j][k]=-1;
                    continue;
                }
                region[i].map[j][k]=0;
                game_map[j][k]=0;
            }
        }
    }
}
void set_regions_map(struct Regions region[],int game_map[][map_x])
{
    int tmpX,tmpY;
    srand(time(0));
    for(int i=0;i<region_size;i++){
        region[i].num_of_boxes=rand()%200+200;
        while(1) {
            tmpX = rand() % 101 +10;
            tmpY = rand() % 53 +10;
            if(game_map[tmpY+radius][tmpX]!=0 || game_map[tmpY-radius][tmpX]!=0 || game_map[tmpY][tmpX+radius]!=0 || game_map[tmpY][tmpX-radius]!=0){
                continue;
            }
            if(game_map[tmpY][tmpX]!=0){
                continue;
            }
            game_map[tmpY][tmpX]=i+10;
            region[i].map[tmpY][tmpX]=1;
            break;
        }
        int counter=0;
        int flag=1;
        int limit1=rand() % 6 + 6 ;
        for(int j=-limit1/(rand()%3 +1);j<limit1+1;j++){
            if(flag==0){
                break;
            }
            int limit=rand() %8  +  7 ;
            if(limit1==7){limit1++;}
            for(int k=-limit/(rand()%3+1);k<limit+1;k++){
                if(tmpY+j > map_y-2 || tmpY+j < 1 || tmpX+k > map_x-2 || tmpX+k < 1) {
                    continue;
                }
                game_map[tmpY+j][tmpX+k]=i+10;
                region[i].map[tmpY+j][tmpX+k]=1;
                counter++;
                if(counter==region[i].num_of_boxes) {
                    flag = 0;
                    break;
                }
            }
        }
    }
}
void set_regions_border(struct Regions region[],int game_map[][map_x])
{
    for(int i=0;i<region_size;i++){
        for(int j=1;j<map_y-1;j++){
            for(int k=1;k<map_x-1;k++){
                if(region[i].map[j][k]==1) {
                    if(region[i].map[j+1][k]==0 && region[i].map[j-1][k]==0){
                        region[i].map[j][k]=0;
                        game_map[j][k]=0;
                        k-=2;
                        continue;
                    }
                    if(region[i].map[j+2][k]==0 && region[i].map[j-1][k]==0){
                        region[i].map[j][k]=0;
                        game_map[j][k]=0;
                        k-=2;
                        continue;

                    }
                    if(region[i].map[j+1][k]==0 && region[i].map[j-2][k]==0){
                        region[i].map[j][k]=0;
                        game_map[j][k]=0;
                        k-=2;
                        continue;
                    }
                    if ((region[i].map[j][k + 1] == 0 || region[i].map[j][k - 1] == 0 || region[i].map[j + 1][k] == 0 || region[i].map[j - 1][k] == 0)) {
                        region[i].map[j][k] = 2;
                    }
                    if((region[i].map[j][k + 1] == -1 || region[i].map[j][k - 1] == -1 || region[i].map[j + 1][k] == -1 || region[i].map[j - 1][k] == -1)){
                        region[i].map[j][k]=2;
                    }

                }
            }
        }
    }
}
void draw_map(struct Regions region[],SDL_Renderer *sdlRenderer)
{
    Uint32 colors_array[10]={0x88000000,0x88ffffff,0x880000ff,0x8800ff00,0x88ff0000,0x88ffff00,0x8800ffff,0x88ff00ff,0x88CCD88D,0x883C3A40};//#403a3c
    srand(time(0));
    for(int i=0;i<region_size;i++){
        Uint32 border_color=0xee5635B0;
        Uint32 color = colors_array[0];
        if(i>region_size-6) {
            color = colors_array[rand() % 9];
        }
        else{
            color= colors_array[9];
        }
        for(int j=1;j<map_y;j++){
            for(int k=1;k<map_x;k++){
                if(region[i].map[j][k]!=0) {
                    Sint16 x1 = (k-1) * 10;
                    Sint16 x2 = x1 + 10;
                    Sint16 y1 = (j-1) * 10;
                    Sint16 y2 = y1 + 10;
                    if(region[i].map[j][k]==1) {
                        boxColor(sdlRenderer, x1, y1, x2, y2, color);
                    }
                    else{
                        boxColor(sdlRenderer,x1,y1,x2,y2,border_color);
                    }
                }
            }
        }
    }
}
void organize_regions(struct Regions region[],int game_map[][map_x])
{
    for(int i=0;i<region_size;i++){
        for(int j=0;j<map_y-1;j++){
            for(int k=0;k<map_x-1;k++){
                if(region[i].map[j][k]!=0  &&  game_map[j][k] != i+10){
                    region[i].map[j][k]=0;
                }
            }
        }
    }
}
void update_game_map(struct Regions region[],int game_map[][map_x]){
    for(int i=0;i<region_size;i++){
        for(int j=0;j<map_y-1;j++){
            for(int k=0;k<map_x-1;k++){
                if(region[i].map[j][k]!=0 && region[i].map[j+1][k]==0 && region[i].map[j-1][k]==0){
                    region[i].map[j][k]=0;
                    game_map[j][k]=0;
                }
                if(region[i].map[j][k]!=0 && game_map[j][k]==0){
                    game_map[j][k]=i+10;
                }
            }
        }
    }
}
void set_region_colors(struct Regions region[],struct Colors_and_symbols color_struct,int players,int neutral_players,struct Players player[])
{
    srand(time(0));
    int random_number=rand()%
    for(int i=0;i<region_size;i++){
        if(i<region_size-players-neutral_players) {
            region[i].color = color_struct.default_color;
        }
        else if(i<region_size-players){
            region[i].color=color_struct.neutral_color;
        }
        else{
            region[i].color=color_struct.player_colors[rand()%10];
        }

    }
}
void get_centre(struct Regions region[])
int main()
{
    srand(time(0));
    const int FPS = 60;
    const int SCREEN_WIDTH = screenW;
    const int SCREEN_HEIGHT = screenH;
    int flag=1;
    int players=chanta_harif; //tedade harif
    int bases=region_size;
    int neutral_players=rand()%3 +2;
    struct Regions region[region_size];
    int game_map[map_y][map_x];

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    SDL_Window *sdlWindow = SDL_CreateWindow("Test_Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                             SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

    SDL_Renderer *sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    SDL_bool shallExit = SDL_FALSE;
    while (shallExit == SDL_FALSE) {
        SDL_SetRenderDrawColor(sdlRenderer, 0x1E, 0x00, 0x1E, 0xf0);
        SDL_RenderClear(sdlRenderer);


        set_maps(region, game_map);
        set_regions_map(region, game_map);
        set_regions_border(region, game_map);
        update_game_map(region,game_map);
        //organize_regions(region,game_map);

        draw_map(region,sdlRenderer);


        SDL_RenderPresent(sdlRenderer);
        SDL_Delay(6000 / FPS);
        SDL_Event sdlEvent;
        while (SDL_PollEvent(&sdlEvent)) {
            switch (sdlEvent.type) {
                case SDL_QUIT:
                    shallExit = SDL_TRUE;
                    break;
            }
        }
    }
//SDL_Quit();
}