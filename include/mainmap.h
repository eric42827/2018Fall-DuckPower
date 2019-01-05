#define _GLIBCXX_USE_CXX11_ABI 0
#ifndef MAINMAP_H
#define MAINMAP_H
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "definition.h"
#include <string>
#include<LTexture.h>
#include<LButton.h>
#include "music.h"

const string sound_name[SOUND]={
       // "music/click2.wav",
        //"music/wan.wav",
        "music/nc.wav",
};

enum sound_enum{
    click2=0,
    swipe=1,
};

class mainmap :public LTexture,public LButton
{
    public:
        //friend class Map;
        mainmap();
        virtual ~mainmap();
        friend class Map;
    protected:

    private:
        music sound[SOUND];
        int l_x,l_y,k;
        bool clean =true;
        void set_value(int,int,int);
        void map_but(SDL_Event &a,int &mode);
        void menu_but(SDL_Event &a,int &mode);
        void mapmusic();


};

#endif // MAINMAP_H
