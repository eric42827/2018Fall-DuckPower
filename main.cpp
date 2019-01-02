#define _GLIBCXX_USE_CXX11_ABI 0
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include<ostream>
#include <string>
#include<cmath>
#include<loop.h>
#include<LTexture.h>
#include<LButton.h>
#include<men_with_arms.h>
#include<base.h>
#include<BUTTON.h>
#include<mainmap.h>
#include<Map.h>
#include<BATTLE_SCENE.h>
//#define _GLIBCXX_USE_CXX11_ABI 0
#define N 40
#define sol_num 6
#define tar_num 60

/********Objects Declaration********/
//The window we'll be rendering to
SDL_Window* gWindow = NULL;
//BATTLE_SCENE DUCK_POWER;

/********Function Declaration********/


//Starts up SDL and creates window
bool init();/***no need***/

//Loads media


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
	Map g;
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
	    //DUCK_POWER.load();


			//Main loop flag
			bool quit = false;
            g.Map_ini();
			//Event handler
			SDL_Event e;

			//Current animation frame
			int frame = 0;

            //initialization
            BATTLE_SCENE **DUCK=new BATTLE_SCENE* [12];
            for(int i=0;i<12;i++)DUCK[i]=new BATTLE_SCENE(0);
            //DUCK[0]=new BATTLE_SCENE(0);
            //DUCK[1]=new BATTLE_SCENE(0);
            //{BATTLE_SCENE *temp=new BATTLE_SCENE(0);DUCK+i=temp;}//delete[]temp;}

            BATTLE_SCENE DUCK_POWER(0);
			//While application is running
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

                    //DUCK_POWER.test();

				}
                    g.Map_mode(e,DUCK);
                    //DUCK_POWER.battle(e,quit);
                    //SDL_RenderPresent( gRenderer );
			}

	//Free resources and close SDL
	close();
	}
	return 0;
}
