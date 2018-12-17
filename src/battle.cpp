
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
#include<mainmap.h>
battle::battle()
{
    //ctor
}

battle::~battle()
{
    //dtor
}
void battle:: test_enter(){
    if( !_test.loadFromFile( "bigmap.png" ) )
	{
		printf( "Failed to load _test texture!\n" );
	}
}



void battle:: battleclose(LTexture &a){
	//Free loaded images
	a.free();/****************/
	//if(b!=NULL)b.free();
}

void battle:: battlestart(SDL_Event &e){
int frame = 0;
create_battlefield();
//initialization
initialize_game();
whose_turn turn=MY;
which_step step=SELECT_UNIT;
//While application is running
//field and tiles
// create_battlefield();
//soldiers
set_soldiers();
//next turn button
static bool prev_click_flag=0;
static bool now_click_flag=0;
now_click_flag = ( e.type == SDL_MOUSEBUTTONDOWN );
click=now_click_flag-prev_click_flag;

//select.set_xy(base[11].get_x(),base[11].get_y());38
//loop_select.render(select.get_x(),select.get_y());next_turn_button.get_x(),next_turn_button.get_y()
//show_target(0,base,1);
static bool start=0;
if(turn==MY){
    next_turn.render(next_turn_button.get_x(),next_turn_button.get_y());

    next_turn_button.handleEvent( &e );

    if(next_turn_button.get_sprite()==BUTTON_SPRITE_MOUSE_DOWN){turn=FOE;}


    if(start ==0){
        for(int k=MY_1;k<=MY_6;k++)mine[k].set_point(mine[k].getrange());
        start=1;
    }
    static int sel;

    if(step==SELECT_UNIT){
       buttons_select_show(e,step,sel,click);
    }
    else if(step==SELECT_TARGET){

        buttons_target_show(e,step,sel,click);
    }
}
else{
    waiting.render(next_turn_button.get_x(),next_turn_button.get_y());
    start=0;
    turn=MY;
}
//buttons



//Update screen
prev_click_flag=now_click_flag;
SDL_RenderPresent( gRenderer );

}
void battle:: battlesuccess(bool &success){
    if( !field.loadFromFile( "battle.png" ) )
	{
		printf( "Failed to load battle field texture!\n" );
		success = false;
	}
	if( !loop_tile.loadFromFile( "whiteloop.png" ) )
	{
		printf( "Failed to load whiteloop texture!\n" );
		success = false;
	}
	if( !loop_select.loadFromFile( "yellowloop.png" ) )
	{
		printf( "Failed to load yellowloop texture!\n" );
		success = false;
	}
	if( !loop_target.loadFromFile( "redloop.png" ) )
	{
		printf( "Failed to load redloop texture!\n" );
		success = false;
	}
	if( !loop_aim.loadFromFile( "blueloop.png" ) )
	{
		printf( "Failed to load blueloop texture!\n" );
		success = false;
	}
	if( !duck_ori.loadFromFile( "stand.png" ) )
	{
		printf( "Failed to load redloop texture!\n" );
		success = false;
	}
	if( !duck_green.loadFromFile( "stand2.png" ) )
	{
		printf( "Failed to load redloop texture!\n" );
		success = false;
	}
	if( !next_turn.loadFromFile( "next_turn.png" ) )
	{
		printf( "Failed to load next_turn texture!\n" );
		success = false;
	}
	if( !waiting.loadFromFile( "waiting.png" ) )
	{
		printf( "Failed to load waiting texture!\n" );
		success = false;
	}

}
