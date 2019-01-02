#ifndef STORE_BUTTON_H
#define STORE_BUTTON_H
#include<LTexture.h>
#include<LButton.h>
#include<string.h>
class STORE_BUTTON
{
    public:
        STORE_BUTTON();
        virtual ~STORE_BUTTON();
        load(std::string ave,std::string over){
            average_image.loadFromFile(ave);
            mouse_over_image.loadFromFile(over);
        }
        void create(int x,int y,int w,int h){
            button.setPosition(x,y);
            button.setdim(w,h);
        }
        void render(SDL_Event *e,bool done){
            if(done==0){
            int x=button.get_x();
            int y=button.get_y();
            button.handleEvent(e);
            if(button.get_sprite()==BUTTON_SPRITE_MOUSE_OVER_MOTION)mouse_over_image.render(x,y);
            else if(button.get_sprite()==BUTTON_SPRITE_MOUSE_OUT)average_image.render(x,y);
            else if(button.get_sprite()==BUTTON_SPRITE_MOUSE_DOWN)mouse_over_image.render(x,y);
            }

        }
        bool button_click(SDL_Event *e){
            button.handleEvent(e);
            if(button.get_sprite()==BUTTON_SPRITE_MOUSE_OVER_MOTION)return 0;
            else if(button.get_sprite()==BUTTON_SPRITE_MOUSE_OUT)return 0;
            else if(button.get_sprite()==BUTTON_SPRITE_MOUSE_DOWN)return 1;
            else if(button.get_sprite()==BUTTON_SPRITE_MOUSE_UP)return 0;
        }
    protected:

    private:
        LButton button;
        LTexture average_image;
        LTexture mouse_over_image;
};

#endif // BUTTON_H
