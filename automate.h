#ifndef AUTOMATE_H
    #define AUTOMATE_H

		extern int allocPB;
        
        typedef struct listOfState{ 
            int state;
            struct listOfState *next;
        } listOfState; // linked list of states

        typedef struct listOfEvents{
            char event;
            struct listOfEvents *next;
        } listOfEvents; // linked list of events
        
        
        
        
        typedef struct Automaton{
            int numberOfStates;       // Number of states in the automaton
            int numberOfEvents;       // Number of events in the automaton
            listOfState*** Matrix;  // Dynamic matrix line=states and colomn=events
            listOfState* finalStates;         // list of final states PK NE PAS METTRE LISTOFSTATE ICI PUISQUE QUE LE TAILLE DE CETTE LISTE PEUT VARIER
            listOfState* initialStates;  // list of initial states MEME REMARQUE ICI
            listOfEvents* events; // list of events
            
            struct Automaton* nextAutomaton; // A VOIR AVK LES AUTRES 
        } Automaton;

        

        //states Manipulation
        listOfState* createState(int);
        void addState(listOfState**, listOfState*);
        void deleteState(listOfState*, int );
        listOfState* searchState(listOfState*, int);
        void freeState(listOfState*);
        void displayStates(listOfState* );
        


        //events Manipulation
        listOfEvents* createEvent(char);
        void addEvent(listOfEvents**, listOfEvents*);
        void deleteEvent(listOfEvents*, char );
        listOfEvents* searchEvent(listOfEvents*, char);
        void freeEvent(listOfEvents*);
        void displayEvents(listOfEvents* );       




        // Automaton creation
		void inputAutomaton(Automaton* );
        Automaton* createAutomaton();
        void initiateAutomaton(Automaton* );
        void navigateAutomaton(Automaton);
        listOfState enterCellsMatrix(int, int); 
        void interpreteMatrix(Automaton);
        void initiateInitialStates(Automaton*);
        void initiateEvents(Automaton* );
        void initiateFinalState(Automaton *);

        //Automaton in files
        void serialization(Automaton);
        void deserialization(Automaton);

        //Modification in Automaton
        void changeFinalStates(Automaton* automaton) {
            int state, isFinal;
            printf("Enter the state number to change its final status (0 to stop): ");
            while (1) {
                scanf("%d", &state);
                if (state == 0) break;
                printf("Is state %d a final state? (1 for yes, 0 for no): ", state);
                scanf("%d", &isFinal);
                listOfState* stateNode = searchState(automaton->finalStates, state);
                if (stateNode != NULL) {
                    stateNode->state = isFinal;
                } else {
                    if (isFinal) {
                        listOfState* newState = createState(state);
                        addState(&(automaton->finalStates), newState);
                    }
                }
            }
        }
        void changeInitialStates(Automaton* automaton) {
            int state, isInitial;
            printf("Enter the state number to change its initial status (0 to stop): ");
            while (1) {
                scanf("%d", &state);
                if (state == 0) break;
                printf("Is state %d an initial state? (1 for yes, 0 for no): ", state);
                scanf("%d", &isInitial);
                listOfState* stateNode = searchState(automaton->initialStates, state);
                if (stateNode != NULL) {
                    stateNode->state = isInitial;
                } else {
                    if (isInitial) {
                        listOfState* newState = createState(state);
                        addState(&(automaton->initialStates), newState);
                    }
                }
            }
        }
        void changeCells(Automaton* automaton) {
            int fromState, eventIndex, toState, newValue;
            printf("Enter the state, event index, target state, and new value (0 to stop): ");
            while (1) {
                scanf("%d %d %d %d", &fromState, &eventIndex, &toState, &newValue);
                if (fromState == 0) break;
                if (fromState < automaton->numberOfStates && eventIndex < automaton->numberOfEvents) {
                    automaton->Matrix[fromState][eventIndex]->state = newValue;
                } else {
                    printf("Invalid indices!\n");
                }
            }
        }

        //Creation in Automaton
        void createStateInAutomaton(Automaton* automaton) {
            int stateNumber;
            printf("Enter new state number: ");
            scanf("%d", &stateNumber);

            listOfState* newState = createState(stateNumber);
            addState(&(automaton->numberOfStates), newState);
        }
        void createEventInAutomaton(Automaton* automaton) {
            char eventChar;
            printf("Enter new event character: ");
            scanf(" %c", &eventChar);

            listOfEvents* newEvent = createEvent(eventChar);
            addEvent(&(automaton->events), newEvent);
        }

        //Suppression in Automaton
        void deleteAutomaton(Automaton* automaton) {
            if (!automaton) return;

            // Free the matrix of transitions
            for (int i = 0; i < automaton->numberOfStates; ++i) {
                for (int j = 0; j < automaton->numberOfEvents; ++j) {
                    freeState(automaton->Matrix[i][j]);
                }
                free(automaton->Matrix[i]);
            }
            free(automaton->Matrix);

            // Free other elements
            freeState(automaton->finalStates);
            freeState(automaton->initialStates);
            freeEvent(automaton->events);

            free(automaton);
        }
        void deleteStateInAutomaton(Automaton* automaton) {
            int stateNumber;
            printf("Enter state number to delete: ");
            scanf("%d", &stateNumber);

            deleteState(automaton->finalStates, stateNumber);
            deleteState(automaton->initialStates, stateNumber);

            // Remove from matrix
            for (int i = 0; i < automaton->numberOfEvents; ++i) {
                deleteState(automaton->Matrix[stateNumber][i], stateNumber);
            }
        }
        void deleteEventInAutomaton(Automaton* automaton) {
            char eventChar;
            printf("Enter event character to delete: ");
            scanf(" %c", &eventChar);

            deleteEvent(automaton->events, eventChar);

            // Remove from matrix
            for (int i = 0; i < automaton->numberOfStates; ++i) {
                for (int j = 0; j < automaton->numberOfEvents; ++j) {
                    if (automaton->events[j].event == eventChar) {
                        freeState(automaton->Matrix[i][j]);
                        automaton->Matrix[i][j] = NULL;  // Set to NULL to avoid dangling pointers
                    }
                }
            }
        }



        




#endif 