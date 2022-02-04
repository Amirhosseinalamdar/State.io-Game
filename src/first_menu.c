

#include "first_menu.h"

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

int first_menu(TTF_Font *font,SDL_Renderer *sdlRenderer,Uint32 colors_array[],int menu_map[][map_x-1]) {
    SDL_Color main_title_color = {0x1E, 0x00, 0x1E, 0xff};
//entering_user_name
    SDL_Rect user_name_background_rect = {350, 400, 500, 100};
    SDL_Color user_name_color = {0xB0, 0x35, 0x56, 0xff};
    SDL_Rect user_name_string_rect = {360, 425, 0, 60};
    SDL_Rect continue_button = {890, 415, 70, 70};

    SDL_Surface *button_surface = TTF_RenderText_Solid(font, "OK", main_title_color);
    SDL_Texture *button_texture = SDL_CreateTextureFromSurface(sdlRenderer, button_surface);


    int menu_option = 1;
    SDL_bool shallExit;
//0xff5635B0
    char user_name[32];
    for (int i = 0; i < 32; i++) { user_name[i] = '\0'; }
    char input = '\0';


    SDL_Surface *user_name_surface = TTF_RenderText_Solid(font, user_name, user_name_color);
    SDL_Texture *user_name_texture = SDL_CreateTextureFromSurface(sdlRenderer, user_name_surface);
    SDL_FreeSurface(user_name_surface);
    SDL_DestroyTexture(user_name_texture);
    SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0x00, 0x00, 0x00);
    SDL_RenderClear(sdlRenderer);
    draw_menu(colors_array, sdlRenderer, 0, menu_map);
    include_welcome_enter(font, sdlRenderer);

    SDL_SetRenderDrawColor(sdlRenderer, 0x1e, 0x00, 0x1e, 255);
    SDL_RenderFillRect(sdlRenderer, &user_name_background_rect);

    SDL_RenderCopy(sdlRenderer, user_name_texture, NULL, &user_name_string_rect);
    SDL_FreeSurface(user_name_surface);
    SDL_DestroyTexture(user_name_texture);

    SDL_SetRenderDrawColor(sdlRenderer, 0xB0, 0x35, 0x56, 255);
    SDL_RenderDrawRect(sdlRenderer, &user_name_background_rect);

    SDL_RenderPresent(sdlRenderer);
    SDL_bool done = SDL_FALSE;
    int mouse_x, mouse_y;
    int flag3 = 0;
    while (!done) {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    done = SDL_TRUE;
                    menu_option=0;
                    break;
                case SDL_KEYDOWN:

                    input = event.key.keysym.sym;
                    if (input == SDLK_RETURN && strlen(user_name) > 0) {
                        done = SDL_TRUE;
                    } else if (input == SDLK_BACKSPACE && strlen(user_name) > 0) {
                        user_name[strlen(user_name) - 1] = '\0';
                        user_name_string_rect.w = strlen(user_name) * 20;
                    } else if (strlen(user_name) == 24) {
                    } else if ((input == SDLK_BACKSPACE && strlen(user_name) == 0) || input < 48 || input > 122 ||
                               (input < 97 && input > 90) || (input < 65 && input > 57)) {
                        if (input == '.' || input == ' ') {
                            user_name[strlen(user_name)] = input;
                            user_name_string_rect.w = 20 * strlen(user_name);
                        }
                    } else {
                        user_name[strlen(user_name)] = input;
                        user_name_string_rect.w = 20 * strlen(user_name);
                    }

                    SDL_SetRenderDrawColor(sdlRenderer, 0x1e, 0x00, 0x1e, 255);
                    SDL_RenderFillRect(sdlRenderer, &user_name_background_rect);
                    SDL_Surface *user_name_surface = TTF_RenderText_Solid(font, user_name, user_name_color);
                    SDL_Texture *user_name_texture = SDL_CreateTextureFromSurface(sdlRenderer, user_name_surface);
                    SDL_RenderCopy(sdlRenderer, user_name_texture, NULL, &user_name_string_rect);
                    SDL_FreeSurface(user_name_surface);
                    SDL_DestroyTexture(user_name_texture);
                    SDL_SetRenderDrawColor(sdlRenderer, 0xB0, 0x35, 0x56, 255);
                    SDL_RenderDrawRect(sdlRenderer, &user_name_background_rect);

                    if (strlen(user_name) > 0) {
                        SDL_SetRenderDrawColor(sdlRenderer, 0xB0, 0x35, 0x56, 255);
                        SDL_RenderFillRect(sdlRenderer, &continue_button);
                        SDL_SetRenderDrawColor(sdlRenderer, 0x1e, 0x00, 0x1e, 255);
                        SDL_RenderDrawRect(sdlRenderer, &continue_button);
                        SDL_Surface *button_surface = TTF_RenderText_Solid(font, "OK", main_title_color);
                        SDL_Texture *button_texture = SDL_CreateTextureFromSurface(sdlRenderer, button_surface);
                        SDL_RenderCopy(sdlRenderer, button_texture, NULL, &continue_button);
                        SDL_FreeSurface(button_surface);
                        SDL_DestroyTexture(button_texture);
                    } else {
                        SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0x00, 0x00, 0x00);
                        SDL_RenderClear(sdlRenderer);
                        draw_menu(colors_array, sdlRenderer, 0, menu_map);
                        include_welcome_enter(font, sdlRenderer);

                        SDL_SetRenderDrawColor(sdlRenderer, 0x1e, 0x00, 0x1e, 255);
                        SDL_RenderFillRect(sdlRenderer, &user_name_background_rect);
                        SDL_Surface *user_name_surface = TTF_RenderText_Solid(font, user_name, user_name_color);
                        SDL_Texture *user_name_texture = SDL_CreateTextureFromSurface(sdlRenderer, user_name_surface);
                        SDL_RenderCopy(sdlRenderer, user_name_texture, NULL, &user_name_string_rect);
                        SDL_FreeSurface(user_name_surface);
                        SDL_DestroyTexture(user_name_texture);
                        SDL_SetRenderDrawColor(sdlRenderer, 0xB0, 0x35, 0x56, 255);
                        SDL_RenderDrawRect(sdlRenderer, &user_name_background_rect);
                    }

                    SDL_RenderPresent(sdlRenderer);
                    break;

                case SDL_MOUSEMOTION:
                    mouse_y = event.motion.y;
                    mouse_x = event.motion.x;
                    if (mouse_x > 890 && mouse_x < 960 && mouse_y > 415 && mouse_y < 485 && strlen(user_name) > 0) {
                        continue_button.x = 880;
                        continue_button.y = 405;
                        continue_button.w = 90;
                        continue_button.h = 90;
//---------------------
                        SDL_SetRenderDrawColor(sdlRenderer, 0xB0, 0x35, 0x56, 255);
                        SDL_RenderFillRect(sdlRenderer, &continue_button);
                        SDL_SetRenderDrawColor(sdlRenderer, 0x1e, 0x00, 0x1e, 255);
                        SDL_RenderDrawRect(sdlRenderer, &continue_button);
                        SDL_Surface *button_surface = TTF_RenderText_Solid(font, "OK", main_title_color);
                        SDL_Texture *button_texture = SDL_CreateTextureFromSurface(sdlRenderer, button_surface);
                        SDL_RenderCopy(sdlRenderer, button_texture, NULL, &continue_button);
                        SDL_FreeSurface(button_surface);
                        SDL_DestroyTexture(button_texture);
                        SDL_RenderPresent(sdlRenderer);
                        flag3 = 1;
                    } else if (flag3 == 1 && !(mouse_x > 890 && mouse_x < 960 && mouse_y > 415 && mouse_y < 485) &&
                               strlen(user_name) > 0) {
                        continue_button.x = 890;
                        continue_button.y = 415;
                        continue_button.w = 70;
                        continue_button.h = 70;
//-------------------
                        SDL_SetRenderDrawColor(sdlRenderer, 0xff, 0x00, 0x00, 0x00);
                        SDL_RenderClear(sdlRenderer);
                        draw_menu(colors_array, sdlRenderer, 0, menu_map);
                        include_welcome_enter(font, sdlRenderer);

                        SDL_SetRenderDrawColor(sdlRenderer, 0x1e, 0x00, 0x1e, 255);
                        SDL_RenderFillRect(sdlRenderer, &user_name_background_rect);
                        SDL_Surface *user_name_surface = TTF_RenderText_Solid(font, user_name, user_name_color);
                        SDL_Texture *user_name_texture = SDL_CreateTextureFromSurface(sdlRenderer, user_name_surface);
                        SDL_RenderCopy(sdlRenderer, user_name_texture, NULL, &user_name_string_rect);
                        SDL_FreeSurface(user_name_surface);
                        SDL_DestroyTexture(user_name_texture);
                        SDL_SetRenderDrawColor(sdlRenderer, 0xB0, 0x35, 0x56, 255);
                        SDL_RenderDrawRect(sdlRenderer, &user_name_background_rect);


                        SDL_SetRenderDrawColor(sdlRenderer, 0xB0, 0x35, 0x56, 255);
                        SDL_RenderFillRect(sdlRenderer, &continue_button);
                        SDL_SetRenderDrawColor(sdlRenderer, 0x1e, 0x00, 0x1e, 255);
                        SDL_RenderDrawRect(sdlRenderer, &continue_button);
                        SDL_Surface *button_surface = TTF_RenderText_Solid(font, "OK", main_title_color);
                        SDL_Texture *button_texture = SDL_CreateTextureFromSurface(sdlRenderer, button_surface);
                        SDL_RenderCopy(sdlRenderer, button_texture, NULL, &continue_button);
                        SDL_FreeSurface(button_surface);
                        SDL_DestroyTexture(button_texture);
                        SDL_RenderPresent(sdlRenderer);
                        flag3 = 0;
                    }

                    break;

                case SDL_MOUSEBUTTONDOWN:
                    mouse_y = event.motion.y;
                    mouse_x = event.motion.x;
                    if (mouse_x > 890 && mouse_x < 960 && mouse_y > 415 && mouse_y < 485 && strlen(user_name) > 0) {
                        done = SDL_TRUE;
                    }
                    break;
            }
        }
    }
    return menu_option;
}