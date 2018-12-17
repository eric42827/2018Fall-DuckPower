#ifndef BASE_H
#define BASE_H


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
        friend class soldier_short;
    protected:

    private:
        int x,y;
        int pos;
        int soldier_num;
};

#endif // BASE_H
