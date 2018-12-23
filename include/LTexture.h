#ifndef LTEXTURE_H
#define LTEXTURE_H

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include<cmath>

extern SDL_Renderer* gRenderer ;

class LTexture
{
    public:
        LTexture();
        LTexture(std::string path);
        virtual ~LTexture();
        //Loads image at specified path
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
		void render( int x, int y )
        {
            //Set rendering space and render to screen
            SDL_Rect renderQuad = { x, y, mWidth, mHeight };


            //Render to screen
            SDL_RenderCopy( gRenderer, mTexture, NULL, &renderQuad );
        }
        void render( int x, int y, SDL_Rect* clip )
        {
        //Set rendering space and render to screen
        SDL_Rect renderQuad = { x, y, mWidth, mHeight };

        //Set clip rendering dimensions
        if( clip != NULL )
        {
            renderQuad.w = clip->w;
            renderQuad.h = clip->h;
        }

        //Render to screen
        SDL_RenderCopy( gRenderer, mTexture, clip, &renderQuad );
        }
		//Gets image dimensions
		int getWidth(){
            return mWidth;
        }
		int getHeight(){
            return mHeight;
        }
		//friend class loop;
    protected:

    private:
        //The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};



#endif // LTEXTURE_H
