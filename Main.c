/**
 * FILEPATH: /h:/Documents/CYTech/ING1/Projet C/ProjetCAutomate/Main.c
 * 
 * Ce fichier contient le code principal du programme qui permet de manipuler des automates finis.
 * Il comprend les fonctions pour afficher les menus, ajouter et supprimer des éléments d'un automate,
 * charger et enregistrer un automate à partir d'un fichier, vérifier des propriétés d'un automate,
 * effectuer des opérations sur un automate, et afficher un automate.
 * 
 * Les fonctions principales sont :
 * - afficheMenu() : Affiche le menu principal du programme.
 * - afficheMenuAjouter() : Affiche le menu d'ajout d'éléments à un automate.
 * - ajout() : Exécute les fonctions d'ajout en fonction du choix de l'utilisateur.
 * - afficheMenuSupprimer() : Affiche le menu de suppression d'éléments d'un automate.
 * - supprimer() : Exécute les fonctions de suppression en fonction du choix de l'utilisateur.
 * - afficheMenuMCD() : Affiche le menu des mots, complet et déterministe.
 * - mcd() : Exécute les fonctions des mots, complet et déterministe en fonction du choix de l'utilisateur.
 * - afficheMenuOper() : Affiche le menu des opérations sur un automate.
 * - main() : Fonction principale du programme.
 * 
 * Les autres fonctions incluses dans le fichier sont des fonctions utilitaires pour manipuler les automates.
 * 
 * Auteur : Amine, Fiorina, Younes, Lyliane
 * Date : 01/09/2023
 **/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "automate.h"

int allocPB = 0;

/**
 * Affiche le menu principale
 * input : rien 
 * output : rien
**/
void afficheMenu(){
    printf("\n\t Menu\n\n");
    printf("\n1\tSaisir un AEF");
    printf("\n2\tModifier ou supprimer un AEF"); 
    printf("\n3\tImporter un AEF a partir d'un fichier");
    printf("\n4\tSauvegarder un AEF sur un fichier");
    printf("\n5\tMot, Complet et deterministe");
    printf("\n6\tOperation sur un AEF");
    printf("\n7\tAfficher AEF");
    printf("\n0\tQuitter\n");
}


/**
 * Affiche le menu d'ajout
 * input : rien 
 * output : rien
**/
void afficheMenuAjouter(){
    
    printf("\n1\tAjouter un etat");
    printf("\n2\tAjouter un etat initial");
    printf("\n3\tAjouter un etat final");
    printf("\n4\tAjouter une transition");
    printf("\n5\tAjouter un evenement");
    printf("\n0\tRevenir en arriere\n");
}


/**
 * execute les fonctions d'ajout en fonction du menu
 * input : un automate 
 * output : rien
**/
void ajout(Automate* automate){
    int choix2;
    do{                    
        choix2=100;
        afficheMenuAjouter();
        printf("Choix : ");
        scanf("%d", &choix2);
        switch(choix2){
            case 1:
                ajouterEtat(automate);
                break;
            case 2:
                ajouterEtatInitial(automate);
                break;
            case 3:
                ajouterEtatFinal(automate);
                break;
            case 4:
                ajoutTransition(automate);
                break;
            case 5:
                ajoutEvent(automate);
                break;
            case 0 :
                break;
            default:
                printf("\nChoix incorrect\n");
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
        }
        


    }while((choix2!=0)&(!allocPB));
}

/**
 * Affiche le menu de suppression
 * input : rien 
 * output : rien
**/
void afficheMenuSupprimer(){
    
    printf("\n1\tSupprimer un etat");
    printf("\n2\tSupprimer un etat initial");
    printf("\n3\tSupprimer un etat final");
    printf("\n4\tSupprimer une transition");
    printf("\n5\tSupprimer un evenement");
    printf("\n0\tRevenir en arriere\n");
}

/**
 * execute les fonctions de suppression en fonction du menu
 * input : un automate 
 * output : rien
**/
void supprimer(Automate* automate){
    int choix2;
    do{                    
        choix2=100;
        afficheMenuSupprimer();
        printf("Choix : ");
        scanf("%d", &choix2);
        switch(choix2){
            case 1:
                suppEtat(automate);
                break;
            case 2:
                suppEtatInitial(automate);
                break;
            case 3:
                suppEtatFinal(automate);
                break;
            case 4:
                suppTransition(automate);
                break;
            case 5:
                suppEvent(automate);
                break;
            case 0 :
                break;
            default:
                printf("\nChoix incorrect\n");
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
        }
        


    }while((choix2!=0)&(!allocPB));

}



/**
 * Affiche le menu des mots, complet et deterministe
 * input : rien 
 * output : rien
**/
void afficheMenuMCD(){
    
    printf("\n1\tReconnaitre un mot");
    printf("\n2\tVerifier s'il est deterministe "); 
    printf("\n3\tVerifier s'il est complet");
    printf("\n4\tRendre deterministe");
    printf("\n5\tRendre complet");
    printf("\n0\tRevenir en arriere\n");
}

/**
 * execute les fonctions des mots, complet et deterministe
 * input : un automate 
 * output : rien
**/
void mcd(Automate* automate){
    int choix2;
    do{                    
        choix2=100;
        afficheMenuMCD();
        printf("\nChoix : ");
        scanf("%d", &choix2);
        switch(choix2){
            case 1:
                if (automate != NULL) {
                    char mot[100];
                    printf("Quel est le mot a tester ?\n");
                    scanf("%s", mot);
                    for (int i = 0; mot[i] != '\0'; i++) {
                        mot[i] = tolower(mot[i]);
                    }
                    if (motValide(automate, mot)) {
                        printf("Le mot est valide\n");
                    } else {
                        printf("Le mot n'est pas valide\n");
                    }
                } else {
                    printf("Erreur : aucun automate cree\n");
                }
                break;
            case 2:
                if(estDeterministe(automate)){
                    printf("\nL'automate est deterministe.");
                }else{
                    printf("\nL'automate n'est pas deterministe.");
                }
                break;
            case 3:
                if(estComplet(automate)){
                    printf("\nL'automate est complet.");
                }else{
                    printf("\nL'automate n'est pas complet.");
                }
                break;
            case 4:
                printf("Fonction non fini");
                break;
            case 5:
                rendreComplet(automate);
                break;
            case 0 :
                break;
            default:
                printf("\nChoix incorrect\n");
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
        }
        


    }while((choix2!=0)&(!allocPB));
}


/**
 * Affiche le menu des operations
 * input : rien 
 * output : rien
**/
void afficheMenuOper(){
    
    printf("\n1\tComplement");
    printf("\n2\tMiroir"); 
    printf("\n3\tConcatenation");
    printf("\n4\tProduit");
    printf("\n0\tRevenir en arriere\n");
}

void operationAuto(Automate* automate){
    int choix2;
    Automate* automate1 = NULL;
    Automate* automate2 = NULL;
    do{                    
        choix2=100;
        afficheMenuOper();
        printf("\nChoix : ");
        scanf("%d", &choix2);
        switch(choix2){
            case 1:
                if (automate != NULL) {
                    afficherAEF(complementAEF(automate));
                }else{
                    printf("Erreur aucun AEF est en cours d'utilisation");
                }
                break;
            case 2:
                if (automate != NULL) {
                    afficherAEF(mirroirAEF(automate));
                }else{
                    printf("Erreur aucun AEF est en cours d'utilisation");
                }
                break;
            case 3:
                printf("Fonction non fini");
                break;
            case 4:
                printf("Fonction non fini");
                break;
            case 0 :
                break;
            default:
                printf("\nChoix incorrect\n");
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
        }
        


    }while((choix2!=0)&(!allocPB));

}


int main(){
    
    printf("Bienvenue !\n");
    int choix;
    Automate* automate = NULL;
    
    do{
        afficheMenu();
        choix=100;

        printf("Choix : ");
        scanf("%d", &choix); 
        
        switch(choix){
            
            case 1:
                
                automate = saisirAutomate();
                break;
            
            case 2: 
                int choix1;
                do{
                    choix1=100;
                    printf("\n\t1-Ajouter\n");
                    printf("\n\t2-Supprimer\n");
                    printf("\n\t0-Revenir en arriere\n");
                    printf("Choix : ");
                    scanf("%d", &choix1); 
                    switch(choix1){
                        case 1:
                            if (automate != NULL) {
                                ajout(automate);
                            }else{
                                printf("Erreur aucun AEF est en cours d'utilisation");
                            }
                            break;
                        case 2:
                            if (automate != NULL) {
                                supprimer(automate);
                            }else{
                                printf("Erreur aucun AEF est en cours d'utilisation");
                            }
                            break;
                        case 0 :
                            break;
                        default :
                            printf("\nChoix incorrect\n");
                            int c;
                            while ((c = getchar()) != '\n' && c != EOF);
                    }
                
                }while((choix1!=0)&(!allocPB));
                break;
            
            case 3:
                if (automate != NULL) {
                    freeAutomate(automate);
                }
                automate = chargerAutomate();
                break;
            
            case 4:
                if (automate != NULL) {
                    enregistrerAutomate(automate);
                } else {
                    printf("Erreur : aucun automate cree\n");
                }
                break;

            case 5:
                if (automate != NULL) {
                    mcd(automate);
                }else{
                    printf("Erreur aucun AEF est en cours d'utilisation");
                }
                break;

            case 6:
                operationAuto(automate);
                break;
             
            case 7:
                if (automate != NULL) {
                    afficherAEF(automate);
                }else{
                    printf("Erreur aucun AEF est en cours d'utilisation");
                };
                break;

            
            case 0:
                printf("\n\tAu revoir !\n");
                break;
            

            default:
                printf("\nChoix incorrect\n");
            

        }
        // vider le tampon d'entree
        int c;
        
        while ((c = getchar()) != '\n' && c != EOF);


    }while((choix!=0)&(!allocPB));

    return EXIT_SUCCESS;


}