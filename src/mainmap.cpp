#include "mainmap.h"

mainmap::mainmap()
{

}

mainmap::~mainmap()
{
    //dtor
}
void mainmap:: mapclose(LTexture&m){
    m.free();
}
void mainmap:: loadmap(bool &success){

    if( !bigmap.loadFromFile( "smap.png" ) )
	{
		printf( "Failed to load bigmap texture!\n" );
		success = false;
	}
    if( !map_icon.loadFromFile( "stand.png" ) )
	{
		printf( "Failed to load map_icon texture!\n" );
		success = false;
	}
	if( !mapshow1.loadFromFile( "s1.png" ) )
	{
		printf( "Failed to load mapshow1 texture!\n" );
		success = false;
	}
	if( !sister.loadFromFile( "s1.png" ) )
	{
		printf( "Failed to load sister texture!\n" );
		success = false;
	}
    printf("good");

    //map_icon.free();
    //map_icon.render(400,200);
    //SDL_RenderPresent( gRenderer );

}
void mainmap:: mapbutton(SDL_Event &a,battle &b){
    //printf("test");
    bigmap.render(0,0);
    //map_icon.render(1160,220,0.25,0.25);
    map_icon_button.handleEvent(&a);
    map_icon_button.setPosition(1160,220);
    map_icon_button.setdim(519*0.5,419*0.5);
    //map_icon_button.setdim(1600,800);
    if(map_icon_button.get_sprite()==BUTTON_SPRITE_MOUSE_OVER_MOTION){
        //map_icon.free();
        //mapshow1.render(1160,220,0.5,0.5);
        map_icon.render(1140,210,1,1);
        printf("correct");
    }
    else if(map_icon_button.get_sprite()==BUTTON_SPRITE_MOUSE_DOWN){
        //sister.render(1160,220,0.5,0.5);
        //b.battlestart(a);
        return;
    }
    else map_icon.render(1160,220,0.8,0.8);
    SDL_RenderPresent( gRenderer );
}
