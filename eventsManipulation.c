#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include "automate.h"

listOfEvents* createEvent(char idEvent){
    listOfEvents * newEvent;
    newEvent=(listOfEvents*)malloc(sizeof(listOfEvents)*1);

    if(newEvent){
        newEvent->event=idEvent;
        newEvent->next=NULL;
    }
    else{
        printf("probleme d'allocation lors de la creation d'un etat");
        allocPB=1;
    }

    return newEvent;
}


void addEvent(listOfEvents** list, listOfEvents* new){
    
    if(*list==NULL){ // first state
        *list=new;
        
    }

    else if ((*list)->next==NULL) // end of the list
    {
        (*list)->next=new;
    }
    
    else { 
        addEvent(&(*list)->next, new );
    }

}


void displayEvents(listOfEvents* list){
    
    while(list!=NULL){
        
        printf("\nNom de l'evenement : %c\n", list->event);
        list=list->next;
        
    }

}

void deleteEvent(listOfEvents* list, char idEvent){ 


}


listOfEvents* searchEvent(listOfEvents* list, char id){
    while(list!=NULL){
        if(list->event==id){
            return list;
        }
        list=list->next;
    }

    return NULL;


}


void freeEvent(listOfEvents*){



}