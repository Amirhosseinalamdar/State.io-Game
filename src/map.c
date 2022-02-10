
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
        if(flag==2){
            region[i].color=colors_array[region[i].id];
            region[i].barracks_color=barracks_colors_array[region[i].id];
            if(i==0) {
                player[1].color = region[i].color;
                player[1].barrack_color = region[i].barracks_color;
            } else{
                player[0].color = region[i].color;
                player[0].barrack_color = region[i].barracks_color;
            }

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

                        boxColor(sdlRenderer, x1, y1, x2, y2, region[i].barracks_color);

                    }
                    else if(region[i].map[j][k]==1) {
                        boxColor(sdlRenderer, x1, y1, x2, y2,region[i].color);
                    }
                    else if(region[i].map[j][k]==2){
                        boxColor(sdlRenderer,x1,y1,x2,y2,colors_array[11]);
                    }
                    else{
                        if(flag==1 || flag==2) {
                            game_map[j][k]=100+i;
                            //SDL_RenderPresent(sdlRenderer);
                            boxColor(sdlRenderer, x1, y1, x2, y2, region[i].barracks_color);
                        }

                        boxColor(sdlRenderer, x1, y1, x2, y2, region[i].barracks_color);
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
            if(flag == 1 || (flag==0 && player[region[i].id].rate==10)) {
                if (region[i].id >= 0 && region[i].soldiers < 50) {
                    region[i].soldiers++;
                } else if (region[i].id == -1 && region[i].soldiers < 15) {
                    region[i].soldiers++;
                }
            }
        }
}

    void include_map(struct Regions region[], int game_map[][map_x], int region_size, SDL_Renderer *sdlRenderer,
                     struct Players player[], int players,int a[][5],int b[][map_y][map_x],int c[][map_x]) {
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

        for(int i=0;i<region_size;i++) {
            for (int j = 0; j < map_y; j++) {
                for (int k = 0; k < map_x; k++) {
                    b[i][j][k]=region[i].map[j][k];
                    if(i==0){
                        c[j][k]=game_map[j][k];
                    }
                }
            }
            a[i][0]=region[i].id;
            a[i][1]=region[i].center_y;
            a[i][2]=region[i].center_x;
            a[i][3]=region[i].num_of_boxes;
            a[i][4]=region[i].is_attacking;
        }
        /*
        FILE *fptr= fopen("map1.txt","w");
        fprintf(fptr,"%d\n",region_size);
        fprintf(fptr,"%d\n",players);
        for(int i=0;i<region_size;i++){
            for(int j=0;j<map_y;j++){
                for(int k=0;k<map_x;k++){
                    fprintf(fptr," %d ",region[i].map[j][k]);
                    if(i==0) {
                        fprintf(fptr, " %d ", game_map[j][k]);
                    }
                }
            }
            fprintf(fptr," %d %d %d %d %d\n",region[i].id,region[i].center_y,region[i].center_x,region[i].num_of_boxes,region[i].is_attacking);


            //fprintf(fptr," %d %d %d ",region[i].soldiers,region[i].num_of_boxes,region[i].damage);
            //fprintf(fptr," %d %d %d \n",region[i].is_attacking,region[i].barracks_color,region[i].color);
        }
        fclose(fptr);*/
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
                if(key1==19){
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
                        squad[i].dx[0]=a1-region[squad[i].origin_region_index].center_x*10;
                        squad[i].dy[0]=b1-region[squad[i].origin_region_index].center_y*10;
                    }
                    else if(j%3==1){
                        squad[i].x[j] = a2;
                        squad[i].y[j] = b2;
                        squad[i].dx[1]=a1-region[squad[i].origin_region_index].center_x*10;
                        squad[i].dy[1]=b1-region[squad[i].origin_region_index].center_y*10;
                    }
                    else{
                        squad[i].x[j] = a3;
                        squad[i].y[j] = b3;
                        squad[i].dx[2]=a1-region[squad[i].origin_region_index].center_x*10;
                        squad[i].dy[2]=b1-region[squad[i].origin_region_index].center_y*10;
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
    int distance_from_center(int x1,int y1,int x2,int y2,int a,int b)
    {
        int m=(y2-y1)/(x2-x1);
        return abs(b-a*m + x1*m - y1)/sqrt(1+ m*m);
    }
int mahjoom_index;
int max_index=0;
    void attack_temp_func(struct Regions region[],int region_size,struct Troops squad[],struct Potion potion[])
    {

        int max=0;
        int distance=0;

        int second_index=0;
        int flag=0,flag2=0;
        /*for(int i=0;i<region_size;i++) {
            for (int j = 0; j < potion_size; j++) {
                if (potion[j].is_active == 1 && potion[j].time > 50 && region[i].id > 0) {
                    for (int k = 0; k < region_size; k++) {
                        if (region[i].center_x != region[k].center_x) {
                            distance = distance_from_center(region[i].center_x, region[i].center_y, region[k].center_x,
                                                            region[k].center_y, potion[j].center_x, potion[j].center_y);
                            int d1=pow(region[i].center_x - region[k].center_x,2)+pow(region[i].center_y - region[k].center_y,2);
                            int x1=region[i].center_x+region[k].center_x/2;
                            int y1=region[i].center_y+region[k].center_y/2;
                            int d2=pow(potion[j].center_x - x1,2)+pow(potion[j].center_y - y1,2);
                            int boolam= d1/4 > d2;

                            if (distance < potion[j].potion_radius && boolam) {
                                if (i != max_index && k != mahjoom_index && region[i].soldiers > region[k].soldiers) {
                                    max_index = i;
                                    mahjoom_index = k;
                                    flag2 = 1;
                                    printf("man boodamm \n");
                                    break;
                                }
                            }
                        }
                    }
                    if (flag2 == 1) {
                        break;
                    }
                }
            }
            if (flag2 == 1) {
                break;}
        }*/
        for(int i=0;i<region_size;i++) {
            if (region[i].id > 0 && flag2 == 0) {
                flag = 1;
                if (region[i].soldiers > max && region[i].is_attacking == 0) {
                    max = region[i].soldiers;
                    max_index = i;
                }
            }
        }

        if(flag2==1){
            initialize_squad(squad, region, max_index, mahjoom_index);
        }
        else if(flag==1)  {
            srand(time(0));
            mahjoom_index = rand() % (region_size);
            int counter = 0;
            while (mahjoom_index == max_index || region[mahjoom_index].id == region[max_index].id ||
                   region[mahjoom_index].soldiers + 5 > region[max_index].soldiers) {
                mahjoom_index = rand() %  (region_size);
                counter++;
                if (counter == 40) {
                    break;
                }
            }
             if(counter==40){
                 counter=0;
                 while(mahjoom_index == max_index || region[mahjoom_index].id != region[max_index].id){
                     mahjoom_index = rand() %  (region_size);
                     counter++;
                     if(counter == 40){
                         break;
                     }
                 }
             }
            if (counter != 40 && region[max_index].id>0) {
                initialize_squad(squad, region, max_index, mahjoom_index);
            }
        }
    }


    void check_soldier_position(struct Troops squad[],int key,int x_pos,int y_pos,struct Potion potion[],struct Players player[])
    {
        int a=10;
        int distance=0;
        for(int i=0;i<potion_size;i++){
            if(potion[i].is_active==1  &&  player[potion[i].player_index].potion_effect==0){
                distance=pow((squad[key].x[x_pos]-potion[i].center_x),2)+pow((squad[key].y[y_pos]-potion[i].center_y),2);
                if(distance < potion[i].potion_radius * potion[i].potion_radius){
                    potion[i].is_active=0;
                    potion[i].is_active_on_player=1;
                    potion[i].player_time=360;
                    potion[i].player_index=squad[key].player_index;
                    player[potion[i].player_index].potion_effect=1;
                    break;
                }
            }
        }
        for(int i=0;i<64;i++){
            if(i==key || squad[i].player_index==squad[key].player_index){continue;}
            if(squad[i].is_empty==0){
                for(int j=0;j<squad[i].counter;j++){
                    if(squad[i].x[j]>0) {
                        distance = pow((squad[i].x[j]-squad[key].x[x_pos]), 2)+pow((squad[i].y[j]-squad[key].y[x_pos]), 2);
                        if(distance<a*a){
                            squad[i].x[j]=-1;
                            squad[i].y[j]=-1;
                            squad[key].x[x_pos]=-1;
                            squad[key].y[y_pos]=-1;
                        }
                    }
                    /*else if (squad[i].y[j]<-1){
                        distance = pow((squad[i].x[j]+squad[key].x[x_pos]), 2)+pow((squad[i].y[j]+squad[key].y[x_pos]), 2);
                        if(distance<a*a){
                            squad[key].x[x_pos]*=-1;
                            squad[key].y[y_pos]*=-1;
                        }
                    }*/
                }
            }
        }
    }

int check_game_state(struct Regions region[],int region_size,struct Troops squad[])
{
    int flag=0,flag2=0;
    for(int i=0;i<region_size;i++){
        if(region[i].id==0){
            flag=1;
        } else if(region[i].id>0){
            flag2=1;
        }
    }
    if(flag2==0){
        /*for(int i=0;i<64;i++){
            if(squad[i].player_index>0){
                return -1;
            }
        }*/
        return 1;
    }else if(flag==0){
        /*for(int i=0;i<64;i++){
            if(squad[i].player_index==0){
                return -1;
            }
        }*/
        return 0;
    } else{
        return -1;
    }
}
void set_potion_struct(struct Potion potion[])
{
    for(int i=0;i<potion_size;i++){
        potion[i].is_active=0;
        potion[i].time=240;
        potion[i].time2=0;
        potion[i].is_active_on_player=0;
    }
}
void initialize_potion(struct Potion potion[],Uint32 potion_colors[],Uint32 potion_border_colors[],Uint32 potion_base_color[])
{
    int tmp;
    int distance=0;
    srand(time(0));
    for(int i=0;i<potion_size;i++){
        if(potion[i].is_active==0 && potion[i].is_active_on_player==0) {
            potion[i].center_x = rand() % (1200 - 2 * potion_border_distance) + potion_border_distance;
            potion[i].center_y = rand() % (720 - 2 * potion_border_distance) + potion_border_distance;
            potion[i].potion_radius = rand()%potion_radius_dif+potion_radius_in;
            for(int j=0;j<potion_size;j++){
                if(potion[j].is_active==1){
                    distance=pow((potion[i].center_x-potion[j].center_x),2)+pow((potion[i].center_y-potion[j].center_y),2);
                    while(potion[i].potion_radius + potion[j].potion_radius > sqrt(distance)){
                        potion[i].center_x = rand() % (1200 - 2 * potion_border_distance) + potion_border_distance;
                        potion[i].center_y = rand() % (720 - 2 * potion_border_distance) + potion_border_distance;
                        distance=pow((potion[i].center_x-potion[j].center_x),2)+pow((potion[i].center_y-potion[j].center_y),2);
                    }
                }
            }
            tmp = rand() % 4 + 1;
            potion[i].potion_type = tmp;
            potion[i].color = potion_colors[tmp-1];
            potion[i].border_color=potion_border_colors[tmp-1];
            potion[i].base_color=potion_base_color[tmp-1];
            potion[i].time2=60;
            potion[i].time=0;
            potion[i].player_time=0;
            break;
        }
    }
}
void update_potion(struct Potion potion[],struct Players player[])
{
    for(int i=0;i<potion_size;i++){
        if(potion[i].is_active_on_player==1){
            potion[i].player_time--;
            if(potion[i].player_time==0){
                potion[i].is_active_on_player=0;
                potion[i].damage=0;
                potion[i].player_time=360;
                player[potion[i].player_index].potion_effect=0;
            }
        }
        else if(potion[i].is_active==1){
            potion[i].time--;
            if(potion[i].time==0){
                potion[i].is_active=0;
                potion[i].time=240;
                potion[i].time2=60;
            }
        }
        else if(potion[i].is_active==0 && potion[i].time2>0){
                potion[i].time2--;
            if(potion[i].time2==0){
                potion[i].is_active=1;
                potion[i].time=240;
            }
        }
    }
}
void draw_potions(struct Potion potion[],SDL_Renderer *sdlRenderer)
{
    int r;
    for(int i=0;i<potion_size;i++){
        if(potion[i].is_active==1 || (potion[i].is_active==0 && potion[i].time2>0)){
            if(potion[i].time2 == 0) {
                filledCircleColor(sdlRenderer, potion[i].center_x, potion[i].center_y, potion[i].potion_radius,
                                  potion[i].color);
            }
            r=potion[i].potion_radius;
            aacircleColor(sdlRenderer, potion[i].center_x, potion[i].center_y, r+1,
                          potion[i].border_color);
            aacircleColor(sdlRenderer, potion[i].center_x, potion[i].center_y, r-1,
                          potion[i].border_color);
            while(r>0) {
                aacircleColor(sdlRenderer, potion[i].center_x, potion[i].center_y, r,
                              potion[i].border_color);
                r-=20;
            }

        }
    }
}
void set_regions_speed(struct Regions region[],int region_size,struct Players player[])
{
    for(int i=0;i<region_size;i++){
        region[i].Vo=10;
        region[i].damage=2;
        region[i].khafan=-1;
        if(region[i].id >= 0){
            player[region[i].id].rate=1;
        }
    }
}
void activate_potion(struct Regions region[],struct Potion potion[],int region_size,struct Players player[])
{
    for(int i=0;i<potion_size;i++){
        if(potion[i].is_active_on_player==1 && potion[i].is_active==0){
            for(int j=0;j<region_size;j++){
                if(potion[i].player_index==region[j].id){
                    if(potion[i].potion_type == 1){
                        region[j].Vo=20;
                    }
                    else if(potion[i].potion_type == 2) {
                        if(potion[i].damage!=0){
                            region[j].damage=potion[i].damage;
                        }else {
                            if (rand() % 2 == 1) {
                                region[j].damage = 1;
                                potion[i].damage=1;
                            } else {
                                region[j].damage = 4;
                                potion[i].damage = 4;
                            }
                        }
                    } else if(potion[i].potion_type == 3){
                        player[region[j].id].rate=10;
                    } else if( potion[i].potion_type == 4){
                        region[j].khafan=1;
                    }
                }
            }
        }
    }
}
int score(int state,int time_0)
{
        int time = SDL_GetTicks() - time_0;
        if(state==1){
            if(700 - time * 10 / 18000 > 350) {
                return 700 - time * 10 / 18000;
            }
            else{
                return 351;
            }
        } else if(state == 0){
            if(time * 10 /18000 < 350) {
                return time * 10 / 6000;
            }else {
                return 349;
            }
        }
}
void score_to_string(int score,char score_string[])
{
        for(int k=0;k<1;k++) {
            for (int j = 0; j < 4; j++) {
                score_string[j] = '\0';
            }
            int tmp = score;
            if (tmp == 0) {
                score_string[0] = '0';
                break;
            }
            int n = tmp;
            int ctr = 0;
            int digit;
            while (tmp != 0) {
                tmp /= 10;
                ctr++;
            }
            while (ctr != 0) {
                digit = n % 10;
                n /= 10;
                score_string[ctr - 1] = digit + '0';
                ctr--;
            }
        }
}
void set_leak_map(struct Regions region[],struct Players player[],int region_size,int players)
{
    for(int i=0;i<region_size;i++){
        if(i==0){
            region[i].id=1;
            region[i].soldiers=20;
            region[i].is_attacking=0;
        }else{
            region[i].id=0;
            region[i].soldiers=20;
            region[i].is_attacking=0;
        }
    }
}
void draw_potion_effect(struct Regions region[],struct Players player[],struct Potion potion[],int region_size,SDL_Renderer *sdlRenderer)
{
        for(int i=0;i<4;i++){
            if(potion[i].is_active_on_player==1 && potion[i].is_active==0){
                for(int j=0;j<region_size;j++) {
                    if(region[j].id==potion[i].player_index) {
                        aacircleColor(sdlRenderer, region[j].center_x * 10 - 5, region[j].center_y * 10, 50,
                                      potion[i].border_color);
                        aacircleColor(sdlRenderer, region[j].center_x * 10 - 5, region[j].center_y * 10, 49,
                                      potion[i].border_color);
                        aacircleColor(sdlRenderer, region[j].center_x * 10 - 5, region[j].center_y * 10, 46,
                                      potion[i].border_color);
                        aacircleColor(sdlRenderer, region[j].center_x * 10 - 5, region[j].center_y * 10, 40,
                                      potion[i].border_color);
                        aacircleColor(sdlRenderer, region[j].center_x * 10 - 5, region[j].center_y * 10, 38,
                                      potion[i].border_color);
                        aacircleColor(sdlRenderer, region[j].center_x * 10 - 5, region[j].center_y * 10, 47,
                                      potion[i].border_color);
                        aacircleColor(sdlRenderer, region[j].center_x * 10 - 5, region[j].center_y * 10, 48,
                                      potion[i].border_color);
                        aacircleColor(sdlRenderer, region[j].center_x * 10 - 5, region[j].center_y * 10, 39,
                                      potion[i].border_color);
                    }
                }
            }
        }
}

    const int FPS = 60;
int map(SDL_Renderer *sdlRenderer, int game_map[][map_x], int region_size, int players, Uint32 colors_array[],
            Uint32 barracks_colors_array[], SDL_Window *sdlWindow,TTF_Font *font,int* myscore) {
    Uint32 potion_colors[4]={0x77349f99,0x77f9e450,0x77a91912,0x77340087};
    Uint32 potion_border_colors[4]={0xff349f99,0xfff9e450,0xffa91912,0xff340087};
    Uint32 potion_base_color[4]={0xdd349f99,0xddf9e450,0xdda91912,0xdd340087};
    int a[20][5],b[20][map_y][map_x],c[map_y][map_x];
    struct Troops squad[64];
    struct Players player[7];
    struct Regions region[20];
    struct Potion potion[potion_size];
    int m=0;
    for(int i=0;i<64;i++){
        squad[i].is_empty=1;
    }

    set_potion_struct(potion);
    int bullet_map[720][1200];
    if(*myscore==99) {
        /*players=5;
        region_size=20;*/
        include_map(region, game_map, region_size, sdlRenderer, player, players,a,b,c);
    } else if(*myscore==110) {
        int a;
        FILE *fptr = fopen("map1.txt", "r");
        fscanf(fptr, "%d", &a);
        region_size = a;
        fscanf(fptr, "%d", &a);
        players = a;
        for (int i = 0; i < region_size; i++) {
            for (int j = 0; j < map_y; j++) {
                for (int k = 0; k < map_x; k++) {
                    fscanf(fptr, "%d", &a);
                    region[i].map[j][k] = a;
                    if (i == 0) {
                        fscanf(fptr, "%d", &a);
                        game_map[j][k] = a;
                    }
                }
            }
            fscanf(fptr, "%d", &a);
            region[i].id = a;
            fscanf(fptr, "%d", &a);
            region[i].center_y = a;
            fscanf(fptr, "%d", &a);
            region[i].center_x = a;
            fscanf(fptr, "%d", &a);
            region[i].num_of_boxes = a;
            fscanf(fptr, "%d", &a);
            region[i].is_attacking = a;
        }
        fclose(fptr);
    } else if(*myscore==120){
        int a;
        FILE *fptr = fopen("map2.txt", "r");
        fscanf(fptr, "%d", &a);
        region_size = a;
        fscanf(fptr, "%d", &a);
        players = a;
        for (int i = 0; i < region_size; i++) {
            for (int j = 0; j < map_y; j++) {
                for (int k = 0; k < map_x; k++) {
                    fscanf(fptr, "%d", &a);
                    region[i].map[j][k] = a;
                    if (i == 0) {
                        fscanf(fptr, "%d", &a);
                        game_map[j][k] = a;
                    }
                }
            }
            fscanf(fptr, "%d", &a);
            region[i].id = a;
            fscanf(fptr, "%d", &a);
            region[i].center_y = a;
            fscanf(fptr, "%d", &a);
            region[i].center_x = a;
            fscanf(fptr, "%d", &a);
            region[i].num_of_boxes = a;
            fscanf(fptr, "%d", &a);
            region[i].is_attacking = a;
        }
        fclose(fptr);
    } else if(*myscore==130) {
        int a;
        FILE *fptr = fopen("map3.txt", "r");
        fscanf(fptr, "%d", &a);
        region_size = a;
        fscanf(fptr, "%d", &a);
        players = a;
        for (int i = 0; i < region_size; i++) {
            for (int j = 0; j < map_y; j++) {
                for (int k = 0; k < map_x; k++) {
                    fscanf(fptr, "%d", &a);
                    region[i].map[j][k] = a;
                    if (i == 0) {
                        fscanf(fptr, "%d", &a);
                        game_map[j][k] = a;
                    }
                }
            }
            fscanf(fptr, "%d", &a);
            region[i].id = a;
            fscanf(fptr, "%d", &a);
            region[i].center_y = a;
            fscanf(fptr, "%d", &a);
            region[i].center_x = a;
            fscanf(fptr, "%d", &a);
            region[i].num_of_boxes = a;
            fscanf(fptr, "%d", &a);
            region[i].is_attacking = a;
        }
        fclose(fptr);
    }else if(*myscore==140){
        players=2;
        region_size=12;
        m=1;
        int a[region_size][5],b[region_size][map_y][map_x],c[map_y][map_x];
        include_map(region, game_map, region_size, sdlRenderer, player, players,a,b,c);
        set_leak_map(region,player,region_size,players);
        draw_map(region, sdlRenderer, region_size, colors_array, players, barracks_colors_array, 2, player, game_map);
    } else if(*myscore==170) {
        int a;
        FILE *fptr = fopen("map4.txt", "r");
        fscanf(fptr, "%d", &a);
        region_size = a;
        fscanf(fptr, "%d", &a);
        players = a;
        for (int i = 0; i < region_size; i++) {
            for (int j = 0; j < map_y; j++) {
                for (int k = 0; k < map_x; k++) {
                    fscanf(fptr, "%d", &a);
                    region[i].map[j][k] = a;
                    if (i == 0) {
                        fscanf(fptr, "%d", &a);
                        game_map[j][k] = a;
                    }
                }
            }
            fscanf(fptr, "%d", &a);
            region[i].id = a;
            fscanf(fptr, "%d", &a);
            region[i].center_y = a;
            fscanf(fptr, "%d", &a);
            region[i].center_x = a;
            fscanf(fptr, "%d", &a);
            region[i].num_of_boxes = a;
            fscanf(fptr, "%d", &a);
            region[i].is_attacking = a;
        }
        fclose(fptr);
    }
    for(int i=0;i<players;i++){
        player[i].potion_effect=0;
    }
    if(m!=1) {
        draw_map(region, sdlRenderer, region_size, colors_array, players, barracks_colors_array, 1, player, game_map);
    }
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
    int state=-1;
    int potion_counter=0;
    int tmp = rand() % 100 + 50;
    int potion_rand=rand()%800;
    int control_damage=0;
    int increase_counter=0;
    int time_0=SDL_GetTicks();
    *myscore=0;
    char score_string[4];
    int flag4=0;



    while (shallExit == SDL_FALSE) {
        set_regions_speed(region,region_size,player);

        if(potion_counter==potion_rand) {
                initialize_potion(potion, potion_colors, potion_border_colors, potion_base_color);
                potion_counter = 0;
                potion_rand = rand() % 800;
        }
        state=check_game_state(region,region_size,squad);
        for(int i=0;i<720;i++){
            for(int j=0;j<1200;j++){
                bullet_map[i][j]=-1;
            }
        }
        if (counter == tmp) {
            if(state!=-1){
                SDL_Color continue_color = {255,255,255,255};
                SDL_Color Winning_color = {48,185,68,255};
                SDL_Color loosing_color = {185,48,48,255};
                *myscore=score(state,time_0);
                int is_in=0;
                int is_in1=0;
                int key=0;
                SDL_Rect state_rect={400,150,400,150};
                SDL_Rect score_rect={370,320,460,150};
                SDL_Rect save_rect={900,600,250,70};

                score_to_string(*myscore,score_string);
                char mystring[16]="your score: ";
                if(m!=1) {
                    mystring[12] = score_string[0];
                    mystring[13] = score_string[1];
                    mystring[14] = score_string[2];
                    mystring[15] = score_string[3];
                    mystring[16] = '\0';
                }else{
                    mystring[12] = '0';
                    mystring[13] = '\0';
                    *myscore=0;
                }
                SDL_Surface *save_surface= TTF_RenderText_Solid(font,"save map",Winning_color);
                SDL_Texture *save_texture= SDL_CreateTextureFromSurface(sdlRenderer,save_surface);

                SDL_Surface *score_surface= TTF_RenderText_Solid(font,mystring,Winning_color);
                SDL_Texture *score_Texture = SDL_CreateTextureFromSurface(sdlRenderer,score_surface);
                SDL_Surface *score_surface1= TTF_RenderText_Solid(font,mystring,loosing_color);
                SDL_Texture *score_Texture1 = SDL_CreateTextureFromSurface(sdlRenderer,score_surface1);

                SDL_Surface *state_surface= TTF_RenderText_Solid(font,"You won!",Winning_color);
                SDL_Texture *state_Texture = SDL_CreateTextureFromSurface(sdlRenderer,state_surface);
                SDL_Surface *state_surface1= TTF_RenderText_Solid(font,"You lost!",loosing_color);
                SDL_Texture *state_Texture1= SDL_CreateTextureFromSurface(sdlRenderer,state_surface1);


                SDL_SetRenderDrawColor(sdlRenderer, 0x1E, 0x00, 0x1E, 0xf0);//0xf01e001e
                SDL_RenderClear(sdlRenderer);
                draw_map(region, sdlRenderer, region_size, colors_array, players, barracks_colors_array, 0, player, game_map);
                draw_bases(region, region_size, game_map, sdlRenderer);
                draw_potions(potion,sdlRenderer);

                print_soldiers(region, region_size, sdlRenderer);
                //SDL_RenderPresent(sdlRenderer);

                boxColor(sdlRenderer,0,0,1200,720,0x99666666);
                SDL_Rect continue_rect = {500,550,200,100};
                SDL_Surface *continue_surface= TTF_RenderText_Solid(font,"continue",Winning_color);
                SDL_Texture *continue_Texture= SDL_CreateTextureFromSurface(sdlRenderer,continue_surface);
                SDL_Surface *continue_surface1= TTF_RenderText_Solid(font,"continue",loosing_color);
                SDL_Texture *continue_Texture1= SDL_CreateTextureFromSurface(sdlRenderer,continue_surface1);

                if(state==1) {
                    SDL_RenderCopy(sdlRenderer, state_Texture, NULL, &state_rect);
                    SDL_RenderCopy(sdlRenderer,continue_Texture,NULL,&continue_rect);
                    SDL_RenderCopy(sdlRenderer,score_Texture,NULL,&score_rect);
                }else{
                    SDL_RenderCopy(sdlRenderer, state_Texture1, NULL, &state_rect);
                    SDL_RenderCopy(sdlRenderer,continue_Texture1,NULL,&continue_rect);
                    SDL_RenderCopy(sdlRenderer,score_Texture1,NULL,&score_rect);
                }

                SDL_RenderCopy(sdlRenderer,save_texture,NULL,&save_rect);
                SDL_RenderPresent(sdlRenderer);
                SDL_bool done=SDL_FALSE;
                while(done == SDL_FALSE){
                    SDL_Event e;
                    if(SDL_PollEvent(&e)){
                         if(e.type==SDL_QUIT){
                             done=SDL_TRUE;
                             state=-100;
                         } else if(e.type==SDL_MOUSEMOTION){
                             x=e.motion.x;
                             y=e.motion.y;
                             if(x>500 && x<700 && y>550 && y<650){
                                 is_in=1;
                                 continue_rect.x=470;
                                 continue_rect.y=520;
                                 continue_rect.w=260;
                                 continue_rect.h=160;

                                 SDL_SetRenderDrawColor(sdlRenderer, 0x1E, 0x00, 0x1E, 0xf0);//0xf01e001e
                                 SDL_RenderClear(sdlRenderer);
                                 draw_map(region, sdlRenderer, region_size, colors_array, players, barracks_colors_array, 0, player, game_map);
                                 draw_bases(region, region_size, game_map, sdlRenderer);
                                 draw_potions(potion,sdlRenderer);

                                 print_soldiers(region, region_size, sdlRenderer);
                                 //SDL_RenderPresent(sdlRenderer);

                                 boxColor(sdlRenderer,0,0,1200,720,0x99666666);
                                 if(state==1) {
                                     SDL_RenderCopy(sdlRenderer, state_Texture, NULL, &state_rect);
                                     SDL_RenderCopy(sdlRenderer,continue_Texture,NULL,&continue_rect);
                                     SDL_RenderCopy(sdlRenderer,score_Texture,NULL,&score_rect);
                                 }else{
                                     SDL_RenderCopy(sdlRenderer, state_Texture1, NULL, &state_rect);
                                     SDL_RenderCopy(sdlRenderer,continue_Texture1,NULL,&continue_rect);
                                     SDL_RenderCopy(sdlRenderer,score_Texture1,NULL,&score_rect);
                                 }
                                 SDL_RenderCopy(sdlRenderer,save_texture,NULL,&save_rect);
                                 SDL_RenderPresent(sdlRenderer);

                                 //render
                             } else if(is_in==1 && !(x>500 && x<700 && y>550 && y<650)){
                                 is_in=0;
                                 continue_rect.x=500;
                                 continue_rect.y=550;
                                 continue_rect.w=200;
                                 continue_rect.h=100;

                                 SDL_SetRenderDrawColor(sdlRenderer, 0x1E, 0x00, 0x1E, 0xf0);//0xf01e001e
                                 SDL_RenderClear(sdlRenderer);
                                 draw_map(region, sdlRenderer, region_size, colors_array, players, barracks_colors_array, 0, player, game_map);
                                 draw_bases(region, region_size, game_map, sdlRenderer);
                                 draw_potions(potion,sdlRenderer);
                                 print_soldiers(region, region_size, sdlRenderer);
                                 //SDL_RenderPresent(sdlRenderer);

                                 boxColor(sdlRenderer,0,0,1200,720,0x99666666);
                                 if(state==1) {
                                     SDL_RenderCopy(sdlRenderer, state_Texture, NULL, &state_rect);
                                     SDL_RenderCopy(sdlRenderer,continue_Texture,NULL,&continue_rect);
                                     SDL_RenderCopy(sdlRenderer,score_Texture,NULL,&score_rect);
                                 }else{
                                     SDL_RenderCopy(sdlRenderer, state_Texture1, NULL, &state_rect);
                                     SDL_RenderCopy(sdlRenderer,continue_Texture1,NULL,&continue_rect);
                                     SDL_RenderCopy(sdlRenderer,score_Texture1,NULL,&score_rect);
                                 }
                                 SDL_RenderCopy(sdlRenderer,save_texture,NULL,&save_rect);
                                 SDL_RenderPresent(sdlRenderer);

                                 //render
                             } else if(x>900 && x<1150 && y>600 && y<670){
                                 is_in1=1;//900 600 250 70
                                 save_rect.x=880;
                                 save_rect.w=290;
                                 save_rect.y=590;
                                 save_rect.h=90;
                                 SDL_SetRenderDrawColor(sdlRenderer, 0x1E, 0x00, 0x1E, 0xf0);//0xf01e001e
                                 SDL_RenderClear(sdlRenderer);
                                 draw_map(region, sdlRenderer, region_size, colors_array, players, barracks_colors_array, 0, player, game_map);
                                 draw_bases(region, region_size, game_map, sdlRenderer);
                                 draw_potions(potion,sdlRenderer);
                                 print_soldiers(region, region_size, sdlRenderer);
                                 //SDL_RenderPresent(sdlRenderer);

                                 boxColor(sdlRenderer,0,0,1200,720,0x99666666);
                                 if(state==1) {
                                     SDL_RenderCopy(sdlRenderer, state_Texture, NULL, &state_rect);
                                     SDL_RenderCopy(sdlRenderer,continue_Texture,NULL,&continue_rect);
                                     SDL_RenderCopy(sdlRenderer,score_Texture,NULL,&score_rect);
                                 }else{
                                     SDL_RenderCopy(sdlRenderer, state_Texture1, NULL, &state_rect);
                                     SDL_RenderCopy(sdlRenderer,continue_Texture1,NULL,&continue_rect);
                                     SDL_RenderCopy(sdlRenderer,score_Texture1,NULL,&score_rect);
                                 }
                                 SDL_RenderCopy(sdlRenderer,save_texture,NULL,&save_rect);
                                 SDL_RenderPresent(sdlRenderer);
                             } else if(is_in1==1 && !(x>900 && x<1150 && y>600 && y<670)){
                                 is_in1=0;
                                 save_rect.x=900;
                                 save_rect.w=250;
                                 save_rect.y=600;
                                 save_rect.h=70;
                                 SDL_SetRenderDrawColor(sdlRenderer, 0x1E, 0x00, 0x1E, 0xf0);//0xf01e001e
                                 SDL_RenderClear(sdlRenderer);
                                 draw_map(region, sdlRenderer, region_size, colors_array, players, barracks_colors_array, 0, player, game_map);
                                 draw_bases(region, region_size, game_map, sdlRenderer);
                                 draw_potions(potion,sdlRenderer);
                                 print_soldiers(region, region_size, sdlRenderer);
                                 //SDL_RenderPresent(sdlRenderer);

                                 boxColor(sdlRenderer,0,0,1200,720,0x99666666);
                                 if(state==1) {
                                     SDL_RenderCopy(sdlRenderer, state_Texture, NULL, &state_rect);
                                     SDL_RenderCopy(sdlRenderer,continue_Texture,NULL,&continue_rect);
                                     SDL_RenderCopy(sdlRenderer,score_Texture,NULL,&score_rect);
                                 }else{
                                     SDL_RenderCopy(sdlRenderer, state_Texture1, NULL, &state_rect);
                                     SDL_RenderCopy(sdlRenderer,continue_Texture1,NULL,&continue_rect);
                                     SDL_RenderCopy(sdlRenderer,score_Texture1,NULL,&score_rect);
                                 }
                                 SDL_RenderCopy(sdlRenderer,save_texture,NULL,&save_rect);
                                 SDL_RenderPresent(sdlRenderer);
                             }
                         } else if(e.type==SDL_MOUSEBUTTONDOWN && e.button.button==SDL_BUTTON_LEFT){
                             if(is_in==1){
                                 break;
                             } else if(is_in1==1 && key==0){
                                 key=1;
                                 FILE *fptr= fopen("map4.txt","w");
                                 fprintf(fptr,"%d\n",region_size);
                                 fprintf(fptr,"%d\n",players);
                                 for(int i=0;i<region_size;i++){
                                     for(int j=0;j<map_y;j++){
                                         for(int k=0;k<map_x;k++){
                                             fprintf(fptr," %d ",b[i][j][k]);
                                             if(i==0) {
                                                 fprintf(fptr, " %d ", c[j][k]);
                                             }
                                         }
                                     }
                                     fprintf(fptr," %d %d %d %d %d\n",a[i][0],a[i][1],a[i][2],a[i][3],a[i][4]);
                                 }
                                 fclose(fptr);
                             }
                         }
                    }
                }
                SDL_DestroyTexture(state_Texture);
                SDL_DestroyTexture(state_Texture1);
                SDL_DestroyTexture(continue_Texture);
                SDL_DestroyTexture(continue_Texture1);
                SDL_DestroyTexture(score_Texture);
                SDL_DestroyTexture(score_Texture1);
                SDL_FreeSurface(state_surface);
                SDL_FreeSurface(state_surface1);
                SDL_FreeSurface(score_surface);
                SDL_FreeSurface(score_surface1);
                SDL_FreeSurface(continue_surface);
                SDL_FreeSurface(continue_surface1);
                SDL_DestroyTexture(save_texture);
                SDL_FreeSurface(save_surface);
                break;
            }
            counter = 0;
            attack_temp_func(region, region_size, squad,potion);
            tmp = rand() % 100 + 50;
        }

        SDL_SetRenderDrawColor(sdlRenderer, 0x1E, 0x00, 0x1E, 0xf0);//0xf01e001e
        SDL_RenderClear(sdlRenderer);
        draw_map(region, sdlRenderer, region_size, colors_array, players, barracks_colors_array, 0, player, game_map);

        update_potion(potion,player);
        draw_potions(potion,sdlRenderer);
        activate_potion(region,potion,region_size,player);
        draw_potion_effect(region,player,potion,region_size,sdlRenderer);

        draw_bases(region, region_size, game_map, sdlRenderer);

        if(counter%50 == 0){
            increase_troops(region,region_size,player,1);
        } else if(counter%15==0){
            increase_troops(region,region_size,player,0);
        }

        for (int i = 0; i < 64; i++) {
            if (squad[i].is_empty == 0) {
                for (int j = 0; j < squad[i].counter; j++) {
                    parcham = 0;
                    if (squad[i].x[j] > 0) {
                        check_soldier_position(squad, i, j, j,potion,player);
                        parcham = 1;
                        if (squad[i].x[j] > 0) {
                            /*if (squad[i].counter < squad[i].sum) {
                                Vo = 15;
                            } else {
                                Vo = 15;
                            }*/

                            squad[i].Vx = region[squad[i].origin_region_index].Vo * ((region[squad[i].destination_region_index].center_x * 10 - 5 -
                                                 squad[i].x[j]) /
                                                (sqrt(pow((region[squad[i].destination_region_index].center_x * 10 -
                                                           5 -
                                                           squad[i].x[j]), 2) +
                                                      pow((region[squad[i].destination_region_index].center_y * 10 -
                                                           5 -
                                                           squad[i].y[j]), 2))));
                            squad[i].Vy = region[squad[i].origin_region_index].Vo * ((region[squad[i].destination_region_index].center_y * 10 - 5-
                                                 squad[i].y[j]) /
                                                (sqrt(pow((region[squad[i].destination_region_index].center_x * 10 -
                                                           5 -
                                                           squad[i].x[j]), 2) +
                                                      pow((region[squad[i].destination_region_index].center_y * 10 -
                                                           5 -
                                                           squad[i].y[j]), 2))));

                            squad[i].x[j] += squad[i].Vx;
                            squad[i].y[j] += squad[i].Vy;
                        }

                    }

                    if (squad[i].x[j] <= region[squad[i].destination_region_index].center_x * 10 + 30 &&
                            squad[i].x[j] >= region[squad[i].destination_region_index].center_x * 10 - 40 &&
                            squad[i].y[j] <= region[squad[i].destination_region_index].center_y * 10 + 30 &&
                            squad[i].y[j] >= region[squad[i].destination_region_index].center_y * 10 - 40) {
                        squad[i].x[j] = -1;
                        squad[i].y[j] = -1;
                        if(/*region[squad[i].destination_region_index].damage==2 &&*/ region[squad[i].destination_region_index].khafan == 1){
                            region[squad[i].destination_region_index].soldiers++;
                        }
                        else if (region[squad[i].destination_region_index].soldiers > 1 && region[squad[i].destination_region_index].id != squad[i].player_index) {
                            if(region[squad[i].origin_region_index].damage != 1) {
                                region[squad[i].destination_region_index].soldiers -=
                                        region[squad[i].origin_region_index].damage / 2;
                            } else{
                                if(control_damage==0){
                                    control_damage++;
                                }else{
                                    control_damage=0;
                                    region[squad[i].destination_region_index].soldiers --;
                                }
                            }
                        }else if(region[squad[i].destination_region_index].soldiers == 1 && region[squad[i].destination_region_index].id != squad[i].player_index) {
                            if(region[squad[i].origin_region_index].damage==4) {
                                region[squad[i].destination_region_index].id = squad[i].player_index;
                                region[squad[i].destination_region_index].color = player[squad[i].player_index].color;
                                region[squad[i].destination_region_index].barracks_color = player[squad[i].player_index].barrack_color;
                            } else if(region[squad[i].origin_region_index].damage==2){
                                region[squad[i].destination_region_index].soldiers --;
                            } else if(region[squad[i].origin_region_index].damage==1){
                                if(control_damage==0){
                                    control_damage++;
                                }else{
                                    control_damage=0;
                                    region[squad[i].destination_region_index].soldiers --;
                                }
                            }
                        }
                        else {
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
                    if (squad[i].counter == squad[i].sum -1) {
                        region[squad[i].origin_region_index].soldiers--;
                    }
                }

                parcham=0;
                for(int j=0;j<squad[i].sum;j++){
                    if(squad[i].x[j]>0){
                        parcham=1;
                    }
                }
                if (parcham == 0) {
                    region[squad[i].origin_region_index].is_attacking = 0;
                    squad[i].is_empty = 1;
                }
            }
        }

        for(int i=0;i<64;i++){
            if(squad[i].is_empty==0){
                for(int j=0;j<squad[i].counter;j++){
                    if(squad[i].x[j]>0){
                        filledCircleColor(sdlRenderer, squad[i].x[j], squad[i].y[j], 8, 0xff000000);
                        filledCircleColor(sdlRenderer, squad[i].x[j], squad[i].y[j], 6,
                                          squad[i].color);
                    }
                }
            }
        }

        soldiers_to_string(region, region_size);
        print_soldiers(region, region_size, sdlRenderer);
        SDL_RenderPresent(sdlRenderer);

        SDL_Delay(1000 / FPS);
        SDL_Event sdlEvent;
        while (SDL_PollEvent(&sdlEvent)) {

            if (SDL_QUIT == sdlEvent.type) {
                shallExit = SDL_TRUE;
                state=-100;
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
                if (key2 > -1 && key1 != key2 && region[key1].id==0) {
                    initialize_squad(squad, region, key1, key2);
                }
            }
        }
        counter++;
        potion_counter++;
    }
    /*if(state !=-1 && m==1){
        return 2;
    }*/
    return state;
}
