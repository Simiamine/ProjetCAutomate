#include <stdio.h>

int main(void){
    printf("Bonjour !\n");
    int a,b, somme, soustraction, multiplication;
    float division;
    printf("Veuillez saisir le premier nombre : \n");
    scanf ("%d",&a);
    printf("Veuillez saisir le deuxieme nombre : \n");
    scanf ("%d",&b);
    printf("Calculs : \n");
    somme = a+b;
    soustraction = a-b;
    multiplication = a*b;
    division = a/(double)b;
    printf("\t %d + %d = %d \n", a,b,somme);
    printf("\t %d - %d = %d \n", a,b,soustraction);
    printf("\t %d * %d = %d \n", a,b,multiplication);
    printf("\t %d / %d = %f \n", a,b,division);
    printf("Au revoir !");
    return 0;
}