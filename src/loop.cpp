#include "loop.h"

loop::loop()
{
    //ctor
}

loop::~loop()
{
    //dtor
}
void loop::set_xy(int a,int b){
            x=a;y=b;
        }
int loop::get_x(){return x;}
int loop::get_y(){return y;}

void loop::setpos(int a){pos=a;}
int loop::get_pos(){return pos;}


void loop::handleEvent(SDL_Event* e){
    loop_button.handleEvent(e);
}
LButtonSprite loop::getsprite(){
    return loop_button.get_sprite();
}

void loop::render(int position,SDL_Event* e,LButtonSprite sprite,base *a,LTexture* image_default,LTexture* image_trigger){
    const int x_i=x_dis/2-x_adj,y_i=y_dis/2-y_adj;
    pos=position;
    set_xy(a[position].x,a[position].y);
    loop_button.setPosition(a[position].x+x_i,a[position].y+y_i);
    loop_button.setdim(x_unit,y_unit);
    loop_button.handleEvent(e);

    if(loop_button.get_sprite()==sprite)image_trigger->render(x,y);
    else image_default->render(x,y);

}
