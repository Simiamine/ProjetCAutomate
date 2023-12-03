#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include "automate.h"

listOfState* createState(int stateId){
    listOfState * newState;
    newState=(listOfState*)malloc(sizeof(listOfState)*1);

    if(newState){
        newState->state=stateId;
        newState->next=NULL;
    }
    else{
        printf("probleme d'allocation lors de la creation d'un etat");
        allocPB=1;
    }

    return newState;
}


void addState(listOfState** list, listOfState* new){
    
    if(*list==NULL){ // first state
        *list=new;
        
    }

    else if ((*list)->next==NULL) // end of the list
    {
        (*list)->next=new;
    }
    
    else { 
        addState(&(*list)->next, new );
    }

}


void displayStates(listOfState* list){
    
    while(list!=NULL){
        
        printf("\nNumero de l'etat : %d", list->state);
        list=list->next;
        
    }

}

void deleteState(listOfState*, int ){ // attention faudra changer les id des autres aussi 



}


listOfState* searchstate(listOfState*, int){



}


void freeState(listOfState*){



}