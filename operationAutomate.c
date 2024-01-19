#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "automate.h"

// Renvoie le complement d'un automate
Automate* complementAEF(Automate* automate){
    // Creer un nouvel automate
    Automate* complement = initAutomate(automate->nombreEtats, automate->nombreEvent);

    // Copier les etats initiaux
    for (int i = 0; i < automate->nombreEtats; i++) {
        complement->etatsInitiaux[i] = automate->etatsInitiaux[i];
    }

    // Copier les etats finaux
    for (int i = 0; i < automate->nombreEtats; i++) {
        complement->etatsFinaux[i] = automate->etatsFinaux[i];
    }

    // Copier les evenements
    for (int i = 0; i < automate->nombreEvent; i++) {
        complement->listeEvent[i] = automate->listeEvent[i];
    }

    // Copier la matrice de transition
    for (int i = 0; i < automate->nombreEtats; i++) {
        for (int j = 0; j < automate->nombreEvent; j++) {
            for (int k = 0; k < automate->nombreEtats; k++) {
                complement->matriceTransition[i][j][k] = automate->matriceTransition[i][j][k];
            }
        }
    }

    // Inverser les etats finaux et non finaux
    for (int i = 0; i < automate->nombreEtats; i++) {
        if (automate->etatsFinaux[i] == 1) {
            complement->etatsFinaux[i] = 0;
        } else {
            complement->etatsFinaux[i] = 1;
        }
    }

    return complement;
}

//Converti un AEF en sont mirroir : inverse les transitions, les Ã©tats finaux deviennent initiaux, et les initiaux deviennent finaux
Automate* mirroirAEF(Automate* automate){
    // Creer un nouvel automate
    Automate* mirroir = initAutomate(automate->nombreEtats, automate->nombreEvent);

    // Copier les etats initiaux
    for (int i = 0; i < automate->nombreEtats; i++) {
        mirroir->etatsInitiaux[i] = automate->etatsFinaux[i];
    }

    // Copier les etats finaux
    for (int i = 0; i < automate->nombreEtats; i++) {
        mirroir->etatsFinaux[i] = automate->etatsInitiaux[i];
    }

    // Copier les evenements
    for (int i = 0; i < automate->nombreEvent; i++) {
        mirroir->listeEvent[i] = automate->listeEvent[i];
    }

    // Copier la matrice de transition
    for (int i = 0; i < automate->nombreEtats; i++) {
        for (int j = 0; j < automate->nombreEvent; j++) {
            for (int k = 0; k < automate->nombreEtats; k++) {
                mirroir->matriceTransition[i][j][k] = automate->matriceTransition[k][j][i];
            }
        }
    }

    return mirroir;
}