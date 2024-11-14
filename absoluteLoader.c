#include<stdio.h>
#include<string.h>
#include<stdlib.h>

FILE *OBJECTCODE,*MEMORY;

void init(){
    OBJECTCODE=fopen("objectcode.txt","r");\
    MEMORY=fopen("memory.txt","w");
}

int convert_hex(char a[]){
    int var=0;
    for(int i=0;i<strlen(a);i++){
        int n=a[i];
        var=var*16+(n<58?n-48:n-55);
    }
    return var;
}

int convert_hexc(char a){
    return a<58?a-48:a-55;
}

int main(){
    char DATA[100];
    char HEADER[10];
    int cursor=0;
    init();
    fscanf(OBJECTCODE,"H^%s",HEADER);
    fscanf(OBJECTCODE,"T^%s",DATA);

    while(DATA[0]!='E'){
        char START[7],SIZE[3];
        START[6]='\0';
        SIZE[2]='\0';
        cursor+=2;
        for(int i=0;i<6;i++){
            START[i]=DATA[cursor];
            cursor++;
        }
        printf("Text Record Starting Address:%s\n",START);
        cursor++;
        for(int i=0;i<2;i++){
            SIZE[i]=DATA[cursor];
            cursor++;
        }
        printf("Size of text record:%s\n",SIZE);
        int bytecounter=0;
        while(DATA[cursor]!='\0'){
            if(bytecounter%8==0){
                fprintf(MEMORY,"\t");
                bytecounter=0;
            }
            if(DATA[cursor]!='^'){
                fprintf(MEMORY,"%s",DATA);
                bytecounter++;
            }
            cursor++;
        }
        fprintf(MEMORY,"\n");
        fscanf(OBJECTCODE,"%s",DATA);
        cursor=0;
    }
}
