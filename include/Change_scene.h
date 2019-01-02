#ifndef CHANGE_SCENE_H
#define CHANGE_SCENE_H
#include<LTexture.h>

class Change_scene:protected LTexture
{
    public:
        Change_scene();
        virtual ~Change_scene();
        friend class Map;
    protected:

    private:
        void scroll(bool x,bool y,bool inf);
};

#endif // CHANGE_SCENE_H
