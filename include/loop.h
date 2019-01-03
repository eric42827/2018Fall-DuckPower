#ifndef LOOP_H
#define LOOP_H
#include <SDL2/SDL.h>
#include <SDL_image.h>

#include<LButton.h>
#include<LTexture.h>
#include<base.h>

class loop
{
    public:
        loop();
        virtual ~loop();


        friend class BATTLE_SCENE;
    protected:

    private:

        int x,y;
        int pos;
        LButton loop_button;

        //set and get x,y
        void set_xy(int a,int b);
        int get_x();
        int get_y();

        //set and get pos
        void setpos(int a);
        int get_pos();

        //extension of the functions in lbutton
        void handleEvent(SDL_Event* e);
        LButtonSprite getsprite();

        //render the image of loop
        void render(int position,SDL_Event* e,LButtonSprite sprite,base *a,LTexture* image_default,LTexture* image_trigger);

};

#endif // LOOP_H
