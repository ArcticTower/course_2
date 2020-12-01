#define X1 10
#define Y1 15
#define X2 70
#define Y2 20

#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
static struct termios old, current;


void initTermios(int echo)
{
    tcgetattr(0, &old);
    current = old;
    current.c_lflag &= ~ICANON;
    if (echo) {
        current.c_lflag |= ECHO;
    } else {
        current.c_lflag &= ~ECHO;
    }
    tcsetattr(0, TCSANOW, &current);
}


void resetTermios(void)
{
    tcsetattr(0, TCSANOW, &old);
}


int getch_(int echo)
{
    int ch;
    initTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}


int getch(void)
{
    return getch_(0);
}

int mcDown(const char* const Arg)
{
    if (Arg == NULL)
        return 1;
    char* ptr;
    size_t i;
    long N;
    N = strtol(Arg, &ptr, 10);
    if (strlen(ptr) != 0)
    {
        return 1;
    }
    if (N <= 0)
    {
        return 1;
    }
    for (i = 0; i < N; i++)
    {
        if (printf("\033[1B") < 0)
        {
            return 2;
        }
    }
    return 0;
}

int cleartext(const char* const Arg)
{
    if (Arg == NULL)
        return 1;
    if (strlen(Arg) != 0)
    {
        return 1;
    }
    if (printf("\033[2J") < 0)
    {
        return 2;
    }
    if (printf("\033[0;0H")<0){
        return 2;
    }
    return 0;
}

int mcRight(const char* const Arg)
{
    if (Arg == NULL)
        return 1;
    size_t i;
    long N;
    char* ptr;
    N = strtol(Arg, &ptr, 10);
    if (strlen(ptr) != 0)
    {
        return 1;
    }
    if (N <= 0)
    {
        return 1;
    }
    for (i = 0; i < N; i++)
    {
        if (printf("\033[1C") < 0)
        {
            return 2;
        }
    }
    return 0;
}

int make_winow(int x1, int y1, int x2, int y2){

    mcDown("15");
    mcRight("10");
    for(int i=0;i<60;i++){
        printf("-");
    }
    for(int i = 0;i<5;i++){
        printf("\n");
        mcRight("10");
        printf("|");
        mcRight("58");
        printf("|");
    }
    printf("\n");
    mcRight("10");
    for(int i=0;i<60;i++){
        printf("-");
    }
    printf("\033[0;0H");
    return 0;
}

//0 - exit
//1 - left
//2 - up
//3 - right
//4 - down
//5 - none
int command(){
    int c;
    int d;
    int v;
    c = getch();
    if(c == 101) return 0;
    d = getch();
    v = getch();
    switch (v) {
        case 68: return 1;
        case 65: return 2;
        case 67: return 3;
        case 66: return 4;
        default: return 5;
    }

}
//вверх65 вниз66 постоянно (влево68, вправо67, e101)
int main(void) {

    int shm_id;
    pid_t pid;
    pid = fork();
    if(pid != (pid_t)0){
        int shm_id = shmget(1000, getpagesize(), IPC_CREAT | S_IRUSR | S_IWUSR);
        int *sh = (int*)shmat(shm_id,NULL,0);
        int x = 58,y = 17; // x 11-69 | y 16-19
        int dir = 1;
        while (dir!=0){
            switch (dir) {
                case 1:
                    //left
                    x-=1;
                    if(x <= 10){
                        x = 68;
                    }
                    break;
                case 2:
                    //up
                    y-=1;
                    if(y <= 15){
                        y = 20;
                    }
                    break;
                case 3:
                    //right
                    x+=1;
                    if(x >=69){
                        x = 11;
                    }
                    break;
                case 4:
                    //down
                    y+=1;
                    if(y >= 21){
                        y = 16;
                    }
                    break;
                default:
                    break;
            }

            cleartext("");
            printf("\033[0;0H");
            make_winow(X1,Y1,X2,Y2);
            printf("\033[%dB",y);//y
            printf("\033[%dC",x);//x
            printf("*");
            printf("\n");
            usleep(300000);

            dir = *sh;
        }
        cleartext("");
        printf("\033[0;0H");
        shmdt(sh);
        return 0;

    } else{
        int shm_id = shmget(1000, getpagesize(), IPC_CREAT | S_IRUSR | S_IWUSR);
        int *sh = (int*)shmat(shm_id,NULL,0);
        *sh = 1;
        int signal = 1;
        int sigold = signal;
        while (signal != 0){
            signal = command();
            if(signal == sigold) continue;
            sigold = signal;
            *sh = signal;

        }
        *sh = 0;
        shmdt(sh);
        shmctl(shm_id, IPC_RMID, NULL);
        return 0;
    }


    //make_winow(X1,Y1,X2,Y2);

    return 0;
}