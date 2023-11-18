#include <stdio.h>
#include <stdlib.h>

// Structure représentant un automate
typedef struct {
    int*** matriceTransition;  // Matrice dynamique
    int* etatsFinaux;          // Tableau d'entiers
    int etatInitial;           // État initial
    int nombreEtats;           // Nombre d'états dans l'automate
    int nombreEvenements;      // Nombre d'événements dans l'automate
} Automate;

// Fonction pour initialiser un automate (à appeler avant utilisation)
void initialiserAutomate(Automate* automate, int nombreEtats, int nombreEvenements) {
    int i, j;

    automate->nombreEtats = nombreEtats;
    automate->nombreEvenements = nombreEvenements;

    // Allocation de la matrice dynamique
    automate->matriceTransition = (int***)malloc(nombreEtats * sizeof(int**));
    for (i = 0; i < nombreEtats; i++) {
        automate->matriceTransition[i] = (int**)malloc(nombreEvenements * sizeof(int*));
        for (j = 0; j < nombreEvenements; j++) {
            automate->matriceTransition[i][j] = (int*)malloc(nombreEtats * sizeof(int));
        }
    }

    // Initialisation des états finaux
    automate->etatsFinaux = (int*)malloc(nombreEtats * sizeof(int));
}

// Fonction pour libérer la mémoire allouée à un automate
void libererAutomate(Automate* automate) {
    int i, j;

    // Libération de la mémoire de la matrice dynamique
    for (i = 0; i < automate->nombreEtats; i++) {
        for (j = 0; j < automate->nombreEvenements; j++) {
            free(automate->matriceTransition[i][j]);
        }
        free(automate->matriceTransition[i]);
    }
    free(automate->matriceTransition);

    // Libération de la mémoire des états finaux
    free(automate->etatsFinaux);
}

// Fonction pour sérialiser l'automate dans un fichier
void serialiserAutomate(const char* nomFichier, const Automate* automate) {
    FILE* fichier = fopen(nomFichier, "wb");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    // Écriture de la structure Automate dans le fichier
    fwrite(automate, sizeof(Automate), 1, fichier);

    fclose(fichier);
}

// Fonction pour désérialiser l'automate depuis un fichier
void deserialiserAutomate(const char* nomFichier, Automate* automate) {
    FILE* fichier = fopen(nomFichier, "rb");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    // Lecture de la structure Automate depuis le fichier
    fread(automate, sizeof(Automate), 1, fichier);

    fclose(fichier);
}

int main() {
    // Initialisation de la structure Automate
    Automate monAutomate;
    initialiserAutomate(&monAutomate, 3, 2);

    // Exemple d'initialisation de l'automate avec vos données
    monAutomate.matriceTransition[0][0][0] = 1;  // 0-0:0
    monAutomate.matriceTransition[0][1][1] = 1;  // 0-1:1
    monAutomate.matriceTransition[1][0][2] = 1;  // 1-0:2
    monAutomate.matriceTransition[1][1][0] = 1;  // 1-1:0
    monAutomate.matriceTransition[2][0][2] = 1;  // 2-0:2
    monAutomate.matriceTransition[2][1][0] = 1;  // 2-1:0

    monAutomate.etatsFinaux[0] = 1;  // État 0 est final
    monAutomate.etatsFinaux[2] = 1;  // État 2 est final
    monAutomate.etatInitial = 0;

    // Sérialisation de l'automate dans un fichier
    serialiserAutomate("automate.dat", &monAutomate);

    // Désérialisation de l'automate depuis le fichier
    Automate automateDeserialise;
    deserialiserAutomate("automate.dat", &automateDeserialise);

    // Utilisation de l'automate désérialisé
    // ...

    // Libération de la mémoire allouée pour l'automate
    libererAutomate(&monAutomate);
    libererAutomate(&automateDeserialise);

    return 0;
}
