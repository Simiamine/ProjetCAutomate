#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>
#include "automate.h"


int verifieEntree(int valeurScanf, int valeur, int reste){
    
    // Vérifier si c'est un entier positif
    if ((valeurScanf != 1) || (valeur <= 0)||(reste != '\n')) {
        
        
        printf("\nErreur : Veuillez rentrer un nombre entier positif.\n");
        if(reste!='\n'){
            int c;
            while ((c = getchar()) != '\n' && c != EOF);

        }
        return 1;
        
    }
    return 0;

}

/**
 * Function to gather all the basic information to create the automaton
 * input : NONE
 * output : NONE
**/
Automate* saisirAutomate(){
    printf("\nNous allons proceder a la creation d'un automate.");
    
    
    int verif;
    int reste;
    int nbEtat;
    do {
        
        

        printf("\nNombre d'etat : ");
        verif = scanf("%d", &nbEtat);
        reste = getchar();

    } while (verifieEntree(verif, nbEtat, reste));
    

    
    
    
    int nbEvenement;
    do {
        
        printf("\nNombre d'evenement : ");
        verif=scanf("%d", &nbEvenement);
        reste = getchar();
    } while (verifieEntree(verif, nbEvenement, reste));
    
    Automate* newAutomate = initAutomate(nbEtat, nbEvenement);
    

    // ajout d'information 
    if (newAutomate){
         remplirAEF(newAutomate); 
        return newAutomate;
    }else{
        return NULL;
    }
    

}

Automate* initAutomate(int nombreEtats, int nombreEvent) {
    // Allouer de la mémoire pour l'automate
    Automate* automate = malloc(sizeof(Automate));

    if(automate){
        // Initialiser le nombre d'états et le nombre d'événements
        automate->nombreEtats = nombreEtats;
        automate->nombreEvent = nombreEvent;

        // Allouer et initialiser la matrice de transition
        automate->matriceTransition = malloc(sizeof(int**) * nombreEtats);
        if(automate->matriceTransition){
            for (int i = 0; i < nombreEtats; i++) {
            automate->matriceTransition[i] = malloc(sizeof(int*) * nombreEvent);
            if(automate->matriceTransition[i]){
                for (int j = 0; j < nombreEvent; j++) {
                    automate->matriceTransition[i][j] = calloc(nombreEtats, sizeof(int));
                    if(!automate->matriceTransition[i][j]){
                        allocPB=1;
                    }
                }
            }else{
                allocPB=1;
            }
                
            }
        }else{
            allocPB=1;
        }
        
        

        // Allouer et initialiser les états finaux et initiaux
        automate->etatsFinaux = calloc(nombreEtats, sizeof(int));
        if(!automate->etatsFinaux){
            allocPB=1;
        }
        automate->etatsInitiaux = calloc(nombreEtats, sizeof(int));
        if(!automate->etatsInitiaux){
            allocPB=1;
        }

        // Allouer et initialiser la liste des événements
        automate->listeEvent = calloc(nombreEvent, sizeof(char));
        if(!automate->listeEvent){
            allocPB=1;
        }

    }else{
        allocPB=1; // informe au main des problemes d'allocation
    }

    
    return automate;
}

int rechercheEvenement(char c, int indiceCourant, char* liste) {
    
    for (int i = 0; i < indiceCourant; i++) {
        if (liste[i] == c) {
            return 1; 
        }
    }
    return 0; 
}

void remplirEvenement(Automate* automate){
    int verif;
    int pb;
    int reste;
    // Demander a l'utilisateur de fournir la liste des evenements
    printf("Veuillez fournir la liste des evenements :\n");
    for (int i = 0; i < automate->nombreEvent; i++){
        do{
            pb=0;
            printf("\nCaractere de l'evenement %d : ", i+1);
            verif= scanf("%c", &(automate->listeEvent[i]));
            automate->listeEvent[i]=tolower(automate->listeEvent[i]);
            reste=getchar();
            if (verif != 1 || isdigit(automate->listeEvent[i])||(reste!='\n')||(automate->listeEvent[i]==' ')||rechercheEvenement(automate->listeEvent[i], i, automate->listeEvent)) {
                pb=1;
                printf("Erreur : Veuillez entrer un unique caractere different des precedents.\n");
                if(reste!='\n'){
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                }
                
        
            }
        }while(pb);
        
    }
}


void remplirAEF(Automate* automate) {
    // Parcourir chaque état
    int pb;
    remplirEvenement( automate);



    // Parcourir chaque etat
    for (int i = 0; i < automate->nombreEtats; i++) {
        printf("Etat %d\n", i+1);

        // Demander si l'état est initial
        do{
            pb=0;
            printf("Etat initial ? (1 pour oui, 0 pour non) : ");
            if(scanf("%d", &(automate->etatsInitiaux[i]))!=1){
                printf("\nErreur, veuillez rentrer 1 ou 0.\n");
                pb=1;
            }
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            if((automate->etatsInitiaux[i]!=1) & (automate->etatsInitiaux[i]!=0)){
                printf("\nErreur :veuillez rentrer soit 1 ou 0.\n");
                pb=1;
            }

        }while(pb);
        
        // Demander si l'état est final
        do{
            pb=0;
            printf("Etat final ? (1 pour oui, 0 pour non) : ");
            if(scanf("%d", &(automate->etatsFinaux[i]))!=1){
                printf("\nErreur, veuillez rentrer 1 ou 0.\n");
                pb=1;
            }
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            if((automate->etatsFinaux[i]!=1) & (automate->etatsFinaux[i]!=0)){
                printf("\nErreur :veuillez rentrer soit 1 ou 0.\n");
                pb=1;
            }

        }while(pb);


        

        // Parcourir chaque événement
        for (int j = 0; j < automate->nombreEvent; j++) {
            printf("Modification matrice transition\n");
            printf("Etat %d --(%c)--> ?\n", i+1, automate->listeEvent[j]);

            // Lire la liste des états liés à l'état i par l'événement j
            for (int k = 0; k < automate->nombreEtats; k++) {
                do{
                    pb=0;
                    printf("Etat %d est-il lie ? (1 pour oui, 0 pour non) : ", k+1);
                    if(scanf("%d", &(automate->matriceTransition[i][j][k]))!=1){
                        printf("\nErreur, veuillez rentrer 1 ou 0.\n");
                        pb=1;
                    }
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF);
                    if((automate->matriceTransition[i][j][k]!=1) & (automate->matriceTransition[i][j][k]!=0)){
                        printf("\nErreur :veuillez rentrer soit 1 ou 0.\n");
                        pb=1;
                    }

                }while(pb);
            }
        }
    }
    

    
}




void afficherAEF(Automate* automate) {
    // Afficher la liste des evenements
    printf("Liste des evenements :\n");
    for (int j = 0; j < automate->nombreEvent; j++) {
        printf("Event %d : %c\n", j+1, automate->listeEvent[j]);
    }

    // Afficher les etats initiaux
    printf("Liste des etats initiaux :\n");
    for (int i = 0; i < automate->nombreEtats; i++) {
        if (automate->etatsInitiaux[i] == 1) {
            printf("Etat %d\n", i+1);
        }
    }

    // Afficher les etats finaux
    printf("Liste des etats finaux :\n");
    for (int i = 0; i < automate->nombreEtats; i++) {
        if (automate->etatsFinaux[i] == 1) {
            printf("Etat %d\n", i+1);
        }
    }

    // Afficher la matrice de transition
    printf("Matrice de transition :\n");
    for (int i = 0; i < automate->nombreEtats; i++) {
        for (int j = 0; j < automate->nombreEvent; j++) {
            printf("Etat %d --(%c)--> ", i+1, automate->listeEvent[j]);
            for (int k = 0; k < automate->nombreEtats; k++) {
                if (automate->matriceTransition[i][j][k] == 1) {
                    printf("%d ", k+1);
                }
            }
            printf("\n");
        }
    }
}



void freeAutomate(Automate* automate) {
    // Liberer la memoire allouee pour la matrice de transition
    for (int i = 0; i < automate->nombreEtats; i++) {
        for (int j = 0; j < automate->nombreEvent; j++) {
            free(automate->matriceTransition[i][j]);
        }
        free(automate->matriceTransition[i]);
    }
    free(automate->matriceTransition);

    // Liberer la memoire allouee pour les etats finaux et initiaux
    free(automate->etatsFinaux);
    free(automate->etatsInitiaux);

    // Liberer la memoire allouee pour la liste des evenements
    free(automate->listeEvent);

    // Liberer la memoire allouee pour l'automate
    free(automate);
}




