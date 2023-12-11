#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "automate.h"


// motvalide qui va permettre de tester si un mot est accepte par l'automate ou pas
bool motValide(Automate* automate, char* mot) {
    // Initialiser l'etat courant a l'etat initial
    int etatCourant = 0;

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
            return false;
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
            return false;
        }

        // Passer a l'etat suivant
        etatCourant = etatSuivant;
    }

    // Si l'etat courant est final, le mot est valide
    if (automate->etatsFinaux[etatCourant] == 1) {
        return true;
    } else {
        return false;
    }
}




// estDeterministe qui va permettre de savoir si l'automate est deterministe ou pas
bool estDeterministe(Automate* automate) {
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

            // Si le nombre d'etats lies est different de 1, l'automate n'est pas deterministe
            if (nombreEtatsLies != 1) {
                return false;
            }
        }
    }

    // Si tous les etats ont passe le test, l'automate est deterministe
    return true;
}




// estComplet qui va permettre de savoir si l'automate est complet ou pas
bool estComplet(Automate* automate) {
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
            if (nombreEtatsLies != 1) {
                return false;
            }
        }
    }

    // Si tous les etats ont passe le test, l'automate est complet
    return true;
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
                if (automate1 != NULL) {
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
