#include "mainmap.h"
#include "iostream"

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

void mainmap::map_but(SDL_Event &a,int &mode){
    //std::cout<<l_x<<" "<<l_y<<'\n';
    if(clean){
        handleEvent(&a);
        setPosition(l_x,l_y);
        setdim(mWidth,mHeight);
        if(get_sprite()==BUTTON_SPRITE_MOUSE_OVER_MOTION){
            //sound[swipe].playsound();
            render(l_x,l_y);
            //printf("correct");
        }
        else if(get_sprite()==BUTTON_SPRITE_MOUSE_DOWN){
            //mode = k;
            sound[0].playsound();
            mode=k;
            return;
        }
        else render(l_x,l_y,0.9,0.9);
    }else {setColor(100,100,100);render(l_x,l_y);}
return;
}

void mainmap::menu_but(SDL_Event &a,int &mode){
    handleEvent(&a);
    setPosition(l_x,l_y);
    setdim(mWidth,mHeight);
    if(get_sprite()==BUTTON_SPRITE_MOUSE_OVER_MOTION){
        //sound[swipe].playsound();
        setColor(255,255,100);
        render(l_x,l_y);
    }
    else if(get_sprite()==BUTTON_SPRITE_MOUSE_DOWN){
        sound[0].playsound();
        mode=k;
        return;
    }
    else {setColor(255,255,255);render(l_x,l_y);}
    return;
}
void mainmap::mapmusic(){
    for(int i=0;i<SOUND;i++)sound[i].loadsound(sound_name[i]);
}
