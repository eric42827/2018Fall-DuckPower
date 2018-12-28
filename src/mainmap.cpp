#include "mainmap.h"


mainmap::mainmap()
{

}

mainmap::~mainmap()
{
    //dtor
}
void mainmap::set_value(int x,int y,int z){
    l_x=x;l_y=y;k=z;
}
int mainmap::map_but(SDL_Event &a,LTexture &l,LButton &b){
    b.handleEvent(&a);
    b.setPosition(l_x,l_y);
    b.setdim(l.mWidth,l.mHeight);
    /*if(k==1){
        if(b.get_sprite()==BUTTON_SPRITE_MOUSE_OVER_MOTION){
            l.render(l_x,l_y,1.05,1.05);
            //printf("correct");
        }
        else if(b.get_sprite()==BUTTON_SPRITE_MOUSE_DOWN){
            //mode = k;
            std::cout<<k;
            return k;
        }
        else l.render(l_x,l_y);
    }
    else{*/
        if(b.get_sprite()==BUTTON_SPRITE_MOUSE_OVER_MOTION){
            l.render(l_x,l_y,0.55,0.55);
            //printf("correct");
        }
        else if(b.get_sprite()==BUTTON_SPRITE_MOUSE_DOWN){
            //mode = k;
            //std::cout<<k;
            return k;
        }
        else l.render(l_x,l_y,0.5,0.5);
    //}

return 0;
            //SDL_RenderPresent( gRenderer );
}

void mainmap::map_but(SDL_Event &a,LTexture &l,LButton &b,int &mode){
    b.handleEvent(&a);
    b.setPosition(l_x,l_y);
    b.setdim(l.mWidth,l.mHeight);
    /*if(k==1){
        if(b.get_sprite()==BUTTON_SPRITE_MOUSE_OVER_MOTION){
            l.render(l_x,l_y,1.05,1.05);
            //printf("correct");
        }
        else if(b.get_sprite()==BUTTON_SPRITE_MOUSE_DOWN){
            //mode = k;
            std::cout<<k;
            return k;
        }
        else l.render(l_x,l_y);
    }
    else{*/
        if(b.get_sprite()==BUTTON_SPRITE_MOUSE_OVER_MOTION){
            l.render(l_x,l_y,0.55,0.55);
            //printf("correct");
        }
        else if(b.get_sprite()==BUTTON_SPRITE_MOUSE_DOWN){
            //mode = k;
            mode=k;
            return;
        }
        else l.render(l_x,l_y,0.5,0.5);
    //}

return;
            //SDL_RenderPresent( gRenderer );
}
