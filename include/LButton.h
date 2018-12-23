#ifndef LBUTTON_H
#define LBUTTON_H
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include<cmath>
enum LButtonSprite
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_MOUSE_UP = 3,
	BUTTON_SPRITE_TOTAL = 4

};
class LButton
{
    public:
        LButton();
        virtual ~LButton();
        void setPosition( int x, int y )
        {
            mPosition.x = x;
            mPosition.y = y;
        }
        int get_x(){return mPosition.x;}
        int get_y(){return mPosition.y;}
        void handleEvent( SDL_Event* e )
        {
            //If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if( x < mPosition.x )
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( x > mPosition.x + BUTTON_WIDTH )
		{
			inside = false;
		}
		//Mouse above the button
		else if( y < mPosition.y )
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > mPosition.y + BUTTON_HEIGHT )
		{
			inside = false;
		}

		//Mouse is outside button
		if( !inside )
		{
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch( e->type )
                {
				case SDL_MOUSEMOTION:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				break;

				case SDL_MOUSEBUTTONDOWN:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
				break;

				case SDL_MOUSEBUTTONUP:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
				break;
                }
            }
            }
        }
        void render(int x,int y)
        {
            //Show current button sprite

            //else if(mCurrentSprite==BUTTON_SPRITE_MOUSE_DOWN)
            //gButtonSpriteSheetTexture.render( mPosition.x, mPosition.y, &gSpriteClips[ mCurrentSprite ] );
        }

        int getwidth(){return BUTTON_WIDTH;}
		int getheight(){return BUTTON_HEIGHT;}
		void setdim(int a,int b){BUTTON_WIDTH=a;BUTTON_HEIGHT=b;}
        void setpos(int a){pos=a;}
        int get_pos(){return pos;}
        LButtonSprite get_sprite(){return mCurrentSprite;}

    protected:

    private:

        //Top left position
		SDL_Point mPosition;
        int pos;
		int BUTTON_WIDTH;
		int BUTTON_HEIGHT;

		//Currently used global sprite
		LButtonSprite mCurrentSprite;
};

#endif // LBUTTON_H
