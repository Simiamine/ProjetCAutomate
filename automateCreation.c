#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>
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

    // rajouter le cas ou ils se sont trompe dans l'entree comme ca ils ont pas a refaire

    initiateInitialStates(newAutomaton);
    printf("Voici la liste des etats initiaux");
    displayStates(newAutomaton->initialStates);


    initiateFinalState(newAutomaton);
    printf("Voici la liste des etats finaux");
    displayStates(newAutomaton->finalStates);

    initiateEvents(newAutomaton);
    printf("Voici la liste des evenements");
    displayEvents(newAutomaton->events);
    


}


void initiateInitialStates(Automaton* newAutomaton){
    int nbInitialState;
    do{
        
        printf("Nombre d'etat initiaux (Attention doit etre <%d et >0): ", newAutomaton->numberOfStates+1);
        scanf("%d",&nbInitialState );
        
    }while((nbInitialState>newAutomaton->numberOfStates)||(nbInitialState<=0)); // est ce qu'on peut avoir autant d'etat que d'etat initiaux ?

    for( int i=0; i<nbInitialState; i++){
        int idState;
        int pb=0;
        do{
            pb=0;
            printf("%d) Numero de l'etat initial : ", i+1); // verifier que le nb n'est pas deja dans la liste et qu'il est compris entre 0 et nb states-1
            scanf("%d", &idState);
            if(searchState(newAutomaton->initialStates, idState)!=NULL){
                printf("\nErreur l'etat est deja initial.\n");
                pb=1;
            }
            if(idState>=newAutomaton->numberOfStates){
                printf("\nErreur le numero est plus grand ou egal que le nombre d'etat.\n");
                pb=1;
            }

            if(idState<0){
                printf("\nErreur le numero est negative.\n");
                pb=1;
            }
        } while (pb);
        listOfState* newState = createState(idState);
        
        addState(&newAutomaton->initialStates,newState);

    }
    
    
}

void initiateFinalState(Automaton *new){
    int nbFinalState;
    do{
        
        printf("\nNombre d'etat finaux (Attention doit etre <%d et >0): ", new->numberOfStates+1);
        scanf("%d",&nbFinalState );
        
    }while((nbFinalState>new->numberOfStates)||(nbFinalState<=0)); // est ce qu'on peut avoir autant d'etat que d'etat initiaux ?

    for( int i=0; i<nbFinalState; i++){
        int idState;
        int pb=0;
        do{
            pb=0;
            printf("%d) Numero de l'etat final : ", i+1); // verifier que le nb n'est pas deja dans la liste et qu'il est compris entre 0 et nb states-1
            scanf("%d", &idState);
            if(searchState(new->finalStates, idState)!=NULL){
                printf("\nErreur l'etat est deja initial.\n");
                pb=1;
            }
            if(idState>=new->numberOfStates){
                printf("\nErreur le numero est plus grand ou egal que le nombre d'etat.\n");
                pb=1;
            }

            if(idState<0){
                printf("\nErreur le numero est negative.\n");
                pb=1;
            }
        } while (pb);
        listOfState* newState = createState(idState);
        
        addState(&new->finalStates,newState);

    }
}

void initiateEvents(Automaton* new ){
    for(int i=0; i<new->numberOfEvents;i++){
        char id;
        int pb;
        do{
            pb=0;
            
            printf("\nCaractere de l'evenement %d ( Attention ne prend que la premiere lettre): ", i+1);
            
            

            if (!(scanf(" %c", &id) == 1 && isalpha(id))) {
            printf("\nVeuillez rentrer une seule lettre.\n");
            pb = 1;
        }

            // Consommer le caractère de nouvelle ligne
            int c;
            while ((c = getchar()) != '\n' && c != EOF);

             if(searchEvent(new->events, id)!=NULL){
                printf("\nErreur le caractere est deja utilise.\n");
                pb=1;
            }
        }while(pb);
        listOfEvents* newEvent = createEvent(tolower(id));
        
        addEvent(&new->events,newEvent);
    }
}


/*
void navigateAutomaton(Automaton){


}
listOfState enterCellsMatrix(int, int){


}
void interpreteMatrix(Automaton){


}
*/