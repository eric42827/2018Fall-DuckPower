/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include<stdlib.h>
#include <string>
#include <STORE_BUTTON.h>
#include<LButton.h>
#include<LTexture.h>
#include<iostream>
#include<time.h>
#include<ctime>
#include <fstream>
#include <sstream>
#include<vector>
using namespace std;
//Screen dimension constants
const int SCREEN_WIDTH = 1300;
const int SCREEN_HEIGHT = 650;
const int card_button_width=150;
const int card_button_height=200;
const int total_card_button=6;
const int total_card=12;
const std::string card_soldier[total_card]={/*****order*****/
    "card_soldier_01.png",
    "card_soldier_02.png",
    "card_soldier_03.png",
    "card_soldier_04.png",
    "card_soldier_05.png",
    "card_soldier_06.png",
    "card_soldier_07.png",
    "card_soldier_08.png",
    "card_soldier_09.png",
    "card_soldier_10.png",
    "card_soldier_11.png",
    "card_soldier_12.png"
    };
const std::string card_soldier_click[total_card]={/*****order*****/
    "card_soldier_click_01.png",
    "card_soldier_click_02.png",
    "card_soldier_click_03.png",
    "card_soldier_click_04.png",
    "card_soldier_click_05.png",
    "card_soldier_click_06.png",
    "card_soldier_click_07.png",
    "card_soldier_click_08.png",
    "card_soldier_click_09.png",
    "card_soldier_click_10.png",
    "card_soldier_click_11.png",
    "card_soldier_click_12.png"
};

vector<double> matrix;
//readfile
fstream file;
//random
int r1=0;int r2=0;int r3=0;int r4=0;int r5=0;int r6=0;
//Starts up SDL and creates window
bool init();
//Loads media
bool loadMedia();
//Frees media and shuts down SDL
void close();
//Get_random
void get_random(int,int);
//The window we'll be rendering to
SDL_Window* gWindow = NULL;
//The window renderer
LTexture gcardTexture[12];
LTexture gstoreTexture;
LTexture gcard2Texture;
LTexture gsoldierTexture[12];
//button numbers
STORE_BUTTON card_buttons[6];
bool card_buttons_buy[6]={0,0,0,0,0,0};
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
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
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
void get_random(int MIN,int MAX) {
   int a[6]={r1,r2,r3,r4,r5,r6};
   for(int i=0;i<total_card_button;i++){
   a[i] = rand() % (MAX - MIN + 1) + MIN;
   for(int j=0;j<i-1;j++)
   if(a[i]==a[j]){
    i=i-1;
    break;
   }
   }
 r1=a[0];r2=a[1];r3=a[2];r4=a[3];r5=a[4];r6=a[5];
 }


bool loadMedia(int card1,int card2,int card3,int card4,int card5,int card6)
{
    int card_num[6]={card1,card2,card3,card4,card5,card6};
	//Loading success flag
	bool success = true;
	//Load Foo' texture

	if( !gstoreTexture.loadFromFile( "store.png" ) )
	{
		printf( "Failed to load store texture image!\n" );
		success = false;
	}
	for(int i=0;i<total_card_button;i++){
        card_buttons[i].load(card_soldier[card_num[i]],card_soldier_click[card_num[i]]);
    }

    card_buttons[0].create(70,40,150,200);
    card_buttons[1].create(260,40,card_button_width,card_button_height);
    card_buttons[2].create(450,40,card_button_width,card_button_height);
    card_buttons[3].create(70,260,card_button_width,card_button_height);
    card_buttons[4].create(260,260,card_button_width,card_button_height);
    card_buttons[5].create(450,260,card_button_width,card_button_height);
	return success;

}

void close()
{
	//Free loaded images
	for(int i=0;i<6;i++)gcardTexture[i].free();
	gstoreTexture.free();

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
    //Map m;
    file.open("soldier_quantity.csv");
    string line;
    get_random(1,10);
    int a[total_card_button]={r1,r2,r3,r4,r5,r6};
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
	    while (getline( file, line,'\n'))  //
        {
            istringstream templine(line); //
            string data;
            while (getline( templine, data,',')) //
            {
            matrix.push_back(atof(data.c_str()));  //
            }
            }
        file.close();
        file.open("soldier_quantity.csv");
		//Load media
		if( !loadMedia(a[0],a[1],a[2],a[3],a[4],a[5]) )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;
			//static
            bool prev_click[total_card_button]={0};
            bool now_click[total_card_button]={0};
			//While application is running
			while( !quit )
			{
			    //Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );


				//Render background texture to screen
				gstoreTexture.render( 0, 0 );
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}
				for (int i = 0; i < total_card_button; ++i){
                     now_click[i]=card_buttons[i].button_click(&e);
                     if (now_click[i]-prev_click[i]==1){
                         if(matrix[0]>=matrix[a[i]+14]){
                            cout<<"here";
                            matrix[0]=matrix[0]-matrix[a[i]+14];
                            matrix[a[i]+1]+=1;
                            card_buttons_buy[i]=1;
                         }
                     }
                     card_buttons[i].render(&e,card_buttons_buy[i]);
                     prev_click[i]=now_click[i];
                }

				//Update screen
				SDL_RenderPresent( gRenderer );
			}

		}
        //writefile
        for (int i=0;i<matrix.size();i++)
        {
            file<<matrix[i]<<",";
            if(i%12==0&&i>=1&&i<24)file<<endl;
        }
        file.close();
    }

	//Free resources and close SDL
	close();

	return 0;
}

