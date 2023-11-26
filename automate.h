#include <stdio.h>
#ifndef AUTOMATE_H_
		#ifndef AUTOMATE
	#define AUTOMATE_H_
			#define WHERE_AUTOMATE extern
		#else
		#endif
			#define WHERE_AUTOMATE

		typedef struct {
            int numberOfStates;       // Number of states in the automaton
            int numberOfEvents;       // Number of events in the automaton
            listOfState** Matrix;  // Dynamic matrix line=states and colomn=events
            int* finalStates;         // list of final states PK NE PAS METTRE LISTOFSTATE ICI PUISQUE QUE LE TAILLE DE CETTE LISTE PEUT VARIER
            int* initialStates;  // list of initial states MEME REMARQUE ICI
            listOfEvents* events; // list of events
            
        } Automaton;

        typedef struct { 
            int state;
            listOfState* next;
        } listOfState; // linked list of states

        typedef struct {
            char event;
            listOfEvents* next;
        } listOfEvents; // linked list of events


        // Automaton creation
		WHERE_AUTOMATE void inputAutomaton();
        WHERE_AUTOMATE void createAutomaton();
        WHERE_AUTOMATE Automaton initiateAutomaton(int, int);
        WHERE_AUTOMATE void navigateAutomaton(Automaton);
        WHERE_AUTOMATE listOfState enterCellsMatrix(int, int); 
        WHERE_AUTOMATE void interpreteMatrix(Automaton);

        //Automaton in files
        WHERE_AUTOMATE void serialization(Automaton*, FILE*);
        WHERE_AUTOMATE void deserialization(Automaton);

        //Modification in Automaton
        WHERE_AUTOMATE void changeFinalStates(Automaton);
        WHERE_AUTOMATE void changeInitialStates(Automaton);
        WHERE_AUTOMATE void changeCells(Automaton);

        //Creation in Automaton
        WHERE_AUTOMATE void createState(Automaton);
        WHERE_AUTOMATE void createEvent(Automaton);

        //Suppression in Automaton
        WHERE_AUTOMATE void deleteAutomaton(Automaton);
        WHERE_AUTOMATE void deleteState(Automaton);
        WHERE_AUTOMATE void deleteEvent(Automaton);



        




#endif 