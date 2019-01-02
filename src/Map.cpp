#include "Map.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 640
Map::Map()
{
    //ctor
}

Map::~Map()
{
    //dtor
}

void Map::Map_ini(){
    load();//load all map pics
    for(int i=0;i<icon_num-1;i++)iconb[i].set_value(iconx[i],icony[i],iconm[i]);//set icon's position
    for(int i=0;i<menu_num-1;i++)menub[i].set_value(800,menuy[i],menum[i]);//set icon's position
    iconb[goback].set_value(SCREEN_WIDTH-203,590,1);
    iconb[gomenu].set_value(0,0,0);
}

void Map::load(){//load LTexture&Change
    for(int k=0;k<map_num;k++)map[k].loadFromFile(map_image[k]);
    for(int k=0;k<icon_num;k++)icon[k].loadFromFile(icon_image[k]);
    for(int k=0;k<menu_num;k++)menu[k].loadFromFile(menu_image[k]);
    for(int k=0;k<scene_num;k++)scene[k].loadFromFile(scene_image[k]);
    for(int k=0;k<tutor_num;k++)tutor[k].loadFromFile(tutor_image[k]);
    for(int k=0;k<about_num;k++)about[k].loadFromFile(about_image[k]);
}
