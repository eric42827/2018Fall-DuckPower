#ifndef MAINMAP_H
#define MAINMAP_H
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include<cmath>
#include<LTexture.h>
#include<LButton.h>

class mainmap :public LTexture,public LButton
{
    public:
        friend class Map;
        mainmap();
        virtual ~mainmap();


    protected:

    private:
        int l_x,l_y,k;
        bool clean =true;
        //int map_but(SDL_Event &,LTexture &,LButton &);
        //void scroll(bool x,bool y,bool inf,LTexture &l);
        void set_value(int,int,int);
        void map_but(SDL_Event &a,int &mode);
        void menu_but(SDL_Event &a,int &mode){
            handleEvent(&a);
            setPosition(l_x,l_y);
            setdim(mWidth,mHeight);
                if(get_sprite()==BUTTON_SPRITE_MOUSE_OVER_MOTION){
                    setColor(255,255,100);
                    render(l_x,l_y);
                }
                else if(get_sprite()==BUTTON_SPRITE_MOUSE_DOWN){
                    mode=k;
                    return;
                }
                else {setColor(255,255,255);render(l_x,l_y);}
            return;
        }



};

#endif // MAINMAP_H
