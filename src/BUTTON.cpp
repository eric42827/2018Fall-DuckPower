#include "BUTTON.h"

BUTTON::BUTTON()
{

}

BUTTON::~BUTTON()
{

}
void BUTTON::load(std::string ave,std::string mouse_o){
            average_image.loadFromFile(ave);
            mouse_over_image.loadFromFile(mouse_o);
}
void BUTTON::init(int x,int y,int w,int h){
            button.setPosition(x,y);
            button.setdim(w,h);
}
void BUTTON::render(SDL_Event *e){
            int x=button.get_x();
            int y=button.get_y();
            button.handleEvent(e);
            if(button.get_sprite()==BUTTON_SPRITE_MOUSE_OVER_MOTION)mouse_over_image.render(x,y);
            else average_image.render(x,y);
}
void BUTTON::handle(int &mode,int obj,int click,clock_t &start_time,music &sound){
    if(this->getsprite()==BUTTON_SPRITE_MOUSE_DOWN and click==1){
        mode=obj;
        start_time=clock();
        sound.playsound();
    }
}
LButtonSprite BUTTON::getsprite(){
            return button.get_sprite();
        }
