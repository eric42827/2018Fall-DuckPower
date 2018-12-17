/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include<iostream>
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
//#include<windows.h>

/********Important Constants********/
const int SCREEN_WIDTH =1600;
const int SCREEN_HEIGHT = 800;

/********Objects Declaration********/
//The window we'll be rendering to
SDL_Window* gWindow = NULL;

/********Battle Declaration********/
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
/********golbal function********/

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia(battle &,mainmap &);

void close();

/********battle function********/

/********Map Declaration********/

/********Map function********/

/********Function Explanation********/

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}
bool loadMedia(battle &b,mainmap &m)
{
	//Loading success flag
	bool success = true;
    b.battlesuccess(success);
    m.loadmap(success);
    return success;
	//Load sprite sheet texture

}
void close()
{


	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	battle b;
	mainmap m;
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia(b,m) )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;


			while( !quit )
			{

				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

				}

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				/*******visualization*******/
                        //Current animation frame
                //int input;
                //std::cin >>input;
                //b.battlestart(e);
                m.mapbutton(e,b);
               if(m.map_icon_button.get_sprite()==BUTTON_SPRITE_MOUSE_DOWN){
                break;
               }
                //m.map_icon.render(1160,220,0.25,0.25);
                //if(input)b.battleclose();
                //bigmap.render(0,0);
			}
			//Sleep(500);
			while(!quit){
                while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
                    if( e.type == SDL_QUIT )
					{
						quit = true;
					}

				}

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
                b.battlestart(e);
			}
		}
	}


	//Free resources and close SDL
	//(m.bigmap).free();
	//b.battleclose(b._test);
	close();

	return 0;
}




