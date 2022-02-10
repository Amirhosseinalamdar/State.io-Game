
#include "choose_num.h"
#include "first_menu.h"



int choose_num(TTF_Font *font,SDL_Renderer *sdlRenderer,Uint32 colors_array[],int menu_map[][map_x-1],int *players,int *region_size)
{
    int menu_option=0;
    char bases_string[2];
    char players_str[2];
    int player_set=0;
    int base_set=0;
    int x,y;
    int is_in[2]={0};
    //colors
    SDL_Color text_color = {0x1E, 0x00, 0x1E, 0xff};
    Uint32 color = 0xff0000ff;
    SDL_Color color1 = {255, 0, 0, 205};
    //rects
    SDL_Rect players_rect={200,200,200,70};
    SDL_Rect bases_rect={200,400,200,70};
    SDL_Rect pn_rect={600,200,40,70};
    SDL_Rect bn_rect={600,400,40,70};

    SDL_Rect continue_rect={900,600,200,70};
    SDL_Rect Back_rect={100,600,100,70};
    //sur and tex
    SDL_Surface *players_surface= TTF_RenderText_Solid(font,"players: ",text_color);
    SDL_Texture *players_texture= SDL_CreateTextureFromSurface(sdlRenderer,players_surface);
    SDL_Surface *bases_surface= TTF_RenderText_Solid(font,"states: ",text_color);
    SDL_Texture *bases_texture= SDL_CreateTextureFromSurface(sdlRenderer,bases_surface);

    SDL_Surface *pn_surface;
    SDL_Texture *pn_texture;
    SDL_Surface *bn_surface;
    SDL_Texture *bn_texture;

    SDL_Surface *continue_surface= TTF_RenderText_Solid(font,"continue",text_color);
    SDL_Texture *continue_texture= SDL_CreateTextureFromSurface(sdlRenderer,continue_surface);
    SDL_Surface *back_surface= TTF_RenderText_Solid(font,"back",text_color);
    SDL_Texture *back_texture= SDL_CreateTextureFromSurface(sdlRenderer,back_surface);

    //------------------



    SDL_SetRenderDrawColor(sdlRenderer, 0xcc, 0x11, 0x11, 0x00);
    SDL_RenderClear(sdlRenderer);
    draw_menu(colors_array, sdlRenderer, 1, menu_map);
    SDL_RenderCopy(sdlRenderer,players_texture,NULL,&players_rect);
    SDL_RenderCopy(sdlRenderer,bases_texture,NULL,&bases_rect);
    SDL_RenderCopy(sdlRenderer,back_texture,NULL,&Back_rect);
    SDL_RenderCopy(sdlRenderer, continue_texture,NULL,&continue_rect);
    SDL_RenderPresent(sdlRenderer);

    char input;
    SDL_bool done=SDL_FALSE;
    while(!done){
        SDL_Event e;
        if(SDL_PollEvent(&e)){
            if(e.type==SDL_QUIT){
                menu_option=-100;
                done=SDL_TRUE;
            } else if(e.type==SDL_KEYDOWN){
               input=e.key.keysym.sym;
               if(input>='2' && input<='7' && player_set==0){
                   player_set=1;
                   *players=input-'0';
                   players_str[0]=input;
                   players_str[1]=' ';
                   pn_surface= TTF_RenderText_Solid(font,players_str,text_color);
                   pn_texture= SDL_CreateTextureFromSurface(sdlRenderer,pn_surface);
                   SDL_RenderCopy(sdlRenderer,pn_texture,NULL,&pn_rect);
                   SDL_RenderPresent(sdlRenderer);
               } else if(input>='0' && input<='9' && base_set==0 && player_set==1){
                   base_set=1;
                   *region_size=input-'0'+10;
                   bases_string[0]='1';
                   bases_string[1]=input;
                   bases_string[2]='\0';
                   bn_surface= TTF_RenderText_Solid(font,bases_string,text_color);
                   bn_texture= SDL_CreateTextureFromSurface(sdlRenderer,bn_surface);
                   SDL_RenderCopy(sdlRenderer,bn_texture,NULL,&bn_rect);
                   SDL_RenderPresent(sdlRenderer);
               }
            }else if(e.type==SDL_MOUSEBUTTONDOWN && e.button.button==SDL_BUTTON_LEFT){
                if(is_in[0]==1){
                    menu_option=99;
                    done=SDL_TRUE;
                } else if(is_in[1]==1){
                    menu_option=0;
                    done=SDL_TRUE;
                }
            }
            else if(e.type==SDL_MOUSEMOTION){
                x=e.motion.x;
                y=e.motion.y;
                if(x>900 && x<1100 && y>600 && y<670 && player_set==1 && base_set==1){
                    is_in[0]=1;
                    SDL_SetRenderDrawColor(sdlRenderer, 0xcc, 0x11, 0x11, 0x00);
                    SDL_RenderClear(sdlRenderer);
                    draw_menu(colors_array, sdlRenderer, 1, menu_map);
                    SDL_RenderCopy(sdlRenderer,players_texture,NULL,&players_rect);
                    SDL_RenderCopy(sdlRenderer,bases_texture,NULL,&bases_rect);
                    SDL_RenderCopy(sdlRenderer,bn_texture,NULL,&bn_rect);
                    SDL_RenderCopy(sdlRenderer,pn_texture,NULL,&pn_rect);
                    continue_surface= TTF_RenderText_Solid(font,"continue",color1);
                    continue_texture= SDL_CreateTextureFromSurface(sdlRenderer,continue_surface);
                    SDL_RenderCopy(sdlRenderer,continue_texture,NULL,&continue_rect);
                    SDL_RenderCopy(sdlRenderer,back_texture,NULL,&Back_rect);
                    SDL_RenderPresent(sdlRenderer);
                } else if(is_in[0]==1 && !(x>900 && x<1100 && y>600 && y<670 && player_set==1 && base_set==1)){
                    is_in[0]=0;
                    SDL_SetRenderDrawColor(sdlRenderer, 0xcc, 0x11, 0x11, 0x00);
                    SDL_RenderClear(sdlRenderer);
                    draw_menu(colors_array, sdlRenderer, 1, menu_map);
                    SDL_RenderCopy(sdlRenderer,players_texture,NULL,&players_rect);
                    SDL_RenderCopy(sdlRenderer,bases_texture,NULL,&bases_rect);
                    SDL_RenderCopy(sdlRenderer,bn_texture,NULL,&bn_rect);
                    SDL_RenderCopy(sdlRenderer,pn_texture,NULL,&pn_rect);
                    continue_surface= TTF_RenderText_Solid(font,"continue",text_color);
                    continue_texture= SDL_CreateTextureFromSurface(sdlRenderer,continue_surface);
                    SDL_RenderCopy(sdlRenderer,continue_texture,NULL,&continue_rect);
                    SDL_RenderCopy(sdlRenderer,back_texture,NULL,&Back_rect);
                    SDL_RenderPresent(sdlRenderer);
                } if(x>100 && x<200 && y>600 && y<670 && player_set==1 && base_set==1){
                    is_in[1]=1;
                    SDL_SetRenderDrawColor(sdlRenderer, 0xcc, 0x11, 0x11, 0x00);
                    SDL_RenderClear(sdlRenderer);
                    draw_menu(colors_array, sdlRenderer, 1, menu_map);
                    SDL_RenderCopy(sdlRenderer,players_texture,NULL,&players_rect);
                    SDL_RenderCopy(sdlRenderer,bases_texture,NULL,&bases_rect);
                    SDL_RenderCopy(sdlRenderer,bn_texture,NULL,&bn_rect);
                    SDL_RenderCopy(sdlRenderer,pn_texture,NULL,&pn_rect);
                    back_surface= TTF_RenderText_Solid(font,"back",color1);
                    back_texture= SDL_CreateTextureFromSurface(sdlRenderer,back_surface);
                    SDL_RenderCopy(sdlRenderer,continue_texture,NULL,&continue_rect);
                    SDL_RenderCopy(sdlRenderer,back_texture,NULL,&Back_rect);
                    SDL_RenderPresent(sdlRenderer);
                }else if(is_in[1]==1 && !(x>100 && x<200 && y>600 && y<670 && player_set==1 && base_set==1)){
                    is_in[1]=0;
                    SDL_SetRenderDrawColor(sdlRenderer, 0xcc, 0x11, 0x11, 0x00);
                    SDL_RenderClear(sdlRenderer);
                    draw_menu(colors_array, sdlRenderer, 1, menu_map);
                    SDL_RenderCopy(sdlRenderer,players_texture,NULL,&players_rect);
                    SDL_RenderCopy(sdlRenderer,bases_texture,NULL,&bases_rect);
                    SDL_RenderCopy(sdlRenderer,bn_texture,NULL,&bn_rect);
                    SDL_RenderCopy(sdlRenderer,pn_texture,NULL,&pn_rect);
                    back_surface= TTF_RenderText_Solid(font,"back",text_color);
                    back_texture= SDL_CreateTextureFromSurface(sdlRenderer,back_surface);
                    SDL_RenderCopy(sdlRenderer,continue_texture,NULL,&continue_rect);
                    SDL_RenderCopy(sdlRenderer,back_texture,NULL,&Back_rect);
                    SDL_RenderPresent(sdlRenderer);
                }
            }
        }
    }
    SDL_FreeSurface(players_surface);
    SDL_FreeSurface(bases_surface);
    SDL_FreeSurface(back_surface);
    SDL_FreeSurface(continue_surface);
    SDL_FreeSurface(bn_surface);
    SDL_FreeSurface(pn_surface);
    SDL_DestroyTexture(players_texture);
    SDL_DestroyTexture(bases_texture);
    SDL_DestroyTexture(back_texture);
    SDL_DestroyTexture(continue_texture);
    SDL_DestroyTexture(bn_texture);
    SDL_DestroyTexture(pn_texture);
return menu_option;
}