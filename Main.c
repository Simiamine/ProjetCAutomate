#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "automate.h"

int allocPB = 0;


void afficheMenu(){
    printf("\n\t Menu\n\n");
    printf("\n1\tSaisir un AEF");
    printf("\n2\tModifier ou supprimer un AEF"); 
    printf("\n3\tImporter un AEF a partir d'un fichier");
    printf("\n4\tSauvegarder un AEF sur un fichier");
    printf("\n5\tMot, Complet et deterministe");
    printf("\n6\tOperation sur un AEF");
    printf("\n0\tQuitter\n");
}

void afficheMenuAjouter(){
    
    printf("\n1\tAjouter un etat");
    printf("\n2\tAjouter un etat initial");
    printf("\n3\tAjouter un etat final");
    printf("\n4\tAjouter une transition");
    printf("\n5\tAjouter un evenement");
    printf("\n0\tRevenir en arriere\n");
}

void ajout(){
    int choix2;
    do{                    
        choix2=100;
        afficheMenuAjouter();
        printf("Choix : ");
        scanf("%d", &choix2);
        switch(choix2){
            case 1:
                printf("Fonction non fini");
                break;
            case 2:
                printf("Fonction non fini");
                break;
            case 3:
                printf("Fonction non fini");
                break;
            case 4:
                printf("Fonction non fini");
                break;
            case 5:
                printf("Fonction non fini");
                break;
            case 0 :
                break;
            default:
                printf("\nChoix incorrect\n");
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
        }
        


    }while((choix2!=0)&(!allocPB));
}


void afficheMenuSupprimer(){
    
    printf("\n1\tSupprimer un etat");
    printf("\n2\tSupprimer un etat initial");
    printf("\n3\tSupprimer un etat final");
    printf("\n4\tSupprimer une transition");
    printf("\n5\tSupprimer un evenement");
    printf("\n0\tRevenir en arriere\n");
}


void supprimer(){
    int choix2;
    do{                    
        choix2=100;
        afficheMenuSupprimer();
        printf("Choix : ");
        scanf("%d", &choix2);
        switch(choix2){
            case 1:
                printf("Fonction non fini");
                break;
            case 2:
                printf("Fonction non fini");
                break;
            case 3:
                printf("Fonction non fini");
                break;
            case 4:
                printf("Fonction non fini");
                break;
            case 5:
                printf("Fonction non fini");
                break;
            case 0 :
                break;
            default:
                printf("\nChoix incorrect\n");
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
        }
        


    }while((choix2!=0)&(!allocPB));

}

void afficheMenuMCD(){
    
    printf("\n1\tReconnaitre un mot");
    printf("\n2\tVerifier s'il est deterministe "); 
    printf("\n3\tVerifier s'il est complet");
    printf("\n4\tRendre deterministe");
    printf("\n5\tRendre complet");
}

void afficheMenuOper(){
    
    printf("\n1\tComplement");
    printf("\n2\tMiroir"); 
    printf("\n3\tConcatenation");
    printf("\n4\tProduit");
}


int main(){
    
    printf("Bienvenue !\n");
    int choix;
    Automate* automate = NULL;
    
    do{
        afficheMenu();
        choix=100;

        printf("Choix : ");
        scanf("%d", &choix); 
        
        switch(choix){
            
            case 1:
                
                automate = saisirAutomate();
                break;
            
            case 2: 
                int choix1;
                do{
                    choix1=100;
                    printf("\n\t1-Ajouter\n");
                    printf("\n\t2-Supprimer\n");
                    printf("\n\t0-Revenir en arriere\n");
                    printf("Choix : ");
                    scanf("%d", &choix1); 
                    switch(choix1){
                        case 1:
                            ajout();
                            break;
                        case 2:
                            supprimer();
                            break;
                        case 0 :
                            break;
                        default :
                            printf("\nChoix incorrect\n");
                            int c;
                            while ((c = getchar()) != '\n' && c != EOF);
                    }
                
                }while((choix1!=0)&(!allocPB));
                break;
            
            case 3:
                if (automate != NULL) {
                    freeAutomate(automate);
                }
                automate = chargerAutomate();
                break;
            
            case 4:
                if (automate != NULL) {
                    enregistrerAutomate(automate);
                } else {
                    printf("Erreur : aucun automate cree\n");
                }
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
        // vider le tampon d'entree
        int c;
        
        while ((c = getchar()) != '\n' && c != EOF);


    }while((choix!=0)&(!allocPB));

    return EXIT_SUCCESS;


}