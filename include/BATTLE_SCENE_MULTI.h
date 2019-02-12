#ifndef BATTLE_SCENE_MULTI_H
#define BATTLE_SCENE_MULTI_H

#include<BATTLE_SCENE.h>

class BATTLE_SCENE_MULTI:public BATTLE_SCENE
{
    public:
        BATTLE_SCENE_MULTI();
        BATTLE_SCENE_MULTI(int category);
        BATTLE_SCENE_MULTI(int cha[12]);
        virtual ~BATTLE_SCENE_MULTI();
        void battle(SDL_Event &e,int &mode);

    protected:

    private:
        void initialize_var(int cha[12]);
};

#endif // BATTLE_SCENE_MULTI_H
