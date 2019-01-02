#define _GLIBCXX_USE_CXX11_ABI 0
#ifndef MAP_H
#define MAP_H
#include <SDL2/SDL.h>
#include<BATTLE_SCENE.h>
#include<mainmap.h>
#define map_num 1
#define icon_num 13
const std::string map_image[map_num]={
        "image/map/land.png",
};
const std::string icon_image[icon_num]={
        "image/map/icon1.png",
        "image/map/icon2.png",
        "image/map/icon3.png",
        "image/map/icon4.png",
        "image/map/icon5.png",
        "image/map/icon6.png",
        "image/map/icon7.png",
        "image/map/icon8.png",
        "image/map/icon9.png",
        "image/map/icon10.png",
        "image/map/icon11.png",
        "image/map/icon12.png",
        "image/map/return.png"
};
enum map_name{
    bigmap=0,
    island_1=1,
    island_2=2,
    island_3=3,
    island_4=4,

};
enum icon_name{
    icon1=0,
    icon2=1,
    icon3=2,
    icon4=3,
    icon5=4,
    icon6=5,
    icon7=6,
    icon8=7,
    icon9=8,
    icon10=9,
    icon11=10,
    icon12=11,
    goback=12
};
const int x[12]={160,140,300,410,610,800,900,1040,1130,1025,920,610};
const int y[12]={110,220,480,390,420,450,350,300,200,100,150,165};

class Map
{

    public:

        Map();
        virtual ~Map();
        void Map_ini();
        void Map_mode(SDL_Event &e,BATTLE_SCENE **b){
            switch(mode){
                case 1:
                    map[bigmap].render(0,0);
                    for(int i=0;i<icon_num-1;i++){
                        if(judge[i]){//judge whether this stage is played or not
                            icon[i].setAlpha(255);
                            iconb[i].map_but(e,icon[i],map_button[i],mode);//press to change mode
                            if(mode!=1){
                                SDL_Delay(200);
                                break;
                            }
                        }
                    }
                    if(check){
                        judge[a]=1;
                        for(int t=0;t<=100;t++){
                            icon[a].setAlpha(t*2.55);
                            icon[a].render(x[a],y[a],0.9,0.9);
                            SDL_RenderPresent( gRenderer );
                        }
                        check=0;
                        a++;
                    }
                    SDL_RenderPresent( gRenderer );
                    break;
                case 2:
                    b[now][0].battle(e,mode);
                    iconb[goback].map_but(e,icon[goback],map_button[goback],mode);
                    if(mode==1){check=1;now++;}
                    SDL_RenderPresent( gRenderer );
                    break;
            }
        }




    protected:

    private:
        LTexture map[map_num];
        LTexture icon[icon_num];
        LButton map_button[icon_num];
        mainmap iconb[icon_num];
        void load();
        bool judge[12]={1,0,0,0,0,0,0,0,0,0,0,0};
        int mode = 1;
        int a=1;
        int now=0;
        int check =0;//jugde which stage is complete
        //mainmap big;


};

#endif // MAP_H
