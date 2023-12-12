#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>
#include "automate.h"




void ajouterEtat(Automate* automate, char identifiant) {
    // Augmenter le nombre d'etats
    automate->nombreEtats++;

    // Ajouter l'etat a la liste des etats finaux
    automate->etatsFinaux = realloc(automate->etatsFinaux, automate->nombreEtats * sizeof(int));
    automate->etatsFinaux[automate->nombreEtats - 1] = 0;

    // Ajouter l'etat a la liste des etats initiaux
    automate->etatsInitiaux = realloc(automate->etatsInitiaux, automate->nombreEtats * sizeof(int));
    automate->etatsInitiaux[automate->nombreEtats - 1] = 0;

    // Ajouter l'etat a la matrice de transition
    automate->matriceTransition = realloc(automate->matriceTransition, automate->nombreEtats * sizeof(int**));
    automate->matriceTransition[automate->nombreEtats - 1] = malloc(automate->nombreEvent * sizeof(int*));
    for (int i = 0; i < automate->nombreEvent; i++) {
        automate->matriceTransition[automate->nombreEtats - 1][i] = calloc(automate->nombreEtats, sizeof(int));
    }
    // Ajouter les transitions pour cet etat
    for (int i = 0; i < automate->nombreEtats; i++) {
        automate->matriceTransition[i] = realloc(automate->matriceTransition[i], automate->nombreEvent * sizeof(int*));
        automate->matriceTransition[i][automate->nombreEvent - 1] = calloc(automate->nombreEtats, sizeof(int));
    }

}


void ajouterEvent(Automate* automate, char event) {
    // Augmenter le nombre d'evenements
    automate->nombreEvent++;

    // Ajouter l'evenement a la liste des evenements
    automate->listeEvent = realloc(automate->listeEvent, automate->nombreEvent * sizeof(char));
    automate->listeEvent[automate->nombreEvent - 1] = event;

    // Ajouter les nouvelles transitions
    for (int i = 0; i < automate->nombreEtats; i++) {
        automate->matriceTransition[i] = realloc(automate->matriceTransition[i], automate->nombreEvent * sizeof(int*));
        automate->matriceTransition[i][automate->nombreEvent - 1] = calloc(automate->nombreEtats, sizeof(int));
    }
}


//fonction qui va retrouver l'entier correspondant a la lettre de l'evenement
int trouverindiceEvent(Automate* automate, char event) {
    int indiceEvent = -1;
    for (int j = 0; j < automate->nombreEvent; j++) {
        if (automate->listeEvent[j] == event) {
            indiceEvent = j;
        }
    }
    return indiceEvent;
}


// fonction modifierTransition qui va permettre de modifier une transition de l'automate. va chercher l'event, inverser 0 et 1 pour la transition choisie
void modifierTransition(Automate* automate, int etatDepart, int etatArrivee, char event) {
    // Trouver l'indice de l'evenement correspondant a la lettre
    int indiceEvent = trouverindiceEvent(automate, event);  
    // Si l'evenement n'existe pas, le mot n'est pas valide
    if (indiceEvent == -1) {
        printf("Erreur : l'evenement n'existe pas\n");
        return;
    }

    // Inverser la transition
    if (automate->matriceTransition[etatDepart][indiceEvent][etatArrivee] == 1) {
        automate->matriceTransition[etatDepart][indiceEvent][etatArrivee] = 0;
    } else {
        automate->matriceTransition[etatDepart][indiceEvent][etatArrivee] = 1;
    }
}


// fonction transition qui va dire si la transition existe ou pas

void transition(Automate* automate, int etatDepart, int etatArrivee, char event) {
    // Trouver l'indice de l'evenement correspondant a la lettre
    int indiceEvent = trouverindiceEvent(automate, event); 

    // Si l'evenement n'existe pas, le mot n'est pas valide
    if (indiceEvent == -1) {
        printf("Erreur : l'evenement n'existe pas\n");
        return;
    }

    // Si la transition existe
    if (automate->matriceTransition[etatDepart][indiceEvent][etatArrivee] == 1) {
        printf("La transition existe\n");
    } else {
        printf("La transition n'existe pas\n");
    }
}


void ajouterEtatInitial(Automate* automate, int etat) {
    // Ajouter l'etat a la liste des etats initiaux
    automate->etatsInitiaux[etat] = 1;
}

void ajouterEtatFinal(Automate* automate, int etat) {
    // Ajouter l'etat a la liste des etats finaux
    automate->etatsFinaux[etat] = 1;
}



//fonction ModifierAutomate qui va permettre de modifier l'automate (changer les transitions actuelles), ajouter ou supprimer un etat (en configurant ses transitions et son charactere d'identification), des evenements (en configurant pour chaque etat la où il va servir), des etats initiaux et finaux.
void ModifierAutomate(Automate* automate) {
    int choix;
    //Afficher l'automate
    afficherAEF(automate);
    //Demander a l'utilisateur ce qu'il veut faire
    printf("Que voulez-vous faire ?\n");
    printf("1. Modifier une transition\n");
    printf("2. Ajouter un etat\n");
    printf("3. Ajouter un evenement\n");
    printf("4. Ajouter un etat initial\n");
    printf("5. Ajouter un etat final\n");
    printf("6. Supprimer un etat\n");
    printf("7. Supprimer un evenement\n");
    printf("8. Supprimer un etat initial\n");
    printf("9. Supprimer un etat final\n");
    printf("10. Quitter\n");
    scanf("%d", &choix); 
    switch (choix) {
        case 1:
            printf("Quelle transition voulez-vous modifier ?\n");
            int etatDepart, etatArrivee;
            char event1;
            printf("Etat de depart : ");
            scanf("%d", &etatDepart);
            printf("Etat d'arrivee : ");
            scanf("%d", &etatArrivee);
            printf("Event : ");
            scanf(" %c", &event1);
            printf("Valeur actuelle : %d\n", automate->matriceTransition[etatDepart][event1][etatArrivee]);
            printf("Voulez vous l'inverser ? (1 pour oui, 0 pour non) : ");
            int choixInversion; // pas utiliser
            scanf("%d", &choixInversion);
            modifierTransition(automate, etatDepart, etatArrivee, event1);
            break;
        case 2:
            printf("Quel est l'identifiant de l'etat a ajouter ?\n");
            char identifiant; // pas besoin
            scanf(" %c", &identifiant);
            ajouterEtat(automate, identifiant);
            break;
        case 3:
            printf("Quel est l'evenement a ajouter ?\n");
            char event2;
            scanf(" %c", &event2);
            ajouterEvent(automate, event2);
            break;
        case 4:
            printf("Quel est l'etat initial a ajouter ?\n"); // aucun controle fait 
            int etatInitial;
            scanf("%d", &etatInitial);
            ajouterEtatInitial(automate, etatInitial);
            break;
        case 5:
            printf("Quel est l'etat final a ajouter ?\n");  // aucun controle fait 
            int etatFinal;
            scanf("%d", &etatFinal);
            ajouterEtatFinal(automate, etatFinal);
            break;
        case 6: // pas de suppression + manque nb etat, etat initial et final
            printf("Quel est l'etat a supprimer ?\n");
            int etat;
            scanf("%d", &etat);
            for (int i = 0; i < automate->nombreEtats; i++) {
                for (int j = 0; j < automate->nombreEvent; j++) {
                    automate->matriceTransition[i][j][etat] = 0;
                }
            }
            for (int i = 0; i < automate->nombreEtats; i++) {
                for (int j = 0; j < automate->nombreEvent; j++) {
                    automate->matriceTransition[etat][j][i] = 0;
                }
            }
            break;
        case 7: //pas de suppression
            printf("Quel est l'evenement a supprimer ?\n");
            int eventSuppr;
            scanf("%d", &eventSuppr);
            for (int i = 0; i < automate->nombreEtats; i++) {
                automate->matriceTransition[i][eventSuppr][i] = 0;
            }
            break;
        case 8: //supprimer un etat initial (on ne peut pas supprimer un etat initial qui est aussi final)
            printf("Quel est l'etat initial a supprimer ?\n");
            int etatInitialSuppr;
            scanf("%d", &etatInitialSuppr);
            automate->etatsInitiaux[etatInitialSuppr] = 0; //pas supprimer
            break;
        case 9: //supprimer un etat final (on ne peut pas supprimer un etat final qui est aussi initial)
            printf("Quel est l'etat final a supprimer ?\n");
            int etatFinalSuppr;
            scanf("%d", &etatFinalSuppr);
            automate->etatsFinaux[etatFinalSuppr] = 0; //pas supprimer
            break;
        case 10:
            break; // pas besoin
        default:
            printf("Erreur : choix invalide\n");
            break;
    }
}