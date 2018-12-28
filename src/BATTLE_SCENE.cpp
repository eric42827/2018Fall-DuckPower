#include "BATTLE_SCENE.h"
BATTLE_SCENE::BATTLE_SCENE()
{
}
BATTLE_SCENE::BATTLE_SCENE(int category)
{
 //load image
            load();

            //property loading
            std::fstream file;
            file.open("property.csv");
            std::string line;
            int a=1;
            while (getline( file, line,'\n'))  //讀檔讀到跳行字元
            {
                std::istringstream templine(line); // string 轉換成 stream
                std::string data;

                int buffer=2;
                for(int b=0;b<buffer;b++){
                    getline( templine, data,',');
                }
                for(int b=0;b<property_num;b++){
                    getline( templine, data,',');
                    property[a][b]=atoi(data.c_str());//std::cout<<property[a][b];
                }
                a++;
            }

            file.close();
            soldier_character soldier_cha[sol_num*3+1]={DUCK_ORI,DUCK_ORI,DUCK_GREEN,DUCK_RED,DUCK_BEIJING,SWAN,BLACK_SWAN
                                            ,DUCK_ORI,DUCK_GREEN,DUCK_RED,DUCK_BEIJING,SWAN,BLACK_SWAN
                                            ,DUCK_ORI,DUCK_ORI,DUCK_ORI,DUCK_ORI,DUCK_ORI,DUCK_ORI};

            //tiles
			int count=0;
			for(int a=0;a<x_num;a++){
                    for(int b=0;b<y_num-(a+1)%2;b++){
                        tiles[count].set_xy(a*x_dis+x_init, b*y_dis+y_init+y_dis*((a+1)%2)/2);
                        tiles[count].setsoldier_num(none);
                        count++;
                    }
				}
            //our soldiers
            /********/
            //soldiers position


            soldier=new men_with_arms*[3*sol_num+1];/*****/

            for(int a=MY_1;a<=NEUTRAL_6;a++)
            {
                if(soldier_cha[a]!=NO_MEN) soldier[a]=new men_with_arms;
                else soldier[a]=NULL;

            }
            int init_pos[19];
            switch (category){
                case 0:
                    {
                    int a[19]={0,5,7,1,2,10,11,32,34,28,29,37,38,40,40,40,40,40,40};/***********/
                    for(int k=0;k<19;k++){init_pos[k]=a[k];}
                    break;
                    }

                case 1:
                    {
                    int b[19]={0,5,7,1,2,10,11,32,34,28,29,37,38,18,21,0,3,36,39};/***********/
                    for(int k=0;k<19;k++){init_pos[k]=b[k];}
                    break;
                    }

                case 2:
                    {
                    int c[19]={0,5,7,1,2,10,11,32,34,28,29,37,38,19,20,0,15,24,39};/***********/
                    for(int k=0;k<19;k++){init_pos[k]=c[k];}
                    break;
                    }


            }

            for(int a=MY_1;a<=FOE_6;a++){
                    if(soldier[a]!=NULL and soldier_cha[a]!=NO_MEN){
                    int k=soldier_cha[a];
                    soldier[a]->set_id(a);
                    int icon_label=((a-1)/6)*3+property[k][arms_property]+1;
                    soldier[a]->load(stand_image_name[k],battle_image_name[k],&scene_image[bar_bottom],&scene_image[bar_top],name_icon[icon_label]);
                    soldier[a]->render(init_pos[a],tiles);
                    soldier[a]->set_property(soldier_cha[a],property[k][arms_property],property[k][health_property]
                                             ,property[k][combat_strength_property],property[k][range_property],property[k][firerange_property]);


                    }
				}
            //FOE soldiers
            for(int k=FOE_1;k<=FOE_6;k++){
                if(soldier[k]!=NULL)soldier[k]->set_point(soldier[k]->getrange());
            }

            //soldiers position


            for(int a=NEUTRAL_1;a<=NEUTRAL_6;a++){
                    int k=soldier_cha[a];
                    if(soldier[a]!=NULL){
                    soldier[a]->set_id(a);
                    soldier[a]->load("image/none.png","image/none.png",&scene_image[none],&scene_image[none],"image/none.png");
                    soldier[a]->render(init_pos[a],tiles);
                    soldier[a]->set_property(soldier_cha[a],property[k][arms_property],property[k][health_property]
                                             ,property[k][combat_strength_property],property[k][range_property],property[k][firerange_property]);
                    }
				}
            //buttons position and dimensions
            int l_x=x_next;int l_y=y_next;
            next_turn_button.setPosition(l_x,l_y);
            next_turn_button.setdim(scene_image[next_turn].getWidth(),scene_image[next_turn].getHeight());

}

BATTLE_SCENE::~BATTLE_SCENE()
{
    for(int a=0;a<image_num;a++)scene_image[a].free();
}
