#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include "automate.h"


/**
 * Function to gather all the basic information to create the automaton
 * input : NONE
 * output : NONE
**/
void inputAutomaton(Automaton* listOfautomaton){
    printf("\nNous allons proceder a la creation d'un automate.");
    
    
    Automaton* newAutomaton = createAutomaton();
    
    

    // ajout d'information 
    if (newAutomaton){
        initiateAutomaton(newAutomaton);
        
    }
    

}
Automaton* createAutomaton(){

    // creation d'un automate
    Automaton * newAutomate=NULL;
    newAutomate=(Automaton*)malloc(sizeof(Automaton)*1);

    
    

	if(newAutomate){ // si la case a ete bien alloué
		newAutomate->numberOfStates=0;
        newAutomate->numberOfEvents=0;
        newAutomate->Matrix=NULL;
        newAutomate->finalStates=NULL;
        newAutomate->initialStates=NULL;
        newAutomate->events=NULL;
        
        newAutomate->nextAutomaton=NULL;
	}
	else{
		printf("\npb allocation lors de la creation d'un automate");
        allocPB=1;
	}

    return newAutomate;
}


void initiateAutomaton(Automaton* newAutomaton){

    printf("\nNombre d'etat : ");
    scanf("%d",&(newAutomaton->numberOfStates));


    printf("\nNombre d'evenement : ");
    scanf("%d",&(newAutomaton->numberOfEvents));

    int nbInitialState;
    do{
        
        printf("Nombre d'etat initiaux (Attention doit etre >%d): ", newAutomaton->numberOfStates+1);
        scanf("%d",&nbInitialState );
        
    }while (nbInitialState>newAutomaton->numberOfStates); // est ce qu'on peut avoir autant d'etat que d'etat initiaux ?

    for( int i=0; i+1<newAutomaton->numberOfStates; i++){
        int idState;
        printf("%d) Numero de l'etat initial : ", i+1); // controle à faire 
        scanf("%d", &idState);
        listOfState* newState = createState(idState);
        
        addState(&newAutomaton->initialStates,newState);

    }
    
    
    
    
    displayStates(newAutomaton->initialStates);
    
    
    

    
    


}

/*
void navigateAutomaton(Automaton){


}
listOfState enterCellsMatrix(int, int){


}
void interpreteMatrix(Automaton){


}
*/