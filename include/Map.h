#define _GLIBCXX_USE_CXX11_ABI 0
#ifndef MAP_H
#define MAP_H
#include <SDL2/SDL.h>
#include <BATTLE_SCENE.h>
#include <mainmap.h>
#include <Change_scene.h>
#include <iostream>
#include "definition.h"
#include "music.h"
using namespace std;

const string music_name[MUSIC]={
        "music/maple.mp3",
        "music/village.wav",
        "music/Warfare.mp3",
        "music/sao.mp3",
        "music/Emiya.mp3",
        "music/teacher1.mp3",
        "music/teacher2.mp3",
};
enum music_enum{
    maple=0,
    village=1,
    battle1=2,
    battle2=3,
    battle3=4,
    teacher1=5,
    teacher2=6,
};


const string menu_image[menu_num]={
        "image/menu/story.png",
        "image/menu/tutorial.png",
        "image/menu/about.png",
};
const string scene_image[scene_num]={//menu background(scroll)
        "image/menu/main41.png",
        "image/change/say1.png",
};
const string map_image[map_num]={
        "image/map/land.png",
        "image/menu/title3.png",
        "image/change/black.png",
        "image/change/brand1.png",
        "image/menu/version.png",

};
const string tutor_image[tutor_num]={
        "image/map/bigmap640f.png",
};
const string about_image[about_num]={
        "image/menu/about3.png",
};
const string icon_image[icon_n]={
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
        "image/map/return1.png",
        "image/change/teacher.png",
};
enum casemode{
    start=13,
};
enum chan_name{

};
enum map_name{
    bigmap=0,
    title=1,
    black=2,
    brand=3,
    version=4,

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
    gomenu=13,
    teacher=14,
};

const int iconx[icon_n]={160,140,300,410,610,800,900,1040,1130,1025,920,610,SCREEN_WIDTH-203,0,1079};
const int icony[icon_n]={110,220,480,390,420,450,350,300,200,100,150,165,590,0,388};
const int menuy[3]={300,400,500};
const int iconm[icon_n]={2,2,2,2,2,2,2,2,2,2,2,2,1,0,1};
const int menum[3]={14,11,12};

class Map
{

    public:

        Map();
        virtual ~Map();
        bool quit;
        friend class mainmap;
        friend int get_mode();
        void Map_ini();
        void Map_mode(SDL_Event &e,BATTLE_SCENE **b,bool &quit){
            switch(mode){
                //if(mode==0)menumusic.playmusic();
                case 0:
                    bgm[maple].playmusic();
                    scene[0].scroll(1,0,1);
                    _map[title].render(340,25);
                    _map[version].render(1138,613);
                    for(int i=0;i<menu_num;i++){
                        menu[i].menu_but(e,mode);
                        if(mode){bgm[maple].stopmusic();SDL_Delay(200);break;}
                    }
                    SDL_RenderPresent( gRenderer );
                    break;
                case 1:
                    bgm[village].playmusic();
                    _map[bigmap].render(0,0);
                    icon[gomenu].map_but(e,mode);
                    for(int i=0;i<icon_n-3;i++){
                        if(judge[i]){//judge whether this stage is played or not
                            icon[i].setAlpha(255);
                            icon[i].map_but(e,mode);//press to change mode
                            if(mode!=1){
                                    b[now]=new BATTLE_SCENE(now%3);
                                    bgm[village].stopmusic();
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
                    bgm[(now)%3+2].playmusic();
                    b[now][0].battle(e,mode);
                    icon[goback].map_but(e,mode);
                    if(mode==1){
                        check=1;
                        icon[now].clean=0;
                        now++;
                        bgm[(now)%3+2].stopmusic();
                        if(now==12){
                                quit = true;
                                break;
                        }
                    }
                    SDL_RenderPresent( gRenderer );
                    break;
                case 11://tutorial
                    //menumusic.playmusic();
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
                case 13:
                    for(int t=0;t<256;t++){
                        _map[black].render(0,0);
                        _map[brand].setAlpha(t);
                        _map[brand].render(206,270);
                        t++;
                        SDL_RenderPresent( gRenderer );
                    }
                    for(int t=255;t>0;t--){
                        _map[black].render(0,0);
                        _map[brand].setAlpha(t);
                        _map[brand].render(206,270);
                        t--;
                        SDL_RenderPresent( gRenderer );
                    }
                    mode=0;
                    break;
                case 14:
                    scene[1].scroll(0,1,0);
                    bgm[teacher1].playmusic();
                    icon[teacher].map_but(e,mode);
                    if(mode!=14){bgm[teacher1].stopmusic();scene[1].offsety=0;}
                    SDL_RenderPresent( gRenderer );


            }
            return;
        }

    private:
        /**********mainmap*********/

        LTexture _map[map_num];//bigmap
        mainmap icon[icon_n];//mix button and pic
        /*********menu*******/
        mainmap menu[menu_num];
        Change_scene scene[scene_num];//scrolling background
        LTexture tutor[tutor_num];
        Change_scene about[about_num];
        //Change_scene change[change_num];
        music bgm[MUSIC];
        //music sound[SOUND];
        /*********other declaration*******/
        void load();
        bool judge[12]={1,0,0,0,0,0,0,0,0,0,0,0};
        int a=1;
        int now=0;
        int check=0;//jugde which stage is complete
        int mode=13;



};

#endif // MAP_H
