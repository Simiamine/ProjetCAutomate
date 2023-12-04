// Structure representing an automaton
typedef struct {
    int*** transitionMatrix;  // Dynamic matrix
    int* finalStates;         // Array of integers
    int initialState;         // Initial state
    int numberOfStates;       // Number of states in the automaton
    int numberOfEvents;       // Number of events in the automaton
} Automaton;

// Function to initialize an automaton (to be called before use)
void initializeAutomaton(Automaton* automaton, int numberOfStates, int numberOfEvents) {
    int i, j, k;

    automaton->numberOfStates = numberOfStates;
    automaton->numberOfEvents = numberOfEvents;

    // Allocation of the dynamic matrix
    automaton->transitionMatrix = (int***)malloc(numberOfStates * sizeof(int**));
    for (i = 0; i < numberOfStates; i++) {
        automaton->transitionMatrix[i] = (int**)malloc(numberOfEvents * sizeof(int*));
        for (j = 0; j < numberOfEvents; j++) {
            automaton->transitionMatrix[i][j] = (int*)calloc(numberOfStates, sizeof(int)); // Using calloc for zero-initialization
            if (!automaton->transitionMatrix[i][j]) {
                // Handle memory allocation error...
            }
        }
    }

    // Initialization of the final states
    automaton->finalStates = (int*)calloc(numberOfStates, sizeof(int)); // Using calloc for zero-initialization
    if (!automaton->finalStates) {
        // Handle memory allocation error...
    }
    automaton->initialState = -1; // Initialize to an invalid state
}

// Function to free the memory allocated to an automaton
void freeAutomaton(Automaton* automaton) {
    int i, j;

    // Freeing the memory of the dynamic matrix
    for (i = 0; i < automaton->numberOfStates; i++) {
        for (j = 0; j < automaton->numberOfEvents; j++) {
            free(automaton->transitionMatrix[i][j]);
        }
        free(automaton->transitionMatrix[i]);
    }
    free(automaton->transitionMatrix);

    // Freeing the memory of the final states
    free(automaton->finalStates);
    // Resetting the structure to avoid dangling pointers
    automaton->transitionMatrix = NULL;
    automaton->finalStates = NULL;
    automaton->numberOfStates = 0;
    automaton->numberOfEvents = 0;
    automaton->initialState = -1;
}

// Fonction auxiliaire pour modifier une transition
void modifierTransition(Automaton* automaton) {
    int etatDepart, event, etatArrivee;

    printf("Entrer l'état de départ: ");
    scanf("%d", &etatDepart);
    printf("Entrer l'indice de l'événement: ");
    scanf("%d", &event);
    printf("Entrer l'état d'arrivée: ");
    scanf("%d", &etatArrivee);

    if (etatDepart >= 0 && etatDepart < automaton->numberOfStates &&
        event >= 0 && event < automaton->numberOfEvents &&
        etatArrivee >= 0 && etatArrivee < automaton->numberOfStates) {
        automaton->transitionMatrix[etatDepart][event][etatArrivee] = 1;
    } else {
        printf("Indices invalides!\n");
    }
}

// Fonction auxiliaire pour modifier les états finaux
void modifierEtatsFinaux(Automaton* automaton) {
    int etat, estFinal;

    printf("Entrer l'indice de l'état à modifier: ");
    scanf("%d", &etat);
    printf("Cet état est-il final? (1 pour oui, 0 pour non): ");
    scanf("%d", &estFinal);

    if (etat >= 0 && etat < automaton->numberOfStates) {
        automaton->finalStates[etat] = estFinal;
    } else {
        printf("Indice d'état invalide!\n");
    }
}

// Fonction auxiliaire pour modifier l'état initial
void modifierEtatInitial(Automaton* automaton) {
    int etatInitial;

    printf("Entrer le nouvel état initial: ");
    scanf("%d", &etatInitial);

    if (etatInitial >= 0 && etatInitial < automaton->numberOfStates) {
        automaton->initialState = etatInitial;
    } else {
        printf("Indice d'état invalide!\n");
    }
}

// Fonction principale pour modifier l'automate
void modifierAutomate(Automaton* automaton) {
    int choix;

    printf("Modifier l'automate:\n");
    printf("1. Modifier une transition\n");
    printf("2. Modifier les états finaux\n");
    printf("3. Modifier l'état initial\n");
    printf("4. Quitter\n");
    printf("Choisir une option: ");
    scanf("%d", &choix);

    switch (choix) {
        case 1:
            modifierTransition(automaton);
            break;
        case 2:
            modifierEtatsFinaux(automaton);
            break;
        case 3:
            modifierEtatInitial(automaton);
            break;
        case 4:
            printf("Sortie du mode de modification.\n");
            break;
        default:
            printf("Option invalide!\n");
            break;
    }
}

// Function to serialize the automaton into a file
void serializeAutomaton(const char* fileName, const Automaton* automaton) {
    FILE* file = fopen(fileName, "wb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Writing the Automaton structure to the file
    fwrite(automaton, sizeof(Automaton), 1, file);

    fclose(file);
}

// Function to deserialize the automaton from a file
void deserializeAutomaton(const char* fileName, Automaton* automaton) {
    FILE* file = fopen(fileName, "rb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Reading the Automaton structure from the file
    fread(automaton, sizeof(Automaton), 1, file);

    fclose(file);
}

// Fonction pour afficher l'automate
void afficherAutomate(const Automaton* automaton) {
    printf("Nombre d'états : %d\n", automaton->numberOfStates);
    printf("Nombre d'événements : %d\n", automaton->numberOfEvents);
    printf("État initial : %d\n", automaton->initialState);
    printf("Matrice de transition :\n");

    for (int i = 0; i < automaton->numberOfStates; i++) {
        for (int j = 0; j < automaton->numberOfEvents; j++) {
            printf("Depuis l'état %d avec l'événement %d : ", i, j);
            for (int k = 0; k < automaton->numberOfStates; k++) {
                if (automaton->transitionMatrix[i][j][k] != 0) {
                    printf("%d ", k);
                }
            }
            printf("\n");
        }
    }

    printf("États finaux : ");
    for (int i = 0; i < automaton->numberOfStates; i++) {
        if (automaton->finalStates[i] != 0) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

int main() {
    // Initializing the Automaton structure
    Automaton myAutomaton;
    initializeAutomaton(&myAutomaton, 3, 2);

    // Example initialization of the automaton with your data
    myAutomaton.transitionMatrix[0][0][0] = 1;  // 0-0:0
    myAutomaton.transitionMatrix[0][1][1] = 1;  // 0-1:1
    myAutomaton.transitionMatrix[1][0][2] = 1;  // 1-0:2
    myAutomaton.transitionMatrix[1][1][0] = 1;  // 1-1:0
    myAutomaton.transitionMatrix[2][0][2] = 1;  // 2-0:2
    myAutomaton.transitionMatrix[2][1][0] = 1;  // 2-1:0

    myAutomaton.finalStates[0] = 1;  // State 0 is final
    myAutomaton.finalStates[2] = 1;  // State 2 is final
    myAutomaton.initialState = 0;

    afficherAutomate(&myAutomaton);

    // Serializing the automaton into a file
    serializeAutomaton("automaton.dat", &myAutomaton);

    // Deserializing the automaton from the file
    Automaton deserializedAutomaton;
    deserializeAutomaton("automaton.dat", &deserializedAutomaton);

    // Using the deserialized automaton
    // ...

    // Freeing the memory allocated for the automaton
    freeAutomaton(&myAutomaton);
    freeAutomaton(&deserializedAutomaton);
