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

    // Allouer et initialiser les états finaux et initiaux
    automate->etatsFinaux = malloc(sizeof(listetats) * nombreEtats);
    automate->etatsInitiaux = malloc(sizeof(listetats) * nombreEtats);
    for (int i = 0; i < nombreEtats; i++) {
        automate->etatsFinaux[i].etat = 0;
        automate->etatsFinaux[i].suivant = NULL;
        automate->etatsInitiaux[i].etat = 0;
        automate->etatsInitiaux[i].suivant = NULL;
    }

    // Initialiser la liste des événements à NULL
    automate->listeEvent = NULL;

    return automate;
}

void main() {

etat 0 --(a)--> etat 2
}