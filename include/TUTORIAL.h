#ifndef TUTORIAL_H
#define TUTORIAL_H
#include<iostream>
#include<ctime>

#include<LTexture.h>
#include<BUTTON.h>
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

        void initialize();

};

#endif // TUTORIAL_H
