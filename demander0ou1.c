#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>
#include "automate.h"

void demander0ou1(int * adresse, char * pharse){
    int pb ;
    do{
        pb=0;
        printf(pharse);
        if(scanf("%d", adresse)!=1){
            printf("\nErreur, veuillez rentrer 1 ou 0.\n");
            pb=1;
        }
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        if((*(adresse)!=1) & (*(adresse)!=0)){
            printf("\nErreur :veuillez rentrer soit 1 ou 0.\n");
            pb=1;
        }

    }while(pb);
} 