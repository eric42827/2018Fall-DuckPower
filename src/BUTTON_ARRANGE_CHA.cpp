#include "BUTTON_ARRANGE_CHA.h"

BUTTON_ARRANGE_CHA::BUTTON_ARRANGE_CHA()
{
    //ctor
}

BUTTON_ARRANGE_CHA::~BUTTON_ARRANGE_CHA()
{
    //dtor
}
void BUTTON_ARRANGE_CHA::render_act(SDL_Event *e){
            int x=button.get_x();
            int y=button.get_y();
            button.handleEvent(e);
            if(button.get_sprite()==BUTTON_SPRITE_MOUSE_OVER_MOTION or button.get_sprite()==BUTTON_SPRITE_MOUSE_DOWN){image.setAlpha(255);image.render(x,y);}
            else {image.setAlpha(155);image.render(x,y);}
}
void BUTTON_ARRANGE_CHA::handle(int &mode,int obj,int &chosen,int obj2,int click,clock_t start_time,music &sound){
            if(this->getsprite()==BUTTON_SPRITE_MOUSE_DOWN and click==1){
                chosen=obj2;
                mode=obj;
                start_time=clock();
                sound.playsound();
            }
}
