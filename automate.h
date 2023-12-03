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
        void changeFinalStates(Automaton);
        void changeInitialStates(Automaton);
        void changeCells(Automaton);

        //Creation in Automaton
        void createStateInAutomaton(Automaton);
        void createEventInAutomaton(Automaton);

        //Suppression in Automaton
        void deleteAutomaton(Automaton);
        void deleteStateInAutomaton(Automaton);
        void deleteEventInAutomaton(Automaton);



        




#endif 