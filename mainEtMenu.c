#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>
#include "automate.h"



// menu qui va permettre a l'utilisateur de choisir ce qu'il veut faire
void menu() {
    int choix;
    Automate* automate = NULL;
    do {
        printf("Que voulez-vous faire ?\n");
        printf("1. Creer un automate\n");
        printf("2. Modifier un automate\n");
        printf("3. Afficher un automate\n");
        printf("4. Enregistrer un automate\n");
        printf("5. Charger un automate\n");
        printf("6. Tester un mot\n");
        printf("7. Operations sur l'automate\n"); // Added option for operations on the automate
        printf("8. Quitter\n");
        scanf("%d", &choix);
        switch (choix) {
            case 1:
                if (automate != NULL) {
                    freeAutomate(automate);
                }
                int nombreEtats, nombreEvent;
                printf("Combien d'etats ?\n");
                scanf("%d", &nombreEtats);
                printf("Combien d'evenements ?\n");
                scanf("%d", &nombreEvent);
                automate = initAutomate(nombreEtats, nombreEvent);
                automate = remplirAEF(automate);
                break;
            case 2:
                if (automate != NULL) {
                    ModifierAutomate(automate);
                } else {
                    printf("Erreur : aucun automate cree\n");
                }
                break;
            case 3:
                if (automate != NULL) {
                    afficherAEF(automate);
                } else {
                    printf("Erreur : aucun automate cree\n");
                }
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
                    freeAutomate(automate);
                }
                automate = chargerAutomate();
                break;
            case 6:
                if (automate != NULL) {
                    char mot[100];
                    printf("Quel est le mot a tester ?\n");
                    scanf("%s", mot);
                    if (motValide(automate, mot)) {
                        printf("Le mot est valide\n");
                    } else {
                        printf("Le mot n'est pas valide\n");
                    }
                } else {
                    printf("Erreur : aucun automate cree\n");
                }
                break;
            case 7:
                    printf("Vous allez effectuer des operations sur des automates charges a partir de fichiers.\n");
                    operationsAutomate(); // Call the function for operations on the automate
                break;
            case 8:
                if (automate != NULL) {
                    freeAutomate(automate);
                }
                break;
            default:
                printf("Erreur : choix invalide\n");
                break;
        }
    } while (choix != 8);
}



int main() {
    menu();
    return 0;
}