#include "BATTLE_SCENE_MULTI.h"

BATTLE_SCENE_MULTI::BATTLE_SCENE_MULTI()
{
    //ctor
}
BATTLE_SCENE_MULTI::BATTLE_SCENE_MULTI(int category)
{
    initialize(category);
}
BATTLE_SCENE_MULTI::BATTLE_SCENE_MULTI(int cha[12])
{
    initialize_var(cha);
}

BATTLE_SCENE_MULTI::~BATTLE_SCENE_MULTI()
{
    //dtor
}
void BATTLE_SCENE_MULTI::battle(SDL_Event &e,int &mode){

            //Handle events on queue
				now_click_flag = ( e.type == SDL_MOUSEBUTTONDOWN );
				int click=now_click_flag-prev_click_flag;
				//Clear screen

				/*******visualization*******/
				//field and tiles
				create_battlefield();
				//soldiers
				set_soldiers();

                //victory judge
                if(victory_judge(tiles,sacred_right)){
                        scene_image[victory].render(SCREEN_WIDTH/2-scene_image[victory].getWidth()/2,SCREEN_HEIGHT/3-scene_image[victory].getHeight()/2);
                        if(on==0){
                                on=1;
                                exit=new BUTTON;
                                exit->init(SCREEN_WIDTH/2-50,SCREEN_HEIGHT/2-25,100,50);
                                exit->load("image/exit.png","image/exit.png");
                        }
                        if(exit!=NULL){
                            exit->render(&e);
                            exit->handle(clock_on,1,click,start_time,sound[0]);
                        }

                        if(clock_on==1 and clock()-start_time>=200)mode++;
                        turn=FROZEN;
                }
                if(victory_judge(tiles,sacred_left)){
                        scene_image[defeat].render(SCREEN_WIDTH/2-scene_image[defeat].getWidth()/2,SCREEN_HEIGHT/3-scene_image[defeat].getHeight()/2);
                         if(on==0){
                                on=1;
                                exit=new BUTTON;
                                exit->init(SCREEN_WIDTH/2-50,SCREEN_HEIGHT/2-25,100,50);
                                exit->load("image/exit.png","image/exit.png");
                        }
                        if(exit!=NULL){
                            exit->render(&e);
                            exit->handle(clock_on,1,click,start_time,sound[0]);
                        }

                        if(clock_on==1 and clock()-start_time>=200)mode++;
                        turn=FROZEN;
                }

                static bool start=0;
                if(turn==MY){
                    //scene_image[next_turn].render(next_turn_button.get_x(),next_turn_button.get_y());
                    clock_t nothing;
                    next_turn_button.render(&e);
                    next_turn_button.handle(turn,FOE,click,nothing,sound[0]);
                    if(turn==FOE){
                        start=0;
                        step=SELECT_UNIT;
                    }
                    if(start ==0){
                        for(int k=MY_1;k<=MY_6;k++){
                            if(soldier[k]!=NULL){
                               soldier[k]->set_point(soldier[k]->getrange());
                            }
                        }
                        start=1;
                    }
                    static int sel;

                    if(step==SELECT_UNIT){
                            battle_judge.show_select(tiles,soldier,e,step,sel,click,&sound[0]);
                        //show_select(e,step,sel,click);
                    }
                    else if(step==SELECT_TARGET){
                        battle_judge.buttons_target_show(tiles,soldier,e,step,sel,click,&sound[1]);
                        //buttons_target_show(e,step,sel,click);
                    }
                }
                else if(turn==FOE){
                    clock_t nothing;
                    next_turn_button.render(&e);
                    next_turn_button.handle(turn,MY,click,nothing,sound[0]);
                    if(turn==MY){
                       start=0;
                       step=SELECT_UNIT;
                    }
                    if(start ==0){
                        for(int k=FOE_1;k<=FOE_6;k++){
                            if(soldier[k]!=NULL){
                               soldier[k]->set_point(soldier[k]->getrange());
                            }
                        }
                        start=1;
                    }
                    static int sel;

                    if(step==SELECT_UNIT){
                            battle_judge.show_select_multi(tiles,soldier,e,step,sel,click,&sound[0]);

                        //show_select(e,step,sel,click);
                    }
                    else if(step==SELECT_TARGET){
                        battle_judge.buttons_target_show_multi(tiles,soldier,e,step,sel,click,&sound[1]);
                        //buttons_target_show(e,step,sel,click);
                    }
                }
                //buttons
				//Update screen
				prev_click_flag=now_click_flag;
				SDL_RenderPresent( gRenderer );
}
void BATTLE_SCENE_MULTI::initialize_var(int cha[12]){
            //load image
            load();
            scene_image[field].loadFromFile(field_name[0]);
            //property loading
            std::fstream file;
            file.open("property.csv");
            std::string line;
            int a=1;
            while (getline( file, line,'\n'))  //Ū��Ū�����r��
            {
                std::istringstream templine(line); // string �ഫ�� stream
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

            //tiles
			int count=0;
			for(int a=0;a<x_num;a++){
                    for(int b=0;b<y_num-(a+1)%2;b++){
                        tiles[count].set_xy(a*x_dis+x_init, b*y_dis+y_init+y_dis*((a+1)%2)/2);
                        tiles[count].setsoldier_num(none);
                        count++;
                    }
				}

            //soldiers position
            int soldier_cha[sol_num*3+1]={DUCK_ORI,DUCK_ORI,DUCK_ORI,DUCK_ORI,DUCK_ORI,DUCK_ORI,DUCK_ORI
                                            ,DUCK_ORI,DUCK_ORI,DUCK_ORI,DUCK_ORI,DUCK_ORI,DUCK_ORI
                                            ,DUCK_ORI,DUCK_ORI,DUCK_ORI,DUCK_ORI,DUCK_ORI,DUCK_ORI};//Everyone is duck.
            for(int k=1;k<=12;k++)soldier_cha[k]=cha[k-1];

            soldier=new men_with_arms*[3*sol_num+1];/*****/

            for(int a=MY_1;a<=NEUTRAL_6;a++)
            {
                if(soldier_cha[a]!=NO_MEN) soldier[a]=new men_with_arms;
                else soldier[a]=NULL;

            }
            int init_pos[19];
            /***set the characters of the soldiers***/

                    //soldier_character

                    int positions_init[sol_num*3+1]={0,5,7,1,2,10,11,32,34,28,29,37,38,40,40,40,40,40,40};/***********/
                    for(int k=0;k<sol_num*3+1;k++){
                            init_pos[k]=positions_init[k];

                    }





            for(int a=MY_1;a<=FOE_6;a++){
                    if(soldier[a]!=NULL and soldier_cha[a]!=NO_MEN){
                    int k=soldier_cha[a];
                    soldier[a]->set_id(a);
                    int icon_label=((a-1)/6)*3+property[k][arms_property]+1;
                    soldier[a]->load(stand_image_name[k],battle_image_name[k],"image/bar_bottom.png","image/bar_top.png",name_icon[icon_label]);
                    soldier[a]->render(init_pos[a],tiles);
                    soldier[a]->set_property(soldier_character(soldier_cha[a]),property[k][arms_property],property[k][health_property]
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
                    soldier[a]->load("image/none.png","image/none.png","image/bar_bottom.png","image/bar_top.png","image/none.png");
                    soldier[a]->render(init_pos[a],tiles);
                    soldier[a]->set_property(soldier_character(soldier_cha[a]),property[k][arms_property],property[k][health_property]
                                             ,property[k][combat_strength_property],property[k][range_property],property[k][firerange_property]);
                    }
				}
            //buttons position and dimensions
            int l_x=x_next;int l_y=y_next;
            next_turn_button.init(l_x,l_y,scene_image[next_turn].getWidth(),scene_image[next_turn].getHeight());
            next_turn_button.load("image/next_turn.png","image/next_turn.png");



            //turn constant
            turn=MY;
            step=SELECT_UNIT;
            prev_click_flag=0;
            now_click_flag=0;

            clock_on=0;
            on=0;

            ai_perform=1;
            end_ai=0;
            //sound
            for(int i=0;i<SOUND;i++){sound[i].loadsound(sound_name[i]);}
}
