#define _GLIBCXX_USE_CXX11_ABI 0
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
previous.load("image/tutorial/previous.png","image/tutorial/previous.png");
next.load("image/tutorial/next.png","image/tutorial/next.png");

for(int i=0;i<SOUND;i++)sound[i].loadsound(sound_name[i]);

previous.init(0,320,200,80);
next.init(1080,320,200,80);
slide=0;
on=0;
click_pre=0;
}
void TUTORIAL::teach(SDL_Event *e){
    //render
    tutorial_image[slide].render(0,0);

    bool click=(e->type==SDL_MOUSEBUTTONDOWN);
    click=click-click_pre;

     
    if(slide!=0 and slide!=TUTORIAL_PICTURE_NUM-1){
        next.render(e);
        previous.render(e);

        next.handle(on,2,click,start_time,sound[0]);
        previous.handle(on,1,click,start_time,sound[0]);

        if(on==2 and clock()-start_time>20){
            slide++;
            #ifdef DEBUG
            printf("%d",slide);
            #endif
            on=0;
        }
        else if(on==1 and clock()-start_time>20){
            slide--;
            #ifdef DEBUG
            printf("%d",slide);
            #endif
            on=0;
        }
    }
    else if(slide==0){
        next.render(e);
        next.handle(on,2,click,start_time,sound[0]);
        #ifdef DEBUG
        if(on==2)printf("%d,on= %d,clock=%d,start_time=%d\n",slide,on,clock(),start_time);
        #endif
        if(on==2 and clock()-start_time>20){
            slide++;
            #ifdef DEBUG
            printf("%d",slide);
            #endif
            on=0;
        }

    }
    else if(slide==TUTORIAL_PICTURE_NUM-1){

        previous.render(e);
        previous.handle(on,1,click,start_time,sound[0]);

        if(on==1 and clock()-start_time>20){
            slide--;
            #ifdef DEBUG
            printf("%d",slide);
            #endif
            on=0;
        }

    }
    click_pre=(e->type==SDL_MOUSEBUTTONDOWN);
}
