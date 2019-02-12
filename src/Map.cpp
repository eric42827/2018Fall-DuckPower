#include "Map.h"
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
    for(int i=0;i<icon_n;i++){
        icon[i].set_value(iconx[i],icony[i],iconm[i]);
        icon[i].mapmusic();
    }//set icon's position
    for(int i=0;i<menu_num;i++){
        menu[i].set_value(440,menuy[i],menum[i]);
        menu[i].mapmusic();
    }//set menu's position
    for(int i=0;i<MUSIC;i++)bgm[i].loadmusic(music_name[i]);
    tutorial_guide=new TUTORIAL;

}

void Map::load(){//load LTexture&Change
    for(int k=0;k<menu_num;k++)menu[k].loadFromFile(menu_image[k]);
    for(int k=0;k<scene_num;k++)scene[k].loadFromFile(scene_image[k]);
    for(int k=0;k<map_num;k++)_map[k].loadFromFile(map_image[k]);
    for(int k=0;k<about_num;k++)about[k].loadFromFile(about_image[k]);
    for(int k=0;k<icon_n;k++)icon[k].loadFromFile(icon_image[k]);
}
