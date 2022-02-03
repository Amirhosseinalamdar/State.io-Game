#include<stdio.h>
#include<stdbool.h>
#include<SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <time.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include <math.h>
#define radius 5
#define radius2 5
#define bases 20
#define screenW 1200 //120
#define screenH 720 //72
#define map_y 74
#define map_x 122
#define chanta_harif 5
#define color_size 10
#define menu 8
//abgr
//har region max 80 khoone

struct Regions{
    int id;  //  -1 default   ....players indexes
    int map[map_y][map_x];// 0 khali 1 vasta 2 border 3 centre
    int num_of_boxes;
    int center_x,center_y;
    Uint32 color;
};

struct Players{
    int Regions[bases];
    Uint32 color;
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
void draw_map(struct Regions region[],SDL_Renderer *sdlRenderer,int region_size,Uint32 colors_array[],int players)
{
    srand(time(0));
    for(int i=0;i<region_size;i++){
        Uint32 chosen_color = colors_array[10];
        if (region[i].id>=0) {
            chosen_color = colors_array[rand() % 10];
        }
        region[i].color = chosen_color;
        for(int j=1;j<map_y;j++){
            for(int k=1;k<map_x;k++){
                if(region[i].map[j][k]!=0) {
                    Sint16 x1 = (k-1) * 10;
                    Sint16 x2 = x1 + 10;
                    Sint16 y1 = (j-1) * 10;
                    Sint16 y2 = y1 + 10;
                    if(region[i].map[j][k]==1) {
                        boxColor(sdlRenderer, x1, y1, x2, y2,region[i].color);
                    }
                    else if(region[i].map[j][k]==2){
                        boxColor(sdlRenderer,x1,y1,x2,y2,colors_array[11]);
                    }
                    else{
                        boxColor(sdlRenderer,x1,y1,x2,y2,colors_array[11]);
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
void draw_menu(Uint32 colors_array[],SDL_Renderer *sdlRenderer,int flag,int menu_map[][map_x-1])
{
    int tmp;
    Uint32 color2,color1;
    if(flag==1) {
        color1 = 0xff3C3A40;
        color2 = 0xff5635B0;
    }
    else{
        color1 = 0xcc3C3A40;
        color2 = 0xcc5635B0;
    }
    srand(time(0));
    for(int i=1;i<map_y-1;i+=menu){
        for(int j=1;j<map_x-1;j+=menu){
            Sint16 x1 = (j-1) * 10;
            Sint16 x2 = x1 + menu*10;
            Sint16 y1 = (i-1) * 10;
            Sint16 y2 = y1 + menu*10;
            if(menu_map[i][j]==0) {
                tmp=rand()%2;
                if (tmp == 0) {
                    boxColor(sdlRenderer, x1, y1, x2, y2, color1);
                    menu_map[i][j] = 1;
                } else {
                    boxColor(sdlRenderer, x1, y1, x2, y2, color2);
                    menu_map[i][j] = 2;
                }
            }
            else {
                if(menu_map[i][j]==1){
                    boxColor(sdlRenderer, x1, y1, x2, y2, color1);
                }
                else{
                    boxColor(sdlRenderer, x1, y1, x2, y2, color2);
                }
            }

        }
    }
}

void include_welcome_enter(TTF_Font *font,SDL_Renderer *sdlRenderer)
{
    SDL_Color main_title_color = {0x1E, 0x00, 0x1E, 0xff};

    SDL_Rect main_title_rect = {300 , 30, 600, 200};
    SDL_Surface *title_surface = TTF_RenderText_Solid(font, "Welcome!", main_title_color);
    SDL_Texture *title_texture = SDL_CreateTextureFromSurface(sdlRenderer, title_surface);
    SDL_RenderCopy(sdlRenderer,title_texture,NULL,&main_title_rect);
    SDL_FreeSurface(title_surface);
    SDL_DestroyTexture(title_texture);
    SDL_Rect enter_user_name_rect={280,250,640,100};
    SDL_Surface *enter_user_name_surface= TTF_RenderText_Solid(font,"Enter your name:",main_title_color);
    SDL_Texture *enter_user_name_texture= SDL_CreateTextureFromSurface(sdlRenderer,enter_user_name_surface);
    SDL_RenderCopy(sdlRenderer,enter_user_name_texture,NULL,&enter_user_name_rect);
    SDL_FreeSurface(enter_user_name_surface);
    SDL_DestroyTexture(enter_user_name_texture);
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
    Uint32 colors_array[12]={0xffffffff,0xffffff00,0xffff0000,0xff000000,0xffff00ff,0xff00ffff,0xff00ff00,0xff0000ff,0xffabcdef,0xffabbcda,0xff3C3A40,0xff5635B0}; //def  //border

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




//case e mouse state edit shavad

    SDL_Color main_title_color = {0x1E, 0x00, 0x1E, 0xff};
    //entering_user_name
    SDL_Rect user_name_background_rect={350,400,500,100};
    SDL_Color user_name_color={0xB0,0x35,0x56,0xff};
    SDL_Rect user_name_string_rect={360,425,0,60};
    SDL_Rect continue_button={890,415,70,70};

    SDL_Surface *button_surface= TTF_RenderText_Solid(font,"OK",main_title_color);
    SDL_Texture *button_texture= SDL_CreateTextureFromSurface(sdlRenderer,button_surface);

    int menu_map[map_y-1][map_x-1]={0};
    int menu_option = 0;
    int close=0;
    SDL_bool shallExit;
    //0xff5635B0
    char user_name[32];
    for(int i=0;i<32;i++){user_name[i]='\0';}
    char input='\0';


    SDL_Surface *user_name_surface= TTF_RenderText_Solid(font,user_name,user_name_color);
    SDL_Texture *user_name_texture= SDL_CreateTextureFromSurface(sdlRenderer,user_name_surface);
    SDL_FreeSurface(user_name_surface);
    SDL_DestroyTexture(user_name_texture);
    SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0x00, 0x00, 0x00);
    SDL_RenderClear(sdlRenderer);
    draw_menu(colors_array,sdlRenderer,0,menu_map);
    include_welcome_enter(font,sdlRenderer);

    SDL_SetRenderDrawColor(sdlRenderer,0x1e,0x00,0x1e,255);
    SDL_RenderFillRect(sdlRenderer,&user_name_background_rect);

    SDL_RenderCopy(sdlRenderer,user_name_texture,NULL,&user_name_string_rect);
    SDL_FreeSurface(user_name_surface);
    SDL_DestroyTexture(user_name_texture);

    SDL_SetRenderDrawColor(sdlRenderer,0xB0,0x35,0x56,255);
    SDL_RenderDrawRect(sdlRenderer,&user_name_background_rect);

    /*SDL_SetRenderDrawColor(sdlRenderer,0xB0,0x35,0x56,255);
    SDL_RenderFillRect(sdlRenderer,&continue_button);
    SDL_SetRenderDrawColor(sdlRenderer,0x1e,0x00,0x1e,255);
    SDL_RenderDrawRect(sdlRenderer,&continue_button);
    SDL_RenderCopy(sdlRenderer,button_texture,NULL,&continue_button);
    SDL_FreeSurface(button_surface);
    SDL_DestroyTexture(button_texture);*/

    SDL_RenderPresent(sdlRenderer);
    SDL_bool done=SDL_FALSE;
    int mouse_x,mouse_y;
    while (!done) {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    done = SDL_TRUE;
                    close=1;
                    break;
                case SDL_KEYDOWN:

                    input=event.key.keysym.sym;
                    if(input==SDLK_RETURN && strlen(user_name)>0){
                        done=SDL_TRUE;
                    }
                    else if(input==SDLK_BACKSPACE && strlen(user_name)>0){
                        user_name[strlen(user_name)-1]='\0';
                        user_name_string_rect.w= strlen(user_name)*20;
                    }
                    else if(strlen(user_name)==24){
                    }
                    else if((input==SDLK_BACKSPACE && strlen(user_name)==0) || input<48 || input>122 || (input<97 && input>90) || (input<65 && input>57)){
                        if(input=='.' || input==' ') {
                            user_name[strlen(user_name)] = input;
                            user_name_string_rect.w = 20 * strlen(user_name);
                        }
                    }
                    else{
                        user_name[strlen(user_name)]=input;
                        user_name_string_rect.w=20* strlen(user_name);
                    }

                    SDL_SetRenderDrawColor(sdlRenderer,0x1e,0x00,0x1e,255);
                    SDL_RenderFillRect(sdlRenderer,&user_name_background_rect);
                    SDL_Surface *user_name_surface= TTF_RenderText_Solid(font,user_name,user_name_color);
                    SDL_Texture *user_name_texture= SDL_CreateTextureFromSurface(sdlRenderer,user_name_surface);
                    SDL_RenderCopy(sdlRenderer,user_name_texture,NULL,&user_name_string_rect);
                    SDL_FreeSurface(user_name_surface);
                    SDL_DestroyTexture(user_name_texture);
                    SDL_SetRenderDrawColor(sdlRenderer,0xB0,0x35,0x56,255);
                    SDL_RenderDrawRect(sdlRenderer,&user_name_background_rect);

                    if(strlen(user_name)>0) {
                        SDL_SetRenderDrawColor(sdlRenderer, 0xB0, 0x35, 0x56, 255);
                        SDL_RenderFillRect(sdlRenderer, &continue_button);
                        SDL_SetRenderDrawColor(sdlRenderer, 0x1e, 0x00, 0x1e, 255);
                        SDL_RenderDrawRect(sdlRenderer, &continue_button);
                        SDL_Surface *button_surface = TTF_RenderText_Solid(font, "OK", main_title_color);
                        SDL_Texture *button_texture = SDL_CreateTextureFromSurface(sdlRenderer, button_surface);
                        SDL_RenderCopy(sdlRenderer, button_texture, NULL, &continue_button);
                        SDL_FreeSurface(button_surface);
                        SDL_DestroyTexture(button_texture);
                    }
                    else{
                        SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0x00, 0x00, 0x00);
                        SDL_RenderClear(sdlRenderer);
                        draw_menu(colors_array,sdlRenderer,0,menu_map);
                        include_welcome_enter(font,sdlRenderer);

                        SDL_SetRenderDrawColor(sdlRenderer,0x1e,0x00,0x1e,255);
                        SDL_RenderFillRect(sdlRenderer,&user_name_background_rect);
                        SDL_Surface *user_name_surface= TTF_RenderText_Solid(font,user_name,user_name_color);
                        SDL_Texture *user_name_texture= SDL_CreateTextureFromSurface(sdlRenderer,user_name_surface);
                        SDL_RenderCopy(sdlRenderer,user_name_texture,NULL,&user_name_string_rect);
                        SDL_FreeSurface(user_name_surface);
                        SDL_DestroyTexture(user_name_texture);
                        SDL_SetRenderDrawColor(sdlRenderer,0xB0,0x35,0x56,255);
                        SDL_RenderDrawRect(sdlRenderer,&user_name_background_rect);
                    }

                    SDL_RenderPresent(sdlRenderer);
                    break;

                /*case SDL_MOUSEMOTION:
                    SDL_GetGlobalMouseState(&mouse_x,&mouse_y);
                    if(mouse_x>890 && mouse_x<960 && mouse_y>415 && mouse_y<485){
                        continue_button.x=880;
                        continue_button.y=880;
                        continue_button.w=90;
                        continue_button.h=90;
                    }
                    break;*/

                case SDL_MOUSEBUTTONDOWN:
                    mouse_y=event.motion.y;
                    mouse_x=event.motion.x;
                    if(mouse_x>890 && mouse_x<960 && mouse_y>415 && mouse_y<485 && strlen(user_name)>0){
                        done=SDL_TRUE;
                    }
                    break;
            }
        }
    }




if(close==0) {

    SDL_Color text_color = {0x1E, 0x00, 0x1E, 0xff};
    SDL_Rect text_rect = {20, 10, 300, 100};
    SDL_Surface *surface = TTF_RenderText_Solid(font2, "State.io", text_color);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(sdlRenderer, surface);

    SDL_RenderClear(sdlRenderer);
    draw_menu(colors_array, sdlRenderer, 1, menu_map);
    SDL_RenderCopy(sdlRenderer, texture, NULL, &text_rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);


    text_rect.x = 150, text_rect.y = 180;
    text_rect.w = 400, text_rect.h = 150;
    SDL_Surface *surface1 = TTF_RenderText_Solid(font, "New map", text_color);
    SDL_Texture *texture1 = SDL_CreateTextureFromSurface(sdlRenderer, surface1);
    SDL_RenderCopy(sdlRenderer, texture1, NULL, &text_rect);
    SDL_DestroyTexture(texture1);
    SDL_FreeSurface(surface1);

    text_rect.x = 650, text_rect.y = 180;
    text_rect.w = 400, text_rect.h = 150;
    SDL_Surface *surface2 = TTF_RenderText_Solid(font, "Select map", text_color);
    SDL_Texture *texture2 = SDL_CreateTextureFromSurface(sdlRenderer, surface2);
    SDL_RenderCopy(sdlRenderer, texture2, NULL, &text_rect);
    SDL_DestroyTexture(texture2);
    SDL_FreeSurface(surface2);

    text_rect.x = 450, text_rect.y = 500;
    text_rect.w = 300, text_rect.h = 100;
    SDL_Surface *surface3 = TTF_RenderText_Solid(font, "Rankings", text_color);
    SDL_Texture *texture3 = SDL_CreateTextureFromSurface(sdlRenderer, surface3);
    SDL_RenderCopy(sdlRenderer, texture3, NULL, &text_rect);
    SDL_DestroyTexture(texture3);
    SDL_FreeSurface(surface3);

    SDL_RenderPresent(sdlRenderer);

    SDL_bool shallExit = SDL_FALSE;
    int x, y;
    while (shallExit == SDL_FALSE) {

        SDL_Delay(30000 / FPS);
        SDL_Event sdlEvent;
        while (SDL_PollEvent(&sdlEvent)) {
            switch (sdlEvent.type) {
                case SDL_QUIT:
                    shallExit = SDL_TRUE;
                    break;
                case SDL_MOUSEMOTION:
                    x = sdlEvent.motion.x;
                    y = sdlEvent.motion.y;
                    if (x > 150 && x < 550 && y > 180 && y < 330) {

                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    x = sdlEvent.motion.x;
                    y = sdlEvent.motion.y;
                    if (x > 150 && x < 550 && y > 180 && y < 330) {
                        shallExit = SDL_TRUE;
                        menu_option = 1;
                    } else if (x > 650 && x < 1050 && y > 180 && y < 330) {
                        shallExit = SDL_TRUE;
                        menu_option = 2;
                    } else if (x > 450 && x < 750 && y > 500 && y < 600) {
                        shallExit = SDL_TRUE;
                        menu_option = 3;
                    }
                    break;
            }

        }
    }
}
    if(menu_option==1) {

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
        draw_map(region, sdlRenderer, region_size, colors_array, players);
        SDL_RenderPresent(sdlRenderer);

        shallExit = SDL_FALSE;
        while (shallExit == SDL_FALSE) {
            SDL_Delay(300 / FPS);
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

