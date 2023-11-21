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
    int i, j;

    automaton->numberOfStates = numberOfStates;
    automaton->numberOfEvents = numberOfEvents;

    // Allocation of the dynamic matrix
    automaton->transitionMatrix = (int***)malloc(numberOfStates * sizeof(int**));
    for (i = 0; i < numberOfStates; i++) {
        automaton->transitionMatrix[i] = (int**)malloc(numberOfEvents * sizeof(int*));
        for (j = 0; j < numberOfEvents; j++) {
            automaton->transitionMatrix[i][j] = (int*)malloc(numberOfStates * sizeof(int));
        }
    }

    // Initialization of the final states
    automaton->finalStates = (int*)malloc(numberOfStates * sizeof(int));
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
