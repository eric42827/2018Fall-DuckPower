#ifndef BUTTON_H
#define BUTTON_H
#include<LTexture.h>
#include<LButton.h>

class BUTTON
{
    public:
        BUTTON();
        virtual ~BUTTON();
        void load(std::string ave,std::string mouse_o){
            average_image.loadFromFile(ave);
            mouse_over_image.loadFromFile(mouse_o);
        }
        void init(int x,int y,int w,int h){
            button.setPosition(x,y);
            button.setdim(w,h);
        }
        void render(SDL_Event *e){
            int x=button.get_x();
            int y=button.get_y();
            button.handleEvent(e);
            if(button.get_sprite()==BUTTON_SPRITE_MOUSE_OVER_MOTION)mouse_over_image.render(x,y);
            else average_image.render(x,y);
        }
        LButtonSprite getsprite(){
            return button.get_sprite();
        }

    protected:
        LButton button;
    private:

        LTexture average_image;
        LTexture mouse_over_image;
};

#endif // BUTTON_H
