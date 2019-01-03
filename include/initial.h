#ifndef INITIAL_H
#define INITIAL_H
#include "SDL2/SDL.h"
#include <SDL_image.h>
#include "definition.h"
#include <stdio.h>
extern SDL_Renderer* gRenderer;
class initial
{
    public:
        initial();
        virtual ~initial();
    /********Objects Declaration********/
    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;
    //BATTLE_SCENE DUCK_POWER;
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
            gWindow = SDL_CreateWindow( "Duck Ultimate Combat King", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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
    protected:

    private:
};

#endif // INITIAL_H
