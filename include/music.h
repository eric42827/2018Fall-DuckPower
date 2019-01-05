#ifndef MUSIC_H
#define MUSIC_H
#include <iostream>
#include "SDL_mixer.h"
using namespace std;

class music
{
    public:
        music();
        virtual ~music();
        friend class Map;
        friend class mainmap;
        //friend class BATTLE_SCENE;
    protected:

    private:
        Mix_Music *Music=NULL;
        Mix_Chunk *Chunk=NULL;
        void loadmusic(string);
        void loadsound(string);
        void playmusic();
        void playmusic(int);
        void paucemusic();
        void resumemusic();
        void stopmusic();
        void playsound();
        void playsound(int,int);

};

#endif // MUSIC_H
