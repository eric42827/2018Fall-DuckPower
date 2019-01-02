#include "BATTLE_SCENE.h"
BATTLE_SCENE::BATTLE_SCENE()
{
}
BATTLE_SCENE::BATTLE_SCENE(int category)
{
 initialize(category);

}

BATTLE_SCENE::~BATTLE_SCENE()
{
    for(int a=0;a<image_num;a++)scene_image[a].free();
}
