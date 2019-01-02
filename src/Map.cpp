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
    for(int i=0;i<icon_num-1;i++)iconb[i].set_value(iconx[i],icony[i],iconm[i]);//set icon's position
    for(int i=0;i<menu_num-2;i++)menub[i].set_value(800,menuy[i],menum[i]);//set icon's position
    iconb[goback].set_value(0,550,1);
}

void Map::load(){
    for(int k=0;k<map_num;k++)map[k].loadFromFile(map_image[k]);
    for(int k=0;k<icon_num;k++)icon[k].loadFromFile(icon_image[k]);
    for(int k=0;k<menu_num;k++)menu[k].loadFromFile(menu_image[k]);
}
