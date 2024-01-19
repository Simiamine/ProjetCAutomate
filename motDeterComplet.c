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
/*
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

    

    // Allouer et initialiser la matrice de transition juste pour un etat
        automate->matriceTransition = malloc(sizeof(int**));
        if(automate->matriceTransition){
            for (int i = 0; i < automateDeterministe->nombreEtats; i++) {
            automate->matriceTransition[i] = malloc(sizeof(int*) * automateDeterministe->nombreEvent);
            if(automate->matriceTransition[i]){
                for (int j = 0; j < automateDeterministe->nombreEvent; j++) {
                    automate->matriceTransition[i][j] = calloc(1, sizeof(int));
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
    
    return automateDeterministe;

}

*/


int Existe(int * tab, int taille,int a)
{
    int i;
    for(i=0;i<taille;i++)
    {
        if(tab[i]==a)
            return 1;
        else
            return 0;
    }
}
/**
 * retourne liste des etat d'arrive pour quelques etats contenu dans un tableau 
 * input : un automate, liste des etats, nombre d'etat
 * output : tableau des etat d'arrivé de taille nombre etat 
**/


int * etatArrive(Automate * automate, int* tabEtat, int nbElem, int event){
    int* arrive  = malloc(sizeof(int*)* automate->nombreEtats) ;
    if(arrive){
        for( int a=0;a<automate->nombreEtats;a++){
            arrive[a]=-1;
        }

        int nbArrive = 0;
        int nbEvent = automate->nombreEvent;
        for ( int i=0;i<nbElem; i++){
            int etat  = tabEtat[i];
            
            
            for(int k =0;k<automate->nombreEtats;k++){
                if(automate->matriceTransition[etat][event][k]){
                    arrive[nbArrive] = k;
                    printf("===%d", k);
                    nbArrive++;
                }
            }
                
            
            
        }
    }else{
        allocPB = 1 ;
    }
    
    return arrive;
    
}

// fonction qui prend en entrÃ©e une matrice 2d et un tableau d'entiers et qui renvoie un booleen si ce tableau est une ligne de la matrice ou pas
int estLigne(int** matrice, int* ligne, int nombreLignes, int nombreColonnes) {
    // Parcourir chaque ligne de la matrice
    int res = 1;
    for (int i = 0; i < nombreLignes; i++) {
        res=1;
        // Parcourir chaque colonne de la matrice
        for (int j = 0; j < nombreColonnes; j++) {
            // Si la valeur de la matrice est differente de la valeur de la ligne, la ligne n'est pas dans la matrice
            if (matrice[i][j] != ligne[j]) {
                res=0;
            }
        }

        if(res){
            return res;
        }
    }

    // Si la ligne a passe tous les tests, la ligne est dans la matrice
    return 0;
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
    Automate* deter = initAutomate(1,automate->nombreEvent);
    deter->etatsInitiaux[0]=1;
    
    // etat initial
    int * etatI=malloc(sizeof(int*)*automate->nombreEtats);
    int courant=0;
    for( int i=0; i<automate->nombreEtats;i++){
        if(automate->etatsInitiaux[i]){
            etatI[courant]=i;
            courant++;
        }
        
    }
    if(courant==0){
        int verif;
        int reste;
        int nbInitiaux;
        printf("\nVous avez aucun etat initial.");
        do {
            printf("Nombre d'etat initial: ");
            verif = scanf("%d", &nbInitiaux);
            reste = getchar();

        } while (verifieEntree(verif, nbInitiaux, reste));
        
        for(int i=0;i<nbInitiaux;i++){
            ajouterEtatInitial(automate);
        }

    }

    for( int i=0; i<automate->nombreEtats;i++){
        if(automate->etatsInitiaux[i]){
            etatI[courant]=i;
            courant++;
        }
        
    }
    
    
    
     
    

    int** tabEtat= malloc(sizeof(int**)); // liste des nvx etat composé d'un ou plusieurs ancien etat
    
    if(tabEtat){
        tabEtat[0] = malloc(sizeof(int*)*automate->nombreEtats);
        
        //intialisation du tableau
        if(tabEtat[0]){
            
            tabEtat[0]= etatI;
            int nbElem = 1;

            for(int i = 0; i<nbElem;i++){
                
                for(int event = 0; event<automate->nombreEvent;event++){
                    
                    int* nvxTab = etatArrive(automate,tabEtat[i],nbElem,event);
                    if(nvxTab[0]!=-1){// si nous n'avons pas un tableau vide
                        if(!estLigne(tabEtat,nvxTab,nbElem,automate->nombreEtats)){// si le tableau est absent dans tabEtat
                            
                            tabEtat = realloc(tabEtat, (nbElem + 1 )*sizeof(int**) ); // rajoute un element dans la tableau de liste des etats
                            tabEtat[nbElem]=nvxTab;
                            nbElem++;

                            


                            


                            

                            
                            //rajout de letat parmis les anciens
                            for (int i = 0; i < nbElem-1; i++) {
                                // Parcourir chaque evenement
                                for (int j = 0; j < deter->nombreEvent; j++) {
                                            
                                    
                                    //rajout d'un element dans chaque cellule
                                    deter->matriceTransition [i][j]= realloc(deter->matriceTransition[i][j], deter->nombreEtats * sizeof(int));
                                    if(!deter->matriceTransition[i][j]){
                                        allocPB=1;
                                    }
                                     
                                    
                                    deter->matriceTransition[i][j][deter->nombreEtats-1] = 0;
                                    
                                    
                                }
                            }
                            deter->matriceTransition[i][event][nbElem-1]=1;



                            
                        }
                        


                        

                    }  
                }
                 
            }


            // rajout d'une nouvelle ligne dans la matrice 
            deter->matriceTransition=realloc(deter->matriceTransition, nbElem * sizeof(int**));
            
            if(deter->matriceTransition){
                // rajout des colonnes pour cette ligne 
                deter->matriceTransition[nbElem-1] = malloc(sizeof(int*) * deter->nombreEvent);
                
                if(deter->matriceTransition[nbElem-1]){
                    for (int j = 0; j < deter->nombreEvent; j++) {
                        // pour chaque colonne rajout des cellules
                        deter->matriceTransition[nbElem-1][j] = calloc(nbElem, sizeof(int));
                        if(!deter->matriceTransition[nbElem-1][j]){
                            allocPB=1;
                        }

                    }

                }else{
                    allocPB=1;
                }
        
            }else{
                allocPB=1;
            }
            deter->nombreEtats=nbElem;
        }else{
            allocPB=1;
        }

        
        
    }allocPB=1;

    

    freeAutomate(automate);
}

/*


int creerNouvelEtat(int ***matrice, int taille) {
    *matrice = realloc(*matrice, (taille + 1) * sizeof(int *));
    (*matrice)[taille] = calloc(taille, sizeof(int));
    return taille;
}

int estDansListe(int **liste, int *ensemble, int tailleListe, int tailleEnsemble) {
    for (int i = 0; i < tailleListe; i++) {
        if (memcmp(liste[i], ensemble, tailleEnsemble * sizeof(int)) == 0) {
            return i;
        }
    }
    return -1;
}

Automate rendreDeterministe(Automate *afn) {
    Automate afd;
    afd.nombreEtats = 0;
    afd.nombreEvent = afn->nombreEvent;
    afd.etatsFinaux = NULL;
    afd.etatsInitiaux = NULL;
    afd.listeEvent = afn->listeEvent;
    

    int **nouveauxEtats = NULL;
    int tailleNouveauxEtats = 0;

    afd.matriceTransition = calloc(1, sizeof(int *));
    afd.matriceTransition[0] = calloc(afn->nombreEvent, sizeof(int));

    int *etatInitialAFD = calloc(afn->nombreEtats, sizeof(int));
    for (int i = 0; i < afn->nombreEtats; i++) {
        if (afn->etatsInitiaux[i] == 1) {
            etatInitialAFD[i] = 1;
        }
    }

    int indiceEtatInitial = creerNouvelEtat(&nouveauxEtats, tailleNouveauxEtats);
    memcpy(nouveauxEtats[indiceEtatInitial], etatInitialAFD, afn->nombreEtats * sizeof(int));
    tailleNouveauxEtats++;

    

    int indiceFile = 0;
    int tailleFile = 1;
    int **file = malloc(tailleFile * sizeof(int *));
    file[indiceFile] = etatInitialAFD;

    while (indiceFile < tailleFile) {
        int *etatCourantAFD = file[indiceFile];
        indiceFile++;

        for (int event = 0; event < afn->nombreEvent; event++) {
            int *nouvelEtatAFD = calloc(afn->nombreEtats, sizeof(int));

            for (int etatAFN = 0; etatAFN < afn->nombreEtats; etatAFN++) {
                if (etatCourantAFD[etatAFN] == 1) {
                    for (int etatSuivantAFN = 0; etatSuivantAFN < afn->nombreEtats; etatSuivantAFN++) {
                        if (afn->matriceTransition[etatAFN][event][etatSuivantAFN] == 1) {
                            nouvelEtatAFD[etatSuivantAFN] = 1;
                        }
                    }
                }
            }

            

            int indiceNouvelEtat = estDansListe(nouveauxEtats, nouvelEtatAFD, tailleNouveauxEtats, afn->nombreEtats);

            if (indiceNouvelEtat == -1) {
                indiceNouvelEtat = creerNouvelEtat(&nouveauxEtats, tailleNouveauxEtats);
                memcpy(nouveauxEtats[indiceNouvelEtat], nouvelEtatAFD, afn->nombreEtats * sizeof(int));
                tailleNouveauxEtats++;

                if (indiceFile < tailleFile) {
                    file[indiceFile] = nouvelEtatAFD;
                    indiceFile++;
                } else {
                    tailleFile++;
                    file = realloc(file, tailleFile * sizeof(int *));
                    file[indiceFile] = nouvelEtatAFD;
                    indiceFile++;
                }
            }

            

            afd.matriceTransition[indiceEtatInitial][event] = &indiceNouvelEtat;

            for (int etatAFN = 0; etatAFN < afn->nombreEtats; etatAFN++) {
                printf("\nrentre");
                if (nouvelEtatAFD[etatAFN] == 1 && afn->etatsFinaux[etatAFN] == 1) {
                    afd.etatsFinaux[indiceNouvelEtat] = 1;
                    printf("dtfgh");
                    break;
                }
            }

            
        }
    }

    

    free(file);

    return afd;
}








//Amine

// Fonction pour vérifier si l'état existe déjà
int etatExiste(int** etats, int nbEtats, int* nouvelEtat, int taille) {
    for (int i = 0; i < nbEtats; i++) {
        if (memcmp(etats[i], nouvelEtat, taille * sizeof(int)) == 0) {
            return i; // Retourne l'indice de l'état existant
        }
    }
    return -1; // L'état n'existe pas
}

// Fonction pour rendre un automate non déterministe en un automate déterministe
Automate* rendreDeterministe1(Automate* automate) {
    if (estDeterministe(automate)) {
        printf("L'automate est déjà déterministe.\n");
        return automate;
    }

    Automate* automateDet = initAutomate(0, automate->nombreEvent);
    int** nouveauxEtats = malloc(sizeof(int*) * (1 << automate->nombreEtats));
    int nbNouveauxEtats = 0;

    nouveauxEtats[nbNouveauxEtats] = calloc(automate->nombreEtats, sizeof(int));
    nouveauxEtats[nbNouveauxEtats][0] = 1;
    nbNouveauxEtats++;

    for (int i = 0; i < nbNouveauxEtats; i++) {
        for (int event = 0; event < automate->nombreEvent; event++) {
            int* nouvelEtat = calloc(automate->nombreEtats, sizeof(int));
            
            for (int etat = 0; etat < automate->nombreEtats; etat++) {
                if (nouveauxEtats[i][etat] == 1) {
                    for (int etatLie = 0; etatLie < automate->nombreEtats; etatLie++) {
                        if (automate->matriceTransition[etat][event][etatLie] == 1) {
                            nouvelEtat[etatLie] = 1;
                        }
                    }
                }
            }
            
            int index = etatExiste(nouveauxEtats, nbNouveauxEtats, nouvelEtat, automate->nombreEtats);
            if (index == -1) {
                nouveauxEtats[nbNouveauxEtats] = nouvelEtat;
                ajouterTransition(automateDet, i, nbNouveauxEtats, automate->listeEvent[event]);
                nbNouveauxEtats++;
            } else {
                ajouterTransition(automateDet, i, index, automate->listeEvent[event]);
                free(nouvelEtat);
            }
        }
    }

    for (int i = 0; i < nbNouveauxEtats; i++) {
        ajouterEtat(automateDet, nouveauxEtats[i]);
        free(nouveauxEtats[i]);
    }
    free(nouveauxEtats);

    return automateDet;
}

*/
