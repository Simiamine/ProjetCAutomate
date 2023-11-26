#include <stdio.h>
#include <stdbool.h>

#include "automate.h"

// Déclaration préalable des structures
typedef struct listetats listetats;
typedef struct listevents listevents;

// Structure representant les etats lies par un evenment
typedef struct {
    int etat;
    listetats* suivant;
} listetats;

typedef struct {
    char event;
    listevents* suivant;
} listevents;

// Structure representant un automate
typedef struct {
    listetats** matriceTransition;  // Matrice dynamique
    int* etatsFinaux;          // Tableau d'entiers
    int etatInitial;           // État initial
    int nombreEtats;           // Nombre d'états dans l'automate
    int nombreEvent;      // Nombre d'événements dans l'automate
    listevents listeEvent; // Liste des événements
} Automate;

void serialization(Automate* automate, FILE* fichier) {
    // Ecriture de l'etat initial
    fprintf(fichier, "%d\n", automate->etatInitial);

    // Ecriture des etats finaux
    for (int i = 0; i < automate->nombreEtats; i++) {
        fprintf(fichier, "%d ", automate->etatsFinaux[i]);
    }
    fprintf(fichier, "\n");

    // Ecriture de la matrice de transition
    for (int i = 0; i < automate->nombreEtats; i++) {
        for (int j = 0; j < automate->nombreEvent; j++) {
            fprintf(fichier, "%d ", automate->matriceTransition[i][j].etat);
        }
        fprintf(fichier, "\n");
    }

    // Ecriture de la liste des evenements
    listevents* event = automate->listeEvent.suivant;
    while (event != NULL) {
        fprintf(fichier, "%c ", event->event);
        event = event->suivant;
    }
    fprintf(fichier, "\n");
}

void deserialization(Automate* automate, FILE* fichier) {
    // Lecture de l'etat initial
    fscanf(fichier, "%d\n", &automate->etatInitial);

    // Lecture des etats finaux
    for (int i = 0; i < automate->nombreEtats; i++) {
        fscanf(fichier, "%d ", &automate->etatsFinaux[i]);
    }
    fscanf(fichier, "\n");

    // Lecture de la matrice de transition
    for (int i = 0; i < automate->nombreEtats; i++) {
        for (int j = 0; j < automate->nombreEvent; j++) {
            fscanf(fichier, "%d ", &automate->matriceTransition[i][j].etat);
        }
        fscanf(fichier, "\n");
    }

    // Lecture de la liste des evenements
    listevents* event = &automate->listeEvent;
    char c;
    while (fscanf(fichier, "%c ", &c) != EOF) {
        event->suivant = malloc(sizeof(listevents));
        event = event->suivant;
        event->event = c;
        event->suivant = NULL;
    }
}

void main() {
    // Ouverture du fichier
    FILE* fichier = fopen("automate.txt", "r");

    // Création de l'automate
    Automate automate;
    automate.nombreEtats = 3;
    automate.nombreEvent = 3;
    automate.etatInitial = 0;
    automate.etatsFinaux = ;
    automate.matriceTransition = NULL;
    automate.listeEvent.suivant = NULL;

    // Lecture du fichier
    deserialization(&automate, fichier);

    // Fermeture du fichier
    fclose(fichier);

    // Ouverture du fichier
    fichier = fopen("automate2.txt", "w");

    // Ecriture du fichier
    serialization(&automate, fichier);

    // Fermeture du fichier
    fclose(fichier);
}
```