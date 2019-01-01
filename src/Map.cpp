#include "Map.h"

Map::Map()
{
    //aload();
    //ctor
}

Map::~Map()
{
    //dtor
}

void Map::Map_ini(){
    load();
    //map[bigmap].render(0,0);
}
void Map::load(){
    for(int k=0;k<map_num;k++){
        map[k].loadFromFile(map_image[k]);
    }
    for(int k=0;k<icon_num;k++){
        icon[k].loadFromFile(icon_image[k]);
    }
    //printf("k");
}
