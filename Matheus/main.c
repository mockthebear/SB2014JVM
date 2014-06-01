#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "filereader.h"

#include "data_control.h"
#include "consolehelp.h"
#include "java.h"

#define SIZEX 80
#define SIZEY 22


/*
    Visualizador de arquivo .class
    SB 1/2014
    Matheus Braga Almeida
    120038412


*/



//Na main só ocorre exibição do arquivo
Console *c;
void ClearSecondCamp(){
    SetColor(c,0x79);
    for (int y=1;y<SIZEY+1;y++){

        for (int x=1;x<SIZEX-1;x++){
           if (x >= 31){
            SetPos(c,x,y);
            printf(" ");
           }
        }
    }
}
void DrawAttr(Java *j){
    SetPos(c,3,2);
    SetColor(c,0x7d);
    printf("%c Magic: %X",175,j->magic);
    SetPos(c,3,3);
    printf("%c Minor: %X",175,j->minor);
    SetPos(c,3,4);
    printf("%c Major: %X",175,j->major);
    int selected = 0;
    int n=255;
    int THISS = 0,CODEFROM=0;;
    bool showAttr=false,showSelected=false,SHOWCODE=false,SHOWATT=false,SHOWL=false;

    goto BGN;
    while ( (n = getch()) ){
        BGN:

        //
        if (n == 27 ){
            break;
        }else if (n == 80 ){
            if (!showAttr)
                selected++;
            else{
                if (!showSelected)
                    THISS++;
            }
        }else if (n == 72 ){
            if (!showAttr)
                selected --;
            else{
                if (!showSelected)
                    THISS--;
            }
        }else if (n == 77 ){
            if (!showAttr){
                showAttr = true;
                THISS = 0;
            }else{
                ClearSecondCamp();
                showSelected = true;
            }
        }else if (n == 75 ){
            if (!showSelected){
                showAttr = false;
                ClearSecondCamp();
            }else{
                ClearSecondCamp();
                showSelected = false;
            }
        }else if (n == 33 ){
            if (showSelected){
                SHOWCODE= true;
                ClearSecondCamp();
                CODEFROM=1;
            }
        }else if (n == 64 ){
            if (showSelected){
                SHOWCODE= true;
                ClearSecondCamp();
                CODEFROM=2;
            }
        }else if (n == 35 ){
            if (showSelected){
                SHOWCODE= true;
                ClearSecondCamp();
                CODEFROM=3;
            }
        }else if (n == 1 ){
            if (showSelected){
                SHOWATT= true;
                ClearSecondCamp();
                CODEFROM=1;
            }
        }else if (n == 2 ){
            if (showSelected){
                SHOWATT= true;
                ClearSecondCamp();
                CODEFROM=2;
            }
        }else if (n == 3 ){
            if (showSelected){
                SHOWATT= true;
                ClearSecondCamp();
                CODEFROM=3;
            }
        }else if (n == 'l'){
            if (SHOWATT){
                ClearSecondCamp();
                SHOWL = true;
            }
        }else{
            if (SHOWCODE || SHOWATT){
                ClearSecondCamp();
                SHOWCODE = false;
                SHOWATT =false;
                SHOWL = false;
            }
        }
        SetColor(c,0x7d);
        selected = selected > 2 ? 0 : (selected < 0 ? 2 : selected);
        SetPos(c,3,10);
        printf("[%c] Constant pull [%d]",selected == 0 ? 16 : 32,j->constant_pull_count);
        SetPos(c,3,11);
        printf("[%c] Methods       [%d]",selected == 1 ? 16 : 32,j->methods_count);
        SetPos(c,3,12);
        printf("[%c] Attributes    [%d]",selected == 2 ? 16 : 32,j->attributes_count);

        //Show Attr;
        if (showAttr){
            SetPos(c,45,1);
            SetColor(c,0x72);
            if (selected == 0){
                if (!showSelected){
                    printf("Constant pool");
                    int XX = 32,YY=3;
                    THISS = THISS > j->constant_pull_count ? 0 : (THISS < 0 ? j->constant_pull_count-2 : THISS);

                    for (int i=0;i<j->constant_pull_count-1;i++){

                        SetPos(c,XX,YY);
                        if (THISS == i){
                            SetColor(c,0x02);
                        }else{
                            SetColor(c,0x72);
                        }
                         printf("%d.%s",i+1,j->constant_pool[i]->name);

                        YY++;
                        if (YY > 20){
                            YY = 3;
                            XX += 15;
                        }
                    }
                }else{
                    printf("%d.%s",THISS+1,j->constant_pool[THISS]->name);
                    SetPos(c,33,3);
                    printf("Tag: %d",j->constant_pool[THISS]->tag);
                    SetPos(c,33,4);
                    switch (j->constant_pool[THISS]->tag){
                        case 1:{
                            printf("Lenght: %d",j->constant_pool[THISS]->lengh);
                            SetPos(c,33,5);
                            printf("Bytes: %c%s%c",16,j->constant_pool[THISS]->bytes,17);
                            break;
                        }
                        case 7:{
                            //Class
                            printf("Name_Index: %d",j->constant_pool[THISS]->name_index);
                            break;
                        }
                        case 8:{
                            //String
                            printf("string_index: %d",j->constant_pool[THISS]->string_index);
                            break;
                        }
                        case 9:{
                            //Fieldref

                            printf("class_index: %d",j->constant_pool[THISS]->class_index);
                            SetPos(c,33,5);
                            printf("name_and_type_index: %d",j->constant_pool[THISS]->name_and_type_index);
                            break;
                        }
                        case 10:{
                            //Method ref
                            printf("class_index: %d",j->constant_pool[THISS]->class_index);
                            SetPos(c,33,5);
                            printf("name_and_type_index: %d",j->constant_pool[THISS]->name_and_type_index);
                            break;
                        }
                        case 12:{
                            //NameAndType
                            printf("Name_Index: %d",j->constant_pool[THISS]->name_index);
                            SetPos(c,33,5);
                            printf("descriptor_index: %d",j->constant_pool[THISS]->descriptor_index);


                            break;
                        }
                        default:{
                            printf("Error: Unknow tag [%d]\n",j->constant_pool[THISS]->tag);
                        }
                    }
                    //
                }
            }else if(selected == 1){
                if (!showSelected){
                    printf("Methods");
                    int XX = 32,YY=3;
                    THISS = THISS > j->methods_count ? 0 : (THISS < 0 ? j->methods_count-1 : THISS);
                    for (int i=0;i<j->methods_count;i++){

                        SetPos(c,XX,YY);
                        if (THISS == i){
                            SetColor(c,0x02);
                        }else{
                            SetColor(c,0x72);
                        }

                         printf("%d.Method: %s",i+1,JAVA_GetUTF8(j,j->methods[i]->name_index));

                        YY++;
                        if (YY > 20){
                            YY = 3;
                            XX += 13;
                        }
                    }
                }else{
                    SetPos(c,35,1);
                    printf("%s %s %s",Flags[j->methods[THISS]->acess_flags],JAVA_GetUTF8(j,j->methods[THISS]->name_index),JAVA_GetUTF8(j,j->methods[THISS]->descriptor_index));
                    SetPos(c,32,2);
                    printf("Attributes: %d",j->methods[THISS]->attributes_count);
                    int XX = 32,YY=4;

                    if (SHOWCODE){
                        SetPos(c,XX,YY+1);
                        printf("Code from attribute %d: ",CODEFROM);
                        Attribute *att = j->methods[THISS]->Attributes[CODEFROM-1];
                        SetColor(c,0x79);
                        for (int i=0;i<att->code_lenght;i++){
                            SetPos(c,XX,YY+2);
                            printf("0x%X ",att->code[i]);
                            XX += 5;;
                            if (XX >= SIZEX-4){
                                XX = 32;
                                YY++;
                            }
                        }
                    }else if(SHOWATT){
                        int XX = 32,YY=4;
                        SetPos(c,XX,YY+1);
                        YY += 3;
                        if (SHOWL){
                            printf("LNT %d form code <1 to %d>",CODEFROM,j->methods[THISS]->Attributes[CODEFROM-1]->Attrs[0]->line_number_table_lenght);
                            for (int k=0;k<j->methods[THISS]->Attributes[CODEFROM-1]->Attrs[0]->line_number_table_lenght;k++){
                                LNT *att = j->methods[THISS]->Attributes[CODEFROM-1]->Attrs[0]->LNTs[k];
                                SetPos(c,XX,YY);
                                printf("%d.start_pc: %d",k+1,att->start_pc);
                                YY++;
                                SetPos(c,XX,YY);
                                printf("%d.line_number: %d",k+1,att->line_number);
                                YY++;
                                if (YY >= 24){
                                    YY = 4;
                                    XX += 10;
                                }
                            }
                        }else{

                            printf("Attributes %d form code <1 to %d>",CODEFROM,j->methods[THISS]->Attributes[CODEFROM-1]->attributes_count);
                            SetPos(c,XX,YY+2);
                            YY += 3;
                            for (int k=0;k<j->methods[THISS]->Attributes[CODEFROM-1]->attributes_count;k++){
                                SetPos(c,XX,YY);
                                printf("%d.Name_Index: %d %c%s%c",k+1,j->methods[THISS]->Attributes[CODEFROM-1]->Attrs[k]->attribute_name_index,16,JAVA_GetUTF8(j,j->methods[THISS]->Attributes[CODEFROM-1]->Attrs[k]->attribute_name_index),17);
                                YY++;
                                SetPos(c,XX,YY);
                                printf("%d.lenght: %d",k+1,j->methods[THISS]->Attributes[CODEFROM-1]->Attrs[k]->attribute_lenght);
                                YY++;
                                SetPos(c,XX,YY);
                                printf("%d.lenght: %d",k+1,j->methods[THISS]->Attributes[CODEFROM-1]->Attrs[k]->attribute_lenght);
                                YY++;
                                SetPos(c,XX,YY);
                                printf("%d.lenght: %d",k+1,j->methods[THISS]->Attributes[CODEFROM-1]->Attrs[k]->line_number_table_lenght);
                                YY++;
                                SetPos(c,XX,YY);
                                SetColor(c,0x79);
                                printf("Press L to list LNT");
                                SetColor(c,0x72);
                                if (YY >= 24){
                                    YY = 4;
                                    XX += 10;
                                }

                            }
                        }
                        //printf("%d.Name_Index: %s",i+1,JAVA_GetUTF8(j,att->attribute_name_index));
                    }else{
                        for (int i=0;i<j->methods[THISS]->attributes_count;i++){
                            SetPos(c,XX,YY);
                            Attribute *att = j->methods[THISS]->Attributes[i];
                            printf("%d.Name_Index: %s",i+1,JAVA_GetUTF8(j,att->attribute_name_index));
                            SetPos(c,XX,YY+1);
                            printf("%d.lenght: %d",i+1,att->attribute_lenght);
                            SetPos(c,XX,YY+2);
                            printf("%d.max_locals: %d",i+1,att->max_locals);
                            SetPos(c,XX,YY+3);
                            printf("%d.max_stack: %d",i+1,att->max_stack);
                            SetPos(c,XX,YY+4);
                            printf("%d.code_lenght: %d",i+1,att->code_lenght);
                            SetPos(c,XX,YY+5);
                            SetColor(c,0x79);
                            printf("%d.<Shift+%d> to view code",i+1,i+1);
                            SetColor(c,0x72);
                            SetPos(c,XX,YY+6);
                            printf("%d.exception len: %d",i+1,att->exception_table_lenght);
                            SetPos(c,XX,YY+7);
                            printf("%d.Attributes count: %d",i+1,att->attributes_count);
                            SetPos(c,XX,YY+8);
                            SetColor(c,0x79);
                            printf("%d.<Ctrl+a,b,c..> to Attributes",i+1);
                            SetColor(c,0x72);




                            XX += 15;


                        }
                    }
                }
            }else{

                if (!showSelected){
                    printf("Attributes");
                    int XX = 32,YY=3;
                    THISS = THISS > j->attributes_count ? 0 : (THISS < 0 ? j->attributes_count-1 : THISS);
                    for (int i=0;i<j->attributes_count;i++){
                            SetPos(c,XX,YY);
                            if (THISS == i){
                                SetColor(c,0x02);
                            }else{
                                SetColor(c,0x72);
                            }
                             printf("%d.%s",i,JAVA_GetUTF8(j,j->FAttr[i]->attribute_name_index));
                            YY++;
                            if (YY > 20){
                                YY = 3;
                                XX += 15;
                            }
                        }

                }else{
                      printf("%d.%s",THISS,JAVA_GetUTF8(j,j->FAttr[THISS]->attribute_name_index));
                      SetPos(c,33,3);
                      printf("name_index: %d %c%s%c",j->FAttr[THISS]->attribute_name_index,16,JAVA_GetUTF8(j,j->FAttr[THISS]->attribute_name_index),17);
                      SetPos(c,33,4);
                      printf("attribute_lenght: %d",j->FAttr[THISS]->attribute_lenght);
                      SetPos(c,33,5);
                      printf("sourcefile_index: %d %c%s%c",j->FAttr[THISS]->sourcefile_index,16,JAVA_GetUTF8(j,j->FAttr[THISS]->sourcefile_index),17);
                }

            }

        }


        SetPos(c,1,SIZEY);
        printf("[%d]",n);
    }


}
int main(){
    c = Start();


    /* Save current attributes */
    /*for (int i=0;i<255;i++){
       printf("%d [%c]\n",i,i);
    }*/
    char name[80];
    printf("Qual arquivo?\n");
    scanf("%s",name);
    SetPos(c,0,0);
    FileHandler *file = FileHandler_LoadFile(name);
    Java *j = JAVA_createJava(file);


    SetColor(c,0x79);
    printf("%c",201);
    for (int i=0;i<SIZEX-2;i++){
        printf("%c",205);
    }
    printf("%c",187);
    for (int i=0;i<SIZEY;i++){
        SetPos(c,30,i+1);
        printf("%c",186);
        SetPos(c,0,i+1);
        printf("%c",186);
        SetPos(c,SIZEX-1,i+1);
        printf("%c",186);
    }
    printf("%c",200);
    for (int i=0;i<SIZEX-2;i++){
        printf("%c",205);
    }
    printf("%c",188);
    SetColor(c,0x79);
    for (int y=1;y<SIZEY+1;y++){

        for (int x=1;x<SIZEX-1;x++){
           if (x != 30){
            SetPos(c,x,y);
            printf(" ");
           }
        }
    }
    SetPos(c,8,1);
    SetColor(c,0x7c);
    printf("Atributos:");
    DrawAttr(j);
    FileHandler_free(file);
    JAVA_freeJava(j);
    //http://msdn.microsoft.com/en-us/library/windows/desktop/ms682088%28v=vs.85%29.aspx#_win32_character_attributes
    Close(c);
    return 0;
}
