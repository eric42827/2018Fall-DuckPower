#ifndef BATTLE_SETTING_H
#define BATTLE_SETTING_H

#define num_of_people 15
#define num_of_loop 6

#include<LTexture.h>
#include<BUTTON_ARRANGE.h>
#include<BUTTON_ARRANGE_CHA.h>
#include<BUTTON_ARRANGE_LOOP.h>
#include<music.h>

#include<ctime>

class BATTLE_SETTING
{
    public:
        BATTLE_SETTING();
        BATTLE_SETTING(int category);
        virtual ~BATTLE_SETTING();
        void arrange(SDL_Event *e,int& mode);
        int get_cha(int a);/***cpp h swap***/
    protected:

    private:
        LTexture background;
        LTexture no_man;
        LTexture white_loop;
        LTexture yellow_loop;
        LTexture characters[num_of_people];
        LTexture characters_on[num_of_people];

        BUTTON_ARRANGE_LOOP loops[num_of_loop];
        BUTTON_ARRANGE_CHA charac_button[num_of_people];
        BUTTON exit;

        const std::string character_image[num_of_people]={
        "image/human/normal.png",
        "image/human/human1.png",
        "image/human/human2.png",
        "image/human/shooter.png",
        "image/human/batman.png",
        "image/human/ike.png",
        "image/human/human3.png",
        "image/human/human4.png",
        "image/human/fly.png",
        "image/human/shooter2.png",
        "image/human/magic1.png",
        "image/human/fly2.png",
        "image/human/fly3.png",
        "image/human/roy.png",
        "image/human/legend.png"
        };


        int step;
        bool prev_click_flag;
        bool now_click_flag;
        int chosen;
        clock_t start_time;
        int clock_on;

        int cha[num_of_loop];
        bool on[num_of_loop];

        void load();
        void initialize(int);
        music sound;
};

#endif // BATTLE_SETTING_H
