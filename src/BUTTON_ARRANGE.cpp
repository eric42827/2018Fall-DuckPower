#include "BUTTON_ARRANGE.h"

BUTTON_ARRANGE::BUTTON_ARRANGE()
{

}

BUTTON_ARRANGE::~BUTTON_ARRANGE()
{
    //dtor
}
void BUTTON_ARRANGE::load(std::string path,std::string path_over){
            image.loadFromFile(path);
            over_image.loadFromFile(path_over);
}

void BUTTON_ARRANGE::init(int x,int y,int w,int h){
            button.setPosition(x,y);
            button.setdim(w,h);
}

void BUTTON_ARRANGE::render(){
            int x=button.get_x();
            int y=button.get_y();

            image.render(x,y);
}



