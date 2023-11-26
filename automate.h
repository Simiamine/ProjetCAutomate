#ifndef AUTOMATE_H
    #define AUTOMATE_H

		typedef struct { 
            int state;
            struct listOfState *next;
        } listOfState; // linked list of states

        typedef struct {
            char event;
            struct listOfEvents *next;
        } listOfEvents; // linked list of events
        
        
        
        
        typedef struct {
            int numberOfStates;       // Number of states in the automaton
            int numberOfEvents;       // Number of events in the automaton
            listOfState*** Matrix;  // Dynamic matrix line=states and colomn=events
            listOfState* finalStates;         // list of final states PK NE PAS METTRE LISTOFSTATE ICI PUISQUE QUE LE TAILLE DE CETTE LISTE PEUT VARIER
            listOfState* initialStates;  // list of initial states MEME REMARQUE ICI
            listOfEvents* events; // list of events
            struct Automaton* nextAutomaton; // A VOIR AVK LES AUTRES 
        } Automaton;

        

        


        // Automaton creation
		void inputAutomaton(Automaton*);
        void createAutomaton();
        Automaton initiateAutomaton(int, int);
        void navigateAutomaton(Automaton);
        listOfState enterCellsMatrix(int, int); 
        void interpreteMatrix(Automaton);

        //Automaton in files
        void serialization(Automaton);
        void deserialization(Automaton);

        //Modification in Automaton
        void changeFinalStates(Automaton);
        void changeInitialStates(Automaton);
        void changeCells(Automaton);

        //Creation in Automaton
        void createState(Automaton);
        void createEvent(Automaton);

        //Suppression in Automaton
        void deleteAutomaton(Automaton);
        void deleteState(Automaton);
        void deleteEvent(Automaton);



        




#endif 