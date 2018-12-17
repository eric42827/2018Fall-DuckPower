#ifndef LOOP_H
#define LOOP_H


class loop
{
    public:
        loop();
        virtual ~loop();
        void set_xy(int a,int b){
            x=a;y=b;
        }
        void setpos(int a){pos=a;}
        int get_pos(){return pos;}
        int get_x(){return x;}
        int get_y(){return y;}
    protected:

    private:
        int x,y;
        int pos;

};

#endif // LOOP_H
