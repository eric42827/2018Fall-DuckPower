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
#include <fstream>
#include <sstream>
#include <stdlib.h>

#define character_num 2
#define property_num 5
#define cha_image 1
#define image_num 21
#define icon_num 7

 //dimensions of base loops
        //const double x_dis=135.0;
       // const double y_dis=150.0;
       extern const double x_dis;extern const double y_dis;
        extern const int SCREEN_WIDTH ;
        extern const int SCREEN_HEIGHT ;
const std::string str[image_num]={/*****order*****/
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
const std::string name_icon[image_num]={
        "image/none.png" ,
        "image/melee_icon.png",
        "image/archer_icon.png",
        "image/air_force_icon.png",
        "image/duck_melee_icon.png",
        "image/duck_archer_icon.png",
        "image/duck_air_force_icon.png"
        };
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
 NEUTRAL_2=14
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
 MY=0,
 FOE=1
};
enum which_step
{
 SELECT_UNIT=0,
 SELECT_TARGET=1
};

const int tiles_num=40;
const int tar_num=60;
const int sol_num=6;


class BATTLE_SCENE
{
    public:
        BATTLE_SCENE();
        virtual ~BATTLE_SCENE();
        /***Primary Level Function***/
        int abs(int a){
            if(a<0)return -a;
            else return a;
        }
        int distance(int pos1,int pos2,base* a){
            const double x=(a[pos2].get_x()-a[pos1].get_x())/x_dis;
            const double y=(a[pos2].get_y()-a[pos1].get_y())/y_dis;
            int dist=0;
            if(x==0)dist=abs(y);
            else{
                const double m=y/x;
                if((m>-0.5)and(m<0.5)and(x>0))dist=x;
                else if((m>-0.5)and(m<0.5)and(x<0))dist=-x;
                else if((m>0.5)and(x>0))dist=0.5*x+y;
                else if((m>0.5)and(x<0))dist=-(0.5*x+y);
                else if((m<-0.5)and(x>0))dist=0.5*x-y;
                else if((m<-0.5)and(x<0))dist=-(0.5*x-y);
                else if((m==0.5)or(m==-0.5))dist=abs(x);
                }
                return dist;
        }
        bool judge(int sel,int sel2,int dis,int tar,base *a){
            return(sel2!=tar)*(sel2<tiles_num)*(sel2>=0)*(abs(a[sel2].get_y()-a[sel].get_y())==dis);
        }
        /***Secondary Level Function***/
        int show_target(int sel,SDL_Event* e,base *a,int n){/****sacred***/
            static bool flag=0;
            static int count=0;
            static bool check[tiles_num];
            static int tar;
            static int max_level;
            static soldier_arms arms;
            if(flag==0){
                    tar=sel;
                    max_level=n;
                    for(int k=0;k<tiles_num;k++)check[k]=0;
                    arms=soldier[a[sel].get_num()]->get_arms();
            }
            if(n==0){
                if((sel!=tar)and(sel!=sacred1)){
                    if((a[sel].get_num()==none)){
                        target[count].render(sel,e,BUTTON_SPRITE_MOUSE_OVER_MOTION,tiles,&scene_image[loop_target],&scene_image[loop_aim]);
                        count++;
                    }
                }
            }
            else{
                flag=1;
                int door=((a[sel].get_num()==none)or((a[sel].get_num()>=MY_1)and(a[sel].get_num()<=MY_6)));
                if(check[sel]==0){
                    show_target(sel,e,a, 0);check[sel]=1;}
                    int next[6]={sel-1,sel+1,sel+y_num,sel-y_num,sel+y_num-1,sel-y_num+1};
                    int dis[6]={y_dis,y_dis,y_dis/2,y_dis/2,y_dis/2,y_dis/2};
                    for(int k=0;k<6;k++){
                        if(judge(sel,next[k],dis[k],tar,tiles)and check[next[k]]==0 and door==true)show_target(next[k],e,a, n-1);
                    }
            }
            int mem=0;
            if((sel==tar)and(n==max_level)){
                    if(arms!=air_force){
                        for(int k=0;k<tiles_num;k++){
                            if((a[k].get_num()<=FOE_6)and(a[k].get_num()>=FOE_1)and(distance(k,sel,a)<=soldier[a[sel].get_num()]->get_firerange())){
                                target[count].render(k,e,BUTTON_SPRITE_MOUSE_OVER_MOTION,tiles,&scene_image[loop_foe],&scene_image[loop_aim]);
                                count++;
                            }
                        }
                    }
                    else{
                        for( int i = FOE_1; i <=FOE_6; i ++){
                            if(soldier[i]!=NULL){
                                target[count].render(soldier[i]->get_pos(),e,BUTTON_SPRITE_MOUSE_OVER_MOTION,tiles,&scene_image[loop_foe],&scene_image[loop_aim]);
                                count++;
                            }
                        }
                    }
                for(int k=0;k<tiles_num;k++)check[k]=0;
                mem=count;
                count=0;
                flag=0;
            }
            return mem;
        }

        int foe_target(int sel,base *a,int n){
            static bool flag=0;
            static int count=0;
            static bool check[tiles_num];
            static int tar;
            static int max_level;
            static soldier_arms arms;
            if(flag==0){
                    tar=sel;
                    max_level=n;
                    for(int k=0;k<tiles_num;k++)check[k]=0;
                    arms=soldier[a[sel].get_num()]->get_arms();
            }
            if(n==0){
                if((sel!=tar)and(sel!=sacred2)){
                    if((a[sel].get_num()==none)){
                        count++;
                    }
                }
            }
            else{
                flag=1;
                int door=((a[sel].get_num()==none)or((a[sel].get_num()>=FOE_1)and(a[sel].get_num()<=FOE_6)));
                if(check[sel]==0){
                    foe_target(sel,a, 0);check[sel]=1;}
                    int next[6]={sel-1,sel+1,sel+y_num,sel-y_num,sel+y_num-1,sel-y_num+1};
                    int dis[6]={y_dis,y_dis,y_dis/2,y_dis/2,y_dis/2,y_dis/2};
                    for(int k=0;k<6;k++){
                        if(judge(sel,next[k],dis[k],tar,tiles)and check[next[k]]==0 and door==true)foe_target(next[k],a, n-1);
                    }
            }
            int mem=0;
            if((sel==tar)and(n==max_level)){
                    if(arms!=air_force){
                        for(int k=0;k<tiles_num;k++){
                            if((a[k].get_num()<=MY_6)and(a[k].get_num()>=MY_1)and(distance(k,sel,a)<=soldier[a[sel].get_num()]->get_firerange())){
                                count++;
                            }
                        }
                    }
                    else{
                        for( int i = MY_1; i <=MY_6; i ++){
                            if(soldier[i]!=NULL){
                                count++;
                            }
                        }
                    }
                for(int k=0;k<tiles_num;k++)check[k]=0;
                mem=count;
                count=0;
                flag=0;
            }
            return mem;

        }
        int read_target(int sel,base *a,int n,int* pre_pos){
            static bool flag=0;
            static int count=0;
            static bool check[tiles_num];
            static int tar;
            static int max_level;
            static soldier_arms arms;
            if(flag==0){
                    tar=sel;
                    max_level=n;
                    for(int k=0;k<tiles_num;k++)check[k]=0;
                    arms=soldier[a[sel].get_num()]->get_arms();
            }
            if(n==0){
                if((sel!=tar)and(sel!=sacred2)){
                    if((a[sel].get_num()==none)){
                        pre_pos[count]=sel;
                        count++;
                    }
                }
            }
            else{
                flag=1;
                int door=((a[sel].get_num()==none)or((a[sel].get_num()>=FOE_1)and(a[sel].get_num()<=FOE_6)));
                if(check[sel]==0){
                    read_target(sel,a, 0,pre_pos);check[sel]=1;}
                    int next[6]={sel-1,sel+1,sel+y_num,sel-y_num,sel+y_num-1,sel-y_num+1};
                    int dis[6]={y_dis,y_dis,y_dis/2,y_dis/2,y_dis/2,y_dis/2};
                    for(int k=0;k<6;k++){
                        if(judge(sel,next[k],dis[k],tar,tiles)and check[next[k]]==0 and door==true)read_target(next[k],a, n-1,pre_pos);
                    }
            }
            int mem=0;
            if((sel==tar)and(n==max_level)){
                    if(arms!=air_force){
                        for(int k=0;k<tiles_num;k++){
                            if((a[k].get_num()<=MY_6)and(a[k].get_num()>=MY_1)and(distance(k,sel,a)<=soldier[a[sel].get_num()]->get_firerange())){
                                pre_pos[count]=k;
                                count++;
                            }
                        }
                    }
                    else{
                        for( int i = MY_1; i <=MY_6; i ++){
                            if(soldier[i]!=NULL){
                                pre_pos[count]=soldier[i]->get_pos();
                                count++;
                            }
                        }
                    }
                for(int k=0;k<tiles_num;k++)check[k]=0;
                mem=count;
                count=0;
                flag=0;
            }
            return mem;

        }
        /***Third Level Function***/
        int soldier_view(int sel,SDL_Event *e,base *a){
            const int mem=show_target(sel,e,a,soldier[a[sel].get_num()]->getpoint());
            return mem;
        }
        void setMonte(base *a){
            for(int k=0;k<tiles_num;k++){
            if(k!=sacred1)a[k].set_Monte(sacredmonte/(degenerate_rate*distance(k,sacred1,a)));
            else a[k].set_Monte(sacredmonte*2);
            int num=a[k].get_num();
            if(num>=MY_1 and num<=MY_6)a[k].set_Monte(a[k].get_Monte()+foe_enhance+foe_health_incr*(soldier[num]->get_maxhealth()-soldier[num]->get_health()));
            }
        }
        /***Highest Level Function***/
        void create_battlefield(){
            scene_image[field].render( 0,0);
            const int x_l=x_dis/2-25;const int y_l=y_dis/2-50;
            scene_image[king].render(tiles[sacred1].get_x()+x_l,tiles[sacred1].get_y()+y_l);
            scene_image[king].render(tiles[sacred2].get_x()+x_l,tiles[sacred2].get_y()+y_l);
            for(int a=0;a<tiles_num;a++)scene_image[loop_tile].render(tiles[a].get_x(),tiles[a].get_y());
        }
        void set_soldiers(){
            for(int a=MY_1;a<=FOE_6;a++){
                if(soldier[a]!=NULL){
                    soldier[a]->render(soldier[a]->get_pos(),tiles,&scene_image[melee_icon]);/*******/
                }
            }

            /*for(int a=NEUTRAL_1;a<=NEUTRAL_2;a++){
                if(soldier[a]!=NULL){
                    soldier[a]->render(soldier[a]->get_pos(),tiles,&scene_image[barrier],&scene_image[none_loop],&scene_image[none_loop],&scene_image[none_loop]);/*******/
               /* }
            }*/
        }
        void initialize_game(){
            //load image
            load();

            //property loading
            std::fstream file;
            file.open("property.csv");
            std::string line;
            int a=0;
            while (getline( file, line,'\n'))  //讀檔讀到跳行字元
            {
                std::istringstream templine(line); // string 轉換成 stream
                std::string data;

                int buffer=2;
                for(int b=0;b<buffer;b++){
                    getline( templine, data,',');
                }
                for(int b=0;b<property_num;b++){
                    getline( templine, data,',');
                    property[a][b]=atoi(data.c_str());//std::cout<<property[a][b];
                }
                for(int c=0;c<cha_image;c++){
                    getline( templine, data,',');
                    name_of_image[a][c]=data;
                }
                a++;
            }

            file.close();
            soldier_character soldier_cha[sol_num*2+1]={DUCK_ORI,DUCK_ORI,DUCK_ORI,DUCK_ORI,DUCK_ORI,DUCK_ORI,DUCK_ORI
                                            ,DUCK_GREEN,DUCK_GREEN,DUCK_GREEN,DUCK_GREEN,DUCK_GREEN,DUCK_GREEN};

            //tiles
			int count=0;
			for(int a=0;a<x_num;a++){
                    for(int b=0;b<y_num-(a+1)%2;b++){
                        tiles[count].set_xy(a*x_dis+x_init, b*y_dis+y_init+y_dis*((a+1)%2)/2);
                        tiles[count].setsoldier_num(none);
                        count++;
                    }
				}
            //our soldiers
            /********/
            //soldiers position
            soldier=new men_with_arms*[2*sol_num+1+2];/*****/
            for(int a=MY_1;a<=NEUTRAL_2;a++)soldier[a]=new men_with_arms;
            int init_pos[15]={0,5,7,1,2,10,11,32,34,28,29,37,38,18,21};/***********/

            for(int a=MY_1;a<=FOE_6;a++){
                    if(soldier[a]!=NULL){
                    int k=soldier_cha[a];
                    soldier[a]->set_id(a);
                    int icon_label=((a-1)/6)*3+soldier_cha[a]+1;
                    soldier[a]->load(name_of_image[k][0],&scene_image[bar_bottom],&scene_image[bar_top],name_icon[icon_label]);
                    soldier[a]->render(init_pos[a],tiles,&scene_image[melee_icon]);
                                        soldier[a]->set_property(soldier_cha[a],property[k][arms_property],property[k][health_property]
                                             ,property[k][combat_strength_property],property[k][range_property],property[k][firerange_property]);


                    }
				}
            //FOE soldiers

            //soldiers position


            /*for(int a=NEUTRAL_1;a<=NEUTRAL_2;a++){
                    if(soldier[a]!=NULL){
                    soldier[a]->set_id(a);
                    soldier[a]->render(init_pos[a],tiles,&scene_image[barrier],&scene_image[none_loop],&scene_image[none_loop],&scene_image[none_loop]);
                    soldier[a]->set_firerange(1);
                    soldier[a]->set_range(1);/*********/
                    /*soldier[a]->set_character(DUCK_GREEN);
                    soldier[a]->set_arms(air_force);
                    soldier[a]->set_maxhealth(100);
                    soldier[a]->set_health(100);
                    soldier[a]->set_strength(20);
                    }
				}*/
            //buttons position and dimensions
            int l_x=x_next;int l_y=y_next;
            next_turn_button.setPosition(l_x,l_y);
            next_turn_button.setdim(scene_image[next_turn].getWidth(),scene_image[next_turn].getHeight());
        }
        void show_select(SDL_Event& e,which_step& step,int& sel,int click){
            for( int i = MY_1; i <=MY_6; i ++)
            {
            if(soldier[i]!=NULL){
                select[i].render(soldier[i]->get_pos(),& e,BUTTON_SPRITE_MOUSE_OVER_MOTION,tiles,&scene_image[none_loop],&scene_image[loop_select]);
                if(select[i].getsprite()==BUTTON_SPRITE_MOUSE_DOWN){
                    if(click==1){
                        step=SELECT_TARGET;
                        sel=soldier[i]->get_pos();
                    }
                }
            }
            }
        }
        void buttons_target_show(SDL_Event& e,which_step& step,int& sel,int click){
            int count;
            const int pt=soldier[tiles[sel].get_num()]->getpoint();
            if(pt!=0){
                count=soldier_view(sel,&e,tiles);
                for( int i = 0; i < count; i ++)
                {
                    if(click==1){
                        if(target[ i ].getsprite()==BUTTON_SPRITE_MOUSE_DOWN){
                            int num=tiles[target[ i ].get_pos()].get_num();
                            if(num==none){
                                soldier[tiles[sel].get_num()]->set_point(soldier[tiles[sel].get_num()]->getpoint()-distance(target[ i ].get_pos(),sel,tiles));
                                soldier[tiles[sel].get_num()]->go(target[ i ].get_pos(),tiles);
                                step=SELECT_UNIT;
                                break;
                            }
                            else if((num<=FOE_6)and(num>=FOE_1)){
                                soldier[tiles[sel].get_num()]->set_point(0);
                                soldier[tiles[sel].get_num()]->fight(soldier,tiles,num);
                                step=SELECT_UNIT;
                                break;
                            }
                        }
                        else {
                            step=SELECT_UNIT;
                        }
                    }
                }
            }
            else{
                step=SELECT_UNIT;
            }
        }
        void AI(){
            for(int k=0;k<tiles_num;k++){
                tiles[k].set_foe(false);

            }
            for(int k=FOE_1;k<=FOE_6;k++){
                if(soldier[k]!=NULL)soldier[k]->set_point(soldier[k]->getrange());
            }

            for(int k=FOE_1;k<=FOE_6;k++){
                if(soldier[k]!=NULL){
                    setMonte(tiles);
                    int list_length;
                    list_length=foe_target(soldier[k]->get_pos(),tiles,soldier[k]->getrange());
                    int pre_pos[list_length];
                    read_target(soldier[k]->get_pos(),tiles,soldier[k]->getrange(),pre_pos);
                    double mont=tiles[pre_pos[0]].get_Monte();
                    int pos=pre_pos[0];
                    for(int j=0;j<list_length;j++){
                        if(tiles[pre_pos[j]].get_Monte()>=mont){
                            mont=tiles[pre_pos[j]].get_Monte();
                            pos=pre_pos[j];}
                    }
                    for(int k=0;k<tiles_num;k++)tiles[k].set_Monte(0);
                    int num=tiles[pos].get_num();
                    if(num==none)soldier[k]->go(pos,tiles);
                    else if((num>=MY_1)and(num<=MY_6)) soldier[k]->fight(soldier,tiles,num);

                    //if(k==FOE_6)printf("%d",list_length);
                    //else if((list_length==0)) soldier[k]->go(0,tiles);
                }
            }
            for(int j=0;j<tiles_num;j++)tiles[j].set_foe(false);
        }
        bool victory_judge(base* a,int sacred){
            if(a[sacred].get_num()!=0)return true;
            else return false;
        }
        void load(){
        for(int k=0;k<image_num;k++){
            scene_image[k].loadFromFile(str[k]);
        }

        }
        /***Battle***/
        void battle(SDL_Event &e,bool &quit){
            static whose_turn turn=MY;
            static which_step step=SELECT_UNIT;
            static bool prev_click_flag=0;
            static bool now_click_flag=0;
            //Handle events on queue
				now_click_flag = ( e.type == SDL_MOUSEBUTTONDOWN );
				int click=now_click_flag-prev_click_flag;
				//Clear screen

				/*******visualization*******/
				//field and tiles
				create_battlefield();
				//soldiers
				set_soldiers();
                //victory judge
                if(victory_judge(tiles,sacred2)){
                        scene_image[victory].render(SCREEN_WIDTH/2-scene_image[victory].getWidth()/2,SCREEN_HEIGHT/2-scene_image[victory].getHeight()/2);
                        quit=true;
                }
                if(victory_judge(tiles,sacred1)){
                        scene_image[defeat].render(SCREEN_WIDTH/2-scene_image[victory].getWidth()/2,SCREEN_HEIGHT/2-scene_image[victory].getHeight()/2);
                        quit=true;
                }
                static bool start=0;
                if(turn==MY){
                    scene_image[next_turn].render(next_turn_button.get_x(),next_turn_button.get_y());
                    next_turn_button.handleEvent( &e );
                    if(next_turn_button.get_sprite()==BUTTON_SPRITE_MOUSE_DOWN){
                            if(click==1){
                            turn=FOE;
                            }
                    }
                    if(start ==0){
                        for(int k=MY_1;k<=MY_6;k++){
                            if(soldier[k]!=NULL){
                               soldier[k]->set_point(soldier[k]->getrange());
                            }
                        }
                        start=1;
                    }
                    static int sel;

                    if(step==SELECT_UNIT){
                        show_select(e,step,sel,click);
                    }
                    else if(step==SELECT_TARGET){
                        buttons_target_show(e,step,sel,click);
                    }
                }
                else {
                        for(int k=FOE_1;k<=FOE_6;k++){
                            if(soldier[k]!=NULL){
                                soldier[k]->set_point(soldier[k]->getrange());
                            }
                        }
                        AI();
                        scene_image[waiting].render(next_turn_button.get_x(),next_turn_button.get_y());
                        start=0;
                        turn=MY;
                        step=SELECT_UNIT;
                }
                //buttons
				//Update screen
				prev_click_flag=now_click_flag;
        }






    protected:

    private:

        LTexture scene_image[image_num];

        LButton next_turn_button;

        men_with_arms ** soldier;

        base tiles[tiles_num];

        loop target[tar_num];
        loop select[sol_num+1];


        const int SCREEN_WIDTH =1600;
        const int SCREEN_HEIGHT = 800;
        //positions of next turn
        const int x_next=1275;
        const int y_next=25;
        //adjust the positions of bases
        const double x_init=170.0;
        const double y_init=45.0;
        //dimensions of base loops
        const double x_dis=135.0;
        const double y_dis=150.0;
        //number of base loops
        const int x_num=9;
        const int y_num=5;
        const int sacred1=6;
        const int sacred2=33;
        //AI
        const double sacredmonte=100.0;
        const double degenerate_rate=5.0;
        const double foe_enhance=50.0;
        const double foe_health_incr=0.05;

        //store property
        int property[character_num][property_num];
        std::string name_of_image[character_num][cha_image];
        LTexture icons[icon_num];


};

#endif // BATTLE_SCENE_H
