#include "Change_scene.h"
#include "iostream"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 640
Change_scene::Change_scene()
{
    //ctor
}

Change_scene::~Change_scene()
{
    //dtor
}

void Change_scene:: scroll(bool x,bool y,bool inf){
    static int offsetx=0;
    static int offsety=0;
    //std::cout<<inf;
    if(x){
        --offsetx;
        if(offsetx<=-getWidth()){
            if(inf){offsetx=0;}
            else ++offsetx;
        }

        render(offsetx,0);
        render(offsetx+getWidth(),0);
    }
    if(y){
        --offsety;
        if(offsety<=SCREEN_HEIGHT-getHeight()){
            if(inf){offsety=0;}
            else {++offsety;}
        }
        render(0,offsety);
        //render(0,offsety+getHeight());
    }

}
