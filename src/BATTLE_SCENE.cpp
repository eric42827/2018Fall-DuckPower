#include "BATTLE_SCENE.h"

BATTLE_SCENE::BATTLE_SCENE()
{
 //ai_perform=0;

}

BATTLE_SCENE::~BATTLE_SCENE()
{
    for(int a=0;a<image_num;a++)scene_image[a].free();
}
