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

    navigateAutomaton(newAutomaton);
    


}


void initiateInitialStates(Automaton* newAutomaton){
    int nbInitialState;
    do{
        
        printf("Nombre d'etat initiaux (Attention doit etre <%d et >0): ", newAutomaton->numberOfStates+1);
        scanf("%d",&nbInitialState );
        
    }while((nbInitialState>newAutomaton->numberOfStates)||(nbInitialState<=0)); // est ce qu'on peut avoir autant d'etat que d'etat initiaux ? + resoudre le probeleme de si le mec rentre des lettres

    for( int i=0; i<nbInitialState; i++){
        createIntitialState(newAutomaton,i);
    }
    
    
}

void createIntitialState(Automaton* newAutomaton, int i ){
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

void initiateFinalState(Automaton *new){
    int nbFinalState;
    do{
        
        printf("\nNombre d'etat finaux (Attention doit etre <%d et >0): ", new->numberOfStates+1);
        scanf("%d",&nbFinalState );
        
    }while((nbFinalState>new->numberOfStates)||(nbFinalState<=0)); // est ce qu'on peut avoir autant d'etat que d'etat initiaux ?

    for( int i=0; i<nbFinalState; i++){
        createFinalState(new, i);

    }
}

void createFinalState(Automaton* new, int i){
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

void initiateEvents(Automaton* new ){
    printf("\tRappel %d evenement(s) a creer",new->numberOfEvents );
    for(int i=0; i<new->numberOfEvents;i++){
        createNewEvent(new, i);
    }
}

void createNewEvent(Automaton* new, int i){
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



void navigateAutomaton(Automaton* new){
    createMatrix(new);
    for(int state=0 ; (state<new->numberOfStates) ; state++ ){
        for(int event=0; event<new->numberOfEvents;event++){
            new->Matrix[state][event]=enterCellsMatrix(state, &(new->events[event]), new->numberOfStates);
        }
        
    }
    


}

void createMatrix(Automaton* new ){
    listOfState*** newMatrix= (listOfState***)malloc(new->numberOfStates*sizeof(listOfState**));
    if(newMatrix){
        
        for(int i =0; i<new->numberOfStates;i++){
            newMatrix[i]=(listOfState**)malloc(new->numberOfEvents * sizeof(listOfState*));
            for(int j=0;j<new->numberOfEvents;j++){
                newMatrix[i][j]=(listOfState*)malloc(sizeof(listOfState));

            }
        }
        new->Matrix=newMatrix;
    }else{
        allocPB=1;
    }
}


listOfState* enterCellsMatrix(int state , listOfEvents* event, int totalNbState){
    listOfState* newList =  NULL;
    for (int i= 0; i<totalNbState;i++ ){
        
        int rep;
        int pb =0;
        do{
            pb=0;
            printf("Si l'etat %d va vers l'etat %d par l'evenement %c, rentrer 1 sinon 0\nReponse : ", state, i,event->event);
            scanf("%d",&rep);
            if((rep!=0)&&(rep!=1)){
                printf("Erreur rentrer 1 ou 0.\n");
                pb=1;
            }
        }while(pb);
        
        listOfState* new = createState(rep);
        addState(&newList,new);

        
    }

    return newList;

}

/*
void interpreteMatrix(Automaton){


}
*/