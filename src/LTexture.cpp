#include "LTexture.h"

SDL_Renderer* gRenderer = NULL;
 LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::LTexture(std::string path)
{
	//Initialize
	loadFromFile(path);
	/*mTexture = NULL;
	mWidth = 0;
	mHeight = 0;*/
}
LTexture::~LTexture()
{
	//Deallocate
	free();
}
