#ifndef GO_JUDGER_H
#define GO_JUDGER_H

#include<base.h>
#include<BUTTON_BATTLE.h>
#include<men_with_arms.h>
class GO_JUDGER
{
    public:
        GO_JUDGER();
        virtual ~GO_JUDGER();
friend class BATTLE_SCENE;
friend class BATTLE_SCENE_MULTI;
    protected:

    private:
        BUTTON_BATTLE choose[2*sol_num+1];
        BUTTON_BATTLE goal[tar_num];

        bool judge(int sel,int sel2,int dis,int tar,base *a);
        int distance(int pos1,int pos2,base* a);

        void show_select(base *tiles,men_with_arms **soldier,SDL_Event& e,int& step,int& sel,int click,music *sound);
        int show_target(base *tiles,men_with_arms **soldier,int sel,SDL_Event* e,base *a,int n);
        void buttons_target_show(base *tiles,men_with_arms **soldier,SDL_Event& e,int& step,int& sel,int click,music *sound);

        void show_select_multi(base *tiles,men_with_arms **soldier,SDL_Event& e,int& step,int& sel,int click,music *sound);
        int show_target_multi(base *tiles,men_with_arms **soldier,int sel,SDL_Event* e,base *a,int n);
        void buttons_target_show_multi(base *tiles,men_with_arms **soldier,SDL_Event& e,int& step,int& sel,int click,music *sound);
};

#endif // GO_JUDGER_H
