#ifndef SOLDIER_SHORT_H
#define SOLDIER_SHORT_H
#include<base.h>
extern const double x_dis;
extern const double y_dis;
class soldier_short
{
    public:
        soldier_short();
        virtual ~soldier_short();
        void set_xy(int a,int b){
            x=a;y=b;
        }
        void setpos(int a){pos=a;}
        int get_pos(){return pos;}
        int getwidth(){return width;}
		int getheight(){return height;}
		int getrange(){return move_range;}
		int getpoint(){return move_points;}
		void setdim(int a,int b){width=a;height=b;}
        int get_x(){return x;}
        int get_y(){return y;}
        void go(int new_pos,base* a){
            int x_l,y_l;
            x_l=x_dis/2-25;y_l=y_dis/2-50;
        pos=new_pos;
        x=a[pos].x+x_l;y=a[pos].y+y_l;
        }
        void set_range(int a){
            move_range=a;
        }
        void set_point(int a){
            move_points=a;
        }
    protected:

    private:
        int x,y;
        int width;
        int height;
        int pos;
        int move_range;
        int move_points;
};

#endif // SOLDIER_SHORT_H
