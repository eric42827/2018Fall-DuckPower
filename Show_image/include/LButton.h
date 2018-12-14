#ifndef LBUTTON_H
#define LBUTTON_H
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
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
		//Initializes internal variables
        LButton()
        {
            mPosition.x = 0;
            mPosition.y = 0;

            mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        }

        ~LButton()
        {
            //dtor
        }
		//Sets top left position
		void setPosition( int x, int y );

		//Handles mouse event
		void handleEvent( SDL_Event* e );

		//Shows button sprite
		void render();

	private:
		//Top left position
		SDL_Point mPosition;

		//Currently used global sprite
		LButtonSprite mCurrentSprite;
};

#endif // LBUTTON_H
