#ifndef MAINMAP_H
#define MAINMAP_H
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include<cmath>
#include<LTexture.h>
#include<LButton.h>

class mainmap
{
    public:
        friend class Map;
        mainmap();
        virtual ~mainmap();


    protected:

    private:
        int l_x,l_y,k;

        void set_value(int,int,int);
        int map_but(SDL_Event &,LTexture &,LButton &);
        void map_but(SDL_Event &a,LTexture &l,LButton &b,int &mode);
        //void map_but(SDL_Event &,LTexture &,LButton &,int &,int,int,int);
        void menu_but(SDL_Event &a,LTexture &l,LButton &b,int &mode){
            //std::cout<<l_x<<" "<<l_y<<'\n';
            b.handleEvent(&a);
            b.setPosition(l_x,l_y);
            b.setdim(l.mWidth,l.mHeight);
                if(b.get_sprite()==BUTTON_SPRITE_MOUSE_OVER_MOTION){
                    l.setColor(255,255,100);
                    l.render(l_x,l_y);
                    //printf("correct");
                }
                else if(b.get_sprite()==BUTTON_SPRITE_MOUSE_DOWN){
                    //mode = k;
                    mode=k;
                    return;
                }
                else {l.setColor(255,255,255);l.render(l_x,l_y);}

        return;
                    //SDL_RenderPresent( gRenderer );
        }



};

#endif // MAINMAP_H
