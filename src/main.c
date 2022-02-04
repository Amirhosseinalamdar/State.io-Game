
#include "first_menu.h"
#include "main_menu.h"

#define radius 5
#define radius2 5
#define bases 20
#define screenW 1200 //120
#define screenH 720 //72
#define chanta_harif 5
#define color_size 10
#define map_y 74
#define map_x 122
#define menu 8
//abgr
//har region max 80 khoone

struct Regions{
    int id;  //  -1 default   ....players indexes
    int map[map_y][map_x];// 0 khali 1 vasta 2 border 3 centre
    int num_of_boxes;
    int center_x,center_y;
    int soldiers;
    char soldiers_string[4];
    Uint32 color;
    Uint32 barracks_color;
};

struct Players{
    int Regions[bases];
    int base_size;
    Uint32 color;
    int rate;
};

void set_mapsAndId(struct Regions region[],int game_map[][map_x],int region_size)
{
    for(int i=0;i<region_size;i++){
        region[i].id=-1;
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
void set_regions_map(struct Regions region[],int game_map[][map_x],int region_size)
{
    int tmpX,tmpY;
    srand(time(0));
    for(int i=0;i<region_size;i++){
        region[i].num_of_boxes=rand()%200+200;
        while(1) {
            tmpX = rand() % 106 +7;
            tmpY = rand() % 63 +5;
            if(game_map[tmpY+radius][tmpX]!=0 || game_map[tmpY-radius][tmpX]!=0 || game_map[tmpY][tmpX+radius]!=0 || game_map[tmpY][tmpX-radius]!=0){
                continue;
            }
            if(game_map[tmpY+radius2][tmpX+radius2]!=0 || game_map[tmpY+radius2][tmpX-radius2]!=0 || game_map[tmpY-radius2][tmpX+radius2]!=0 || game_map[tmpY-radius2][tmpX-radius2]!=0){
                continue;
            }
            if(game_map[tmpY][tmpX]!=0){
                continue;
            }
            game_map[tmpY][tmpX]=i+10;
            region[i].map[tmpY][tmpX]=1;
            region[i].center_x=tmpX;
            region[i].center_y=tmpY;
            break;
        }
        int counter=0;
        int flag=1;
        int limit1=rand() % 6 + 5 ;
        for(int j=-limit1/(rand()%3 +1);j<limit1+1;j++){
            if(flag==0){
                break;
            }
            int limit=rand() %8  +  6 ;
            if(limit1==7){limit1++;}
            for(int k=-limit/(rand()%3+1);k<limit+1;k++){
                if(tmpY+j > map_y-2 || tmpY+j < 1 || tmpX+k > map_x-2 || tmpX+k < 1) {
                    continue;
                }
                //if(game_map[tmpY+j][tmpX+k]==0) {
                    game_map[tmpY + j][tmpX + k] = i + 10;
                    region[i].map[tmpY + j][tmpX + k] = 1;
                    counter++;
                //}
                if(counter==region[i].num_of_boxes) {
                    flag = 0;
                    break;
                }
            }
        }
        region[i].num_of_boxes=counter;
    }
}
void set_regions_border(struct Regions region[],int game_map[][map_x],int region_size)
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
void draw_map(struct Regions region[],SDL_Renderer *sdlRenderer,int region_size,Uint32 colors_array[],int players,Uint32 barracks_colors_array[])
{
    srand(time(0));
    int tmp[region_size];
    int flag=1;
    for(int i=0;i<region_size;i++){
        flag=1;
        Uint32 chosen_color = colors_array[10];
        region[i].barracks_color=barracks_colors_array[10];


        if (region[i].id>=0) {
            tmp[i]=rand()%10;
            for(int l=0;l<i;l++){
                if(tmp[l]==tmp[i]){
                    l=-1;
                    tmp[i]=rand()%10;
                }
            }
            chosen_color = colors_array[tmp[i]];
            region[i].barracks_color=barracks_colors_array[tmp[i]];
        }
        region[i].color = chosen_color;
        for(int j=1;j<map_y;j++){
            for(int k=1;k<map_x;k++){
                if(region[i].map[j][k]!=0) {
                    Sint16 x1 = (k-1) * 10;
                    Sint16 x2 = x1 + 10;
                    Sint16 y1 = (j-1) * 10;
                    Sint16 y2 = y1 + 10;
                    if(region[i].map[j+1][k]==3 || region[i].map[j-1][k]==3 || region[i].map[j][k+1]==3 || region[i].map[j][k-1]==3){
                        boxColor(sdlRenderer,x1,y1,x2,y2,region[i].barracks_color);
                    }
                    else if(region[i].map[j][k]==1) {
                        boxColor(sdlRenderer, x1, y1, x2, y2,region[i].color);
                    }
                    else if(region[i].map[j][k]==2){
                        boxColor(sdlRenderer,x1,y1,x2,y2,colors_array[11]);
                    }
                    else{
                        SDL_RenderPresent(sdlRenderer);
                        boxColor(sdlRenderer, x1, y1, x2, y2,region[i].barracks_color);
                    }
                }
            }
        }
    }
}
void organize_regions(struct Regions region[],int game_map[][map_x],int region_size)
{
    for(int i=0;i<region_size;i++){
        region[i].num_of_boxes=0;
        for(int j=1;j<map_y-1;j++){
            for(int k=1;k<map_x-1;k++){
                if(region[i].map[j][k]!=0){
                    region[i].num_of_boxes++;
                }
                if(region[i].map[j][k]!=0  &&  game_map[j][k] != i+10){
                    region[i].map[j][k]=0;
                    region[i].num_of_boxes--;
                }
            }
        }
    }
}
void set_num_of_boxes(struct Regions region[],int game_map[][map_x],int region_size)
{
    for(int i=0;i<region_size;i++){
        region[i].num_of_boxes=0;
        for(int j=1;j<map_y-1;j++){
            for(int k=1;k<map_x-1;k++){
                if(region[i].map[j][k]!=0){
                    region[i].num_of_boxes++;
                    game_map[j][k]=i+10;
                }
            }
        }
    }
}
void update_game_map(struct Regions region[],int game_map[][map_x],int region_size){
    for(int i=1;i<region_size;i++){
        for(int j=1;j<map_y-1;j++){
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
void get_centre(struct Regions region[],int region_size)
{
    int sum_x=0,sum_y=0;
    int sum=0;
    for(int i=0;i<region_size;i++) {
        for (int j = 1; j < map_y - 1; j++) {
            for (int k = 1; k < map_x-1; k++) {
                if(region[i].map[j][k]!=0){
                    sum_y+=j;
                    sum_x+=k;
                }
            }
        }
        region[i].center_x = sum_x / (region[i].num_of_boxes);
        region[i].center_y = sum_y / (region[i].num_of_boxes);
        region[i].map[region[i].center_y][region[i].center_x] = 3;
        sum_x=0;
        sum_y=0;
    }
}
void give_regions_equivalently(struct Regions region[],int region_size, int game_map[][map_x],int players)
{
    int tmp1=0;
    int tmp2=0;
    int index_of_max=0;
    for(int i=0;i<players;i++){
        for(int j=0;j<region_size;j++){
            if(region[j].id>=0){continue;}
            tmp1=(region[j].center_x-61)*(region[j].center_x-61)+(region[j].center_y-37)*(region[j].center_y-37)*4;
            if(tmp1>tmp2){
                index_of_max = j;
                tmp2 = tmp1;
            }
        }
        region[index_of_max].id=i;
        tmp2=0;
        index_of_max=0;
    }
}
void set_soldiers_and_rate(struct Regions region[],int region_size,struct Players player[],int players)
{
    int ctr=0;
    for(int i=0;i<region_size;i++){
        if(region[i].id==-1) {
            region[i].soldiers = 30;
        }
        else{
            player[ctr].Regions[0]=i;
            region[i].soldiers=rand()%20 + 10;
            ctr++;
        }
    }
    for(int i=0;i<players;i++){
        if(i==0){
            player[i].rate=1;
        }
        else{
            player[i].rate=2;
        }
    }

}
void soldiers_to_string(struct Regions region[],int region_size)
{
    for(int i=0;i<region_size;i++){
        int tmp=region[i].soldiers;
        int n=tmp;
        int ctr=0;
        int digit;
        while(tmp!=0){
            tmp/=10;
            ctr++;
        }
        while(ctr!=0){
            digit=n%10;
            n/=10;
            region[i].soldiers_string[ctr-1]=digit+'0';
            ctr--;
        }
    }
}
void print_soldiers(struct Regions region[],int region_size,SDL_Renderer *sdlRenderer)
{
    for(int i=0;i<region_size;i++){
        stringRGBA(sdlRenderer,region[i].center_x,region[i].center_y,region[i].soldiers_string,255,255,255,255);
    }
}


int main()
{

    srand(time(0));
    const int FPS = 60;
    const int SCREEN_WIDTH = screenW;
    const int SCREEN_HEIGHT = screenH;
    int flag=1;
    int players=chanta_harif; //tedade harif
    int region_size=bases;
    struct Regions region[region_size];
    int game_map[map_y][map_x];
    struct Players player[players];
    Uint32 colors_array[12]={0xffff3445,0xffffff00,0xffff0000,0xff803400,0xffff00ff,0xff00ffff,0xff00ff00,0xff0000ff,0xffabcdef,0xffabbcda,0xff3C3A40,0xff5635B0}; //def  //border
    Uint32 barracks_colors_array[12]={0x77ff3445,0x77ffff00,0x77ff0000,0x77803400,0x77ff00ff,0x7700ffff,0x7700ff00,0x770000ff,0x77abcdef,0x77abbcda,0x773C3A40,0x775635B0};

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
    int menu_option =first_menu(font,sdlRenderer,colors_array,menu_map);
    menu_option=main_menu(menu_map,sdlRenderer,font,font2,colors_array);    //menu_option==0 => quit //1 => random map //2 select map //3 rankings




    if(menu_option == 1) {

        SDL_SetRenderDrawColor(sdlRenderer, 0x1E, 0x00, 0x1E, 0xf0);//0xf01e001e
        SDL_RenderClear(sdlRenderer);
        set_mapsAndId(region, game_map, region_size);
        set_regions_map(region, game_map, region_size);
        set_regions_border(region, game_map, region_size);
        update_game_map(region, game_map, region_size);
        set_num_of_boxes(region, game_map, region_size);
        organize_regions(region, game_map, region_size);
        get_centre(region, region_size);
        give_regions_equivalently(region, region_size, game_map, players);
        draw_map(region, sdlRenderer, region_size, colors_array, players,barracks_colors_array);
        //stringRGBA(sdlRenderer,300,200,"34",255,255,255,255);
        SDL_RenderPresent(sdlRenderer);
        set_soldiers_and_rate(region,region_size,player,players);
        print_soldiers(region,region_size,sdlRenderer);

        SDL_bool shallExit = SDL_FALSE;
        while (shallExit == SDL_FALSE) {
            SDL_Delay(1000 / FPS);
            SDL_Event sdlEvent;
            while (SDL_PollEvent(&sdlEvent)) {
                switch (sdlEvent.type) {
                    case SDL_QUIT:
                        shallExit = SDL_TRUE;
                        break;
                }
            }
        }
    }

SDL_Quit();
}

