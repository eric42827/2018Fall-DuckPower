#ifndef LTEXTURE_H
#define LTEXTURE_H
#include<iostream>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include<cmath>

extern SDL_Renderer* gRenderer ;

class LTexture
{
    public:
        int x0,y0;
        LTexture();
        virtual ~LTexture();
        //Loads image at specified path
        		//Image dimensions
        int mWidth;
		int mHeight;
		bool loadFromFile( std::string path )
		{
        //Get rid of preexisting texture
        free();

        //The final texture
        SDL_Texture* newTexture = NULL;

        //Load image at specified path
        SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
        if( loadedSurface == NULL )
        {
            printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
        }
        else
        {
            //Color key image//************
            SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

            //Create texture from surface pixels
            newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
            if( newTexture == NULL )
            {
                printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
            }
            else
            {
                //Get image dimensions
                mWidth = loadedSurface->w;
                mHeight = loadedSurface->h;
            }

            //Get rid of old loaded surface
            SDL_FreeSurface( loadedSurface );
        }

            //Return success
            mTexture = newTexture;
            return mTexture != NULL;
        }

            //Deallocates texture
        void free()
        {
            //Free texture if it exists
            if( mTexture != NULL )
            {
            SDL_DestroyTexture( mTexture );
            mTexture = NULL;
            mWidth = 0;
            mHeight = 0;
        }
        }

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue )
        {
        //Modulate texture rgb
        SDL_SetTextureColorMod( mTexture, red, green, blue );
        }

		//Set blending
		void setBlendMode( SDL_BlendMode blending )
        {
        //Set blending function
        SDL_SetTextureBlendMode( mTexture, blending );
        }
		//Set alpha modulation
		void setAlpha( Uint8 alpha )
        {
            //Modulate texture alpha
            SDL_SetTextureAlphaMod( mTexture, alpha );
        }

		//Renders texture at given point
		/************зя************/
		void render( int x, int y,double a=1.0,double b=1.0)
        {
            //Set rendering space and render to screen
            SDL_Rect renderQuad = { x, y, mWidth*a, mHeight*b};
            a0=a;b0=b;x=x0;y=y0;
            //std::cout<<mWidth*a0<<" ";
            //std::cout<<mHeight*b0;
            //Render to screen
            SDL_RenderCopy( gRenderer, mTexture, NULL, &renderQuad );
        }
		//Gets image dimensions
		int getWidth(){
            return mWidth*a0;
            //std::cout<<mWidth*a0;
        }
		int getHeight(){
            return mHeight*b0;
            //std::cout<<mHeight*b0;
        }
		//friend class whiteloop;
    protected:

    private:
        //The actual hardware texture
		SDL_Texture* mTexture;
		int a0,b0;



};



#endif // LTEXTURE_H
