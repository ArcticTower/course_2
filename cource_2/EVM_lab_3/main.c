#include <stdio.h>
#include <graphics.h>
#include <math.h>
#include <X11/Xlib.h>

void wait_for_char(){
    int in = 0;
    while (in == 0) {
        in = getchar();
    }
}
int main(int argc, char *argv[]) {
    XInitThreads();
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
    safe_update(0,0,800,600);
    double q=0.001;
    double x,y,
    max_y=(pow(sin((0+M_PI)/(double )4),2)),
    min_y=(pow(sin((0+M_PI)/(double )4),2));
    double coefx = getmaxx()/((double )10*M_PI);
    double coefy = (getmaxy()/2)/(pow(sin((11*M_PI)/(double )4),2)-sqrt(11*M_PI));
    for(x = 0; x< (double )10*M_PI;x+=q){
        y = (pow(sin((x+M_PI)/(double )4),2)-sqrt(x));
        if(y>max_y){max_y=y;}
        if(y<min_y){min_y=y;}
        y=getmaxy()/2+y*coefy;
        putpixel(x*coefx,y,15);
    }
    char num[55];

    line(0, getmaxy() / 2, getmaxx(), getmaxy() / 2);
    for(int i =-5; i<6;i++){
        sprintf(num,"%d",i);
        line(0, getmaxy()/2 +i*coefy, coefx/4, getmaxy()/2 +i*coefy);
        outtextxy(coefx/4,getmaxy()/2 +i*coefy,num);
    }

    for(int i=0;i<10*M_PI;i++){
        sprintf(num,"%d",i+(int)M_PI);
        line(i*coefx,getmaxy()/2 -coefy/4,i*coefx,getmaxy()/2 +coefy/4);
        outtextxy(i*coefx,getmaxy()/2 -coefy/4,num);
    }
    printf("\tmax val:\t%lf\n",max_y);
    printf("\tmin val:\t%lf\n",min_y);
    wait_for_char();
    closegraph();
    return 0;
}
