#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "automate.h"

/**
 * Teste si un mot est accepte par l'automate ou pas
 * input : un automate et un mot
 * output : 1 si c'est valide 0 sinon
**/
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



/**
 * permet de savoir si l'automate est deterministe ou pas
 * input : un automate 
 * output : 1 si c'est deterministe 0 sinon
**/
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



/**
 * permet de savoir si l'automate est complet ou pas
 * input : un automate 
 * output : 1 si c'est complet 0 sinon
**/
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

// rendreComplet qui va 
/**
 * permet de rendre complet l'automate 
 * input : un automate 
 * output : automate complet
**/
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

            

            if (nombreEtatsLies == 0) {  
                
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


/**
 * Initialise l'automate deterministe à partir d'un automate non deterministe
 * input : un automate 
 * output : automate 
**/
Automate* initAutomateDeter(Automate* automate) {

    // partir de automate comme base pour l'automate deterministe
    Automate* automateDeterministe = automate;
    automateDeterministe->nombreEtats=automate->nombreEtats;
    automateDeterministe->nombreEvent=automate->nombreEvent;
    automateDeterministe->etatsFinaux=automate->etatsFinaux;
    automateDeterministe->listeEvent=automate->listeEvent;
    

    // un seul état initial
    int nbInitiaux = 0;
    int etatI = NULL;
    for (int i=0; i<automate->nombreEtats;i++){
        if(automate->etatsInitiaux[i]){
            etatI=i;
            nbInitiaux++;
        }
    }

    
    if(nbInitiaux!=1){
        printf("\nVous avez aucun ou plusieurs etat initiaux.");
        int verif;
        int reste;
        
        do {
            printf("Quelle est l'etat initial : ");
            verif = scanf("%d", &etatI);
            reste = getchar();

        } while (verifieEntree(verif, etatI, reste));
    }

    automateDeterministe->etatsInitiaux = calloc(automateDeterministe->nombreEtats, sizeof(int));
    automateDeterministe->etatsInitiaux[etatI]=1;

    return automateDeterministe;

}


int * etatArrive(Automate * automate, int* tabEtat, int nbElem){
    int* arrive  = malloc(sizeof(int*)* automate->nombreEtats) ;
    if(arrive){
        int nbEvent = automate->nombreEvent;
        for ( int i=0;i<nbElem; i++){
            int etat  = tabEtat[i];
            for(int event = 0; event<nbEvent;event++){
                for(int k =0;k<automate->nombreEtats;k++){
                    if(automate->matriceTransition[etat][event][k]){
                        
                    }
                }
                
            }
            
        }
    }
    
}

// rendreDeterministe qui va permettre de rendre l'automate deterministe en partant de l'automate charge et en lui ajoutant un etat poubelle qui sera lie a tous les etats qui n'ont pas de transition pour un evenement
/**
 * permet de rendre deterministe l'automate 
 * input : un automate 
 * output : automate deterministe
**/
Automate* rendreDeterministe(Automate* automate) {
    // Si l'automate est deterministe, on ne fait rien
    if (estDeterministe(automate)) {
        printf("L'automate est deja deterministe.");
        return automate;
    }

    // recupere les informations de l'automate de base 
    Automate* deter = initAutomateDeter(automate);
    int etatI = NULL;
    for (int i = 0; i<deter->nombreEtats;i++){
        if(deter->etatsInitiaux[i] ){
            etatI = i;
            i=deter->nombreEtats;
        }
    }



     
    int** tabEtat= malloc(sizeof(int**));
    
    if(tabEtat){
        tabEtat[0] = malloc(sizeof(int*));
        if(tabEtat[0]){
            tabEtat[0][0]= etatI;
        }else{
            allocPB=1;
        }

        
        
    }allocPB=1;

    
    




    
    
    




    freeAutomate(automate);
}



