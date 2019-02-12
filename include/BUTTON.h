#ifndef BUTTON_H
#define BUTTON_H
#include<LTexture.h>
#include<LButton.h>
#include<ctime>
#include<music.h>

class BUTTON
{
    public:
        BUTTON();
        virtual ~BUTTON();
        void load(std::string ave,std::string mouse_o);
        void init(int x,int y,int w,int h);
        void render(SDL_Event *e);
        void handle(int &mode,int obj,int click,clock_t &start_time,music &sound);
        LButtonSprite getsprite();
    protected:
        LButton button;
        LTexture average_image;
        LTexture mouse_over_image;
    private:


};

#endif // BUTTON_H
