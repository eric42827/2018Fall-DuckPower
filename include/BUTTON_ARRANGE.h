#ifndef BUTTON_ARRANGE_H
#define BUTTON_ARRANGE_H
#include<BUTTON.h>
#include<LTexture.h>

class BUTTON_ARRANGE:public BUTTON/***cpp h swap***//***new operator***/
{
    public:
        BUTTON_ARRANGE();
        virtual ~BUTTON_ARRANGE();


        void load(std::string path,std::string path_over);
        void init(int x,int y,int w,int h);

        void render();
        virtual void render_act(SDL_Event *e)=0;



    protected:

        LTexture image;
        LTexture over_image;
    private:


};

#endif // BUTTON_ARRANGE_H
