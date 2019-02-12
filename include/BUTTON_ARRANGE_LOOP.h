#ifndef BUTTON_ARRANGE_LOOP_H
#define BUTTON_ARRANGE_LOOP_H
#include<BUTTON_ARRANGE.h>
#include<LTexture.h>
class BUTTON_ARRANGE_LOOP:public BUTTON_ARRANGE
{
    public:
        BUTTON_ARRANGE_LOOP();
        virtual ~BUTTON_ARRANGE_LOOP();
        BUTTON_ARRANGE_LOOP& operator+(const int& a);

        void render_act(SDL_Event *e);
        void handle(int &mode,int obj,int chosen,int click,clock_t start_time,music &sound);
        int get_cha(){return cha;}
        int get_on(){return on;}


    protected:

    private:
        int on;
        int cha;

};

#endif // BUTTON_ARRANGE_LOOP_H
