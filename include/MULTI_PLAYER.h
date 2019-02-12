#ifndef MULTI_PLAYER_H
#define MULTI_PLAYER_H

#include<BATTLE_SETTING.h>
#include<BATTLE_SCENE_MULTI.h>
class MULTI_PLAYER
{
    public:
        MULTI_PLAYER();
        virtual ~MULTI_PLAYER();
        void play(SDL_Event &e,int& out_mode);

    protected:

    private:
        //arrangement of soldiers
            BATTLE_SETTING *setting1;
			BATTLE_SETTING *setting2;
        //battlefield scene of multi_player
			BATTLE_SCENE_MULTI *bat;
			int mode;
			int set_on;
};

#endif // MULTI_PLAYER_H
