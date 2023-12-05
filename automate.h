#include <stdio.h>
#ifndef AUTOMATE_H_
		#ifndef AUTOMATE
	#define AUTOMATE_H_
			#define WHERE_AUTOMATE extern
		#else
		#endif
			#define WHERE_AUTOMATE

    typedef struct {
        int nombreEtats;           // Nombre d'états dans l'automate
        int nombreEvent;      // Nombre d'événements dans l'automate
        int*** matriceTransition;  // Matrice dynamique contenant les transitions : matriceTransition[etat][event][etatsliés] avec etat liés = 1 si lié et 0 sinon
        int* etatsFinaux;          // Tableau d'entiers de taille nbEtats : 1 si final et 0 sinon
        int* etatsInitiaux;           //  Tableau d'entiers de taille nbEtats : 1 si initial et 0 sinon
        char* listeEvent; // Liste des événements : listeEvent[event] = lettre de l'événement à l'indice event
    } Automaton;

        // Automaton creation
		WHERE_AUTOMATE void inputAutomaton();
        WHERE_AUTOMATE void createAutomaton();
        WHERE_AUTOMATE Automaton initiateAutomaton(int, int);
        WHERE_AUTOMATE void navigateAutomaton(Automaton);
        WHERE_AUTOMATE int* enterCellsMatrix(int, int); 
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