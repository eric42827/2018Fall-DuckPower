#include "men_with_arms.h"

men_with_arms::men_with_arms()
{
    perform=0;
}

men_with_arms::~men_with_arms()
{
    //dtor
}
int men_with_arms::Random(int strength){
    int sum=0;
    double sum2=0.;
    for(int i=strength;i<=1.5*strength;i++)sum+=pow(i,2);
    int c=rand();

    for(int i=0;i<=0.5*strength;i++){
        sum2+=pow((1.5*strength-i),2);
        if(c<=RAND_MAX*sum2/(sum))

            return i+strength;
        }
    }

void men_with_arms::set_xy(int a,int b){
    x=a;y=b;
}
int men_with_arms::get_x(){return x;}
int men_with_arms::get_y(){return y;}

void men_with_arms::setpos(int a){pos=a;}
int men_with_arms::get_pos(){return pos;}

void men_with_arms::set_character(soldier_character a){character=a;}
void men_with_arms::set_arms(soldier_arms a){arms=a;}
soldier_arms men_with_arms::get_arms(){return arms;}
void men_with_arms::set_id(int a){id=a;}

void men_with_arms::set_maxhealth(int a){max_health=a;}
int men_with_arms::get_maxhealth(){return max_health;}

void men_with_arms::set_health(int a){health=a;}
int men_with_arms::get_health(){return health;}

void men_with_arms::set_strength(int a){strength=a;}
int men_with_arms::get_strength(){return strength;}

void men_with_arms::set_range(int a){
    move_range=a;
}
int men_with_arms::getrange(){return move_range;}

void men_with_arms::set_point(int a){
    move_points=a;
}
int men_with_arms::getpoint(){return move_points;}

int men_with_arms::get_firerange(){return fire_range;}
void men_with_arms::set_firerange(int a){fire_range=a;}


void men_with_arms::render(int position,base *a){
    //set position
    const int x_i=(x_dis/2-x_adj),y_i=(y_dis/2-y_adj);
    pos=position;
    set_xy(a[position].x+x_i,a[position].y+y_i);
    width=x_unit;height=y_unit;

    if(id>=FOE_1 and id<=FOE_6){
        if(perform==0)image_stand.flip_render(x,y);
        else if(perform==1){
            image_fight.flip_render(x,y);
            clock_t now=clock();
            if(now-start>=500)perform=0;
    }
    }
    else{
    if(perform==0)image_stand.render(x,y);
    else if(perform==1){
            image_fight.render(x,y);
            clock_t now=clock();
            if(now-start>=500)perform=0;
    }}
    //set health bar
    bar_bottom_image.render(x,y+height);
    SDL_Rect barclip[1];
    double rate;
    if(max_health!=0)rate=(health*1.0)/(max_health*1.0);
    else rate=0;
    barclip[0].x =   0;
    barclip[0].y =   0;
    barclip[0].w =   (bar_top_image.getWidth())*rate;//*(this->health)/(this->max_health);
    barclip[0].h =   bar_top_image.getHeight();
    bar_top_image.render(x,y+height,&barclip[0]);
    a[position].setsoldier_num(id);

    //set icon
    if(id>=MY_1 and id<=MY_6 ){
    if(move_points!=0)arms_icon.setAlpha(255);
    else arms_icon.setAlpha(100);
    arms_icon.render(x,y);}
    else if(id>=FOE_1 and id<=FOE_6 ){
    if(move_points!=0)arms_icon.setAlpha(255);
    else arms_icon.setAlpha(100);
    arms_icon.render(x+width-x_adj,y);}
}

void men_with_arms::go(int new_pos,base* a){
    int mem=pos;
    const int x_l=(x_dis/2-x_adj),y_l=(y_dis/2-y_adj);
    pos=new_pos;
    x=a[pos].x+x_l;y=a[pos].y+y_l;
    a[new_pos].setsoldier_num(id);
    a[mem].setsoldier_num(0);
}


void men_with_arms::fight(men_with_arms **foe,base *a,int foe_id){

    foe[foe_id]->set_health(foe[foe_id]->get_health()-Random(strength));
    //set animation time
    this->perform=1;
    start=clock();
    if((this->arms==melee)or(this->arms==air_force)){
        if(foe[foe_id]->get_health()<=0){
            int mem=this->get_pos();
            this->go(foe[foe_id]->get_pos(),a);
            a[mem].setsoldier_num(0);
            delete foe[foe_id];
            foe[foe_id]=NULL;

        }
    }
    else if(this->arms==archer){
        if(foe[foe_id]->get_health()<=0){
            int mem=foe[foe_id]->get_pos();
            a[mem].setsoldier_num(0);
            delete foe[foe_id];
            foe[foe_id]=NULL;
        }
    }
}
        //set combat properties
void men_with_arms::set_property(soldier_character cha,int arms_input,int health_input,int strength_input,int range_input,int fire_range_input){
    character=cha;
    arms=soldier_arms(arms_input);
    max_health=health_input;
    health=health_input;
    strength=strength_input;
    move_range=range_input;move_points=range_input;
    fire_range=fire_range_input;
}

