
#include "main_menu.h"
#include "first_menu.h"


/*void draw_menu(Uint32 colors_array[],SDL_Renderer *sdlRenderer,int flag,int menu_map[][map_x-1])
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
*/


int main_menu(int menu_map[][map_x-1],SDL_Renderer *sdlRenderer,TTF_Font *font,TTF_Font *font2,Uint32 colors_array[]) {

    int menu_option=0;
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

        SDL_Delay(1000/60);
        //SDL_Delay(1000 / FPS);
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
    return menu_option;
}