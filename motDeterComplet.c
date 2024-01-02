#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "automate.h"


// motvalide qui va permettre de tester si un mot est accepte par l'automate ou pas
int motValide(Automate* automate, char* mot) {
    // A RENDRE DETERMINISTE AVANT SI CE N EST PAS LE CAS 
    
    /*
    if(!estDeterministe){
        automate = rendreDeterministe(automate);
    }
    */
    
    int trouve=0;
    int i=0;
    while(!trouve){
        if(automate->etatsInitiaux[i]==1){
            trouve=1;
        }else{
            i++;
        }
    }
    int etatCourant = i; // l'etat initial n'est pas forcement etat 0

    // Parcourir chaque lettre du mot
    for (int i = 0; i < strlen(mot); i++) {
        // Trouver l'indice de l'evenement correspondant a la lettre
        int indiceEvent = -1;
        for (int j = 0; j < automate->nombreEvent; j++) {
            if (automate->listeEvent[j] == mot[i]) {
                indiceEvent = j;
            }
        }

        // Si l'evenement n'existe pas, le mot n'est pas valide
        if (indiceEvent == -1) {
            return 0;
        }

        // Trouver l'etat suivant
        int etatSuivant = -1;
        for (int j = 0; j < automate->nombreEtats; j++) {
            if (automate->matriceTransition[etatCourant][indiceEvent][j] == 1) {
                etatSuivant = j;
            }
        }

        // Si l'etat suivant n'existe pas, le mot n'est pas valide
        if (etatSuivant == -1) {
            return 0;
        }

        // Passer a l'etat suivant
        etatCourant = etatSuivant;
    }

    // Si l'etat courant est final, le mot est valide
    if (automate->etatsFinaux[etatCourant] == 1) {
        return 1;
    } else {
        return 0;
    }
}




// estDeterministe qui va permettre de savoir si l'automate est deterministe ou pas
int estDeterministe(Automate* automate) {
    // Parcourir chaque etat
    int nombreEtatsLies = 0;
    for (int i = 0; i < automate->nombreEtats; i++) {
        // Parcourir chaque evenement
        for (int j = 0; j < automate->nombreEvent; j++) {
            // Compter le nombre d'etats lies par l'evenement
            nombreEtatsLies = 0;
            
            for (int k = 0; k < automate->nombreEtats; k++) {
                
                if (automate->matriceTransition[i][j][k] == 1) {
                    
                    nombreEtatsLies++;
                }
                
                
            }
            

            // Si le nombre d'etats lies est different de 1, l'automate n'est pas deterministe
            if ((nombreEtatsLies != 1)&&(nombreEtatsLies != 0)) {
                return 0;
            }
        }
    }

    // Si tous les etats ont passe le test, l'automate est deterministe
    return 1;
}




// estComplet qui va permettre de savoir si l'automate est complet ou pas
int estComplet(Automate* automate) {
    // Parcourir chaque etat
    for (int i = 0; i < automate->nombreEtats; i++) {
        // Parcourir chaque evenement
        for (int j = 0; j < automate->nombreEvent; j++) {
            // Compter le nombre d'etats lies par l'evenement
            int nombreEtatsLies = 0;
            for (int k = 0; k < automate->nombreEtats; k++) {
                if (automate->matriceTransition[i][j][k] == 1) {
                    nombreEtatsLies++;
                }
            }

            // Si le nombre d'etats lies est different de 1, l'automate n'est pas complet
            if (nombreEtatsLies == 0) {  // MODIFIE AVANT CT 1
                return 0;
            }
        }
    }

    // Si tous les etats ont passe le test, l'automate est complet
    return 1;
}

// rendreComplet qui va permettre de rendre complet l'automate 
Automate* rendreComplet(Automate* automate) {
    
    if(estComplet(automate)){
        printf("L'automate est deja complet");
        return automate;
    }

    // rajout d'un etat puit
    automate->nombreEtats++;
    automate->etatsInitiaux[automate->nombreEtats-1]=0;
    automate->etatsFinaux[automate->nombreEtats-1]=0;
    
    // Parcourir chaque etat
    for (int i = 0; i < automate->nombreEtats-1; i++) {
        // Parcourir chaque evenement
        for (int j = 0; j < automate->nombreEvent; j++) {
            // Compter le nombre d'etats lies par l'evenement
            int nombreEtatsLies = 0;
            for (int k = 0; k < automate->nombreEtats-1; k++) {
                if (automate->matriceTransition[i][j][k] == 1) {
                    nombreEtatsLies++;
                }
            }
            

            //rajout d'un element dans chaque cellule
            automate->matriceTransition [i][j]= realloc(automate->matriceTransition[i][j], automate->nombreEtats * sizeof(int));
            if(!automate->matriceTransition[i][j]){
                allocPB=1;
            }

            printf("==%d",nombreEtatsLies);

            if (nombreEtatsLies == 0) {  
                printf("rnetr");
                automate->matriceTransition[i][j][automate->nombreEtats-1] = 1;
            }
        }
    }
    
    // rajout d'une nouvelle ligne dans la matrice 
    automate->matriceTransition=realloc(automate->matriceTransition, automate->nombreEtats * sizeof(int**));
    
    if(automate->matriceTransition){
        // rajout des colonnes pour cette ligne 
        automate->matriceTransition[automate->nombreEtats-1] = malloc(sizeof(int*) * automate->nombreEvent);
        
        if(automate->matriceTransition[automate->nombreEtats-1]){
            for (int j = 0; j < automate->nombreEvent; j++) {
                // pour chaque colonne rajout des cellules
                automate->matriceTransition[automate->nombreEtats-1][j] = calloc(automate->nombreEtats, sizeof(int));
                if(!automate->matriceTransition[automate->nombreEtats-1][j]){
                    allocPB=1;
                }

                // rajout d'une transition vers l'etat puit pour chaque evenement 
                automate->matriceTransition[automate->nombreEtats-1][j][automate->nombreEtats-1] = 1;
            }

        }else{
            allocPB=1;
        }
   
    }else{
        allocPB=1;
    }


    

            


    
    return automate;
}

// rendreDeterministe qui va permettre de rendre l'automate deterministe en partant de l'automate charge et en lui ajoutant un etat poubelle qui sera lie a tous les etats qui n'ont pas de transition pour un evenement
Automate* rendreDeterministe(Automate* automate) {
    // Si l'automate est deterministe, on ne fait rien
    if (estDeterministe(automate)) {
        return automate;
    }

    // partir de automate comme base pour l'automate deterministe
    Automate* automateDeterministe = automate;

    ajouterEtat(automateDeterministe, 'p');
}




// Function for operations on the automate
void operationsAutomate() {
    int choix;
    Automate* automate1 = NULL;
    Automate* automate2 = NULL;
    do {
        printf("Que voulez-vous faire ?\n");
        printf("1. Verifier si l'automate est deterministe\n");
        printf("2. Rendre l'automate deterministe\n");
        printf("3. Verifier si l'automate est complet\n");
        printf("4. Retourner au menu principal\n");
        scanf("%d", &choix);
        switch (choix) {
            case 1:
                if (automate1 != NULL) { // pk je peux creer une matrice faire les operations et laisse ou enregistrer apres 
                    freeAutomate(automate1);
                }
                automate1 = chargerAutomate();
                afficherAEF(automate1);
                if (estDeterministe(automate1)) {
                    printf("L'automate est deterministe\n");
                } else {
                    printf("L'automate n'est pas deterministe\n");
                }
                break;
            case 2:
                if (automate1 != NULL) {
                    freeAutomate(automate1);
                }
                automate1 = chargerAutomate();
                automate1 = rendreDeterministe(automate1);
                printf("L'automate a ete rendu deterministe\n");
                break;
            case 3:
                if (automate1 != NULL) {
                    freeAutomate(automate1);
                }
                automate1 = chargerAutomate();
                if (estComplet(automate1)) {
                    printf("L'automate est complet\n");
                } else {
                    printf("L'automate n'est pas complet\n");
                }
                break;
            case 4:
                return; // Return to the main menu
            default:
                printf("Erreur : choix invalide\n");
                break;
        }
    } while (choix != 4);
}
