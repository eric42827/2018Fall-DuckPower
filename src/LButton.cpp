#include "LButton.h"

LButton::LButton()
{
    mPosition.x = 0;
	mPosition.y = 0;

	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

LButton::~LButton()
{
    //dtor
}
