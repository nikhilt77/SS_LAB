#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

int main(){
    FILE *input,*output,*optab,*symtab,*symch;
    input=fopen("input.txt","r");
    optab=fopen("optab.txt","r");
    symch=fopen("symtab.txt","r");
    symtab=fopen("symtab.txt","w");
    output=fopen("intertab.txt","w");
    int locctr,start;
    bool err=false,found;
    char label[10],opcode[10],operand[10],code[10],mnemonic[10];

    fscanf(input,"%s\t%s\t%s",label,opcode,operand);
    if(strcmp(opcode,"START")==0){
        fseek(input,SEEK_SET,0);
        fscanf(input,"%s\t%s\t%X",label,opcode,&start);
        locctr=start;
        fprintf(output,"-\t%s\t%s\t%s\n",label,opcode,operand);
        fscanf(input,"%s\t%s\t%s",label,opcode,operand);
    }
    else{
        locctr=0;
    }
    while(strcmp(opcode,"END")!=0){
        if(label[0]=='#'){
            continue;
        }
        fprintf(output,"%X\t",locctr);
        if(strcmp(label,"-")!=0){
            char symbol[10],loc[10];
            fseek(symch,SEEK_SET,0);
            fscanf(symch,"%s\t%s",symbol,loc);
            while(!feof(symch)){
                if(strcmp(symbol,label)==0){
                    err=true;
                    printf("Duplicate\n");
                    exit(0);
                }
                fscanf(symch,"%s\t%s",symbol,loc);
            }
            fprintf(symtab,"%s\t%X\n",label,locctr);
        }
        fseek(optab,SEEK_SET,0);
        fscanf(optab,"%s\t%s",code,mnemonic);
        found=false;
        while(strcmp(code,"END")!=0){
            if(strcmp(opcode,code)==0){
                locctr+=3;
                found=true;
                break;
            }
            fscanf(optab,"%s\t%s",code,mnemonic);
        }
        if(strcmp(opcode,"BYTE")==0){
            if(opcode[0]=='X'){
                locctr+=1;
                continue;
            }
            locctr+=strlen(operand)-3;
        }
        else if(strcmp(opcode,"RESW")==0){
            locctr+=3*atoi(operand);
        }
        else if(strcmp(opcode,"RESB")==0){
            locctr+=atoi(operand);
        }
        else if(strcmp(opcode,"WORD")==0){
            locctr+=3;
        }
        else if(!found){
            err=true;
            printf("Invalid Opcode %s",opcode);
            exit(0);
        }
        fprintf(output,"%s\t%s\t%s\n",label,opcode,operand);
        fscanf(input,"%s\t%s\t%s",label,opcode,operand);
    }
    fprintf(output,"%s\t%s\t%s\n",label,opcode,operand);
    printf("Length:%d",locctr-start);
    fclose(symch);
    fclose(symtab);
    fclose(input);
    fclose(output);
    fclose(optab);

}
