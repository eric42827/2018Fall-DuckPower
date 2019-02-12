#define _GLIBCXX_USE_CXX11_ABI 0
#include <stdio.h>
#include <SDL2/SDL.h>
#include "definition.h"
#include "initial.h"
#include "Map.h"

#include <MULTI_PLAYER.h>
Map m;
initial i;//initial window and music
int get_mode();

int main( int argc, char* args[] )
{
	if( !i.init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{

			//Main loop flag
			static bool quit = false;
            m.Map_ini();
			//Event handler
			SDL_Event e;
            //initialization
            BATTLE_SCENE **DUCK=new BATTLE_SCENE* [12];

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
				}
                    m.Map_mode(e,DUCK,quit);
					SDL_RenderClear( gRenderer );
			}


        //Free resources and close SDL
        i.close();
        /*//Main loop flag
			static bool quit = false;
            m.Map_ini();
			//Event handler
			SDL_Event e;
            //initialization
            MULTI_PLAYER player;

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
				}int mode=0;
                    player.play(e,mode);
                    if(mode==3)quit=true;
			}


        //Free resources and close SDL
        i.close();*/
	}
	return 0;
}
int get_mode(){
    return m.mode;
}

