#include "GO_JUDGER.h"

GO_JUDGER::GO_JUDGER()
{
    for(int k=1;k<=12;k++){
                choose[k].init(0,0,x_unit,y_unit);
                choose[k].load("image/none.png","image/yellowloop.png","image/yellowloop.png");
            }
    for(int k=0;k<40;k++){
                goal[k].init(0,0,x_unit,y_unit);
                goal[k].load("image/greenloop.png","image/blueloop.png","image/redloop.png");
    }
}

GO_JUDGER::~GO_JUDGER()
{
    //dtor
}
bool GO_JUDGER::judge(int sel,int sel2,int dis,int tar,base *a){
            return(sel2!=tar)*(sel2<tiles_num)*(sel2>=0)*(abs(a[sel2].y-a[sel].y)==dis);
        }
int GO_JUDGER::distance(int pos1,int pos2,base* a){
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
 void GO_JUDGER::show_select(base *tiles,men_with_arms **soldier,SDL_Event& e,int& step,int& sel,int click,music *sound){
            for( int i = 1; i <=6; i ++){
                if(soldier[i]!=NULL){

                    choose[i].render(&e,soldier[i]->get_pos(),tiles);
                    choose[i].handle(step,1,sel,click,NULL,sound);

                }
            }
}
int GO_JUDGER::show_target(base *tiles,men_with_arms **soldier,int sel,SDL_Event* e,base *a,int n){
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
                if((sel!=tar)and(sel!=sacred_left)){
                    if((a[sel].soldier_num==none)){
                        goal[count].render(e,sel,tiles);
                        count++;
                    }
                }
            }
            else{
                flag=1;
                int door=((a[sel].soldier_num==none)or((a[sel].soldier_num>=MY_1)and(a[sel].soldier_num<=MY_6)));
                if(check[sel]==0){
                    show_target(tiles,soldier,sel,e,a, 0);check[sel]=1;}
                    int next[6]={sel-1,sel+1,sel+y_num,sel-y_num,sel+y_num-1,sel-y_num+1};
                    int dis[6]={y_dis,y_dis,y_dis/2,y_dis/2,y_dis/2,y_dis/2};
                    for(int k=0;k<6;k++){
                        if(judge(sel,next[k],dis[k],tar,tiles)and check[next[k]]==0 and door==true)show_target(tiles,soldier,next[k],e,a, n-1);
                    }
            }
            int mem=0;
            if((sel==tar)and(n==max_level)){
                    if(arms!=air_force){
                        for(int k=0;k<tiles_num;k++){
                            if((a[k].soldier_num<=FOE_6)and(a[k].soldier_num>=FOE_1)and(distance(k,sel,a)<=soldier[a[sel].soldier_num]->get_firerange())){
                                goal[count].render_alarm(e,k,tiles);
                                count++;
                            }
                        }
                    }
                    else{
                        for( int i = FOE_1; i <=FOE_6; i ++){
                            if(soldier[i]!=NULL){
                                goal[count].render_alarm(e,soldier[i]->get_pos(),tiles);
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
void GO_JUDGER::buttons_target_show(base *tiles,men_with_arms **soldier,SDL_Event& e,int& step,int& sel,int click,music *sound){
            int count;
            const int pt=soldier[tiles[sel].soldier_num]->getpoint();
            if(pt!=0){
                count=show_target(tiles,soldier,sel,&e,tiles,pt);
                if(count!=0){
                    for( int i = 0; i < count; i ++){
                        int chosen= goal[i].get_pos();
                        int num=tiles[chosen].soldier_num;

                        goal[i].handle(step,0,chosen,click,NULL,sound);
                        if(step==0){
                    if(num==none){
                            soldier[tiles[sel].soldier_num]->set_point(soldier[tiles[sel].soldier_num]->getpoint()-distance(chosen,sel,tiles));
                                soldier[tiles[sel].soldier_num]->go(chosen,tiles);

                            }
                    else if((num<=FOE_6)and(num>=FOE_1)){
                                soldier[tiles[sel].soldier_num]->set_point(0);
                                soldier[tiles[sel].soldier_num]->fight(soldier,tiles,num);
                            }
                            break;
                            }
                    }
                    if(click==1)step =0;
                }
                else step=0;
            }
            else{
                step=0;
            }
        }


void GO_JUDGER::show_select_multi(base *tiles,men_with_arms **soldier,SDL_Event& e,int& step,int& sel,int click,music *sound){
            for( int i = 7; i <=12; i ++){
                if(soldier[i]!=NULL){

                    choose[i].render(&e,soldier[i]->get_pos(),tiles);
                    choose[i].handle(step,1,sel,click,NULL,sound);

                }
            }
}
int GO_JUDGER::show_target_multi(base *tiles,men_with_arms **soldier,int sel,SDL_Event* e,base *a,int n){
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
                        goal[count].render(e,sel,tiles);
                        count++;
                    }
                }
            }
            else{
                flag=1;
                int door=((a[sel].soldier_num==none)or((a[sel].soldier_num>=FOE_1)and(a[sel].soldier_num<=FOE_6)));
                if(check[sel]==0){
                    show_target_multi(tiles,soldier,sel,e,a, 0);check[sel]=1;}
                    int next[6]={sel-1,sel+1,sel+y_num,sel-y_num,sel+y_num-1,sel-y_num+1};
                    int dis[6]={y_dis,y_dis,y_dis/2,y_dis/2,y_dis/2,y_dis/2};
                    for(int k=0;k<6;k++){
                        if(judge(sel,next[k],dis[k],tar,tiles)and check[next[k]]==0 and door==true)show_target_multi(tiles,soldier,next[k],e,a, n-1);
                    }
            }
            int mem=0;
            if((sel==tar)and(n==max_level)){
                    if(arms!=air_force){
                        for(int k=0;k<tiles_num;k++){
                            if((a[k].soldier_num<=MY_6)and(a[k].soldier_num>=MY_1)and(distance(k,sel,a)<=soldier[a[sel].soldier_num]->get_firerange())){
                                goal[count].render_alarm(e,k,tiles);
                                count++;
                            }
                        }
                    }
                    else{
                        for( int i = MY_1; i <=MY_6; i ++){
                            if(soldier[i]!=NULL){
                                goal[count].render_alarm(e,soldier[i]->get_pos(),tiles);
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
void GO_JUDGER::buttons_target_show_multi(base *tiles,men_with_arms **soldier,SDL_Event& e,int& step,int& sel,int click,music *sound){
            int count;
            const int pt=soldier[tiles[sel].soldier_num]->getpoint();
            if(pt!=0){
                count=show_target_multi(tiles,soldier,sel,&e,tiles,pt);
                if(count!=0){
                    for( int i = 0; i < count; i ++){
                        int chosen= goal[i].get_pos();
                        int num=tiles[chosen].soldier_num;

                        goal[i].handle(step,0,chosen,click,NULL,sound);
                        if(step==0){
                    if(num==none){
                            soldier[tiles[sel].soldier_num]->set_point(soldier[tiles[sel].soldier_num]->getpoint()-distance(chosen,sel,tiles));
                                soldier[tiles[sel].soldier_num]->go(chosen,tiles);

                            }
                    else if((num<=MY_6)and(num>=MY_1)){
                                soldier[tiles[sel].soldier_num]->set_point(0);
                                soldier[tiles[sel].soldier_num]->fight(soldier,tiles,num);

                            }
                            break;
                            }

                    }
                    if(click==1)step =0;
                }
                else step=0;
            }
            else{
                step=0;
            }
        }
