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
        void set_xy(int a,int b){
            x=a;y=b;
        }
        int get_x(){return x;}
        int get_y(){return y;}

        //set and get pos
        void setpos(int a){pos=a;}
        int get_pos(){return pos;}

        //extension of the functions in lbutton
        void handleEvent(SDL_Event* e){
            loop_button.handleEvent(e);
        }
        LButtonSprite getsprite(){
            return loop_button.get_sprite();
        }

        //render the image of loop
        void render(int position,SDL_Event* e,LButtonSprite sprite,base *a,LTexture* image_default,LTexture* image_trigger){

            const int x_i=x_dis/2-x_adj,y_i=y_dis/2-y_adj;
            pos=position;
            set_xy(a[position].x,a[position].y);
            loop_button.setPosition(a[position].x+x_i,a[position].y+y_i);
            loop_button.setdim(x_unit,y_unit);
            loop_button.handleEvent(e);

            if(loop_button.get_sprite()==sprite)image_trigger->render(x,y);
            else image_default->render(x,y);

        }

};

#endif // LOOP_H
