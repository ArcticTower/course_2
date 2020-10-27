#define X1 10
#define Y1 15
#define X2 70
#define Y2 20
#define T 700
#define S 2



#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
//фон и цвет на русском
//вверх



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

int recolor(const char* const Arg)
{
    if (Arg == NULL)
        return 1;
    if (strlen(Arg) != 0)
        return 1;
    if (printf("\033[0m") < 0)
    {
        return 2;
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

int main() {
    int line =1;
    for (int j = 40; j <= 47; j++) {
        for (int i = 30; i <= 37; i++) {
            cleartext("");
            printf("\033[0;0H");
            make_winow(X1,Y1,X2,Y2);
            if(line <=0){line = 5;}
            printf("\033[%dB",Y1+line);
            mcRight("11");
            printf("\033[%dm", j);
            printf("\033[%dm", i);
            printf("текст: ");
            switch (i) {
                case 30:
                    printf("чёрный");
                    break;
                case 31:
                    printf("красный");
                    break;
                case 32:
                    printf("зелёный");
                    break;
                case 33:
                    printf("жёлтый");
                    break;
                case 34:
                    printf("голубой");
                    break;
                case 35:
                    printf("маджента");
                    break;
                case 36:
                    printf("берюзовый");
                    break;
                case 37:
                    printf("белый");
                    break;
                default:
                    printf("какой-то");
                    break;
            }
            printf(", фон: ");
            switch (j) {
                case 40:
                    printf("чёрный");
                    break;
                case 41:
                    printf("красный");
                    break;
                case 42:
                    printf("зелёный");
                    break;
                case 43:
                    printf("жёлтый");
                    break;
                case 44:
                    printf("голубой");
                    break;
                case 45:
                    printf("маджента");
                    break;
                case 46:
                    printf("берюзовый");
                    break;
                case 47:
                    printf("белый");
                    break;
                default:
                    printf("какой-то");
                    break;
            }

            printf("\n");
            recolor("");
            usleep(500000);
            printf("\033[0;0H");
            line--;
        }
    }
    return 0;
}