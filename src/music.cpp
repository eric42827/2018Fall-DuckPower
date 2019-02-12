#include "music.h"

music::music()
{
    //ctor
}

music::~music()
{
	Mix_FreeChunk( Chunk );
	Mix_FreeMusic( Music );
	Chunk = NULL;
	Music = NULL;
    //dtor
}

void music::playmusic(){
    if( Mix_PlayingMusic() == 0 ){Mix_PlayMusic( Music, -1 );}//-1 = inf loop ,0=1 times
    else if( Mix_PausedMusic() == 1 )
    {
        //Resume the music
        Mix_ResumeMusic();
    }
}

void music::playmusic(int time){
    Mix_PlayMusic( Music, time );//-1 = inf loop ,0=1 times
}

void music::paucemusic(){
    Mix_PauseMusic();
}

void music::resumemusic(){
    if( Mix_PausedMusic() == 1 )Mix_ResumeMusic();
}

void music::stopmusic(){
    Mix_HaltMusic();
}

void music::playsound(){
    Mix_PlayChannel( -1, Chunk, 0 );//loop=0:1 times
}

void music::playsound(int ch,int loop){
    Mix_PlayChannel( ch, Chunk, loop );//loop=0:1 times
}
