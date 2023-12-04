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
        listetats** matriceTransition;  // Matrice dynamique
        int* etatsFinaux;          // Tableau d'entiers
        int etatInitial;           // État initial
        int nombreEtats;           // Nombre d'états dans l'automate
        int nombreEvent;      // Nombre d'événements dans l'automate
        listevents listeEvent; // Liste des événements
    } Automate;

    void serialization(Automate* automate) {
        // Lecture du compteur d'automates
        FILE* indexFile = fopen("index.txt", "r");
        int automateCount;
        fscanf(indexFile, "%d", &automateCount);
        fclose(indexFile);

        // Génération du nom de fichier
        char filename[20];
        sprintf(filename, "automate%d.txt", automateCount);

        // Incrémentation du compteur d'automates
        automateCount++;
        indexFile = fopen("index.txt", "w");
        fprintf(indexFile, "%d", automateCount);
        fclose(indexFile);

        // Ouverture du fichier en écriture
        FILE* fichier = fopen(filename, "w");
        if (fichier == NULL) {
            printf("Erreur lors de l'ouverture du fichier.\n");
            return;
        }

        // Écriture du contenu de l'automate dans le fichier
        fprintf(fichier, "%d\n", automate->etatInitial);
        for (int i = 0; i < automate->nombreEtats; i++) {
            fprintf(fichier, "%d ", automate->etatsFinaux[i]);
        }
        fprintf(fichier, "\n");
        for (int i = 0; i < automate->nombreEtats; i++) {
            for (int j = 0; j < automate->nombreEvent; j++) {
                fprintf(fichier, "%d ", automate->matriceTransition[i][j].etat);
            }
            fprintf(fichier, "\n");
        }
        listevents* event = &automate->listeEvent;
        while (event != NULL) {
            fprintf(fichier, "%c ", event->event);
            event = event->suivant;
        }

        // Fermeture du fichier
        fclose(fichier);
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
    //fonction qui permet d'afficher l'automate
    void afficherAutomate(Automate* automate) {
        printf("Etat initial : %d\n", automate->etatInitial);
        printf("Etats finaux : ");
        for (int i = 0; i < automate->nombreEtats; i++) {
            printf("%d ", automate->etatsFinaux[i]);
        }
        printf("\n");
        printf("Matrice de transition : \n");
        for (int i = 0; i < automate->nombreEtats; i++) {
            for (int j = 0; j < automate->nombreEvent; j++) {
                printf("Etat %d ----(%d)----> Etat %d\n", i+1, j+1, automate->matriceTransition[i][j].etat);
            }
        }
        printf("Liste des evenements : ");
        listevents* event = &automate->listeEvent;
        while (event != NULL) {
            printf("%c ", event->event);
            event = event->suivant;
        }
        printf("\n");
    }

    //fonction qui permet de creer un automate
    void creerAutomate(Automate* automate) {
        // Lecture du nombre d'états
        printf("Nombre d'etats : ");
        scanf("%d", &automate->nombreEtats);

        // Lecture du nombre d'événements
        printf("Nombre d'evenements : ");
        scanf("%d", &automate->nombreEvent);

        // Lecture de l'état initial
        printf("Etat initial : ");
        scanf("%d", &automate->etatInitial);

        // Lecture des états finaux
        printf("Etats finaux : ");
        automate->etatsFinaux = malloc(sizeof(int) * automate->nombreEtats);
        for (int i = 0; i < automate->nombreEtats; i++) {
            scanf("%d", &automate->etatsFinaux[i]);
        }

        // Lecture de la matrice de transition
        automate->matriceTransition = malloc(sizeof(listetats*) * automate->nombreEtats);
        for (int i = 0; i < automate->nombreEtats; i++) {
            automate->matriceTransition[i] = malloc(sizeof(listetats) * automate->nombreEvent);
            for (int j = 0; j < automate->nombreEvent; j++) {
                printf("Transition de l'etat %d avec l'evenement %d : ", i, j);
                scanf("%d", &automate->matriceTransition[i][j].etat);
            }
        }

        // Lecture de la liste des événements
        listevents* event = &automate->listeEvent;
        char c;
        printf("Liste des evenements : ");
        while ((c = getchar()) != '\n' && c != EOF);
        while ((c = getchar()) != '\n' && c != EOF) {
            event->suivant = malloc(sizeof(listevents));
            event = event->suivant;
            event->event = c;
            event->suivant = NULL;
        }
    }
    
    void main() {
        Automate automate; // Déclaration d'un automate
        FILE* fichier; // Déclaration d'un fichier

        // Création d'un automate
        creerAutomate(&automate);

        // Affichage de l'automate
        afficherAutomate(&automate);

        // Serialization de l'automate
        serialization(&automate);

        // Deserialization de l'automate
        fichier = fopen("automate0.txt", "r");
        deserialization(&automate, fichier);
        fclose(fichier);

        // Affichage de l'automate
        afficherAutomate(&automate);
    }
    