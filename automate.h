#include <stdio.h>
#include <stdbool.h>

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
