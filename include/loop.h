#ifndef LOOP_H
#define LOOP_H
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include<LButton.h>
#include<LTexture.h>
#include<base.h>


extern const double x_dis;extern const double y_dis;

class loop
{
    public:
        loop();
        virtual ~loop();
        void set_xy(int a,int b){
            x=a;y=b;
        }
        void setpos(int a){pos=a;}
        int get_pos(){return pos;}
        int get_x(){return x;}
        int get_y(){return y;}
        void handleEvent(SDL_Event* e){
            loop_button.handleEvent(e);
        }
        LButtonSprite getsprite(){
            return loop_button.get_sprite();
        }
        void render(int position,SDL_Event* e,LButtonSprite sprite,base *a,LTexture* image_default,LTexture* image_trigger){

            const int x_i=x_dis/2-25,y_i=y_dis/2-50;
            pos=position;
            set_xy(a[position].get_x(),a[position].get_y());
            loop_button.setPosition(a[position].get_x()+x_i,a[position].get_y()+y_i);
            loop_button.setdim(100,100);
            loop_button.handleEvent(e);

            if(loop_button.get_sprite()==sprite)image_trigger->render(x,y);
            else image_default->render(x,y);

        }
        void test(int position,LButtonSprite sprite,base *a,LTexture image_default){
        }
    protected:

    private:

        int x,y;
        int pos;

        LButton loop_button;

};

#endif // LOOP_H
