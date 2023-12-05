#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


// Structure representant un automate
typedef struct {
    int nombreEtats;           // Nombre d'états dans l'automate
    int nombreEvent;      // Nombre d'événements dans l'automate
    int*** matriceTransition;  // Matrice dynamique contenant les transitions : matriceTransition[etat][event][etatsliés] avec etat liés = 1 si lié et 0 sinon
    int* etatsFinaux;          // Tableau d'entiers de taille nbEtats : 1 si final et 0 sinon
    int* etatsInitiaux;           //  Tableau d'entiers de taille nbEtats : 1 si initial et 0 sinon
    char* listeEvent; // Liste des événements : listeEvent[event] = lettre de l'événement à l'indice event
} Automate;

Automate* initAutomate(int nombreEtats, int nombreEvent) {
    // Allouer de la mémoire pour l'automate
    Automate* automate = malloc(sizeof(Automate));

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

    return automate;
}


Automate* remplirAEF(Automate* automate) {
    // Demander à l'utilisateur de fournir la liste des événements
    printf("Veuillez fournir la liste des événements :\n");
    for (int j = 0; j < automate->nombreEvent; j++) {
        printf("Event %d : ", j+1);
        scanf(" %c", &(automate->listeEvent[j])); // Notez l'espace avant %c pour ignorer les espaces blancs
    }

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

    return automate;
}

void afficherAEF(Automate* automate) {
    // Afficher la liste des événements
    printf("Liste des événements :\n");
    for (int j = 0; j < automate->nombreEvent; j++) {
        printf("Event %d : %c\n", j+1, automate->listeEvent[j]);
    }

    // Afficher les états initiaux
    printf("Liste des états initiaux :\n");
    for (int i = 0; i < automate->nombreEtats; i++) {
        if (automate->etatsInitiaux[i] == 1) {
            printf("Etat %d\n", i+1);
        }
    }

    // Afficher les états finaux
    printf("Liste des états finaux :\n");
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

void generateDot(Automate* automate) {
    printf("digraph G {\n");

    // Créer un nœud pour chaque état
    for (int i = 0; i < automate->nombreEtats; i++) {
        if (automate->etatsFinaux[i] == 1) {
            printf("  %d [shape=doublecircle];\n", i+1);
        } else {
            printf("  %d;\n", i+1);
        }
    }

    // Créer une arête pour chaque transition
    for (int i = 0; i < automate->nombreEtats; i++) {
        for (int j = 0; j < automate->nombreEvent; j++) {
            for (int k = 0; k < automate->nombreEtats; k++) {
                if (automate->matriceTransition[i][j][k] == 1) {
                    printf("  %d -> %d [label=\"%c\"];\n", i+1, k+1, automate->listeEvent[j]);
                }
            }
        }
    }

    printf("}\n");
}
void freeAutomate(Automate* automate) {
    // Libérer la mémoire allouée pour la matrice de transition
    for (int i = 0; i < automate->nombreEtats; i++) {
        for (int j = 0; j < automate->nombreEvent; j++) {
            free(automate->matriceTransition[i][j]);
        }
        free(automate->matriceTransition[i]);
    }
    free(automate->matriceTransition);

    // Libérer la mémoire allouée pour les états finaux et initiaux
    free(automate->etatsFinaux);
    free(automate->etatsInitiaux);

    // Libérer la mémoire allouée pour la liste des événements
    free(automate->listeEvent);

    // Libérer la mémoire allouée pour l'automate
    free(automate);
}

int main() {
    // Initialiser un automate avec 3 états et 2 événements
    Automate* automate = initAutomate(3, 2);

    // Remplir l'automate avec des données d'exemple
    automate->etatsInitiaux[0] = 1;
    automate->etatsFinaux[2] = 1;
    automate->listeEvent[0] = 'a';
    automate->listeEvent[1] = 'b';
    automate->matriceTransition[0][0][1] = 1; // état 1 --a--> état 2
    automate->matriceTransition[1][1][2] = 1; // état 2 --b--> état 3

    // Générer la description dot de l'automate
    generateDot(automate);

    // Libérer la mémoire allouée pour l'automate
    freeAutomate(automate);

    return 0;
}