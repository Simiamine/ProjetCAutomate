#ifndef AUTOMATE_H
    #define AUTOMATE_H

		extern int allocPB;

        // Structure representant un automate
        typedef struct {
            int nombreEtats;           // Nombre d'états dans l'automate
            int nombreEvent;      // Nombre d'événements dans l'automate
            int*** matriceTransition;  // Matrice dynamique contenant les transitions : matriceTransition[etat][event][etatsliés] avec etat liés = 1 si lié et 0 sinon
            int* etatsFinaux;          // Tableau d'entiers de taille nbEtats : 1 si final et 0 sinon
            int* etatsInitiaux;           //  Tableau d'entiers de taille nbEtats : 1 si initial et 0 sinon
            char* listeEvent; // Liste des événements : listeEvent[event] = lettre de l'événement à l'indice event
        } Automate;

        // Automaton creation
        Automate* initAutomate(int , int);
        Automate* remplirAEF(Automate* );
        Automate* saisirAutomate();
        int verifieEntree(int , int, int );
        void remplirEvenement(Automate* );
        int rechercheEvenement(char , int , char* );
        




/*

        // Automaton creation
		void inputAutomaton(Automaton* );
        Automaton* createAutomaton();
        void initiateAutomaton(Automaton* );
        void navigateAutomaton(Automaton*);
        listOfState* enterCellsMatrix(int  , listOfEvents* , int ); 
        void interpreteMatrix(Automaton);
        void initiateInitialStates(Automaton*);
        void initiateEvents(Automaton* );
        void initiateFinalState(Automaton *);
        void createIntitialState(Automaton* , int  );
        void createFinalState(Automaton* , int );
        void createNewEvent(Automaton* , int );
        void createMatrix(Automaton*  );

        //Automaton in files
        void serialization(Automaton);
        void deserialization(Automaton);

        //Modification in Automaton
        void changeFinalStates(Automaton);
        void changeInitialStates(Automaton);
        void changeCells(Automaton);

        

        //Suppression in Automaton
        void deleteAutomaton(Automaton);
        void deleteStateInAutomaton(Automaton);
        void deleteEventInAutomaton(Automaton);


*/
        




#endif 