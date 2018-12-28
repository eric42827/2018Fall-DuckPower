#ifndef BASE_H
#define BASE_H
//screen dimensions defined here
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 640

//some important lengths used to adjust the positions of figures
 const double x_dis=108.0;
 const double y_dis=120.0;
 const double x_init=136.0;
 const double y_init=36.0;
 const int x_next=1020;
 const int y_next=20;
 const int x_unit=80;
 const int y_unit=80;
 const int x_adj=20;
 const int y_adj=40;

class base
{
    public:
        base();
        virtual ~base();

        friend class BATTLE_SCENE;
        friend class men_with_arms;
        friend class loop;
    protected:

    private:
        int x,y;//(x,y)positions
        int pos;//position number
        int soldier_num;//id of soldiers on the base
        int Monte;//

        //set x,y
        void set_xy(int a,int b){
            x=a;y=b;
        }

        //set pos
        void setpos(int a){pos=a;}

        //set soldier_num
        void setsoldier_num(int a){soldier_num=a;}


        //set Monte
        void set_Monte(int a){
            Monte=a;
        }


};

#endif // BASE_H
