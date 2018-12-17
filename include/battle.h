#ifndef BATTLE_H
#define BATTLE_H
#define q 40
#define sol_num 6
#define tar_num 60
#include "battle.h"
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include<cmath>
#include<loop.h>
#include<LTexture.h>
#include<LButton.h>
#include<soldier_short.h>
#include<base.h>
#include<battle.h>
//#include<mainmap.h>
class battle
{
    public:
        LTexture _test;
        void test_enter();
        void battleclose(LTexture &);
        void battlesuccess(bool&);
        void battlestart(SDL_Event &);
        battle();
        virtual ~battle();
        battle(const battle & p);
        LTexture field;
        LTexture loop_tile;
        LTexture loop_select;
        LTexture loop_target;
        LTexture loop_aim;
        LTexture duck_ori;
        LTexture duck_green;
        LTexture next_turn;
        LTexture waiting;
        const int TOTAL_BUTTONS=6;
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
         FOE_6=12
        };
        base tiles[q];

        loop select;
        loop target;

        soldier_short  mine[2*sol_num+1];
        soldier_short  foe[sol_num+1];

        LButton buttons_select[sol_num+1];
        LButton buttons_aim[tar_num];
        LButton next_turn_button;

    protected:

    private:
int click;
int abs(int a){
    if(a<0)return -a;
    else return a;
}
void create_battlefield(){
    field.render( 0,0);
    //bigmap.render(0,0);
    for(int a=0;a<q;a++)loop_tile.render(tiles[a].get_x(),tiles[a].get_y());

}
void set_soldiers(){
    for(int a=MY_1;a<=MY_6;a++){
        duck_ori.render(mine[a].get_x(),mine[a].get_y());
    }
    for(int a=FOE_1;a<=FOE_6;a++){
        duck_green.render(mine[a].get_x(),mine[a].get_y());
    }
}
void buttons_select_show(SDL_Event& e,which_step& step,int& sel,int click){
    for( int i = MY_1; i <=MY_6; i ++)
    {
        buttons_select[ i ].handleEvent( &e );
        buttons_select[i].setPosition(mine[i].get_x(),mine[i].get_y());
        buttons_select[i].setpos(mine[i].get_pos());
        //loop_select.render(tiles[buttons_select[ i ].get_pos()].get_x(),tiles[buttons_select[ i ].get_pos()].get_y());
    }
    for( int i = MY_1; i <=MY_6; i++ )
    {
        if(buttons_select[ i ].get_sprite()==BUTTON_SPRITE_MOUSE_OVER_MOTION)loop_select.render(tiles[buttons_select[ i ].get_pos()].get_x(),tiles[buttons_select[ i ].get_pos()].get_y());
        else if(buttons_select[ i ].get_sprite()==BUTTON_SPRITE_MOUSE_DOWN){
            if(click==1){
                step=SELECT_TARGET;
                sel=mine[i].get_pos();
            }

        }
    }
}

void buttons_target_show(SDL_Event& e,which_step& step,int& sel,int click){
    int count;
    const int pt=mine[tiles[sel].get_num()].getpoint();
    //count=show_target(sel,tiles,2);/**********/
    if(pt!=0){
        count=soldier_view(sel,tiles);
        for( int i = 0; i < count; i ++)
        {
            buttons_aim[ i ].handleEvent( &e );
        }
        //int flag=0;
        for( int i = 0; i < count; i ++)
        {
            if(buttons_aim[ i ].get_sprite()==BUTTON_SPRITE_MOUSE_OVER_MOTION)loop_aim.render(tiles[buttons_aim[ i ].get_pos()].get_x(),tiles[buttons_aim[ i ].get_pos()].get_y());
            else if(buttons_aim[ i ].get_sprite()==BUTTON_SPRITE_MOUSE_DOWN){

                if(click==1){
                    if(tiles[buttons_aim[ i ].get_pos()].get_num()==none){

                        mine[tiles[sel].get_num()].set_point(mine[tiles[sel].get_num()].getpoint()-distance(buttons_aim[ i ].get_pos(),sel,tiles));

                        mine[tiles[sel].get_num()].go(buttons_aim[ i ].get_pos(),tiles);

                        tiles[buttons_aim[ i ].get_pos()].setsoldier_num(tiles[sel].get_num());tiles[sel].setsoldier_num(none);

                        step=SELECT_UNIT;

                        break;
                    }
                }

            }
        }
    }
    else {
        if(click==1){
            step=SELECT_UNIT;
        }
    }
}
int soldier_view(int sel,base *a){
    const int pt=mine[a[sel].get_num()].getpoint();
    const int mem=show_target(sel,a,mine[a[sel].get_num()].getpoint());

    return mem;
}


bool judge(int sel,int sel2,int dis,int tar,base *a){
    //if((a[sel2].get_num()<=MY_6)and(a[sel2].get_num()>=MY_1)) return 0;
    //if(sel2==sacred1)return 0;
    return(sel2!=tar)*(sel2<q)*(sel2>=0)*(abs(a[sel2].get_y()-a[sel].get_y())==dis);
}

int show_target(int sel,base *a,int n){/****sacred***/
    static bool check[q];
    static bool flag=0;
    static int tar;
    static int max_level;
    static int count=0;
    if(flag==0){
        tar=sel;
        max_level=n;
    }
    if(n==0){
        int x_adj=x_dis/2-25;int y_adj=y_dis/2-50;
            if((sel!=tar)and(sel!=sacred1)and((a[sel].get_num()>MY_6)or(a[sel].get_num()<MY_1))){
            loop_target.render(a[sel].get_x(),a[sel].get_y());
            buttons_aim[count].setPosition(a[sel].get_x()+x_adj,a[sel].get_y()+y_adj);buttons_aim[count].setpos(sel);
            count++;
            }
    }
   else{
        flag=1;
        if(check[sel]==0){
        show_target(sel,a, 0);check[sel]=1;}
        if(judge(sel,sel-1,y_dis,tar,tiles)and check[sel-1]==0){
            show_target(sel-1,a, n-1);
        }
        if(judge(sel,sel+1,y_dis,tar,tiles)and check[sel+1]==0){

                show_target(sel+1,a, n-1);

        }
        if(judge(sel,sel+y_num,y_dis/2,tar,tiles)and check[sel+y_num]==0){

                show_target(sel+y_num,a, n-1);

        }
        if(judge(sel,sel-y_num,y_dis/2,tar,tiles)and check[sel-y_num]==0){

                show_target(sel-y_num,a, n-1);

        }
        if(judge(sel,sel+y_num-1,y_dis/2,tar,tiles)and check[sel+y_num-1]==0){

                show_target(sel+y_num-1,a, n-1);

        }
        if(judge(sel,sel-y_num+1,y_dis/2,tar,tiles)and check[sel-y_num+1]==0){

                show_target(sel-y_num+1,a, n-1);

        }


    }
    int mem=count;
    if((sel==tar)and(n==max_level)){
        for(int k=0;k<q;k++)check[k]=0;
        count=0;
        flag=0;
    }
    return mem;
}


void initialize_game(){
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
			int  x_soldier_init[7];int  y_soldier_init[7];
				for(int a=MY_1;a<=MY_6;a++){
                    mine[a].setdim(duck_ori.getWidth(),duck_ori.getHeight());/*********/
                    x_soldier_init[a]=x_dis/2-mine[a].getwidth()/4;
                    y_soldier_init[a]=y_dis/2-mine[a].getheight()/2;
                }
            mine[MY_1].set_xy(tiles[5].get_x(),tiles[5].get_y());mine[MY_1].setpos(5);tiles[5].setsoldier_num(MY_1);
            mine[MY_2].set_xy(tiles[7].get_x(),tiles[7].get_y());mine[MY_2].setpos(7);tiles[7].setsoldier_num(MY_2);
            mine[MY_3].set_xy(tiles[1].get_x(),tiles[1].get_y());mine[MY_3].setpos(1);tiles[1].setsoldier_num(MY_3);
            mine[MY_4].set_xy(tiles[2].get_x(),tiles[2].get_y());mine[MY_4].setpos(2);tiles[2].setsoldier_num(MY_4);
            mine[MY_5].set_xy(tiles[10].get_x(),tiles[10].get_y());mine[MY_5].setpos(10);tiles[10].setsoldier_num(MY_5);
            mine[MY_6].set_xy(tiles[11].get_x(),tiles[11].get_y());mine[MY_6].setpos(11);tiles[11].setsoldier_num(MY_6);

            for(int a=MY_1;a<=MY_6;a++){
                    mine[a].set_xy(mine[a].get_x()+x_soldier_init[a],mine[a].get_y()+y_soldier_init[a]);

                    //soldiers move_range
                    mine[a].set_range(2);
				}
            //FOE soldiers
            /********/
            //soldiers position
			//int  x_soldier_init[7];int  y_soldier_init[7];
            for(int a=FOE_1;a<=FOE_6;a++){
                    mine[a].setdim(duck_ori.getWidth(),duck_ori.getHeight());/*********/
                    //x_soldier_init[a]=x_dis/2-mine[a].getwidth()/4;
                    //y_soldier_init[a]=y_dis/2-mine[a].getheight()/2;
                }
            mine[FOE_1].set_xy(tiles[32].get_x(),tiles[32].get_y());mine[FOE_1].setpos(32);tiles[32].setsoldier_num(FOE_1);
            mine[FOE_2].set_xy(tiles[34].get_x(),tiles[34].get_y());mine[FOE_2].setpos(34);tiles[34].setsoldier_num(FOE_2);
            mine[FOE_3].set_xy(tiles[28].get_x(),tiles[28].get_y());mine[FOE_3].setpos(28);tiles[28].setsoldier_num(FOE_3);
            mine[FOE_4].set_xy(tiles[29].get_x(),tiles[29].get_y());mine[FOE_4].setpos(29);tiles[29].setsoldier_num(FOE_4);
            mine[FOE_5].set_xy(tiles[37].get_x(),tiles[37].get_y());mine[FOE_5].setpos(37);tiles[37].setsoldier_num(FOE_5);
            mine[FOE_6].set_xy(tiles[38].get_x(),tiles[38].get_y());mine[FOE_6].setpos(38);tiles[38].setsoldier_num(FOE_6);

            for(int a=FOE_1;a<=FOE_6;a++){
                    mine[a].set_xy(mine[a].get_x()+x_soldier_init[a-sol_num],mine[a].get_y()+y_soldier_init[a-sol_num]);

                    //soldiers move_range
                    mine[a].set_range(2);
				}
            //buttons position and dimensions
            for(int a=MY_1;a<=MY_6;a++){
				    buttons_select[a].setpos(mine[a].get_pos());
                    buttons_select[a].setPosition(mine[a].get_x(),mine[a].get_y());
                    buttons_select[a].setdim(duck_ori.getWidth(),duck_ori.getHeight());/**********/

				}
            for(int k=0;k<tar_num;k++)buttons_aim[k].setdim(duck_ori.getWidth(),duck_ori.getHeight());/**********/
            int l_x=x_next;int l_y=y_next;
            next_turn_button.setPosition(l_x,l_y);
            next_turn_button.setdim(next_turn.getWidth(),next_turn.getHeight());

}
int distance(int pos1,int pos2,base* a){
const double x=(a[pos2].get_x()-a[pos1].get_x())/x_dis;
const double y=(a[pos2].get_y()-a[pos1].get_y())/y_dis;
int dist=0;
if(x==0)dist=abs(y);
else{

const double m=y/x;

if((m>-0.5)and(m<0.5)and(x>0)){dist=x;

}
else if((m>-0.5)and(m<0.5)and(x<0)){dist=-x;

}
else if((m>0.5)and(x>0)){dist=0.5*x+y;

}
else if((m>0.5)and(x<0)){dist=-(0.5*x+y);

}
else if((m<-0.5)and(x>0)){dist=0.5*x-y;

}
else if((m<-0.5)and(x<0)){dist=-(0.5*x-y);

}
else if((m==0.5)or(m==-0.5)){dist=abs(x);

}

}
return dist;
}
};

#endif // BATTLE_H
