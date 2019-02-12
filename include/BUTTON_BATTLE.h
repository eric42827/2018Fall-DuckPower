#ifndef BUTTON_BATTLE_H
#define BUTTON_BATTLE_H

#include<base.h>
#include<LTexture.h>
#include<LButton.h>
#include<ctime>
#include<music.h>
#include<BUTTON.h>

class BUTTON_BATTLE:public BUTTON
{
    public:
        BUTTON_BATTLE();
        virtual ~BUTTON_BATTLE();
        void load(std::string ave,std::string mouse_o,std::string alert);
        void set_pos(int position,base *a);
        void render(SDL_Event *e,int position,base *a);
        void render_alarm(SDL_Event *e,int position,base *a);
        void handle(int &mode,int obj,int& sel,int click,clock_t start_time,music *sound);
        int get_pos(){return pos;}
    protected:

    private:
        int pos;

        LTexture alert_image;

};

#endif // BUTTON_BATTLE_H
