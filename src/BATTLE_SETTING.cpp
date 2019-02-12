#include "BATTLE_SETTING.h"
#include<base.h>
#define arr_x_ini 10
#define arr_y_ini 130
#define arr_x_dis 80
#define button_x 100
#define button_y 100
BATTLE_SETTING::BATTLE_SETTING()
{
    initialize(0);
}

BATTLE_SETTING::BATTLE_SETTING(int category)
{
    initialize(category);
}

BATTLE_SETTING::~BATTLE_SETTING()
{
    //dtor
}
void  BATTLE_SETTING::load()
{
    if(background.loadFromFile("image/arrangement/castle_room.png")==0)printf( "Unable to create texture from ! SDL Error: %s\n", SDL_GetError() );
    for(int k=0;k<num_of_people;k++)characters[k].loadFromFile(character_image[k]);
    for(int k=0;k<num_of_people;k++)characters_on[k].loadFromFile(character_image[k]);
    white_loop.loadFromFile("image/whiteloop.png" );
    yellow_loop.loadFromFile("image/yellowloop.png" );
    no_man.loadFromFile("image/none.png" );
    for(int k=0;k<num_of_people;k++){
            charac_button[k].load(character_image[k],character_image[k]);
            charac_button[k].init(arr_x_ini+arr_x_dis*k,arr_y_ini-characters[k].getHeight(),arr_x_dis,arr_y_ini);//
    }
    for(int k=0;k<num_of_loop;k++){
            loops[k].load("image/whiteloop.png","image/yellowloop.png");
            int x_i=SCREEN_WIDTH/2;int y_i=SCREEN_HEIGHT/2;
            int x[num_of_loop]={x_i-x_dis/2,x_i-x_dis/2,x_i-3*x_dis/2,x_i-3*x_dis/2,x_i+x_dis/2,x_i+x_dis/2};
            int y[num_of_loop]={y_i-y_dis,y_i+y_dis,y_i-y_dis/2,y_i+y_dis/2,y_i-y_dis/2,y_i+y_dis/2};
            loops[k].init(x[k],y[k],button_x,button_y);//
    }

}
void BATTLE_SETTING::initialize(int category){

    sound.loadsound("music/click2.wav");
    load();
    exit.load("image/exit.png","image/exit.png");
    if(category==0)exit.init(0,0,100,50);
    else if(category==1)exit.init(1000,500,100,50);


    step=0;
    prev_click_flag=0;
    now_click_flag=0;
    chosen=50;
    start_time=clock();
    clock_on=0;

}
void BATTLE_SETTING::arrange(SDL_Event *e,int& mode){
    background.render(0,0);

    now_click_flag=(e->type==SDL_MOUSEBUTTONDOWN);
    int click=now_click_flag-prev_click_flag;

    exit.render(e);
    if(clock_on==0){
        exit.handle(clock_on,1,click,start_time,sound);

    }
    if(clock()-start_time>=200 and clock_on==1){mode++; click=0;}

    if(step==0){
        for(int a=0;a<num_of_people;a++){
            charac_button[a].render_act(e);
            charac_button[a].handle(step,1,chosen,a,click,NULL,sound);
        }
        for(int b=0;b<num_of_loop;b++){
            loops[b].render();
            if(loops[b].get_on()==1){
                int x_i=SCREEN_WIDTH/2;int y_i=SCREEN_HEIGHT/2;
                int x[num_of_loop]={x_i-x_dis/2,x_i-x_dis/2,x_i-3*x_dis/2,x_i-3*x_dis/2,x_i+x_dis/2,x_i+x_dis/2};
                int y[num_of_loop]={y_i-y_dis,y_i+y_dis,y_i-y_dis/2,y_i+y_dis/2,y_i-y_dis/2,y_i+y_dis/2};

                if(loops[b].get_on()==1)characters_on[loops[b].get_cha()].render(x[b]+(x_dis/2-x_adj),y[b]+(y_dis/4-y_adj));
            }
        }

    }
    else if(step==1){
        for(int a=0;a<num_of_people;a++){
            charac_button[a].render();

        }
        for(int b=0;b<num_of_loop;b++){
                loops[b].render_act(e);
                loops[b].handle(step,0,chosen,click,start_time,sound);
                if(loops[b].get_on()==1){
                    int x_i=SCREEN_WIDTH/2;int y_i=SCREEN_HEIGHT/2;
                    int x[num_of_loop]={x_i-x_dis/2,x_i-x_dis/2,x_i-3*x_dis/2,x_i-3*x_dis/2,x_i+x_dis/2,x_i+x_dis/2};
                    int y[num_of_loop]={y_i-y_dis,y_i+y_dis,y_i-y_dis/2,y_i+y_dis/2,y_i-y_dis/2,y_i+y_dis/2};

                    if(loops[b].get_on()==1)characters_on[loops[b].get_cha()].render(x[b]+(x_dis/2-x_adj),y[b]+(y_dis/4-y_adj));

                }
        }
        if(click==1)step=0;

    }
    prev_click_flag=now_click_flag;
SDL_RenderPresent( gRenderer );
}

int BATTLE_SETTING::get_cha(int a){
    if(loops[a].get_on()==1)return loops[a].get_cha();
    else return -13;
}




