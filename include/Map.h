#ifndef MAP_H
#define MAP_H
#include <SDL2/SDL.h>
#include<BATTLE_SCENE.h>
#include<mainmap.h>
#define map_num 5
#define icon_num 13
const std::string map_image[map_num]={
        "image/map/land.png",
        "image/map/m1.jpg",
        "image/map/m2.jpg",
        "image/map/m3.jpg",
        "image/map/m4.jpg",

};
const std::string icon_image[icon_num]={
        "image/map/icon5.png",
        "image/map/icon2.png",
        "image/map/icon3.png",
        "image/map/icon4.png",
        "image/map/icon1.png",
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
const int x[12]={160,140,300,410,610,800,900,1040,1130,1025,920,620};
const int y[12]={110,220,480,390,420,450,350,300,200,100,150,165};

class Map
{

    public:

        Map();
        virtual ~Map();
        void Map_ini();
        void Map_mode(SDL_Event &e,BATTLE_SCENE &b){
        //void Map_mode(SDL_Event &e,BATTLE_SCENE b[]){

            switch(mode){
                case 1:
                    map[bigmap].render(0,0);
                    //judge[0]=1;
                    //iconb[0].map_but(e,icon[0],map_button[0],mode,0,0,2);
                    for(int i=0;i<icon_num-1;i++){
                        if(judge[i]!=0){
                            iconb[i].set_value(x[i],y[i],2);
                            //mode=iconb[i].map_but(e,icon[i],map_button[i]);
                            iconb[i].map_but(e,icon[i],map_button[i],mode);
                            if(mode!=1){i0=i; printf("w");SDL_Delay(200);break;}

                        }

                        //if(mode!=0)break;
                    }
                    //mode=iconb[icon1].map_but(e,icon[icon1],map_button[icon1],mode,100,100,2);
                    //if(mode==0){mode=1;printf("s");}
                    SDL_RenderPresent( gRenderer );
                    break;
                case 2:
                    static int a=1;
                    //b[i0].battle(e,mode);
                    b.battle(e,mode);
                    iconb[goback].set_value(0,550,1);
                    //mode=iconb[goback].map_but(e,icon[goback],map_button[goback]);
                    iconb[goback].map_but(e,icon[goback],map_button[goback],mode);
                    //if(mode==0){mode=2;printf("q");}
                    //else {judge[a]=1;a++;}
                    if(mode==1){judge[a]=1;a++;SDL_Delay(200);}
                    SDL_RenderPresent( gRenderer );
                    break;
            }
            SDL_RenderPresent( gRenderer );
        }




    protected:

    private:
        int i0;
        int mode = 1;
        LTexture map[map_num];
        LTexture icon[icon_num];
        LButton map_button[icon_num];
        mainmap iconb[icon_num];
        BATTLE_SCENE b[12];
        void load();
        bool judge[12]={1,0,0,0,0,0,0,0,0,0,0,0};
        //mainmap big;


};

#endif // MAP_H
