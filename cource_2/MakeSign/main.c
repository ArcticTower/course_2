#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

int main() {
    FILE* signFile;
    FILE* useFile;
    unsigned long mov;
    unsigned long len;
    unsigned char sign[1000];
    char fileName[FILENAME_MAX];
    signFile = fopen("sign.sig","w+b");
    if(signFile == NULL){ return 1;}
    if(printf("Enter file name:\n")<0){return 2;}
    if(scanf("%s",fileName)!=1){return 3;}
    useFile = fopen(fileName,"rb");
    if(useFile==NULL){return 4;}
    if(printf("Enter mov\n")<0){return 2;}
    if(scanf("%lu",&mov)!=1){return 3;}
    if(fseek(useFile,mov,SEEK_SET)!=0){return 5;}
    if(printf("Enter sign len:\n")<0){return 2;}
    if(scanf("%lu",&len)!=1){return 3;}
    if(fread(sign, sizeof(unsigned char),len,useFile)!=len){return 6;}
    if(printf("\nGetting sign is success\n")<0){return 2;}
    if(fclose(useFile)!=0){return 7;}
    char prefix[]="SIGN";
    if(fwrite(prefix, sizeof(prefix), 1, signFile) != 1){ return 8;}
    if(fwrite(&mov, sizeof(mov),1,signFile)!=1){return 8;}
    if(fwrite(&len, sizeof(len),1,signFile)!=1){return 8;}
    if(fwrite(sign, sizeof(unsigned char),len,signFile)!=len){return 8;}
    if(fclose(signFile)!=0){return 7;}
    if(printf("\nEND\n")<0){return 2;}
    getchar();


    return 0;
}
