#ifndef MEN_WITH_ARMS_H
#define MEN_WITH_ARMS_H
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include<LButton.h>
#include<LTexture.h>
#include<base.h>
#include<ctime>
extern const double x_dis;extern const double y_dis;
enum soldier_arms{
    melee=0,
    archer=1,
    air_force=2

};
enum soldier_character{
    NO_MEN=0,
    DUCK_ORI=1,
    DUCK_GREEN=2

};
extern const double x_dis;
extern const double y_dis;

class men_with_arms
{
    public:
        men_with_arms();
        virtual ~men_with_arms();
void set_xy(int a,int b){
            x=a;y=b;
        }
        void setpos(int a){pos=a;}
        int get_pos(){return pos;}
        int getwidth(){return width;}
		int getheight(){return height;}
		int getrange(){return move_range;}
		int getpoint(){return move_points;}
		void setdim(int a,int b){width=a;height=b;}
        int get_x(){return x;}
        int get_y(){return y;}
        void go(int new_pos,base* a){
            int x_l,y_l;int mem=pos;
            x_l=x_dis/2-25;y_l=y_dis/2-50;
        pos=new_pos;
        x=a[pos].get_x()+x_l;y=a[pos].get_y()+y_l;
        a[new_pos].setsoldier_num(id);
        a[mem].setsoldier_num(0);
        }
        void set_range(int a){
            move_range=a;
        }
        void set_point(int a){
            move_points=a;
        }
        int get_firerange(){return fire_range;}
        void set_firerange(int a){fire_range=a;}

        void render(int position,base *a){
            //set position
            const int x_i=x_dis/2-25,y_i=y_dis/2-50;
            pos=position;
            set_xy(a[position].get_x()+x_i,a[position].get_y()+y_i);
            width=100;height=100;
            if(perform==0)image_stand.render(x,y);
            else if(perform==1){
                    image_fight.render(x,y);

                    clock_t now=clock();
                    if(now-start>=1000)perform=0;
                    }
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
            //icon->
            if(move_points!=0)arms_icon.setAlpha(255);
            else arms_icon.setAlpha(100);
            arms_icon.render(x,y);
        }
        void set_character(soldier_character a){character=a;}
        void set_arms(soldier_arms a){arms=a;}
        soldier_arms get_arms(){return arms;}
        void set_id(int a){id=a;}
        void set_maxhealth(int a){max_health=a;}
         int get_maxhealth(){return max_health;}
        void set_health(int a){health=a;}
        int get_health(){return health;}
        void set_strength(int a){strength=a;}
        int get_strength(){return strength;}
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
        void set_property(soldier_character cha,int arms_input,int health_input,int strength_input,int range_input,int fire_range_input){
            character=cha;
            arms=soldier_arms(arms_input);
            max_health=health_input;
            health=health_input;
            strength=strength_input;
            move_range=range_input;
            fire_range=fire_range_input;
        }
        void load(std::string stand,std::string fight_in,LTexture*bar_b,LTexture*bar_t,std::string icon){
            image_stand.loadFromFile(stand);
            image_fight.loadFromFile(fight_in);
            bar_bottom_image=bar_b;
            bar_top_image=bar_t;
            arms_icon.loadFromFile(icon);
        }



    protected:

    private:

        int id;
        soldier_character character;
        soldier_arms arms;
        int x,y;
        int width;
        int height;
        int pos;

        int max_health;
        int health;
        int strength;
        int move_range;
        int move_points;
        int fire_range;
        clock_t start;
        bool perform;

        LTexture image_stand;
        LTexture image_fight;
        LTexture arms_icon;
        LTexture *bar_bottom_image;
        LTexture *bar_top_image;
};

#endif // MEN_WITH_ARMS_H
