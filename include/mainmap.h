#ifndef MAINMAP_H
#define MAINMAP_H
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include<cmath>
#include<loop.h>
#include<LTexture.h>
#include<LButton.h>
#include<soldier_short.h>
#include<base.h>
#include<battle.h>
#include<mainmap.h>

class mainmap
{
    public:
        mainmap();
        virtual ~mainmap();
        LTexture bigmap;
        void loadmap(bool&);
        void mapclose(LTexture&);
        LTexture map_icon;
        LTexture sister;
        LTexture mapshow1;
        LButton map_icon_button;
        void mapbutton(SDL_Event &,battle &);
    protected:

    private:


};

#endif // MAINMAP_H
