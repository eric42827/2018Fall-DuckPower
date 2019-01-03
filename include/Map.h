#ifndef MAP_H
#define MAP_H
#include <SDL2/SDL.h>
#include <BATTLE_SCENE.h>
#include <mainmap.h>
#include <Change_scene.h>
#include <iostream>
#include "definition.h"
using namespace std;

const string change_image[change_num]={
        "image/change/brand.png",

};
const string menu_image[menu_num]={
        "image/menu/story.png",
        "image/menu/tutorial.png",
        //"image/menu/setting.png",
        "image/menu/about.png",
        //"image/menu/title3.png",
};
const string scene_image[scene_num]={//menu background(scroll)
        "image/menu/main4.png",
};
const string map_image[map_num]={
        "image/map/land.png",
        "image/menu/title3.png",
};
const string tutor_image[tutor_num]={
        "image/map/bigmap640f.png",
};
const string about_image[about_num]={
        "image/menu/about2.png",
};
const string icon_image[icon_num]={
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
        "image/map/skip1.png",
        "image/map/return1.png"
};
enum menu_name{

};
enum map_name{
    bigmap=0,
    title=1,

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
    goback=12,
    gomenu=13

};
const int iconx[12]={160,140,300,410,610,800,900,1040,1130,1025,920,610};
const int icony[12]={110,220,480,390,420,450,350,300,200,100,150,165};
const int menuy[3]={300,400,500};
const int iconm[12]={2,2,2,2,2,2,2,2,2,2,2,2};
const int menum[3]={1,11,12};
class Map
{

    public:
        bool quit;
        Map();
        virtual ~Map();
        void Map_ini();
        void Map_mode(SDL_Event &e,BATTLE_SCENE **b,bool &quit){
            switch(mode){

                case 0:
                    //menu[background].scro
                    /*--scrollingOffset;
                    if( scrollingOffset < -menu[background].getWidth())scrollingOffset = 0;
                    menu[background].render(scrollingOffset,0);
                    menu[background].render(scrollingOffset + menu[background].getWidth(),0);
                    */
                    scene[0].scroll(1,0,1);
                    map[title].render(340,25);
                    for(int i=0;i<menu_num;i++){
                        menu[i].menu_but(e,mode);
                        if(mode){SDL_Delay(200);break;}
                    }

                    SDL_RenderPresent( gRenderer );
                    break;
                case 1:
                    map[bigmap].render(0,0);
                    icon[gomenu].map_but(e,mode);
                    for(int i=0;i<icon_num-2;i++){
                        if(judge[i]){//judge whether this stage is played or not
                            icon[i].setAlpha(255);
                            icon[i].map_but(e,mode);//press to change mode
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
                case 2://each stage
                    b[now][0].battle(e,mode);
                    icon[goback].map_but(e,mode);
                    if(mode==1){
                        check=1;
                        icon[now].clean=0;
                        //delete[]b[now];
                        now++;
                        if(now==12){
                                quit = true;
                                break;
                        }
                    }
                    SDL_RenderPresent( gRenderer );
                    break;

                case 11://tutorial
                    tutor[0].render(0,0);
                    icon[gomenu].map_but(e,mode);
                    SDL_RenderPresent( gRenderer );
                    break;
                case 12://about
                    about[0].scroll(0,1,0);
                    icon[gomenu].map_but(e,mode);
                    if(mode==0)about[0].offsety=0;
                    SDL_RenderPresent( gRenderer );
                    break;
            }
            return;
        }

    protected:

    private:
        /**********mainmap*********/
        LTexture map[map_num];//bigmap
        mainmap icon[icon_num];//mix button and pic
        /*********menu*******/
        mainmap menu[menu_num];
        Change_scene scene[scene_num];//scrolling background
        LTexture tutor[tutor_num];
        Change_scene about[about_num];
        Change_scene change[change_num];
        /*********other declaration*******/
        void load();
        bool judge[12]={1,0,0,0,0,0,0,0,0,0,0,0};
        int mode = 0;
        int a=1;
        int now=0;
        int check =0;//jugde which stage is complete
        //int scrollingOffset = 0;



};

#endif // MAP_H
