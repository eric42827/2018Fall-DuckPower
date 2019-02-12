#ifndef MEN_WITH_ARMS_H
#define MEN_WITH_ARMS_H
#include <stdio.h>
#include<iostream>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include<stdlib.h>
#include<cmath>

#include<LButton.h>
#include<LTexture.h>
#include<base.h>
#include<ctime>
//extern const double x_dis;extern const double y_dis;
enum soldier_arms{
    melee=0,
    archer=1,
    air_force=2

};
enum soldier_character{
    //DUCKS
    NO_MEN=0,
    DUCK_ORI=1,
    DUCK_GREEN=2,
    DUCK_RED=3,
    DUCK_BEIJING=4,
    SWAN=5,
    BLACK_SWAN=6,
    SEAGULL=7,
    CEIBA=8,
    PENGUIN=9,
    RED_BIRD=10,
    RUBBER_DUCK=11,
    MOLTRES=12,


    NORMAL=13,
    HUMAN1=14,
    HUMAN2=15,
    SHOOTER=16,
    BATMAN=17,
    IKE =18,
    HUMAN3=19,
    HUMAN4=20,
    FLY=21,
    SHOOTER2=22,
    MAGIC1=23,
    FLY2=24,
    FLY3=25,
    ROY=26,
    LEGEND=27

};
enum number_of_soldier
{
 none=0,
 MY_1=1,
 MY_2=2,
 MY_3=3,
 MY_4=4,
 MY_5=5,
 MY_6=6,
 FOE_1=7,
 FOE_2=8,
 FOE_3=9,
 FOE_4=10,
 FOE_5=11,
 FOE_6=12,
 NEUTRAL_1=13,
 NEUTRAL_2=14,
 NEUTRAL_3=15,
 NEUTRAL_4=16,
 NEUTRAL_5=17,
 NEUTRAL_6=18,
};

class men_with_arms
{
    public:
        men_with_arms();
        virtual ~men_with_arms();
        men_with_arms& operator+(const int &);
        int operator-(men_with_arms *);



    friend class BATTLE_SCENE;
    friend class BATTLE_SCENE_SINGAL;
    friend class BATTLE_SCENE_MULTI;
    friend class GO_JUDGER;
    protected:

    private:
        //id and attributes of soldiers
        int id;
        soldier_character character;
        soldier_arms arms;
        int x,y;
        int width;
        int height;
        int pos;

        //combat properties
        int max_health;
        int health;
        int strength;
        int move_range;
        int move_points;
        int fire_range;

        //animation variables
        clock_t start;
        bool perform;

        //images alongside soldiers
        LTexture image_stand;
        LTexture image_fight;
        LTexture arms_icon;
        LTexture bar_bottom_image;
        LTexture bar_top_image;

        //Randomize attack_points
        int Random(int strength);

        //set and get x,y
        void set_xy(int a,int b);
        int get_x();
        int get_y();

        //set and get pos
        void setpos(int a);
        int get_pos();


        //set and get basic attributes of soldiers
        void set_character(soldier_character a);
        void set_arms(soldier_arms a);
        soldier_arms get_arms();
        void set_id(int a);
        //set and get combat properties
        void set_maxhealth(int a);
        int get_maxhealth();

        void set_health(int a);
        int get_health();

        void set_strength(int a);
        int get_strength();

        void set_range(int a);
        int getrange();

		void set_point(int a);
		int getpoint();

        int get_firerange();
        void set_firerange(int a);


        //render images of soldier
        void render(int position,base *a);

        //move to another tile
        void go(int new_pos,base* a);

        //fight with another soldier on another tile
        void fight(men_with_arms **foe,base *a,int foe_id);

        //set combat properties
        void set_property(soldier_character cha,int arms_input,int health_input,int strength_input,int range_input,int fire_range_input);

        //load images of soldier
        void load(std::string stand,std::string fight_in,std::string bar_b,std::string bar_t,std::string icon){
            image_stand.loadFromFile(stand);
            image_fight.loadFromFile(fight_in);
            bar_bottom_image.loadFromFile(bar_b);
            bar_top_image.loadFromFile(bar_t);
            arms_icon.loadFromFile(icon);
        }

};

#endif // MEN_WITH_ARMS_H
