#include "choose_map.h"
#include "first_menu.h"


int choose_map(TTF_Font *font,SDL_Renderer *sdlRenderer,Uint32 colors_array[],int menu_map[][map_x-1])
{
    int state=0;
    int is_in=0,is_in1=0,is_in2=0,is_in3=0;
    int is_in4=0;

    SDL_Rect rect1={100,100,400,100};
    SDL_Rect rect2={100,300,100,100};
    SDL_Rect leak_rect={150,250,200,70};
    SDL_Rect back_rect={500,550,200,100};
    SDL_Rect rect[6];
    for(int i=0;i<6;i++){
        rect[i].x=600+150*i;
        if(i<3) {
            rect[i].y = 105;
        } else{
            rect[i].y = 300;
        }
        rect[i].w = 30;
        rect[i].h = 100;
    }
    SDL_Color text_color = {0x1E, 0x00, 0x1E, 0xff};
    Uint32 color=0xff0000ff;
    SDL_Color color1={0xff,0,0,255};
    SDL_Surface *back_surface= TTF_RenderText_Solid(font,"Back",text_color);
    SDL_Texture *back_texture= SDL_CreateTextureFromSurface(sdlRenderer,back_surface);

    SDL_Surface *leak_surface= TTF_RenderText_Solid(font,"leak test",text_color);
    SDL_Texture *leak_texture= SDL_CreateTextureFromSurface(sdlRenderer,leak_surface);

    SDL_Surface *original_surface= TTF_RenderText_Solid(font,"original maps:",text_color);
    SDL_Texture *original_Texture= SDL_CreateTextureFromSurface(sdlRenderer,original_surface);

    SDL_Surface *map1_surface= TTF_RenderText_Solid(font,"1",text_color);
    SDL_Texture *map1_Texture= SDL_CreateTextureFromSurface(sdlRenderer,map1_surface);
    SDL_Surface *map2_surface= TTF_RenderText_Solid(font,"2",text_color);
    SDL_Texture *map2_Texture= SDL_CreateTextureFromSurface(sdlRenderer,map2_surface);
    SDL_Surface *map3_surface= TTF_RenderText_Solid(font,"3",text_color);
    SDL_Texture *map3_Texture= SDL_CreateTextureFromSurface(sdlRenderer,map3_surface);


    SDL_SetRenderDrawColor(sdlRenderer, 0xcc, 0x11, 0x11, 0x00);
    SDL_RenderClear(sdlRenderer);
    draw_menu(colors_array, sdlRenderer, 1, menu_map);
    SDL_RenderCopy(sdlRenderer,original_Texture,NULL,&rect1);
    SDL_RenderCopy(sdlRenderer,map1_Texture,NULL,&rect[0]);
    SDL_RenderCopy(sdlRenderer,map2_Texture,NULL,&rect[1]);
    SDL_RenderCopy(sdlRenderer,map3_Texture,NULL,&rect[2]);
    SDL_RenderCopy(sdlRenderer,back_texture,NULL,&back_rect);
    SDL_RenderCopy(sdlRenderer,leak_texture,NULL,&leak_rect);

    SDL_RenderPresent(sdlRenderer);
    SDL_bool done=SDL_FALSE;
    while(!done){
        SDL_Event e;
        if(SDL_PollEvent(&e)){
            if(e.type== SDL_QUIT){
                state=-100;
                done=SDL_TRUE;
            }
            else if(e.type==SDL_MOUSEBUTTONDOWN && e.button.button==SDL_BUTTON_LEFT){
                if(is_in==1){
                    state=110;
                    done=SDL_TRUE;
                } else if(is_in1==1){
                    state=120;
                    done=SDL_TRUE;
                } else if(is_in2==1){
                    state=130;
                    done=SDL_TRUE;
                } else if(is_in3==1){
                    state=101;
                    done=SDL_TRUE;
                } else if(is_in4==1){
                    state=140;
                    done=SDL_TRUE;
                }
            }else if(e.type == SDL_MOUSEMOTION){
                int x=e.motion.x;
                int y=e.motion.y;
                if(x>600 && x<630 && y>105 && y<205){
                    is_in=1;
                    SDL_SetRenderDrawColor(sdlRenderer, 0xcc, 0x11, 0x11, 0x00);
                    SDL_RenderClear(sdlRenderer);
                    draw_menu(colors_array, sdlRenderer, 1, menu_map);
                    filledCircleColor(sdlRenderer,615,155,40,color);
                    aacircleRGBA(sdlRenderer,615,155,40,31,00,00,255);
                    aacircleRGBA(sdlRenderer,615,155,39,31,00,00,255);
                    aacircleRGBA(sdlRenderer,615,155,38,31,00,00,255);
                    SDL_RenderCopy(sdlRenderer,original_Texture,NULL,&rect1);
                    SDL_RenderCopy(sdlRenderer,map1_Texture,NULL,&rect[0]);
                    SDL_RenderCopy(sdlRenderer,map2_Texture,NULL,&rect[1]);
                    SDL_RenderCopy(sdlRenderer,map3_Texture,NULL,&rect[2]);
                    SDL_RenderCopy(sdlRenderer,back_texture,NULL,&back_rect);
                    SDL_RenderCopy(sdlRenderer,leak_texture,NULL,&leak_rect);
                    SDL_RenderPresent(sdlRenderer);

                } else if(is_in==1 && !(x>600 && x<630 && y>105 && y<205)){
                    is_in=0;
                    SDL_SetRenderDrawColor(sdlRenderer, 0xcc, 0x11, 0x11, 0x00);
                    SDL_RenderClear(sdlRenderer);
                    draw_menu(colors_array, sdlRenderer, 1, menu_map);
                    SDL_RenderCopy(sdlRenderer,original_Texture,NULL,&rect1);
                    SDL_RenderCopy(sdlRenderer,map1_Texture,NULL,&rect[0]);
                    SDL_RenderCopy(sdlRenderer,map2_Texture,NULL,&rect[1]);
                    SDL_RenderCopy(sdlRenderer,map3_Texture,NULL,&rect[2]);
                    SDL_RenderCopy(sdlRenderer,back_texture,NULL,&back_rect);
                    SDL_RenderCopy(sdlRenderer,leak_texture,NULL,&leak_rect);
                    SDL_RenderPresent(sdlRenderer);
                }else if(x>750 && x<780 && y>105 && y<205){
                    is_in1=1;
                    SDL_SetRenderDrawColor(sdlRenderer, 0xcc, 0x11, 0x11, 0x00);
                    SDL_RenderClear(sdlRenderer);
                    draw_menu(colors_array, sdlRenderer, 1, menu_map);
                    filledCircleColor(sdlRenderer,765,155,40,color);
                    aacircleRGBA(sdlRenderer,765,155,40,31,00,00,255);
                    aacircleRGBA(sdlRenderer,765,155,39,31,00,00,255);
                    aacircleRGBA(sdlRenderer,765,155,38,31,00,00,255);
                    SDL_RenderCopy(sdlRenderer,original_Texture,NULL,&rect1);
                    SDL_RenderCopy(sdlRenderer,map1_Texture,NULL,&rect[0]);
                    SDL_RenderCopy(sdlRenderer,map2_Texture,NULL,&rect[1]);
                    SDL_RenderCopy(sdlRenderer,map3_Texture,NULL,&rect[2]);
                    SDL_RenderCopy(sdlRenderer,back_texture,NULL,&back_rect);
                    SDL_RenderCopy(sdlRenderer,leak_texture,NULL,&leak_rect);
                    SDL_RenderPresent(sdlRenderer);
                } else if(is_in1==1 && !(x>750 && x<780 && y>105 && y<205)){
                    is_in1=0;
                    SDL_SetRenderDrawColor(sdlRenderer, 0xcc, 0x11, 0x11, 0x00);
                    SDL_RenderClear(sdlRenderer);
                    draw_menu(colors_array, sdlRenderer, 1, menu_map);
                    SDL_RenderCopy(sdlRenderer,original_Texture,NULL,&rect1);
                    SDL_RenderCopy(sdlRenderer,map1_Texture,NULL,&rect[0]);
                    SDL_RenderCopy(sdlRenderer,map2_Texture,NULL,&rect[1]);
                    SDL_RenderCopy(sdlRenderer,map3_Texture,NULL,&rect[2]);
                    SDL_RenderCopy(sdlRenderer,back_texture,NULL,&back_rect);
                    SDL_RenderCopy(sdlRenderer,leak_texture,NULL,&leak_rect);
                    SDL_RenderPresent(sdlRenderer);
                }else if(x>900 && x<930 && y>105 && y<205){
                    is_in2=1;
                    SDL_SetRenderDrawColor(sdlRenderer, 0xcc, 0x11, 0x11, 0x00);
                    SDL_RenderClear(sdlRenderer);
                    draw_menu(colors_array, sdlRenderer, 1, menu_map);
                    filledCircleColor(sdlRenderer,915,155,40,color);
                    aacircleRGBA(sdlRenderer,915,155,40,31,00,00,255);
                    aacircleRGBA(sdlRenderer,915,155,39,31,00,00,255);
                    aacircleRGBA(sdlRenderer,915,155,38,31,00,00,255);
                    SDL_RenderCopy(sdlRenderer,original_Texture,NULL,&rect1);
                    SDL_RenderCopy(sdlRenderer,map1_Texture,NULL,&rect[0]);
                    SDL_RenderCopy(sdlRenderer,map2_Texture,NULL,&rect[1]);
                    SDL_RenderCopy(sdlRenderer,map3_Texture,NULL,&rect[2]);
                    SDL_RenderCopy(sdlRenderer,back_texture,NULL,&back_rect);
                    SDL_RenderCopy(sdlRenderer,leak_texture,NULL,&leak_rect);
                    SDL_RenderPresent(sdlRenderer);
                } else if(is_in2==1 && !(x>900 && x<930 && y>105 && y<205)){
                    is_in2=0;
                    SDL_SetRenderDrawColor(sdlRenderer, 0xcc, 0x11, 0x11, 0x00);
                    SDL_RenderClear(sdlRenderer);
                    draw_menu(colors_array, sdlRenderer, 1, menu_map);
                    SDL_RenderCopy(sdlRenderer,original_Texture,NULL,&rect1);
                    SDL_RenderCopy(sdlRenderer,map1_Texture,NULL,&rect[0]);
                    SDL_RenderCopy(sdlRenderer,map2_Texture,NULL,&rect[1]);
                    SDL_RenderCopy(sdlRenderer,map3_Texture,NULL,&rect[2]);
                    SDL_RenderCopy(sdlRenderer,back_texture,NULL,&back_rect);
                    SDL_RenderCopy(sdlRenderer,leak_texture,NULL,&leak_rect);
                    SDL_RenderPresent(sdlRenderer);
                } else if(x>500 && x<700 && y>550 && y<650){
                    is_in3=1;
                    SDL_SetRenderDrawColor(sdlRenderer, 0xcc, 0x11, 0x11, 0x00);
                    SDL_RenderClear(sdlRenderer);
                    draw_menu(colors_array, sdlRenderer, 1, menu_map);
                    SDL_RenderCopy(sdlRenderer,original_Texture,NULL,&rect1);
                    SDL_RenderCopy(sdlRenderer,map1_Texture,NULL,&rect[0]);
                    SDL_RenderCopy(sdlRenderer,map2_Texture,NULL,&rect[1]);
                    SDL_RenderCopy(sdlRenderer,map3_Texture,NULL,&rect[2]);
                    SDL_Surface *back_surface= TTF_RenderText_Solid(font,"Back",color1);
                    SDL_Texture *back_texture= SDL_CreateTextureFromSurface(sdlRenderer,back_surface);
                    SDL_RenderCopy(sdlRenderer,back_texture,NULL,&back_rect);
                    SDL_RenderCopy(sdlRenderer,leak_texture,NULL,&leak_rect);
                    SDL_RenderPresent(sdlRenderer);
                } else if(is_in3==1 && !(x>500 && x<700 && y>550 && y<650)){
                    is_in3=0;
                    SDL_SetRenderDrawColor(sdlRenderer, 0xcc, 0x11, 0x11, 0x00);
                    SDL_RenderClear(sdlRenderer);
                    draw_menu(colors_array, sdlRenderer, 1, menu_map);
                    SDL_RenderCopy(sdlRenderer,original_Texture,NULL,&rect1);
                    SDL_RenderCopy(sdlRenderer,map1_Texture,NULL,&rect[0]);
                    SDL_RenderCopy(sdlRenderer,map2_Texture,NULL,&rect[1]);
                    SDL_RenderCopy(sdlRenderer,map3_Texture,NULL,&rect[2]);
                    SDL_Surface *back_surface= TTF_RenderText_Solid(font,"Back",text_color);
                    SDL_Texture *back_texture= SDL_CreateTextureFromSurface(sdlRenderer,back_surface);
                    SDL_RenderCopy(sdlRenderer,back_texture,NULL,&back_rect);
                    SDL_RenderCopy(sdlRenderer,leak_texture,NULL,&leak_rect);
                    SDL_RenderPresent(sdlRenderer);
                } else if(x>150 && x<350 && y>250 && y<320){
                    is_in4=1;
                    SDL_SetRenderDrawColor(sdlRenderer, 0xcc, 0x11, 0x11, 0x00);
                    SDL_RenderClear(sdlRenderer);
                    draw_menu(colors_array, sdlRenderer, 1, menu_map);
                    filledEllipseRGBA(sdlRenderer,250,285,130,40,255,0,0,255);
                    ellipseRGBA(sdlRenderer,250,285,130,40,31,00,31,255);
                    ellipseRGBA(sdlRenderer,250,285,129,39,31,00,31,255);
                    ellipseRGBA(sdlRenderer,250,285,128,38,31,00,31,255);
                    SDL_RenderCopy(sdlRenderer,original_Texture,NULL,&rect1);
                    SDL_RenderCopy(sdlRenderer,map1_Texture,NULL,&rect[0]);
                    SDL_RenderCopy(sdlRenderer,map2_Texture,NULL,&rect[1]);
                    SDL_RenderCopy(sdlRenderer,map3_Texture,NULL,&rect[2]);
                    SDL_RenderCopy(sdlRenderer,back_texture,NULL,&back_rect);
                    SDL_RenderCopy(sdlRenderer,leak_texture,NULL,&leak_rect);
                    SDL_RenderPresent(sdlRenderer);
                } else if(is_in4==1 && !(x>150 && x<350 && y>250 && y<320)){
                    is_in4=0;
                    SDL_SetRenderDrawColor(sdlRenderer, 0xcc, 0x11, 0x11, 0x00);
                    SDL_RenderClear(sdlRenderer);
                    draw_menu(colors_array, sdlRenderer, 1, menu_map);
                    SDL_RenderCopy(sdlRenderer,original_Texture,NULL,&rect1);
                    SDL_RenderCopy(sdlRenderer,map1_Texture,NULL,&rect[0]);
                    SDL_RenderCopy(sdlRenderer,map2_Texture,NULL,&rect[1]);
                    SDL_RenderCopy(sdlRenderer,map3_Texture,NULL,&rect[2]);
                    SDL_RenderCopy(sdlRenderer,back_texture,NULL,&back_rect);
                    SDL_RenderCopy(sdlRenderer,leak_texture,NULL,&leak_rect);
                    SDL_RenderPresent(sdlRenderer);
                }
            }
        }

    }

    SDL_DestroyTexture(original_Texture);
    SDL_DestroyTexture(map1_Texture);
    SDL_DestroyTexture(map2_Texture);
    SDL_DestroyTexture(map3_Texture);
    SDL_FreeSurface(original_surface);
    SDL_FreeSurface(map2_surface);
    SDL_FreeSurface(map1_surface);
    SDL_FreeSurface(map3_surface);

    SDL_DestroyTexture(back_texture);
    SDL_DestroyTexture(leak_texture);
    SDL_FreeSurface(back_surface);
    SDL_FreeSurface(leak_surface);
    return state;
}