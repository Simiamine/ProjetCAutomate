#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>
#include "automate.h"




/**
 * Function to gather all the basic information to create the automaton
 * input : NONE
 * output : NONE
**/
Automate* saisirAutomate(){
    printf("\nNous allons proceder a la creation d'un automate.");
    
    unsigned int nbEtat;
    int verif;
    do {
        // Vider le tampon d'entrée
        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        printf("\nNombre d'etat : ");
        verif = scanf("%u", &nbEtat);

        // Vérifier si c'est un entier positif
        if (verif != 1 || nbEtat <= 0) {
            printf("\nErreur : Veuillez rentrer un nombre entier positif.\n");
        }
    } while (verif != 1 || nbEtat <= 0);

    printf("===%d", nbEtat);
    
    
    int nbEvenement;
    printf("\nNombre d'evenement : ");
    scanf("%d", &nbEvenement);
    
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
        for (int i = 0; i < nombreEtats; i++) {
            automate->matriceTransition[i] = malloc(sizeof(int*) * nombreEvent);
            for (int j = 0; j < nombreEvent; j++) {
                automate->matriceTransition[i][j] = calloc(nombreEtats, sizeof(int));
            }
        }

        // Allouer et initialiser les états finaux et initiaux
        automate->etatsFinaux = calloc(nombreEtats, sizeof(int));
        automate->etatsInitiaux = calloc(nombreEtats, sizeof(int));

        // Allouer et initialiser la liste des événements
        automate->listeEvent = calloc(nombreEvent, sizeof(char));


    }else{
        allocPB=1; // informe au main des problemes d'allocation
    }

    
    return automate;
}


void remplirAEF(Automate* automate) {
    // Parcourir chaque état
    for (int i = 0; i < automate->nombreEtats; i++) {
        printf("Etat %d\n", i+1);

        // Demander si l'état est initial
        printf("Etat initial ? (1 pour oui, 0 pour non) : ");
        scanf("%d", &(automate->etatsInitiaux[i]));

        // Demander si l'état est final
        printf("Etat final ? (1 pour oui, 0 pour non) : ");
        scanf("%d", &(automate->etatsFinaux[i]));

        // Parcourir chaque événement
        for (int j = 0; j < automate->nombreEvent; j++) {
            printf("Modification matrice transition\n");
            printf("Etat %d --(%c)--> ?\n", i+1, automate->listeEvent[j]);

            // Lire la liste des états liés à l'état i par l'événement j
            for (int k = 0; k < automate->nombreEtats; k++) {
                printf("Etat %d est-il lié ? (1 pour oui, 0 pour non) : ", k+1);
                scanf("%d", &(automate->matriceTransition[i][j][k]));
            }
        }
    }

    
}