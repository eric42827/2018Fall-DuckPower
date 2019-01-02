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
    for(int i=0;i<icon_num-1;i++)iconb[i].set_value(x[i],y[i],2);//set icon's position
    iconb[goback].set_value(0,550,1);
}

void Map::load(){
    for(int k=0;k<map_num;k++)map[k].loadFromFile(map_image[k]);
    for(int k=0;k<icon_num;k++)icon[k].loadFromFile(icon_image[k]);
}
