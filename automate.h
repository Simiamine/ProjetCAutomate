#ifndef AUTOMATE_H
    #define AUTOMATE_H

typedef struct {
    int numStates;           // Number of states in the automaton
    int numEvents;      // Number of events in the automaton
    int*** transitionMatrix;  // Dynamic matrix containing transitions: transitionMatrix[state][event][linkedStates] with linked state = 1 if linked and 0 otherwise
    int* finalStates;          // Integer array of size numStates: 1 if final and 0 otherwise
    int* initialStates;           // Integer array of size numStates: 1 if initial and 0 otherwise
    char* eventList; // List of events: eventList[event] = letter of the event at the event index
} Automaton;

	void deleteState(Automaton* automaton, int state) {
    // Check if the state is valid
    if (state < 0 || state >= automaton->numStates) {
        printf("Invalid state.\n");
        return;
    }

    // Remove all transitions to the state to be deleted
    for (int i = 0; i < automaton->numStates; i++) {
        for (int j = 0; j < automaton->numEvents; j++) {
            automaton->transitionMatrix[i][j][state] = 0;
        }
    }

    // Decrease the number of states
    automaton->numStates--;

    // Shift the initial and final states
    for (int i = state; i < automaton->numStates; i++) {
        automaton->initialStates[i] = automaton->initialStates[i + 1];
        automaton->finalStates[i] = automaton->finalStates[i + 1];
    }

    // Shift the transition matrix
    for (int i = state; i < automaton->numStates; i++) {
        for (int j = 0; j < automaton->numEvents; j++) {
            for (int k = state; k < automaton->numStates; k++) {
                automaton->transitionMatrix[i][j][k] = automaton->transitionMatrix[i][j][k + 1];
            }
            automaton->transitionMatrix[i][j] = realloc(automaton->transitionMatrix[i][j], automaton->numStates * sizeof(int));
        }
        free(automaton->transitionMatrix[i]);
        automaton->transitionMatrix[i] = automaton->transitionMatrix[i + 1];
        automaton->transitionMatrix[i + 1] = NULL;
    }

    // Reallocate the initial and final states
    automaton->initialStates = realloc(automaton->initialStates, automaton->numStates * sizeof(int));
    automaton->finalStates = realloc(automaton->finalStates, automaton->numStates * sizeof(int));

    // Reallocate the transition matrix
    automaton->transitionMatrix = realloc(automaton->transitionMatrix, automaton->numStates * sizeof(int**));
}

void deleteEvent(Automaton* automaton, int event) {
    // Check if the event is valid
    if (event < 0 || event >= automaton->numEvents) {
        printf("Invalid event.\n");
        return;
    }

    // Shift the event list
    for (int i = event; i < automaton->numEvents - 1; i++) {
        automaton->eventList[i] = automaton->eventList[i + 1];
    }

    // Shift the transition matrix
    for (int i = 0; i < automaton->numStates; i++) {
        for (int j = event; j < automaton->numEvents - 1; j++) {
            free(automaton->transitionMatrix[i][j]);
            automaton->transitionMatrix[i][j] = automaton->transitionMatrix[i][j + 1];
        }
        automaton->transitionMatrix[i] = realloc(automaton->transitionMatrix[i], (automaton->numEvents - 1) * sizeof(int*));
    }

    // Decrease the number of events
    automaton->numEvents--;

    // Reallocate the event list
    automaton->eventList = realloc(automaton->eventList, automaton->numEvents * sizeof(char));
}

#include <stdio.h>

void addEvent(Automaton* automaton, char newEvent) {
    // Check if the event already exists
    for (int i = 0; i < automaton->numEvents; i++) {
        if (automaton->eventList[i] == newEvent) {
            printf("Event already exists.\n");
            return;
        }
    }

    // Increase the number of events
    automaton->numEvents++;

    // Reallocate the event list and add the new event
    automaton->eventList = realloc(automaton->eventList, automaton->numEvents * sizeof(char));
    automaton->eventList[automaton->numEvents - 1] = newEvent;

    // Reallocate the transition matrix
    automaton->transitionMatrix = realloc(automaton->transitionMatrix, automaton->numStates * sizeof(int**));
    for (int i = 0; i < automaton->numStates; i++) {
        automaton->transitionMatrix[i] = realloc(automaton->transitionMatrix[i], automaton->numEvents * sizeof(int*));
        automaton->transitionMatrix[i][automaton->numEvents - 1] = calloc(automaton->numStates, sizeof(int));
    }

    // Ask the user if the new event should be associated with states
    char answer;
    printf("Should the new event be associated with states? (y/n): ");
    scanf(" %c", &answer);

    if (answer == 'y' || answer == 'Y') {
        // Ask the user for the start and end states
        int startState, endState;
        while (1) {
            printf("Enter a start state (or -1 to stop): ");
            scanf("%d", &startState);

            if (startState == -1) {
                break;
            }

            printf("Enter an end state: ");
            scanf("%d", &endState);

            // Check if the states are valid
            if (startState < 0 || startState >= automaton->numStates || endState < 0 || endState >= automaton->numStates) {
                printf("Invalid states.\n");
                continue;
            }

            // Add the transition
            automaton->transitionMatrix[startState][automaton->numEvents - 1][endState] = 1;
        }
    }
}




#endif 