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
        friend class BUTTON;
        friend class BUTTON_BATTLE;
        friend class BUTTON_ARRANGE;
        friend class BUTTON_ARRANGE_CHA;
        friend class BUTTON_ARRANGE_LOOP;

        friend class Map;
        friend class mainmap;
        friend class TUTORIAL;
        friend class BATTLE_SCENE;
        friend class BATTLE_SCENE_MULTI;
        friend class BATTLE_SETTING;

        //friend class BATTLE_SCENE;
    protected:

    private:
        Mix_Music *Music=NULL;
        Mix_Chunk *Chunk=NULL;
        void loadmusic(string path){
   Music = Mix_LoadMUS( path.c_str() );
   if(Music==NULL)cout<<"loadmusic error: "<<path.c_str()<<"!"<<'\n';
}
        void loadsound(string path){
   Chunk = Mix_LoadWAV( path.c_str() );
   if(Chunk==NULL)cout<<"loadsound error: "<<path.c_str()<<"!"<<'\n';
}
        void playmusic();
        void playmusic(int);
        void paucemusic();
        void resumemusic();
        void stopmusic();
        void playsound();
        void playsound(int,int);

};

#endif // MUSIC_H
