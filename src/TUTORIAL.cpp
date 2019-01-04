#include "TUTORIAL.h"

TUTORIAL::TUTORIAL()
{
   initialize();
}

TUTORIAL::~TUTORIAL()
{
    //dtor
}
void TUTORIAL::initialize(){
for(int k=0;k<TUTORIAL_PICTURE_NUM;k++)tutorial_image[k].loadFromFile(tutorial_pic_name[k]);
previous.load("image/character/duck_ori_quack.png","image/character/duck_ori_quack.png");
next.load("image/character/duck_green_quack.png","image/character/duck_green_quack.png");

previous.init(0,0,100,100);
next.init(1000,0,100,100);
slide=0;
on=0;
}
void TUTORIAL::teach(SDL_Event *e){
    //render
    tutorial_image[slide].render(0,0);

    if(slide!=0 and slide!=TUTORIAL_PICTURE_NUM){
        next.render(e);
        previous.render(e);
        if(next.getsprite()==BUTTON_SPRITE_MOUSE_DOWN){
            on=2;
            start_time=clock();
        }
        else if(previous.getsprite()==BUTTON_SPRITE_MOUSE_DOWN){
            on=1;
            start_time=clock();
        }

        if(on==2 and clock()-start_time>200){
            slide++;
            on=0;
        }
        else if(on==1 and clock()-start_time>200){
            slide--;
            on=0;
        }
    }
    else if(slide==0){
        next.render(e);

        if(next.getsprite()==BUTTON_SPRITE_MOUSE_DOWN){
            on=2;
            start_time=clock();
        }


        if(on==2 and clock()-start_time>200){
            slide++;
            on=0;
        }

    }
    else if(slide==TUTORIAL_PICTURE_NUM-1){
        previous.render(e);

        if(next.getsprite()==BUTTON_SPRITE_MOUSE_DOWN){
            on=1;
            start_time=clock();
        }


        if(on==1 and clock()-start_time>200){
            slide--;
            on=0;
        }

    }
}
