#define _GLIBCXX_USE_CXX11_ABI 0
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <ostream>
#include <string>
#include <cmath>
#include <loop.h>
#include <LTexture.h>
#include <LButton.h>
#include <men_with_arms.h>
#include <base.h>
#include <BUTTON.h>
#include <mainmap.h>
#include <Map.h>
#include <BATTLE_SCENE.h>
#include "definition.h"
#include "initial.h"

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	initial i;
	Map m;
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
            //for(int i=0;i<12;i++)DUCK[i]=new BATTLE_SCENE(0);
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
			}

        //Free resources and close SDL
        i.close();
	}
	return 0;
}
