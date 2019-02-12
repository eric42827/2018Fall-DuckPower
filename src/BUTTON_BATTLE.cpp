#include "BUTTON_BATTLE.h"

BUTTON_BATTLE::BUTTON_BATTLE()
{

}

BUTTON_BATTLE::~BUTTON_BATTLE()
{
    //dtor
}
void BUTTON_BATTLE::load(std::string ave,std::string mouse_o,std::string alert){
    average_image.loadFromFile(ave);
    mouse_over_image.loadFromFile(mouse_o);
    alert_image.loadFromFile(alert);
}

void BUTTON_BATTLE::set_pos(int position,base *a){
    pos=position;

    const int x_i=x_dis/2-x_adj,y_i=y_dis/2-y_adj;
    int x=a[position].x+x_i;
    int y=a[position].y+y_i;
    button.setPosition(x,y);

}
void BUTTON_BATTLE::render(SDL_Event *e,int position,base *a){
    pos=position;
    const int x_i=x_dis/2-x_adj,y_i=y_dis/2-y_adj;
    button.setPosition(a[position].x+x_i,a[position].y+y_i);
    button.handleEvent(e);
    if(button.get_sprite()==BUTTON_SPRITE_MOUSE_OVER_MOTION)mouse_over_image.render(a[position].x,a[position].y);
    else average_image.render(a[position].x,a[position].y);

}
void BUTTON_BATTLE::render_alarm(SDL_Event *e,int position,base *a){
    pos=position;
    const int x_i=x_dis/2-x_adj,y_i=y_dis/2-y_adj;
    button.setPosition(a[position].x+x_i,a[position].y+y_i);
    button.handleEvent(e);
    if(button.get_sprite()==BUTTON_SPRITE_MOUSE_OVER_MOTION)mouse_over_image.render(a[position].x,a[position].y);
    else alert_image.render(a[position].x,a[position].y);

}
void BUTTON_BATTLE::handle(int &mode,int obj,int& sel,int click,clock_t start_time,music *sound){
if(this->getsprite()==BUTTON_SPRITE_MOUSE_DOWN and click==1){
        mode=obj;
        start_time=clock();
        sound->playsound();
        sel=pos;
    }
}
