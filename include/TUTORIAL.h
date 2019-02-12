#define _GLIBCXX_USE_CXX11_ABI 0
#ifndef TUTORIAL_H
#define TUTORIAL_H
#include<iostream>
#include<ctime>
#include "definition.h"

#include<LTexture.h>
#include<BUTTON.h>
#include<music.h>
#define TUTORIAL_PICTURE_NUM 9

class TUTORIAL
{
    public:
        TUTORIAL();
        virtual ~TUTORIAL();
        void teach(SDL_Event *e);
    protected:

    private:
        LTexture tutorial_image[TUTORIAL_PICTURE_NUM];
        BUTTON previous;
        BUTTON next;
        const std::string tutorial_pic_name[TUTORIAL_PICTURE_NUM]={
         "image/tutorial/tutorial01.png" ,
         "image/tutorial/tutorial02.png" ,
         "image/tutorial/tutorial03.png" ,
         "image/tutorial/tutorial04.png" ,
         "image/tutorial/tutorial05.png" ,
         "image/tutorial/tutorial06.png" ,
         "image/tutorial/tutorial07.png" ,
         "image/tutorial/tutorial08.png" ,
         "image/tutorial/tutorial09.png"
        };
        int slide;
        clock_t start_time;
        int on;
        music sound[SOUND];
        bool click_pre;

        void initialize();
        const string sound_name[SOUND]={
        "music/click2.wav",
        "music/nc.wav",
        "music/wan.wav"
        };

};

#endif // TUTORIAL_H
