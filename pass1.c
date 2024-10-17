#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

int main(){
    char opcode[10],label[10],operand[10],mnemonic[10],code[10];
    FILE *input,*output,*symtab,*optab,*symch;
    int locctr,start;
    bool err=false,found;

    input=fopen("input.txt","r");
    optab=fopen("optab.txt","r");
    symtab=fopen("symtab.txt","w");
    symch=fopen("symtab.txt","r");
    output=fopen("output.txt","w");

    fscanf(input,"%s\t%s\t%s",label,opcode,operand);

    if(strcmp(opcode,"START")==0){
        start=atoi(operand);
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
        fprintf(output,"%d\t",locctr);
        if(strcmp(label,"-")!=0){

            char symbol[10],loc[10];
            fseek(symch,SEEK_SET,0);
            fscanf(symch,"%s\t%s",symbol,loc);
            while(!feof(symch)){
                if(strcmp(label,symbol)==0){
                    err=true;
                    printf("Duplicate Encountered\n");
                    exit(0);
                }
                fscanf(symch,"%s\t%s",label,loc);
            }
            fprintf(symtab,"%s\t%d\n",label,locctr);
        }
        found=false;
        fseek(optab,SEEK_SET,0);
        fscanf(optab,"%s\t%s",code,mnemonic);
        while(strcmp(code,"END")!=0){
            if(strcmp(code,opcode)==0){
                locctr+=3;
                found=true;
                break;
            }
            fscanf(optab,"%s\t%s",code,mnemonic);
        }
        if(strcmp(opcode,"WORD")==0){
            locctr+=3;
        }
        else if(strcmp(opcode,"RESB")==0){
            locctr+=atoi(operand);
        }
        else if(strcmp(opcode,"RESW")==0){
            locctr+=3*(atoi(operand));
        }
        else if(strcmp(opcode,"RESB")==0){
            locctr+=atoi(operand);
        }
        else if(strcmp(opcode,"BYTE")==0){
            if(opcode[0]=='X'){
                locctr+=1;
                continue;
            }
            locctr+=strlen(operand)-3;
        }
        else if(!found){
            printf("Invalid\n");
            err=true;
            exit(0);
        }
        fprintf(output,"%s\t%s\t%s\n",label,opcode,operand);
        fscanf(input,"%s\t%s\t%s",label,opcode,operand);
    }
    fprintf(output,"-\t%s\t%s\t%s",label,opcode,operand);
    printf("Length of code:%d\n",locctr-start);
    fclose(input);
    fclose(symtab);
    fclose(optab);
    fclose(symch);
    fclose(output);
}
/*
SOURCE CODE:

-	START	2000
-	LDA FIVE
-	STA	ALPHA
-	LDCH 	CHARZ
- 	STCH 	C1
ALPHA 	RESW 	2
FIVE 	WORD 	5
CHARZ 	BYTE 	C'Z'
C1 	RESB 	1
- 	END	-

OBJECT TABLE:

LDA 03
STA	0F
LDCH	53
STCH	57
END -

SYMBOL TABLE:

ALPHA	2012
FIVE	2018
CHARZ	2021
C1	2022
INTERMEDIATE FILE:

-	-	START	2000
2000	-	LDA	FIVE
2003	-	STA	ALPHA
2006	-	LDCH	CHARZ
2009	-	STCH	C1
2012	ALPHA	RESW	2
2018	FIVE	WORD	5
2021	CHARZ	BYTE	C'Z'
2022	C1	RESB	1
-	-	END	-

Length of code = 23
*/
