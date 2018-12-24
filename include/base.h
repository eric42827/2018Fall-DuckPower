#ifndef BASE_H
#define BASE_H

 //extern const double x_dis;
 //extern const double y_dis;

 const double x_dis=135.0;
 const double y_dis=150.0;
class base
{
    public:
        base();
        virtual ~base();
        void set_xy(int a,int b){
            x=a;y=b;
        }
        void setpos(int a){pos=a;}
        void setsoldier_num(int a){soldier_num=a;}
        int get_pos(){return pos;}
        int get_x(){return x;}
        int get_y(){return y;}
        int get_num(){return soldier_num;}
        void set_Monte(double a){
        Monte=a;
        }
        double get_Monte(){
        return Monte;
        }
        void set_foe(bool a){foe_goable=a;}
        bool get_foe(){return foe_goable;}
        friend class soldier_short;
    protected:

    private:
        int x,y;
        int pos;
        int soldier_num;
        double Monte;
        bool foe_goable;
};

#endif // BASE_H
