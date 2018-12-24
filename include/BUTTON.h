#ifndef BUTTON_H
#define BUTTON_H
#include<LTexture.h>
#include<LButton.h>

class BUTTON
{
    public:
        BUTTON();
        virtual ~BUTTON();
        void load(LTexture* average,LTexture* mouse_over){
            average_image=average;
            mouse_over_image=mouse_over;
        }
        void init(int x,int y,int w,int h){
            button->setPosition(x,y);
            button->setdim(w,h);
        }
        void render(SDL_Event *e){
            int x=button->get_x();
            int y=button->get_y();
            button->handleEvent(e);
            if(button->get_sprite()==BUTTON_SPRITE_MOUSE_OVER_MOTION)mouse_over_image->render(x,y);
            else if(button->get_sprite()==BUTTON_SPRITE_MOUSE_OUT)average_image->render(x,y);
        }
    protected:

    private:
        LButton *button;
        LTexture *average_image;
        LTexture *mouse_over_image;
};

#endif // BUTTON_H
