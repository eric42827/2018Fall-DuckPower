#ifndef BUTTON_ARRANGE_CHA_H
#define BUTTON_ARRANGE_CHA_H
#include<BUTTON_ARRANGE.h>
#include<LTexture.h>
class BUTTON_ARRANGE_CHA:public BUTTON_ARRANGE
{
    public:
        BUTTON_ARRANGE_CHA();
        virtual ~BUTTON_ARRANGE_CHA();
        void render_act(SDL_Event *e);
        void handle(int &mode,int obj,int &chosen,int obj2,int click,clock_t start_time,music &sound);

    protected:

    private:
};

#endif // BUTTON_ARRANGE_CHA_H
