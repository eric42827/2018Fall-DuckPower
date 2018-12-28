#ifndef MEN_WITH_ARMS_H
#define MEN_WITH_ARMS_H
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL_image.h>

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
    NO_MEN=0,
    DUCK_ORI=1,
    DUCK_GREEN=2,
    DUCK_RED=3,
    DUCK_BEIJING=4,
    SWAN=5,
    BLACK_SWAN=6

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



    friend class BATTLE_SCENE;

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
        LTexture *bar_bottom_image;
        LTexture *bar_top_image;

        //set and get x,y
        void set_xy(int a,int b){
            x=a;y=b;
        }
        int get_x(){return x;}
        int get_y(){return y;}

        //set and get pos
        void setpos(int a){pos=a;}
        int get_pos(){return pos;}


        //set and get basic attributes of soldiers
        void set_character(soldier_character a){character=a;}
        void set_arms(soldier_arms a){arms=a;}
        soldier_arms get_arms(){return arms;}
        void set_id(int a){id=a;}

        //set and get combat properties
        void set_maxhealth(int a){max_health=a;}
        int get_maxhealth(){return max_health;}

        void set_health(int a){health=a;}
        int get_health(){return health;}

        void set_strength(int a){strength=a;}
        int get_strength(){return strength;}

        void set_range(int a){
            move_range=a;
        }
        int getrange(){return move_range;}

		void set_point(int a){
            move_points=a;
        }
		int getpoint(){return move_points;}

        int get_firerange(){return fire_range;}
        void set_firerange(int a){fire_range=a;}


        //render images of soldier
        void render(int position,base *a){
            //set position
            const int x_i=(x_dis/2-x_adj),y_i=(y_dis/2-y_adj);
            pos=position;
            set_xy(a[position].x+x_i,a[position].y+y_i);
            width=x_unit;height=y_unit;

            if(id>=FOE_1 and id<=FOE_6){
                if(perform==0)image_stand.flip_render(x,y);
                else if(perform==1){
                    image_fight.flip_render(x,y);
                    clock_t now=clock();
                    if(now-start>=500)perform=0;
            }
            }
            else{
            if(perform==0)image_stand.render(x,y);
            else if(perform==1){
                    image_fight.render(x,y);
                    clock_t now=clock();
                    if(now-start>=500)perform=0;
            }}
            //set health bar
            bar_bottom_image->render(x,y+height);
            SDL_Rect barclip[1];
            double rate;
            if(max_health!=0)rate=(health*1.0)/(max_health*1.0);
            else rate=0;
            barclip[0].x =   0;
            barclip[0].y =   0;
            barclip[0].w =   (bar_top_image->getWidth())*rate;//*(this->health)/(this->max_health);
            barclip[0].h =   bar_top_image->getHeight();
            bar_top_image->render(x,y+height,&barclip[0]);
            a[position].setsoldier_num(id);

            //set icon
            if(id>=MY_1 and id<=MY_6 ){
            if(move_points!=0)arms_icon.setAlpha(255);
            else arms_icon.setAlpha(100);
            arms_icon.render(x,y);}
            else if(id>=FOE_1 and id<=FOE_6 ){
            if(move_points!=0)arms_icon.setAlpha(255);
            else arms_icon.setAlpha(100);
            arms_icon.render(x+width-x_adj,y);}
        }

        //move to another tile
        void go(int new_pos,base* a){
            int mem=pos;
            const int x_l=(x_dis/2-x_adj),y_l=(y_dis/2-y_adj);
            pos=new_pos;
            x=a[pos].x+x_l;y=a[pos].y+y_l;
            a[new_pos].setsoldier_num(id);
            a[mem].setsoldier_num(0);
        }

        //fight with another soldier on another tile
        void fight(men_with_arms **foe,base *a,int foe_id){
            foe[foe_id]->set_health(foe[foe_id]->get_health()-this->get_strength());
            //set animation time
            this->perform=1;
            start=clock();
            if((this->arms==melee)or(this->arms==air_force)){
                if(foe[foe_id]->get_health()<=0){
                    int mem=this->get_pos();
                    this->go(foe[foe_id]->get_pos(),a);
                    a[mem].setsoldier_num(0);
                    delete foe[foe_id];
                    foe[foe_id]=NULL;

                    /*******/
                }
            }
            else if(this->arms==archer){
                if(foe[foe_id]->get_health()<=0){
                    int mem=foe[foe_id]->get_pos();
                    a[mem].setsoldier_num(0);
                    delete foe[foe_id];
                    foe[foe_id]=NULL;
                }
            }
        }
        //set combat properties
        void set_property(soldier_character cha,int arms_input,int health_input,int strength_input,int range_input,int fire_range_input){
            character=cha;
            arms=soldier_arms(arms_input);
            max_health=health_input;
            health=health_input;
            strength=strength_input;
            move_range=range_input;
            fire_range=fire_range_input;
        }
        //load images of soldier
        void load(std::string stand,std::string fight_in,LTexture*bar_b,LTexture*bar_t,std::string icon){
            image_stand.loadFromFile(stand);
            image_fight.loadFromFile(fight_in);
            bar_bottom_image=bar_b;
            bar_top_image=bar_t;
            arms_icon.loadFromFile(icon);
        }
};

#endif // MEN_WITH_ARMS_H
