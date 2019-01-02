#ifndef MAP_H
#define MAP_H
#include <SDL2/SDL.h>
#include<BATTLE_SCENE.h>
#include<mainmap.h>
#include<iostream>
#define map_num 1
#define icon_num 13
#define menu_num 6
const std::string menu_image[menu_num]={
        "image/menu/story1.png",
        "image/menu/tutorial.png",
        "image/menu/setting.png",
        "image/menu/about.png",
        "image/menu/main4.png",
        "image/menu/title2.png",
};
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
enum menu_name{
    background=4,
    title=5,


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
const int iconx[12]={160,140,300,410,610,800,900,1040,1130,1025,920,610};
const int icony[12]={110,220,480,390,420,450,350,300,200,100,150,165};
const int menuy[4]={182,300,400,500};
const int iconm[12]={2,2,2,2,2,2,2,2,2,2,2,2};
const int menum[4]={1,1,1,1};
class Map
{

    public:

        Map();
        virtual ~Map();
        void Map_ini();
        void Map_mode(SDL_Event &e,BATTLE_SCENE **b){
            switch(mode){
                case 0:
                    --scrollingOffset;
                    if( scrollingOffset < -menu[background].getWidth()){std::cout<<scrollingOffset;
                        scrollingOffset = 0;
                    }
                    menu[background].render(scrollingOffset,0);
                    menu[background].render( scrollingOffset + menu[background].getWidth(), 0 );
                    menu[title].render(0,0);
                    for(int i=0;i<menu_num-2;i++){
                        menub[i].menu_but(e,menu[i],menu_button[i],mode);
                    }

                    SDL_RenderPresent( gRenderer );
                    break;
                case 1:
                    map[bigmap].render(0,0);
                    for(int i=0;i<icon_num-1;i++){
                        if(judge[i]){//judge whether this stage is played or not
                            icon[i].setAlpha(255);
                            iconb[i].map_but(e,icon[i],map_button[i],mode);//press to change mode
                            if(mode!=1){
                                    b[now]=new BATTLE_SCENE(0);
                                    SDL_Delay(200);break;
                            }
                        }
                    }
                    if(check){
                        judge[a]=1;
                        for(int t=0;t<=100;t++){
                            icon[a].setAlpha(t);
                            SDL_Delay(2);
                            icon[a].render(iconx[a],icony[a],0.9,0.9);
                            SDL_RenderPresent( gRenderer );
                        }
                        check=0;
                        a++;
                    }
                    SDL_RenderPresent( gRenderer );
                    break;
                case 2:
                    //std::cout<<now+2;

                    b[now][0].battle(e,mode);
                    iconb[goback].map_but(e,icon[goback],map_button[goback],mode);
                    if(mode==1){
                        check=1;
                        now++;
                    }
                    SDL_RenderPresent( gRenderer );
                    break;
            }
        }




    protected:

    private:
        /**********mainmap*********/
        LTexture map[map_num];//bigmap
        LTexture icon[icon_num];//pics
        LButton map_button[icon_num];//button
        mainmap iconb[icon_num];//mix button and pic
        /*********menu*******/
        LTexture menu[menu_num];
        LButton menu_button[menu_num-2];
        mainmap menub[menu_num-2];
        /*********other declaration*******/
        void load();
        bool judge[12]={1,0,0,0,0,0,0,0,0,0,0,0};
        int mode = 0;
        int a=1;
        int now=0;
        int check =0;//jugde which stage is complete
        int scrollingOffset = 0;


};

#endif // MAP_H
