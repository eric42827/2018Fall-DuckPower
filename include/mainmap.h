#ifndef MAINMAP_H
#define MAINMAP_H
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include<cmath>
#include<LTexture.h>
#include<LButton.h>

class mainmap
{
    public:
        friend class Map;
        mainmap();
        virtual ~mainmap();


    protected:

    private:
        int l_x,l_y,k;

        void set_value(int,int,int);
        int map_but(SDL_Event &,LTexture &,LButton &);
        void map_but(SDL_Event &a,LTexture &l,LButton &b,int &mode);
        //void map_but(SDL_Event &,LTexture &,LButton &,int &,int,int,int);




};

#endif // MAINMAP_H
