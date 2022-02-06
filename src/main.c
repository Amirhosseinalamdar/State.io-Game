
#include "first_menu.h"
#include "main_menu.h"
#include "map.h"

#define radius 6
#define radius2 5
#define bases 20
#define screenW 1200 //120
#define screenH 720 //72
#define chanta_harif 7
#define color_size 10
#define map_y 74
#define map_x 122
#define menu 8


int main()
{

    srand(time(0));

    const int SCREEN_WIDTH = screenW;
    const int SCREEN_HEIGHT = screenH;
    int flag=1;
    int players=chanta_harif; //tedade harif
    int region_size=bases;

    int game_map[map_y][map_x];

    Uint32 colors_array[12]={0xffff3445,0xffffff00,0xffff0000,0xff803400,0xffff00ff,0xff00ffff,
                             0xff00ff00,0xff0000ff,0xffabcdef,0xffabbcda,0xff3C3A40,0xff5635B0}; //def  //border
    Uint32 barracks_colors_array[12]={0x77ff3445,0x77ffff00,0x77ff0000,0x77803400,0x77ff00ff,0x7700ffff,
                                      0x7700ff00,0x770000ff,0x77abcdef,0x77abbcda,0x773C3A40,0x775635B0};

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    SDL_Window *sdlWindow = SDL_CreateWindow("Test_Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                             SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

    SDL_Renderer *sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);



    TTF_Init();
    TTF_Font * font = TTF_OpenFont("RussoOne-Regular.ttf" , 500);
    TTF_Font *font2= TTF_OpenFont("sample.ttf",500);

    int menu_map[map_y - 1][map_x - 1] = {0};


    //int menu_option =first_menu(font,sdlRenderer,colors_array,menu_map);
    //menu_option=main_menu(menu_map,sdlRenderer,font,font2,colors_array);    //menu_option==0 => quit //1 => random map //2 select map //3 rankings
    int temp=map(sdlRenderer,game_map,region_size,players,colors_array,barracks_colors_array,sdlWindow);


SDL_Quit();
}

