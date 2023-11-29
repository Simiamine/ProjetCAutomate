#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#define AUTOMATE
#include "automate.h"


/**
 * Function to gather all the basic information to create the automaton
 * input : NONE
 * output : NONE
**/
void inputAutomaton(Automaton* listOfautomaton){
    printf("\nNous allons procéder à la création d'un automate.");
    
    Automaton * newAutomate;
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
		printf("\npb allocation");
	}

    printf("\nNombre d'état :");
    scanf("%d",newAutomate->numberOfStates);
    printf("\nNombre d'évenement :");
    scanf("%d",newAutomate->numberOfEvents);

    


}
void createAutomaton(){


}
/*

Automaton initiateAutomaton(int, int){


}
void navigateAutomaton(Automaton){


}
listOfState enterCellsMatrix(int, int){


}
void interpreteMatrix(Automaton){


}
*/