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
    for(int i=0;i<icon_n-2;i++)icon[i].set_value(iconx[i],icony[i],iconm[i]);//set icon's position
    for(int i=0;i<menu_num;i++)menu[i].set_value(440,menuy[i],menum[i]);//set menu's position
    icon[goback].set_value(SCREEN_WIDTH-203,590,1);
    icon[gomenu].set_value(0,0,0);
    //for(int i=0;i<MUSIC;i++)music
    for(int i=0;i<MUSIC;i++)bgm[i].loadmusic(music_name[i]);
}

void Map::load(){//load LTexture&Change
    for(int k=0;k<change_num;k++)change[k].loadFromFile(change_image[k]);
    for(int k=0;k<menu_num;k++)menu[k].loadFromFile(menu_image[k]);
    for(int k=0;k<scene_num;k++)scene[k].loadFromFile(scene_image[k]);
    for(int k=0;k<map_num;k++)map[k].loadFromFile(map_image[k]);
    for(int k=0;k<tutor_num;k++)tutor[k].loadFromFile(tutor_image[k]);
    for(int k=0;k<about_num;k++)about[k].loadFromFile(about_image[k]);
    for(int k=0;k<icon_n;k++)icon[k].loadFromFile(icon_image[k]);
}
