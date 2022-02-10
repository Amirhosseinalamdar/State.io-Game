#include "ranks.h"
#include "first_menu.h"

void score_to_string_s(int score,char score_string[])
{
    for(int k=0;k<1;k++) {
        for (int j = 0; j < 8; j++) {
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

int ranks(TTF_Font *font,SDL_Renderer *sdlRenderer,Uint32 colors_array[],int menu_map[][map_x-1]) {
    int menu_option;
    int is_in[7] = {0};
    char users[6][32];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 32; j++) {
            users[i][j] = '\0';
        }
    }
    int scores[6];
    char score_string[6][8];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            score_string[i][j] = '\0';
        }
    }
    int n = 6;
    char c;

    FILE *fptr = fopen("leaderboard.txt", "r");
    fscanf(fptr, "%d\n", &n);
    for (int i = 0; i < n; i++) {
        fscanf(fptr, "%c", &c);
        for (int j = 0; c != '\n'; j++) {
            users[i][j] = c;
            fscanf(fptr, "%c", &c);
        }
        fscanf(fptr, "%d\n", &scores[i]);
    }
    fclose(fptr);

    for (int i = 0; i < 6; i++) {
        score_to_string_s(scores[i], score_string[i]);
    }
    //colors
    SDL_Color text_color = {0x1E, 0x00, 0x1E, 0xff};
    Uint32 color = 0xff0000ff;
    SDL_Color color1 = {255, 0, 0, 205};
    //rects
    SDL_Rect rect[12];
    SDL_Rect title_rect = {50, 30, 350, 110};
    SDL_Rect back_button = {950, 600, 150, 70};
    for (int i = 0; i < 6; i++) {
        rect[i].x = 350;
        rect[i].y = 150 + i * 70;
        if (strlen(users[i]) >= 10) {
            rect[i].w = strlen(users[i]) * 13;
        } else {
            rect[i].w = strlen(users[i]) * 25;
        }
        rect[i].h = 70;
    }
    for (int i = 6; i < 12; i++) {
        rect[i].x = 750;
        rect[i].y = 150 + (i - 6) * 70;
        rect[i].w = strlen(score_string[i - 6]) * 25;
        rect[i].h = 70;
    }
    SDL_Surface *surface[6];
    SDL_Texture *texture[6];
    SDL_Surface *Surface[6];
    SDL_Texture *Texture[6];

    for (int i = 0; i < 6; i++) {
        surface[i] = TTF_RenderText_Solid(font, users[i], text_color);
        texture[i] = SDL_CreateTextureFromSurface(sdlRenderer, surface[i]);
    }
    for (int i = 0; i < 6; i++) {
        Surface[i] = TTF_RenderText_Solid(font, score_string[i], text_color);
        Texture[i] = SDL_CreateTextureFromSurface(sdlRenderer, Surface[i]);
    }
    SDL_Surface *title_surface = TTF_RenderText_Solid(font, "leader board:", text_color);
    SDL_Texture *title_texture = SDL_CreateTextureFromSurface(sdlRenderer, title_surface);

    SDL_Surface *back_surface = TTF_RenderText_Solid(font, "back", text_color);
    SDL_Texture *back_texture = SDL_CreateTextureFromSurface(sdlRenderer, back_surface);


    SDL_SetRenderDrawColor(sdlRenderer, 0xcc, 0x11, 0x11, 0x00);
    SDL_RenderClear(sdlRenderer);
    draw_menu(colors_array, sdlRenderer, 1, menu_map);
    for (int i = 0; i < 6; i++) {
        SDL_RenderCopy(sdlRenderer, texture[i], NULL, &rect[i]);
        SDL_RenderCopy(sdlRenderer, Texture[i], NULL, &rect[i + 6]);
    }
    SDL_RenderCopy(sdlRenderer, title_texture, NULL, &title_rect);
    SDL_RenderCopy(sdlRenderer, back_texture, NULL, &back_button);
    SDL_RenderPresent(sdlRenderer);

    int x, y;
    SDL_bool done = SDL_FALSE;
    while (!done) {
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                menu_option = -100;
                done = SDL_TRUE;
            } else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                if(is_in[6]==1){
                    menu_option = 0;
                    done = SDL_TRUE;
                }
            } else if (e.type == SDL_MOUSEMOTION) {
                x = e.motion.x;
                y = e.motion.y;

                if (x > back_button.x && x < back_button.x + back_button.w && y > back_button.y &&
                    y < back_button.y + back_button.h) {
                    is_in[6] = 1;
                    SDL_SetRenderDrawColor(sdlRenderer, 0xcc, 0x11, 0x11, 0x00);
                    SDL_RenderClear(sdlRenderer);
                    draw_menu(colors_array, sdlRenderer, 1, menu_map);
                    for (int i = 0; i < 6; i++) {
                        SDL_RenderCopy(sdlRenderer, texture[i], NULL, &rect[i]);
                        SDL_RenderCopy(sdlRenderer, Texture[i], NULL, &rect[i + 6]);
                    }
                    SDL_RenderCopy(sdlRenderer, title_texture, NULL, &title_rect);
                    back_surface = TTF_RenderText_Solid(font, "back", color1);
                    back_texture = SDL_CreateTextureFromSurface(sdlRenderer, back_surface);
                    SDL_RenderCopy(sdlRenderer, back_texture, NULL, &back_button);
                    SDL_RenderPresent(sdlRenderer);
                } else if (is_in[6] == 1 &&
                           !(x > back_button.x && x < back_button.x + back_button.w && y > back_button.y &&
                             y < back_button.y + back_button.h)) {
                    is_in[6] = 0;
                    SDL_SetRenderDrawColor(sdlRenderer, 0xcc, 0x11, 0x11, 0x00);
                    SDL_RenderClear(sdlRenderer);
                    draw_menu(colors_array, sdlRenderer, 1, menu_map);
                    for (int i = 0; i < 6; i++) {
                        SDL_RenderCopy(sdlRenderer, texture[i], NULL, &rect[i]);
                        SDL_RenderCopy(sdlRenderer, Texture[i], NULL, &rect[i + 6]);
                    }
                    SDL_RenderCopy(sdlRenderer, title_texture, NULL, &title_rect);
                    back_surface = TTF_RenderText_Solid(font, "back", text_color);
                    back_texture = SDL_CreateTextureFromSurface(sdlRenderer, back_surface);
                    SDL_RenderCopy(sdlRenderer, back_texture, NULL, &back_button);
                    SDL_RenderPresent(sdlRenderer);
                }
            }
        }
    }
    for (int i = 0; i < 6; i++) {
        SDL_DestroyTexture(texture[i]);
        SDL_FreeSurface(surface[i]);
        SDL_DestroyTexture(Texture[i]);
        SDL_FreeSurface(Surface[i]);
    }
    SDL_FreeSurface(title_surface);
    SDL_FreeSurface(back_surface);
    SDL_DestroyTexture(back_texture);
    SDL_DestroyTexture(title_texture);
    return menu_option;
}


