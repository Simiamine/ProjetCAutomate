#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Structure representant les etats lies par un evenment
typedef struct listetats {
    int etat;
    struct listetats* suivant;
} listetats;

// Structure representant les evenements
typedef struct listevents {
    char event;
    struct listevents* suivant;
} listevents;

// Structure representant un automate
typedef struct {
    int nombreEtats;           // Nombre d'états dans l'automate
    int nombreEvent;      // Nombre d'événements dans l'automate
    listetats*** matriceTransition;  // Matrice dynamique
    listetats* etatsFinaux;          // Tableau d'entiers
    listetats* etatsInitiaux;           // État initial
    listevents* listeEvent; // Liste des événements
} Automate;

Automate* initAutomate(int nombreEtats, int nombreEvent) {
    // Allouer de la mémoire pour l'automate
    Automate* automate = malloc(sizeof(Automate));

    // Initialiser le nombre d'états et le nombre d'événements
    automate->nombreEtats = nombreEtats;
    automate->nombreEvent = nombreEvent;

    // Allouer et initialiser la matrice de transition
    automate->matriceTransition = malloc(sizeof(listetats**) * nombreEtats);
    for (int i = 0; i < nombreEtats; i++) {
        automate->matriceTransition[i] = malloc(sizeof(listetats*) * nombreEvent);
        for (int j = 0; j < nombreEvent; j++) {
            automate->matriceTransition[i][j] = malloc(sizeof(listetats) * nombreEtats);
            for (int k = 0; k < nombreEtats; k++) {
                automate->matriceTransition[i][j][k].etat = 0;
                automate->matriceTransition[i][j][k].suivant = NULL;
            }
        }
    }
