
#include "first_menu.h"
#include "main_menu.h"
#include "map.h"
#include "choose_map.h"
#include "ranks.h"
#include "choose_num.h"

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

void swap(char users[][32],int i,int j,int scores[])
{
    int tmp=scores[i];
    scores[i]=scores[j];
    scores[j]=tmp;
    char tmp_str[32];
    strcpy(tmp_str,users[i]);
    strcpy(users[i],users[j]);
    strcpy(users[j],tmp_str);
}

void add_to_leaderboard(int tmp_score,char users[][32],int scores[],char user_name[])
{
    char c=' ';
    int n;
    if(tmp_score>0){
        FILE *fptr=fopen("leaderboard.txt","r");
        fscanf(fptr,"%d\n",&n);

        for(int i=0;i<n;i++) {
            fscanf(fptr,"%c", &c);
            for(int j=0;c!='\n';j++){
                users[i][j]=c;
                fscanf(fptr, "%c", &c);
            }
            fscanf(fptr,"%d\n",&scores[i]);
        }
        fclose(fptr);
        int flag=0;
        for(int i=0;i<n;i++){
            if(strcmp(user_name,users[i])==0){
                scores[i]+=tmp_score;
                flag=1;
            }
        }
        if(flag==0){
            for(int i=0;i< strlen(user_name);i++){
                users[n][i]=user_name[i];
            }
            scores[n]=tmp_score;
            n++;
        }
        //sort
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(scores[i]>scores[j]){
                    swap(users,i,j,scores);
                }
            }
        }
        FILE *fptr1 = fopen("leaderboard.txt","w");
        fprintf(fptr1,"%d\n",n);
        for(int i=0;i<n;i++){
            for(int j=0;j< strlen(users[i]);j++){
                fprintf(fptr1,"%c",users[i][j]);
            }
            fprintf(fptr1,"\n%d\n",scores[i]);
        }
        fclose(fptr1);
    }
}

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
                             0xff00ff00,0xff0000ff,0xffabcdef,0xffabbc00,0xff3C3A40,0xff5635B0}; //def  //border
    Uint32 barracks_colors_array[12]={0x77ff3445,0x77ffff00,0x77ff0000,0x77803400,0x77ff00ff,0x7700ffff,
                                      0x7700ff00,0x770000ff,0x77abcdef,0x77abbcda,0x773C3A40,0x775635B0};

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

    SDL_Window *sdlWindow = SDL_CreateWindow("state.io", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                                             SCREEN_HEIGHT, SDL_WINDOW_OPENGL);

    SDL_Renderer *sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);



    TTF_Init();
    TTF_Font * font = TTF_OpenFont("RussoOne-Regular.ttf" , 500);
    TTF_Font *font2= TTF_OpenFont("sample.ttf",500);

    int menu_map[map_y - 1][map_x - 1] = {0};
    int myscore;
    int menu_option=-1;
    char user_name[32];
    char users[128][32];
    int scores[128];
    int tmp_score=0;
//menu_option == -100 quit /0 bakht/1bord/100 random map/20 select map/30 rankings /-1 enter name/0 ya 1 main_menu
// 110 map1.txt 120 map2.txt 130 map3.txt //140 memory leak map //101 back  //2 yani memory boode va emtiaz hesab nashe
//99 random map
    while(menu_option!=-100)
    {
        if(menu_option==-1){
            menu_option =first_menu(font,sdlRenderer,colors_array,menu_map,user_name);

        } else if(menu_option==0 || menu_option==1 || menu_option==101){
            menu_option=main_menu(menu_map,sdlRenderer,font,font2,colors_array);
            myscore=menu_option;
        } else if(menu_option==110 || menu_option==120 || menu_option==130 || menu_option==140 || menu_option==99 || menu_option==170){
            menu_option=map(sdlRenderer,game_map,region_size,players,colors_array,barracks_colors_array,sdlWindow,font,&myscore);
            tmp_score=myscore;
            add_to_leaderboard(tmp_score,users,scores,user_name);
        } else if(menu_option == 20){
            menu_option=choose_map(font,sdlRenderer,colors_array,menu_map);
            myscore=menu_option;//110 ya 120 ya 130 ya 140
        }else if(menu_option == 30){
            menu_option=ranks(font,sdlRenderer,colors_array,menu_map);
        } else if(menu_option == 100){
            menu_option=choose_num(font,sdlRenderer,colors_array,menu_map,&players,&region_size);
            myscore=menu_option;
        }
    }
    SDL_DestroyWindow(sdlWindow);
    SDL_DestroyRenderer(sdlRenderer);
TTF_Quit();
SDL_Quit();
}

