
#include "map.h"

int squad_structs_counter=1;

#define deploy_radius 17


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
void draw_map(struct Regions region[],SDL_Renderer *sdlRenderer,int region_size,Uint32 colors_array[],int players,Uint32 barracks_colors_array[],int flag,struct Players player[],int game_map[][map_x])
{
    srand(time(0));
    int tmp[region_size];
    for(int i=0;i<region_size;i++){
        if(flag==1) {
            Uint32 chosen_color = colors_array[10];
            region[i].barracks_color = barracks_colors_array[10];
            if (region[i].id >= 0) {
                tmp[i] = rand() % 10;
                for (int l = 0; l < i; l++) {
                    if (tmp[l] == tmp[i]) {
                        l = -1;
                        tmp[i] = rand() % 10;
                    }
                }
                chosen_color = colors_array[tmp[i]];
                region[i].barracks_color = barracks_colors_array[tmp[i]];
                player[region[i].id].barrack_color=barracks_colors_array[tmp[i]];
            }
            region[i].color = chosen_color;
            player[region[i].id].color=chosen_color;
        }
        for(int j=1;j<map_y;j++){
            for(int k=1;k<map_x;k++){
                if(region[i].map[j][k]!=0) {
                    Sint16 x1 = (k-1) * 10;
                    Sint16 x2 = x1 + 10;
                    Sint16 y1 = (j-1) * 10;
                    Sint16 y2 = y1 + 10;
                    if(region[i].map[j+1][k]==3 || region[i].map[j-1][k]==3 || region[i].map[j][k+1]==3 || region[i].map[j][k-1]==3
                    || region[i].map[j+1][k+1]==3 || region[i].map[j-1][k-1]==3 || region[i].map[j-1][k+1]==3 || region[i].map[j+1][k-1]==3){
                        if(i!=19) {
                            boxColor(sdlRenderer, x1, y1, x2, y2, region[i].barracks_color);
                        }
                    }
                    else if(region[i].map[j][k]==1) {
                        boxColor(sdlRenderer, x1, y1, x2, y2,region[i].color);
                    }
                    else if(region[i].map[j][k]==2){
                        boxColor(sdlRenderer,x1,y1,x2,y2,colors_array[11]);
                    }
                    else{
                        if(flag==1) {
                            game_map[j][k]=100+i;
                            SDL_RenderPresent(sdlRenderer);
                        }
                        if(i!=19) {
                            boxColor(sdlRenderer, x1, y1, x2, y2, region[i].barracks_color);
                        }
                    }
                }
            }
        }
    }
}
void draw_bases(struct Regions region[],int region_size,int game_map[][map_x],SDL_Renderer *sdlRenderer)
{
    SDL_Rect rect;
    rect.h=90;
    rect.w=90;
    SDL_Surface *base_surface= IMG_Load("samg4.png");
    SDL_Texture *base_texture= SDL_CreateTextureFromSurface(sdlRenderer,base_surface);
    SDL_Surface *base_surface_me= IMG_Load("samg2.png");
    SDL_Texture *base_texture_me= SDL_CreateTextureFromSurface(sdlRenderer,base_surface_me);
    for(int i=1;i<map_y-1;i++){
        for(int j=1;j<map_x-1;j++){
            if(game_map[i][j]-100>=0 && region[game_map[i][j]-100].id>=0){
                rect.x=j*10-50;
                rect.y=i*10-50;
                if(region[game_map[i][j]-100].id==0){
                    SDL_RenderCopy(sdlRenderer,base_texture_me,NULL,&rect);
                }
                else {
                    SDL_RenderCopy(sdlRenderer, base_texture, NULL, &rect);
                }
            }
            else if(game_map[i][j]-100>=0 && region[game_map[i][j]-100].id<0){

            }
        }
    }
    SDL_FreeSurface(base_surface);
    SDL_DestroyTexture(base_texture);
    SDL_FreeSurface(base_surface_me);
    SDL_DestroyTexture(base_texture_me);
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
        region[i].is_attacking=0;
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
            region[i].soldiers = 15;
        }
        else{
            player[ctr].Regions[0]=i;
            if(region[i].id==0) {
                region[i].soldiers =  20;
            } else {
                region[i].soldiers =  20;
            }
            ctr++;
        }
    }
    for(int i=0;i<players;i++){
        if(i==0){
            player[i].rate=1;
        }
        else{
            player[i].rate=1;
        }
    }
}
void soldiers_to_string(struct Regions region[],int region_size)
{
    for(int i=0;i<region_size;i++){
        for(int j=0;j<4;j++){
            region[i].soldiers_string[j]='\0';
        }
        int tmp=region[i].soldiers;
        if(tmp==0){
            region[i].soldiers_string[0]='0';
            break;
        }
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
void print_soldiers(struct Regions region[],int region_size,SDL_Renderer *sdlRenderer1)
{
    for(int i=0;i<region_size;i++){
        stringRGBA(sdlRenderer1,region[i].center_x*10-15,region[i].center_y*10-9,region[i].soldiers_string,255,255,255,255);
    }
}
void increase_troops(struct Regions region[],int region_size,struct Players player[],int flag) {
    for (int i = 0; i < region_size; i++) {
        if (region[i].id == 0) {
            if (region[i].soldiers < 50) {
                region[i].soldiers += player[region[i].id].rate;
            }
            continue;
        }
        if (flag == 1) {
            if (region[i].id != -1) {
                if (region[i].soldiers < 49) {
                    region[i].soldiers += player[region[i].id].rate;
                } else if (region[i].soldiers == 49) {
                    region[i].soldiers++;
                }
            } else {
                if (region[i].soldiers < 14) {
                    region[i].soldiers += 2;
                } else if (region[i].soldiers == 14) {
                    region[i].soldiers++;
                }
            }
        }
    }
}
    void include_map(struct Regions region[], int game_map[][map_x], int region_size, SDL_Renderer *sdlRenderer,
                     struct Players player[], int players) {
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
    }
    void initialize_squad(struct Troops squad[], struct Regions region[], int key1, int key2) {

    int a1, b1,a2,b2,a3,b3;
        for (int i = 0; i < 64; i++) {
            if (squad[i].is_empty == 1) {
                squad[i].origin_region_index = key1;
                squad[i].player_index = region[key1].id;
                squad[i].destination_region_index = key2;
                squad[i].color = region[key1].color;
                squad[i].sum = region[key1].soldiers;
                squad[i].counter = 1;
                squad[i].is_empty = 0;
                region[key1].is_attacking=1;
                if(key1!=19){
                    region[19].is_attacking=0;
                }
                if (region[key1].center_x >= region[key2].center_x && region[key1].center_y >= region[key2].center_y) {
                    a1 = region[key1].center_x * 10 - 15;
                    b1 = region[key1].center_y * 10 - 15;
                    a2 = a1 + deploy_radius;
                    b2 = b1- deploy_radius;
                    a3 = a1 -deploy_radius;
                    b3 = b1 +deploy_radius;
                } else if (region[key1].center_x <= region[key2].center_x &&
                           region[key1].center_y >= region[key2].center_y) {
                    a1 = region[key1].center_x * 10 + 5;
                    b1 = region[key1].center_y * 10 - 15;
                    a2 = a1 + deploy_radius;
                    b2 = b1 + deploy_radius;
                    a3 = a1 - deploy_radius;
                    b3 = b1 - deploy_radius;
                } else if (region[key1].center_x <= region[key2].center_x &&
                           region[key1].center_y <= region[key2].center_y) {
                    a1 = region[key1].center_x * 10 + 5;
                    b1 = region[key1].center_y * 10 + 5;
                    a2 = a1 + deploy_radius;
                    b2 = b1-deploy_radius;
                    a3 = a1 -deploy_radius;
                    b3 = b1 +deploy_radius;
                } else if (region[key1].center_x >= region[key2].center_x &&
                           region[key1].center_y <= region[key2].center_y) {
                    a1 = region[key1].center_x * 10 - 15;
                    b1 = region[key1].center_y * 10 + 5;
                    a2 = a1 + deploy_radius;
                    b2 = b1 + deploy_radius;
                    a3 = a1 - deploy_radius;
                    b3 = b1 - deploy_radius;
                }
                for (int j = 0; j < squad[i].sum; j++) {
                    if(j%3==0) {
                        squad[i].x[j] = a1;
                        squad[i].y[j] = b1;
                    }
                    else if(j%3==1){
                        squad[i].x[j] = a2;
                        squad[i].y[j] = b2;
                    }
                    else{
                        squad[i].x[j] = a3;
                        squad[i].y[j] = b3;
                    }
                }
                break;
            }
        }
    }
    int is_in_player_center(struct Regions region[], int region_size, int x, int y, struct Players player[]) {
        for (int i = 0; i < region_size; i++) {
            if (x > region[i].center_x * 10 - 30 && x < region[i].center_x * 10 + 20 &&
                y > region[i].center_y * 10 - 30 && y < region[i].center_y * 10 + 20 && region[i].id == 0) {
                return i;
            }
        }
        return -1;
    }
    int is_in_center(struct Regions region[], int region_size, int x, int y) {
        for (int i = 0; i < region_size; i++) {
            if (x > region[i].center_x * 10 - 30 && x < region[i].center_x * 10 + 20 &&
                y > region[i].center_y * 10 - 30 && y < region[i].center_y * 10 + 20) {
                return i;
            }
        }
        return -1;
    }
    void attack_temp_func(struct Regions region[],int region_size,struct Troops squad[])
    {
        int max_index=0;
        int max=0;
        int second_index=0;
        int flag=0;
        for(int i=0;i<region_size;i++){
            if(region[i].id > 0){
                flag=1;
                if(region[i].soldiers > max && region[i].is_attacking==0){
                    second_index=max_index;
                    max=region[i].soldiers;
                    max_index=i;
                }
            }
        }
        if(flag==1) {
            srand(time(0));
            int mahjoom_index = rand() % (region_size);
            int counter = 0;
            while (mahjoom_index == max_index || region[mahjoom_index].id == region[max_index].id ||
                   region[mahjoom_index].soldiers + 5 > region[max_index].soldiers) {
                mahjoom_index = rand() %  (region_size);
                counter++;
                if (counter == 200) {
                    break;
                }
            }
            /**
             * bot age zooresh nemiresid berize too regione khodesh
             *
             */
            if (counter != 200 && region[max_index].id>0) {
                initialize_squad(squad, region, max_index, mahjoom_index);
            }
        }
    }
    void render_bulllets(struct Troops squad[],int bullet_map[][1200],SDL_Renderer *sdlRenderer)
    {
    int a=8;
        for(int i=0;i<720;i++){
            for(int j=0;j<1200;j++){
                if(bullet_map[i][j]>=0){
                    for(int k=-a;k<a+1;k++){
                        for(int l=-a;l<a+1;l++){
                            if(k==0 && l==0){
                                continue;
                            }
                            if(bullet_map[i+k][j+l]>=0 && squad[bullet_map[i+k][j+l]%100].player_index!=squad[bullet_map[i][j]%100].player_index){

                                squad[bullet_map[i+k][j+l]%100].x[bullet_map[i+k][j+l]/100]=-1;
                                squad[bullet_map[i+k][j+l]%100].y[bullet_map[i+k][j+l]/100]=-1;
                                squad[bullet_map[i][j]%100].x[bullet_map[i][j]/100]=-1;
                                squad[bullet_map[i][j]%100].y[bullet_map[i][j]/100]=-1;
                                squad[bullet_map[i][j]%100].sum--;
                                squad[bullet_map[i+k][j+l]%100].sum--;
                                bullet_map[i+k][j+l]=-2;
                                bullet_map[i][j]=-2;
                            }
                            else if(bullet_map[i+k][j+l]==-2){
                                squad[bullet_map[i][j]%100].x[bullet_map[i][j]/100]=-1;
                                squad[bullet_map[i][j]%100].y[bullet_map[i][j]/100]=-1;
                                squad[bullet_map[i][j]%100].sum--;
                                bullet_map[i][j]=-2;
                            }
                        }
                    }
                    if(bullet_map[i][j]>=0) {
                        filledCircleColor(sdlRenderer, j, i, 8, 0xff000000);
                        filledCircleColor(sdlRenderer, j, i, 6,
                                          squad[bullet_map[i][j] % 100].color);
                    }
                }
            }
        }
    }

    const int FPS = 45;
int map(SDL_Renderer *sdlRenderer, int game_map[][map_x], int region_size, int players, Uint32 colors_array[],
            Uint32 barracks_colors_array[], SDL_Window *sdlWindow) {
    struct Troops squad[64];
    struct Players player[players];
    struct Regions region[region_size];
    int bullet_map[720][1200];
    include_map(region, game_map, region_size, sdlRenderer, player, players);
    draw_map(region, sdlRenderer, region_size, colors_array, players, barracks_colors_array, 1, player, game_map);
    draw_bases(region, region_size, game_map, sdlRenderer);
    set_soldiers_and_rate(region, region_size, player, players);
    soldiers_to_string(region, region_size);
    print_soldiers(region, region_size, sdlRenderer);
    SDL_RenderPresent(sdlRenderer);
    SDL_bool shallExit = SDL_FALSE;
    int counter = 1;
    int parcham = 0;
    int flag = 0, key1, key2;
    int clicked = 0;
    int x, y;
    srand(time(0));
    int Vo;
    int tmp = rand() % 200;
    while (shallExit == SDL_FALSE) {
        for(int i=0;i<720;i++){
            for(int j=0;j<1200;j++){
                bullet_map[i][j]=-1;
            }
        }
        if (counter == tmp) {
            counter = 0;
            attack_temp_func(region, region_size, squad);
            tmp = rand() % 200;
        }
        if (counter % 40 == 0) {
            SDL_SetRenderDrawColor(sdlRenderer, 0x1E, 0x00, 0x1E, 0xf0);//0xf01e001e
            SDL_RenderClear(sdlRenderer);
            increase_troops(region, region_size, player, 1);

            draw_map(region, sdlRenderer, region_size, colors_array, players, barracks_colors_array, 0, player,
                     game_map);
            draw_bases(region, region_size, game_map, sdlRenderer);
            soldiers_to_string(region, region_size);
            print_soldiers(region, region_size, sdlRenderer);
            SDL_RenderPresent(sdlRenderer);
        }
        SDL_SetRenderDrawColor(sdlRenderer, 0x1E, 0x00, 0x1E, 0xf0);//0xf01e001e
        SDL_RenderClear(sdlRenderer);
        draw_map(region, sdlRenderer, region_size, colors_array, players, barracks_colors_array, 0, player, game_map);
        draw_bases(region, region_size, game_map, sdlRenderer);

        for (int i = 0; i < 64; i++) {
            if (squad[i].is_empty == 0) {
                for (int j = 0; j < squad[i].counter; j++) {
                    parcham = 0;
                    if (squad[i].x[j] != -1) {
                        if (bullet_map[squad[i].y[j]][squad[i].x[j]] == -1) {
                            bullet_map[squad[i].y[j]][squad[i].x[j]] = j * 100 + i;
                        }
                        /*filledCircleColor(sdlRenderer, squad[i].x[j], squad[i].y[j], 7, 0xff000000);
                        filledCircleColor(sdlRenderer, squad[i].x[j], squad[i].y[j], 5,
                                          squad[i].color);
                        */
                        if (squad[i].counter < squad[i].sum) {
                            Vo = 10;
                        } else {
                            Vo = 10;
                        }
                        if (j % 3 == 0) {
                            squad[i].Vx = Vo * ((region[squad[i].destination_region_index].center_x * 10 - 5 -
                                                 squad[i].x[j]) /
                                                (sqrt(pow((region[squad[i].destination_region_index].center_x * 10 - 5 -
                                                           squad[i].x[j]), 2) +
                                                      pow((region[squad[i].destination_region_index].center_y * 10 - 5 -
                                                           squad[i].y[j]), 2))));
                            squad[i].Vy = Vo * ((region[squad[i].destination_region_index].center_y * 10 - 5 -
                                                 squad[i].y[j]) /
                                                (sqrt(pow((region[squad[i].destination_region_index].center_x * 10 - 5 -
                                                           squad[i].x[j]), 2) +
                                                      pow((region[squad[i].destination_region_index].center_y * 10 - 5 -
                                                           squad[i].y[j]), 2))));
                        }
                        squad[i].x[j] += squad[i].Vx;
                        squad[i].y[j] += squad[i].Vy;
                        parcham = 1;
                    }
                    if (squad[i].x[j] <= region[squad[i].destination_region_index].center_x * 10 + 40 &&
                            squad[i].x[j] >= region[squad[i].destination_region_index].center_x * 10 - 50 &&
                            squad[i].y[j] <= region[squad[i].destination_region_index].center_y * 10 + 40 &&
                            squad[i].y[j] >= region[squad[i].destination_region_index].center_y * 10 - 50) {
                        squad[i].x[j] = -1;
                        squad[i].y[j] = -1;

                        if (region[squad[i].destination_region_index].soldiers > 0 &&
                            region[squad[i].destination_region_index].id != squad[i].player_index) {
                            region[squad[i].destination_region_index].soldiers--;
                        } else {
                            region[squad[i].destination_region_index].id = squad[i].player_index;
                            region[squad[i].destination_region_index].color = player[squad[i].player_index].color;
                            region[squad[i].destination_region_index].barracks_color = player[squad[i].player_index].barrack_color;
                            region[squad[i].destination_region_index].soldiers++;
                        }
                        continue;
                    }

                }
                if (squad[i].counter < squad[i].sum && region[squad[i].origin_region_index].soldiers > 0) {
                    region[squad[i].origin_region_index].soldiers--;
                    squad[i].counter++;
                    if (squad[i].counter == squad[i].sum) {
                        region[squad[i].origin_region_index].soldiers--;
                    }
                }


                if (parcham == 0) {

                    region[squad[i].origin_region_index].is_attacking = 0;
                    squad[i].is_empty = 1;
                }
            }
        }

        soldiers_to_string(region, region_size);
        print_soldiers(region, region_size, sdlRenderer);
        render_bulllets(squad,bullet_map,sdlRenderer);
        SDL_RenderPresent(sdlRenderer);

        SDL_Delay(1000 / FPS);
        SDL_Event sdlEvent;
        while (SDL_PollEvent(&sdlEvent)) {

            if (SDL_QUIT == sdlEvent.type) {
                shallExit = SDL_TRUE;
            } else if (sdlEvent.type == SDL_MOUSEBUTTONDOWN && sdlEvent.button.button == SDL_BUTTON_LEFT) {
                x = sdlEvent.motion.x;
                y = sdlEvent.motion.y;
                key1 = is_in_player_center(region, region_size, x, y, player);
                if (key1 > -1 && region[key1].is_attacking == 0) {
                    clicked = 1;
                }
            } else if (sdlEvent.type == SDL_MOUSEBUTTONUP && clicked == 1) {
                x = sdlEvent.motion.x;
                y = sdlEvent.motion.y;
                clicked = 0;
                key2 = is_in_center(region, region_size, x, y);
                if (key2 > -1 && key1 != key2 && region[key1].id==0 && region[key2].soldiers<=500) {
                    initialize_squad(squad, region, key1, key2);
                }
            }
        }
        counter++;
    }
    return 0;
}
