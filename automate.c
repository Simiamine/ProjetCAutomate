#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>



// Structure representant un automate
typedef struct {
    int nombreEtats;           // Nombre d'etats dans l'automate
    int nombreEvent;      // Nombre d'evenements dans l'automate
    int*** matriceTransition;  // Matrice dynamique contenant les transitions : matriceTransition[etat][event][etatslies] avec etat lies = 1 si lie et 0 sinon
    int* etatsFinaux;          // Tableau d'entiers de taille nbEtats : 1 si final et 0 sinon
    int* etatsInitiaux;           //  Tableau d'entiers de taille nbEtats : 1 si initial et 0 sinon
    char* listeEvent; // Liste des evenements : listeEvent[event] = lettre de l'evenement a l'indice event
} Automate;

Automate* initAutomate(int nombreEtats, int nombreEvent) {
    // Allouer de la memoire pour l'automate
    Automate* automate = malloc(sizeof(Automate));

    // Initialiser le nombre d'etats et le nombre d'evenements
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

    // Allouer et initialiser les etats finaux et initiaux
    automate->etatsFinaux = calloc(nombreEtats, sizeof(int));
    automate->etatsInitiaux = calloc(nombreEtats, sizeof(int));

    // Allouer et initialiser la liste des evenements
    automate->listeEvent = calloc(nombreEvent, sizeof(char));

    return automate;
}


Automate* remplirAEF(Automate* automate) {
    // Demander a l'utilisateur de fournir la liste des evenements
    printf("Veuillez fournir la liste des evenements :\n");
    for (int j = 0; j < automate->nombreEvent; j++) {
        printf("Event %d : ", j+1);
        scanf(" %c", &(automate->listeEvent[j])); // Notez l'espace avant %c pour ignorer les espaces blancs
    }

    // Parcourir chaque etat
    for (int i = 0; i < automate->nombreEtats; i++) {
        printf("Etat %d\n", i+1);

        // Demander si l'etat est initial
        int estInitial;
        do {
            printf("Etat initial ? (1 pour oui, 0 pour non) : ");
            scanf("%d", &estInitial);
        } while (estInitial != 0 && estInitial != 1);
        automate->etatsInitiaux[i] = estInitial;

        // Demander si l'etat est final
        int estFinal;
        do {
            printf("Etat final ? (1 pour oui, 0 pour non) : ");
            scanf("%d", &estFinal);
        } while (estFinal != 0 && estFinal != 1);
        automate->etatsFinaux[i] = estFinal;

        // Parcourir chaque evenement
        for (int j = 0; j < automate->nombreEvent; j++) {
            printf("Modification matrice transition\n");
            printf("Etat %d --(%c)--> ?\n", i+1, automate->listeEvent[j]);

            // Lire la liste des etats lies a l'etat i par l'evenement j
            for (int k = 0; k < automate->nombreEtats; k++) {
                int estLie;
                do {
                    printf("Etat %d est-il lie ? (1 pour oui, 0 pour non) : ", k+1);
                    scanf("%d", &estLie);
                } while (estLie != 0 && estLie != 1);
                automate->matriceTransition[i][j][k] = estLie;
            }
        }
    }

    return automate;
}

void afficherAEF(Automate* automate) {
    // Afficher la liste des evenements
    printf("Liste des evenements :\n");
    for (int j = 0; j < automate->nombreEvent; j++) {
        printf("Event %d : %c\n", j+1, automate->listeEvent[j]);
    }

    // Afficher les etats initiaux
    printf("Liste des etats initiaux :\n");
    for (int i = 0; i < automate->nombreEtats; i++) {
        if (automate->etatsInitiaux[i] == 1) {
            printf("Etat %d\n", i+1);
        }
    }

    // Afficher les etats finaux
    printf("Liste des etats finaux :\n");
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


void freeAutomate(Automate* automate) {
    // Liberer la memoire allouee pour la matrice de transition
    for (int i = 0; i < automate->nombreEtats; i++) {
        for (int j = 0; j < automate->nombreEvent; j++) {
            free(automate->matriceTransition[i][j]);
        }
        free(automate->matriceTransition[i]);
    }
    free(automate->matriceTransition);

    // Liberer la memoire allouee pour les etats finaux et initiaux
    free(automate->etatsFinaux);
    free(automate->etatsInitiaux);

    // Liberer la memoire allouee pour la liste des evenements
    free(automate->listeEvent);

    // Liberer la memoire allouee pour l'automate
    free(automate);
}

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
            int choixInversion;
            scanf("%d", &choixInversion);
            modifierTransition(automate, etatDepart, etatArrivee, event1);
            break;
        case 2:
            printf("Quel est l'identifiant de l'etat a ajouter ?\n");
            char identifiant;
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
            printf("Quel est l'etat initial a ajouter ?\n");
            int etatInitial;
            scanf("%d", &etatInitial);
            ajouterEtatInitial(automate, etatInitial);
            break;
        case 5:
            printf("Quel est l'etat final a ajouter ?\n");
            int etatFinal;
            scanf("%d", &etatFinal);
            ajouterEtatFinal(automate, etatFinal);
            break;
        case 6: //supprimer un etat
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
        case 7: //supprimer un evenement
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
            automate->etatsInitiaux[etatInitialSuppr] = 0;
            break;
        case 9: //supprimer un etat final (on ne peut pas supprimer un etat final qui est aussi initial)
            printf("Quel est l'etat final a supprimer ?\n");
            int etatFinalSuppr;
            scanf("%d", &etatFinalSuppr);
            automate->etatsFinaux[etatFinalSuppr] = 0;
            break;
        case 10:
            break;
        default:
            printf("Erreur : choix invalide\n");
            break;
    }
}

// enregistrer l'automate dans un fichier .json en demandant a l'utilisateur le nom du fichier et en verifiant si le fichier existe deja ou pas
void enregistrerAutomate(Automate* automate) {
    char nomFichier[100];
    printf("Quel est le nom du fichier ?\n");
    scanf("%s", nomFichier);
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier != NULL) {
        printf("Erreur : le fichier existe deja\n");
        fclose(fichier);
    } else {
        fichier = fopen(nomFichier, "w");
        fprintf(fichier, "{\n");
        fprintf(fichier, "\t\"nombreEtats\" : %d,\n", automate->nombreEtats);
        fprintf(fichier, "\t\"nombreEvent\" : %d,\n", automate->nombreEvent);
        fprintf(fichier, "\t\"listeEvent\" : [\n");
        for (int i = 0; i < automate->nombreEvent; i++) {
            fprintf(fichier, "\t\t\"%c\"", automate->listeEvent[i]);
            if (i < automate->nombreEvent - 1) {
                fprintf(fichier, ",");
            }
            fprintf(fichier, "\n");
        }
        fprintf(fichier, "\t],\n");
        fprintf(fichier, "\t\"etatsInitiaux\" : [\n");
        for (int i = 0; i < automate->nombreEtats; i++) {
            fprintf(fichier, "\t\t%d", automate->etatsInitiaux[i]);
            if (i < automate->nombreEtats - 1) {
                fprintf(fichier, ",");
            }
            fprintf(fichier, "\n");
        }
        fprintf(fichier, "\t],\n");
        fprintf(fichier, "\t\"etatsFinaux\" : [\n");
        for (int i = 0; i < automate->nombreEtats; i++) {
            fprintf(fichier, "\t\t%d", automate->etatsFinaux[i]);
            if (i < automate->nombreEtats - 1) {
                fprintf(fichier, ",");
            }
            fprintf(fichier, "\n");
        }
        fprintf(fichier, "\t],\n");
        fprintf(fichier, "\t\"matriceTransition\" : [\n");
        for (int i = 0; i < automate->nombreEtats; i++) {
            fprintf(fichier, "\t\t[\n");
            for (int j = 0; j < automate->nombreEvent; j++) {
                fprintf(fichier, "\t\t\t[");
                for (int k = 0; k < automate->nombreEtats; k++) {
                    fprintf(fichier, "%d", automate->matriceTransition[i][j][k]);
                    if (k < automate->nombreEtats - 1) {
                        fprintf(fichier, ",");
                    }
                }
                fprintf(fichier, "]");
                if (j < automate->nombreEvent - 1) {
                    fprintf(fichier, ",");
                }
                fprintf(fichier, "\n");
            }
            fprintf(fichier, "\t\t]");
            if (i < automate->nombreEtats - 1) {
                fprintf(fichier, ",");
            }
            fprintf(fichier, "\n");
        }
        fprintf(fichier, "\t]\n");
        fprintf(fichier, "}");
        fclose(fichier);
    }
}

// charger un automate a partir d'un fichier .json en demandant a l'utilisateur le nom du fichier et en verifiant si le fichier existe ou pas  
Automate* chargerAutomate() {
    char nomFichier[100];
    printf("Quel est le nom du fichier ?\n");
    scanf("%s", nomFichier);
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Erreur : le fichier n'existe pas\n");
        return NULL;
    } else {
        int nombreEtats, nombreEvent;
        fscanf(fichier, "{\n");
        fscanf(fichier, "\t\"nombreEtats\" : %d,\n", &nombreEtats);
        fscanf(fichier, "\t\"nombreEvent\" : %d,\n", &nombreEvent);
        fscanf(fichier, "\t\"listeEvent\" : [\n");
        char* listeEvent = calloc(nombreEvent, sizeof(char));
        for (int i = 0; i < nombreEvent; i++) {
            fscanf(fichier, "\t\t\"%c\"", &(listeEvent[i]));
            if (i < nombreEvent - 1) {
                fscanf(fichier, ",");
            }
            fscanf(fichier, "\n");
        }
        fscanf(fichier, "\t],\n");
        fscanf(fichier, "\t\"etatsInitiaux\" : [\n");
        int* etatsInitiaux = calloc(nombreEtats, sizeof(int));
        for (int i = 0; i < nombreEtats; i++) {
            fscanf(fichier, "\t\t%d", &(etatsInitiaux[i]));
            if (i < nombreEtats - 1) {
                fscanf(fichier, ",");
            }
            fscanf(fichier, "\n");
        }
        fscanf(fichier, "\t],\n");
        fscanf(fichier, "\t\"etatsFinaux\" : [\n");
        int* etatsFinaux = calloc(nombreEtats, sizeof(int));
        for (int i = 0; i < nombreEtats; i++) {
            fscanf(fichier, "\t\t%d", &(etatsFinaux[i]));
            if (i < nombreEtats - 1) {
                fscanf(fichier, ",");
            }
            fscanf(fichier, "\n");
        }
        fscanf(fichier, "\t],\n");
        fscanf(fichier, "\t\"matriceTransition\" : [\n");
        int*** matriceTransition = malloc(sizeof(int**) * nombreEtats);
        for (int i = 0; i < nombreEtats; i++) {
            matriceTransition[i] = malloc(sizeof(int*) * nombreEvent);
            fscanf(fichier, "\t\t[\n");
            for (int j = 0; j < nombreEvent; j++) {
                matriceTransition[i][j] = calloc(nombreEtats, sizeof(int));
                fscanf(fichier, "\t\t\t[");
                for (int k = 0; k < nombreEtats; k++) {
                    fscanf(fichier, "%d", &(matriceTransition[i][j][k]));
                    if (k < nombreEtats - 1) {
                        fscanf(fichier, ",");
                    }
                }
                fscanf(fichier, "]");
                if (j < nombreEvent - 1) {
                    fscanf(fichier, ",");
                }
                fscanf(fichier, "\n");
            }
            fscanf(fichier, "\t\t]");
            if (i < nombreEtats - 1) {
                fscanf(fichier, ",");
            }
            fscanf(fichier, "\n");
        }
        fscanf(fichier, "\t]\n");
        fscanf(fichier, "}");
        fclose(fichier);
    //l'automate a ete charge
        Automate* automate = initAutomate(nombreEtats, nombreEvent);
        automate->listeEvent = listeEvent;
        automate->etatsInitiaux = etatsInitiaux;
        automate->etatsFinaux = etatsFinaux;
        automate->matriceTransition = matriceTransition;

        //message de reussite
        printf("L'automate a ete charge avec succes\n");

        return automate;

    }
}
// fonction qui va permettre de faire l'union de deux automates
Automate* unionAutomate(Automate* automate1, Automate* automate2) {
    // Creer un nouvel automate
    Automate* automate = initAutomate(0, 0);

    // Ajouter les etats de l'automate 1
    for (int i = 0; i < automate1->nombreEtats; i++) {
        ajouterEtat(automate, i);
    }

    // Ajouter les etats de l'automate 2
    for (int i = 0; i < automate2->nombreEtats; i++) {
        ajouterEtat(automate, i + automate1->nombreEtats);
    }

    // Ajouter les evenements de l'automate 1
    for (int i = 0; i < automate1->nombreEvent; i++) {
        ajouterEvent(automate, automate1->listeEvent[i]);
    }

    // Ajouter les evenements de l'automate 2
    for (int i = 0; i < automate2->nombreEvent; i++) {
        ajouterEvent(automate, automate2->listeEvent[i]);
    }

    // Ajouter les etats initiaux de l'automate 1
    for (int i = 0; i < automate1->nombreEtats; i++) {
        if (automate1->etatsInitiaux[i] == 1) {
            ajouterEtatInitial(automate, i);
        }
    }

    // Ajouter les etats initiaux de l'automate 2
    for (int i = 0; i < automate2->nombreEtats; i++) {
        if (automate2->etatsInitiaux[i] == 1) {
            ajouterEtatInitial(automate, i + automate1->nombreEtats);
        }
    }

    // Ajouter les etats finaux de l'automate 1
    for (int i = 0; i < automate1->nombreEtats; i++) {
        if (automate1->etatsFinaux[i] == 1) {
            ajouterEtatFinal(automate, i);
        }
    }

    // Ajouter les etats finaux de l'automate 2
    for (int i = 0; i < automate2->nombreEtats; i++) {
        if (automate2->etatsFinaux[i] == 1) {
            ajouterEtatFinal(automate, i + automate1->nombreEtats);
        }
    }
}

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