#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "automate.h"
#include "automateCreation.h"

void afficheMenu(){
    printf("\n\t Menu\n\n");
    printf("\n1\tSaisir un AEF");
    printf("\n2\tImporter un AEF à partir d'un fichier");
    printf("\n3\tModifier un AEF");
    printf("\n4\tSauvegarder un AEF sur un fichier");
    printf("\n5\tSupprimer un AEF");
    printf("\n6\tReconnaître un mot");
    printf("\n7\tVérifier si un AEF est complet");
    printf("\n8\tRendre un AEF complet");
    printf("\n9\tVérifier si un AEF est deterministe");
    printf("\n10\tRendre un AEF deterministe");
    printf("\n11\tComplément d'un AEF");
    printf("\n12\tMirroir d'un AEF");
    printf("\n13\tProduit de deux AEF");
    printf("\n14\tConcaténation de deux AEF");
    printf("\n0\tQuitter\n");
}


int main(){
    Automaton* listOfAutomaton ;
    printf("Bienvenue !\n");
    int choix=0;
    do{
        


        printf("Choix : ");
        scanf("%d", &choix);
        
        switch(choix){
            
            case 1:
                
                inputAutomaton(listOfAutomaton);
                break;
            
            case 2:
                printf("\n\tImporter un AEF à partir d'un fichier\n");
                break;
            
            case 3:
                printf("\n\tModifier un AEF\n");
                break;
            
            case 4:
                printf("\n\tSauvegarder un AEF sur un fichier\n");
                break;

            case 5:
                printf("\n\tSupprimer un AEF\n");
                break;

            case 6:
                printf("\n\tReconnaître un mot\n");
                break;

            case 7:
                printf("\n\tVérifier si un AEF est complet\n");
                break;

            case 8:
                printf("\n\tRendre un AEF complet\n");
                break;

            case 9:
                printf("\n\tVérifier si un AEF est deterministe\n");
                break;

            case 10:
                printf("\n\tRendre un AEF deterministe\n");
                break;

            case 11:
                printf("\n\tComplément d'un AEF\n");
                break;

                case 12:
                printf("\n\tMirroir d'un AEF\n");
                break;

            case 13:
                printf("\n\tProduit de deux AEF\n");
                break;
            
            case 14:
                printf("\n\tConcaténation de deux AEF\n");
                break;
            case 0:
                printf("\n\tAu revoir !\n");
                break;
            

                default:
                    printf("\nChoix incorrect\n");
            

        }


    }while(choix!=0);

    return EXIT_SUCCESS;


}