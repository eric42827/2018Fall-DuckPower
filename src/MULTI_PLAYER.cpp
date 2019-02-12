#include "MULTI_PLAYER.h"

MULTI_PLAYER::MULTI_PLAYER()
{
    setting1=new BATTLE_SETTING(0);
    setting2=new BATTLE_SETTING(1);
    mode=0;
	set_on=0;
}

MULTI_PLAYER::~MULTI_PLAYER()
{
    //dtor
}

void MULTI_PLAYER::play(SDL_Event &e,int& out_mode){
    switch(mode){
        case 0:setting1->arrange(&e,mode);break;
        case 1:setting2->arrange(&e,mode);break;
        case 2:bat->battle(e,mode);break;
    }
    if(mode==2 and set_on==0){
        set_on=1;
        int cha[12];
        for(int k=0;k<12;k++){
            if(k<6)cha[k]=setting1->get_cha(k)+13;
            else cha[k]=setting2->get_cha(k-6)+13;
        }
        bat=new BATTLE_SCENE_MULTI(cha);
    }
    if(mode==3)out_mode=1;
}
