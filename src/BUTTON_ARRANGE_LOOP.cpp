#include "BUTTON_ARRANGE_LOOP.h"

BUTTON_ARRANGE_LOOP::BUTTON_ARRANGE_LOOP()
{
    on=0;
    cha=-13;
}

BUTTON_ARRANGE_LOOP::~BUTTON_ARRANGE_LOOP()
{
    //dtor
}
void BUTTON_ARRANGE_LOOP::render_act(SDL_Event *e){
            int x=button.get_x();
            int y=button.get_y();
            button.handleEvent(e);
            if((button.get_sprite()==BUTTON_SPRITE_MOUSE_OVER_MOTION or button.get_sprite()==BUTTON_SPRITE_MOUSE_DOWN)and on==0){over_image.render(x,y);}
            else image.render(x,y);
}
void BUTTON_ARRANGE_LOOP::handle(int &mode,int obj,int chosen,int click,clock_t start_time,music &sound){
            if(this->getsprite()==BUTTON_SPRITE_MOUSE_DOWN and click==1 and on==0){
                *this=*this+chosen;
                mode=obj;
                start_time=clock();
                sound.playsound();
            }
}
BUTTON_ARRANGE_LOOP& BUTTON_ARRANGE_LOOP::operator+(const int& a){
    this->cha=a;
    this->on=1;
    return *this;
}
