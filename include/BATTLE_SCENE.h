#define _GLIBCXX_USE_CXX11_ABI 0
#ifndef BATTLE_SCENE_H
#define BATTLE_SCENE_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<loop.h>
#include<LTexture.h>
#include<LButton.h>
#include<men_with_arms.h>
#include<base.h>
#include<BUTTON.h>

#include <fstream>
#include <sstream>
#include <stdlib.h>
#include<ctime>
#include "definition.h"

enum L_texture_name{
field=0,
loop_tile=1,
loop_select=2,
loop_target=3,
loop_foe=4,
loop_aim=5,

next_turn=6,
waiting=7,
bar_bottom=8,
bar_top=9,
none_loop=10,
king=11,
victory=12,
barrier=13,
defeat=14,
melee_icon=15,
archer_icon=16,
air_force_icon=17,
duck_melee_icon=18,
duck_archer_icon=19,
duck_air_force_icon=20
};


enum property_of_soldiers{
 arms_property=0,
 health_property=1,
 combat_strength_property=2,
 range_property=3,
 firerange_property=4

};
enum whose_turn
{
 MY=1,
 FOE=0,
 FROZEN=2
};
enum which_step
{
 SELECT_UNIT=0,
 SELECT_TARGET=1
};




class BATTLE_SCENE
{
    public:
        BATTLE_SCENE();
        BATTLE_SCENE(int category);
        virtual ~BATTLE_SCENE();

        /***Battle***/
        void battle(SDL_Event &e,int &mode);

    protected:


        LTexture scene_image[image_num];

        LButton next_turn_button;

        BUTTON *exit;

        men_with_arms ** soldier;

        base tiles[tiles_num];

        loop target[tar_num];
        loop select[sol_num+1];

        clock_t start_time;
        bool clock_on;
        bool on;

        bool ai_perform;
        bool end_ai;



        whose_turn turn;
        which_step step;
        bool prev_click_flag;
        bool now_click_flag;

        const std::string field_name[field_num]={/*****order*****/
        "image/field/field01.png",
        "image/field/field01.png",
        "image/field/field01.png",
        "image/field/field01.png",
        "image/field/field01.png",
        "image/field/field01.png",
        "image/field/field01.png",
        "image/field/field01.png",
        "image/field/field01.png",
        "image/field/field01.png",
        "image/field/field01.png",
        "image/field/field01.png"


        };
        const std::string scene_image_name[image_num]={/*****order*****/
        "image/battle.png",
        "image/whiteloop.png",
        "image/yellowloop.png",
        "image/greenloop.png",
        "image/redloop.png",
        "image/blueloop.png",
        "image/next_turn.png",
        "image/waiting.png",
        "image/bar_bottom.png",
        "image/bar_top.png" ,
        "image/none.png" ,
        "image/king.png",
        "image/victory.png",
        "image/barrier.png",
        "image/defeat.png",
        "image/melee_icon.png",
        "image/archer_icon.png",
        "image/air_force_icon.png",
        "image/duck_melee_icon.png",
        "image/duck_archer_icon.png",
        "image/duck_air_force_icon.png"

        };
        const std::string name_icon[icon_num+1]={
        "image/none.png" ,
        "image/melee_icon.png",
        "image/archer_icon.png",
        "image/air_force_icon.png",
        "image/duck_melee_icon.png",
        "image/duck_archer_icon.png",
        "image/duck_air_force_icon.png"
        };
        const std::string stand_image_name[character_num+1]={
        "image/none.png" ,
        "image/character/duck_ori.png",
        "image/character/duck_green.png",
        "image/character/duck_red.png",
        "image/character/duck_beijing.png",
        "image/character/swan.png",
        "image/character/black_swan.png",
        "image/character/seagull.png",
        "image/character/ceiba.png",
        "image/character/penguin.png",
        "image/character/red_bird.png",
        "image/character/rubber_duck.png",
        "image/character/moltres.png",
        //Humans
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
        const std::string battle_image_name[character_num+1]={
        "image/none.png" ,
        "image/character/duck_ori_quack.png",
        "image/character/duck_green_quack.png",
        "image/character/duck_red_quack.png",
        "image/character/duck_beijing_quack.png",
        "image/character/swan_quack.png",
        "image/character/black_swan_quack.png",
        "image/character/seagull_quack.png",
        "image/character/ceiba_quack.png",
        "image/character/penguin_quack.png",
        "image/character/red_bird_quack.png",
        "image/character/rubber_duck_quack.png",
        "image/character/moltres_quack.png",
        //Humans
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
        //store property
        int property[character_num][property_num];
        LTexture icons[icon_num];

        /***Primary Level Function***/
        int abs(int a);
        int distance(int pos1,int pos2,base* a);
        bool judge(int sel,int sel2,int dis,int tar,base *a);

        /***Secondary Level Function***/
        int show_target(int sel,SDL_Event* e,base *a,int n);
        int foe_target(int sel,base *a,int n);
        int read_target(int sel,base *a,int n,int* pre_pos);

        /***Third Level Function***/
        int soldier_view(int sel,SDL_Event *e,base *a);
        void setMonte(base *a);

        /***Highest Level Function***/
        void create_battlefield();
        void set_soldiers();

        void show_select(SDL_Event& e,which_step& step,int& sel,int click);
        void buttons_target_show(SDL_Event& e,which_step& step,int& sel,int click);
        void AI(int k);
        bool victory_judge(base* a,int sacred);
        void load();

        /*****Initialization****/
        void initialize(int category);
    private:


};

#endif // BATTLE_SCENE_H
