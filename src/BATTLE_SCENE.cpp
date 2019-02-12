#include "BATTLE_SCENE.h"
BATTLE_SCENE::BATTLE_SCENE()
{
}
BATTLE_SCENE::BATTLE_SCENE(int category)
{
 initialize(category);

}

BATTLE_SCENE::~BATTLE_SCENE()
{
    for(int a=0;a<image_num;a++)scene_image[a].free();
}
void BATTLE_SCENE::battle(SDL_Event &e,int &mode){

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

                        if(clock_on==1 and clock()-start_time>=200)mode=1;
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

                        if(clock_on==1 and clock()-start_time>=200)mode=1;
                        turn=FROZEN;
                }

                static bool start=0;
                if(turn==MY){
                    //scene_image[next_turn].render(next_turn_button.get_x(),next_turn_button.get_y());
                    clock_t nothing;
                    next_turn_button.render(&e);
                    next_turn_button.handle(turn,FOE,click,nothing,sound[0]);

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
                    }
                    else if(step==SELECT_TARGET){
                        battle_judge.buttons_target_show(tiles,soldier,e,step,sel,click,&sound[1]);

                    }
                }
                else if(turn==FOE){
                        static int num=FOE_1;

                        if(ai_perform){
                            AI(num);
                            num++;
                            ai_perform=0;
                            start_time=clock();
                        }
                        if(clock()-start_time>=500)ai_perform=1;
                        scene_image[waiting].render(x_next,y_next);

                        if(num==FOE_6+1 and ai_perform==1)end_ai=1;
                        if(end_ai){
                            num=FOE_1;
                            ai_perform=1;
                            end_ai=0;

                            start=0;
                            turn=MY;
                            step=SELECT_UNIT;
                            }
                }
                //buttons
				//Update screen
				prev_click_flag=now_click_flag;
}

/***Primary Level Function***/
int BATTLE_SCENE::abs(int a){
    if(a<0)return -a;
    else return a;
}
int BATTLE_SCENE::distance(int pos1,int pos2,base* a){
        const double x=(a[pos2].x-a[pos1].x)/x_dis;
        const double y=(a[pos2].y-a[pos1].y)/y_dis;
        int dist=0;
        if(x==0)dist=abs(y);
        else{
            const double m=y/x;
            if((m>-0.5)and(m<0.5)and(x>0))dist=x;
            else if((m>-0.5)and(m<0.5)and(x<0))dist=-x;
            else if((m>0.5)and(x>0))dist=0.5*x+y;
            else if((m>0.5)and(x<0))dist=-(0.5*x+y);
            else if((m<-0.5)and(x>0))dist=0.5*x-y;
            else if((m<-0.5)and(x<0))dist=-(0.5*x-y);
            else if((m==0.5)or(m==-0.5))dist=abs(x);
            }
            return dist;
}
bool BATTLE_SCENE::judge(int sel,int sel2,int dis,int tar,base *a){
    return(sel2!=tar)*(sel2<tiles_num)*(sel2>=0)*(abs(a[sel2].y-a[sel].y)==dis);
}
/***Secondary Level Function***/


int BATTLE_SCENE::foe_target(int sel,base *a,int n){
            static bool flag=0;
            static int count=0;
            static bool check[tiles_num];
            static int tar;
            static int max_level;
            static soldier_arms arms;
            if(flag==0){
                    tar=sel;
                    max_level=n;
                    for(int k=0;k<tiles_num;k++)check[k]=0;
                    arms=soldier[a[sel].soldier_num]->get_arms();
            }
            if(n==0){
                if((sel!=tar)and(sel!=sacred_right)){
                    if((a[sel].soldier_num==none)){
                        count++;
                    }
                }
            }
            else{
                flag=1;
                int door=((a[sel].soldier_num==none)or((a[sel].soldier_num>=FOE_1)and(a[sel].soldier_num<=FOE_6)));
                if(check[sel]==0){
                    foe_target(sel,a, 0);check[sel]=1;}
                    int next[6]={sel-1,sel+1,sel+y_num,sel-y_num,sel+y_num-1,sel-y_num+1};
                    int dis[6]={y_dis,y_dis,y_dis/2,y_dis/2,y_dis/2,y_dis/2};
                    for(int k=0;k<6;k++){
                        if(judge(sel,next[k],dis[k],tar,tiles)and check[next[k]]==0 and door==true)foe_target(next[k],a, n-1);
                    }
            }
            int mem=0;
            if((sel==tar)and(n==max_level)){
                    if(arms!=air_force){
                        for(int k=0;k<tiles_num;k++){
                            if((a[k].soldier_num<=MY_6)and(a[k].soldier_num>=MY_1)and(distance(k,sel,a)<=soldier[a[sel].soldier_num]->get_firerange())){
                                count++;
                            }
                        }
                    }
                    else{
                        for( int i = MY_1; i <=MY_6; i ++){
                            if(soldier[i]!=NULL){
                                count++;
                            }
                        }
                    }
                for(int k=0;k<tiles_num;k++)check[k]=0;
                mem=count;
                count=0;
                flag=0;
            }
            return mem;

        }
int BATTLE_SCENE::read_target(int sel,base *a,int n,int* pre_pos){
            static bool flag=0;
            static int count=0;
            static bool check[tiles_num];
            static int tar;
            static int max_level;
            static soldier_arms arms;
            if(flag==0){
                    tar=sel;
                    max_level=n;
                    for(int k=0;k<tiles_num;k++)check[k]=0;
                    arms=soldier[a[sel].soldier_num]->get_arms();
            }
            if(n==0){
                if((sel!=tar)and(sel!=sacred_right)){
                    if((a[sel].soldier_num==none)){
                        pre_pos[count]=sel;
                        count++;
                    }
                }
            }
            else{
                flag=1;
                int door=((a[sel].soldier_num==none)or((a[sel].soldier_num>=FOE_1)and(a[sel].soldier_num<=FOE_6)));
                if(check[sel]==0){
                    read_target(sel,a, 0,pre_pos);check[sel]=1;}
                    int next[6]={sel-1,sel+1,sel+y_num,sel-y_num,sel+y_num-1,sel-y_num+1};
                    int dis[6]={y_dis,y_dis,y_dis/2,y_dis/2,y_dis/2,y_dis/2};
                    for(int k=0;k<6;k++){
                        if(judge(sel,next[k],dis[k],tar,tiles)and check[next[k]]==0 and door==true)read_target(next[k],a, n-1,pre_pos);
                    }
            }
            int mem=0;
            if((sel==tar)and(n==max_level)){
                    if(arms!=air_force){
                        for(int k=0;k<tiles_num;k++){
                            if((a[k].soldier_num<=MY_6)and(a[k].soldier_num>=MY_1)and(distance(k,sel,a)<=soldier[a[sel].soldier_num]->get_firerange())){
                                pre_pos[count]=k;
                                count++;
                            }
                        }
                    }
                    else{
                        for( int i = MY_1; i <=MY_6; i ++){
                            if(soldier[i]!=NULL){
                                pre_pos[count]=soldier[i]->get_pos();
                                count++;
                            }
                        }
                    }
                for(int k=0;k<tiles_num;k++)check[k]=0;
                mem=count;
                count=0;
                flag=0;
            }
            return mem;

}
/***Third Level Function***/
void BATTLE_SCENE::setMonte(base *a){
            for(int k=0;k<tiles_num;k++){
            if(k!=sacred_left)a[k].set_Monte(sacredmonte/(degenerate_rate*distance(k,sacred_left,a)));
            else a[k].set_Monte(sacredmonte*2);
            int num=a[k].soldier_num;
            if(num>=MY_1 and num<=MY_6)a[k].set_Monte(a[k].Monte+foe_enhance*5/distance(k,sacred_right,tiles)+foe_health_incr*(soldier[num]->get_maxhealth()-soldier[num]->get_health())/20);
            }
}
/***Highest Level Function***/
void BATTLE_SCENE::create_battlefield(){
            scene_image[field].render( 0,0);
            const int x_l=x_dis/2-x_adj;const int y_l=y_dis/2-y_adj;
            scene_image[king].render(tiles[sacred_left].x+x_l-x_adj/2,tiles[sacred_left].y+y_l-y_adj/4);
            scene_image[king].render(tiles[sacred_right].x+x_l-x_adj/2,tiles[sacred_right].y+y_l-y_adj/4);
            for(int a=0;a<tiles_num;a++){
                    if(tiles[a].soldier_num<=FOE_6)scene_image[loop_tile].render(tiles[a].x,tiles[a].y);
            }
        }
void BATTLE_SCENE::set_soldiers(){
            for(int a=MY_1;a<=FOE_6;a++){
                if(soldier[a]!=NULL){
                    soldier[a]->render(soldier[a]->get_pos(),tiles);/*******/
                }
            }
        }

void BATTLE_SCENE::AI(int k){
                if(soldier[k]!=NULL){
                    setMonte(tiles);
                    int list_length;
                    list_length=foe_target(soldier[k]->get_pos(),tiles,soldier[k]->getrange());
                    int pre_pos[list_length];
                    read_target(soldier[k]->get_pos(),tiles,soldier[k]->getrange(),pre_pos);
                    int mont=tiles[pre_pos[0]].Monte;
                    int pos=pre_pos[0];
                    for(int j=0;j<list_length;j++){
                        if(tiles[pre_pos[j]].Monte>=mont){
                            mont=tiles[pre_pos[j]].Monte;
                            pos=pre_pos[j];}
                    }
                    for(int k=0;k<tiles_num;k++)tiles[k].set_Monte(0);
                    int num=tiles[pos].soldier_num;
                    if(num==none)soldier[k]->go(pos,tiles);
                    else if((num>=MY_1)and(num<=MY_6)){
                        soldier[k]->fight(soldier,tiles,num);
                        sound[2].playsound();

                    }
                }
        }
bool BATTLE_SCENE::victory_judge(base* a,int sacred){
            if(sacred==sacred_left){
                int num=0;
                for(int k=MY_1;k<=MY_6;k++){
                    if(soldier[k]==NULL)num++;
                }
                if(num==6)return true;

            }
            else if(sacred==sacred_right){
                int num=0;
                for(int k=FOE_1;k<=FOE_6;k++){
                    if(soldier[k]==NULL)num++;
                }
                if(num==6)return true;

            }
            if(a[sacred].soldier_num!=0)return true;
            else return false;
        }
void  BATTLE_SCENE::load(){
        for(int k=0;k<image_num;k++){
            if(k!=field)scene_image[k].loadFromFile(scene_image_name[k]);
        }


}
/*****Initialization****/
void BATTLE_SCENE::initialize(int category){
            //load image
            load();
            scene_image[field].loadFromFile(field_name[category]);
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
                    property[a][b]=atoi(data.c_str());
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
            soldier_character soldier_cha[sol_num*3+1]={DUCK_ORI,DUCK_ORI,DUCK_ORI,DUCK_ORI,DUCK_ORI,DUCK_ORI,DUCK_ORI
                                            ,DUCK_ORI,DUCK_ORI,DUCK_ORI,DUCK_ORI,DUCK_ORI,DUCK_ORI
                                            ,DUCK_ORI,DUCK_ORI,DUCK_ORI,DUCK_ORI,DUCK_ORI,DUCK_ORI};//Everyone is duck.

            soldier=new men_with_arms*[3*sol_num+1];/*****/

            for(int a=MY_1;a<=NEUTRAL_6;a++)
            {
                if(soldier_cha[a]!=NO_MEN) soldier[a]=new men_with_arms;
                else soldier[a]=NULL;

            }
            int init_pos[19];
            /***set the characters of the soldiers***/
            switch (category){
                case 0:
                    {
                    //soldier_character
                     soldier_character cha[sol_num*3+1]={DUCK_ORI,SHOOTER,SHOOTER,FLY,FLY,HUMAN1,HUMAN1
                                            ,DUCK_ORI,DUCK_ORI,DUCK_GREEN,DUCK_GREEN,DUCK_RED,DUCK_RED
                                            ,DUCK_ORI,DUCK_ORI,DUCK_ORI,DUCK_ORI,DUCK_ORI,DUCK_ORI};

                    int a[sol_num*3+1]={0,5,7,1,2,10,11,32,34,28,29,37,38,40,40,40,40,40,40};/***********/
                    for(int k=0;k<sol_num*3+1;k++){
                            init_pos[k]=a[k];
                            soldier_cha[k]=cha[k];
                    }
                    break;
                    }

                case 1:
                    {
                    //soldier_character
                     soldier_character cha[sol_num*3+1]={DUCK_ORI,SHOOTER2,SHOOTER2,FLY2,FLY2,IKE,HUMAN2
                                            ,RED_BIRD,RED_BIRD,SWAN,BLACK_SWAN,SEAGULL,SEAGULL
                                            ,DUCK_ORI,DUCK_ORI,DUCK_ORI,DUCK_ORI,DUCK_ORI,DUCK_ORI};

                    int a[sol_num*3+1]={0,5,7,1,2,10,11,32,34,28,29,37,38,18,21,0,3,36,39};/***********/
                    for(int k=0;k<sol_num*3+1;k++){
                            init_pos[k]=a[k];
                            soldier_cha[k]=cha[k];
                    }
                    break;
                    }

                case 2:
                    {
                    //soldier_character
                     soldier_character cha[sol_num*3+1]={DUCK_ORI,FLY3,LEGEND,FLY3,FLY3,IKE,ROY
                                            ,PENGUIN,PENGUIN,RUBBER_DUCK,DUCK_BEIJING,CEIBA,MOLTRES
                                            ,DUCK_ORI,DUCK_ORI,DUCK_ORI,DUCK_ORI,DUCK_ORI,DUCK_ORI};


                   int a[sol_num*3+1]={0,5,7,1,2,10,11,32,34,28,29,37,38,19,20,0,15,24,39};/***********///
                    for(int k=0;k<sol_num*3+1;k++){
                            init_pos[k]=a[k];
                            soldier_cha[k]=cha[k];
                    }
                    break;
                    }

            }

            for(int a=MY_1;a<=FOE_6;a++){
                    if(soldier[a]!=NULL and soldier_cha[a]!=NO_MEN){
                    int k=soldier_cha[a];
                    soldier[a]->set_id(a);
                    int icon_label=((a-1)/6)*3+property[k][arms_property]+1;
                    soldier[a]->load(stand_image_name[k],battle_image_name[k],"image/bar_bottom.png","image/bar_top.png",name_icon[icon_label]);
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
                    soldier[a]->load("image/none.png","image/none.png","image/bar_bottom.png","image/bar_top.png","image/none.png");
                    soldier[a]->render(init_pos[a],tiles);
                    soldier[a]->set_property(soldier_cha[a],property[k][arms_property],property[k][health_property]
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
