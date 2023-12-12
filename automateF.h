#ifndef AUTOMATE_H
    #define AUTOMATE_H

		extern int allocPB;

        // Structure representant un automate
        typedef struct {
            int nombreEtats;           // Nombre d'états dans l'automate
            int nombreEvent;      // Nombre d'événements dans l'automate
            int*** matriceTransition;  // Matrice dynamique contenant les transitions : matriceTransition[etat][event][etatsliés] avec etat liés = 1 si lié et 0 sinon
            int* etatsFinaux;          // Tableau d'entiers de taille nbEtats : 1 si final et 0 sinon
            int* etatsInitiaux;           //  Tableau d'entiers de taille nbEtats : 1 si initial et 0 sinon
            char* listeEvent; // Liste des événements : listeEvent[event] = lettre de l'événement à l'indice event
        } Automate;

        // Automaton creation
        Automate* initAutomate(int , int); // initialise l'automate
        void remplirAEF(Automate* ); // remplie l'automate :  etat initiaux, finaux et matrice
        Automate* saisirAutomate(); // recupere les informations de base et execute les fonctions de creation d'automate
        int verifieEntree(int , int, int ); // utiliser pour controler les entrees de nombres positif
        void remplirEvenement(Automate* ); // remplie les evenements
        int rechercheEvenement(char , int , char* ); // recherche un evenement parmi ceux deja cree
        void afficherAEF(Automate* ); // sur le terminal 
        void freeAutomate(Automate* ); // supprime l'automate en cours d'utilisation

        //Modification d'automate
        void ajouterEtat(Automate* , char ); // PB AVK REALLOC pas besoin de caractere et initialise seulement remplie rien LYLIANNE
        void ajouterEvent(Automate* , char ); // PB AVK REALLOC idem initialise mais remplie pas 
        int trouverindiceEvent(Automate* , char ); // retourne indice de l'evenement ou -1 sinon  OK 
        void modifierTransition(Automate* , int , int , char ); // modifie cellule OK 
        
        void ajouterEtatInitial(Automate* , int ); // verifier que l'etat existe lylianne
        void ajouterEtatFinal(Automate* , int ); // verifier que l'etat existe LYLIANNE
        void ModifierAutomate(Automate* ); // tous les scanf a gerer + voir directement les commentaires


        //Manipulation de fichier json
        void enregistrerAutomate(Automate* ); // controle a faire sinon OK
        Automate* chargerAutomate();// controle a faire sinon OK


        // operation 
        Automate* unionAutomate(Automate* , Automate* );//jcp ce que c'est ni ou le mettre

        // Mot, complet, deterministe
        int motValide(Automate* automate, char* mot); // verif deter + pb etat intial 
        int estDeterministe(Automate* automate); // OK
        int estComplet(Automate* automate); // ok
        Automate* rendreDeterministe(Automate* automate); // a refaire 
        void operationsAutomate(); // manque rendre complet + voir commentaire

        // main et menu reste a voir ensemble
        void menu();
        int main();





        




/*

        

        //Automaton in files
        void serialization(Automaton);
        void deserialization(Automaton);

        //Modification in Automaton
        void changeFinalStates(Automaton);
        void changeInitialStates(Automaton);
        void changeCells(Automaton);

        

        //Suppression in Automaton
        void deleteAutomaton(Automaton);
        void deleteStateInAutomaton(Automaton);
        void deleteEventInAutomaton(Automaton);


*/
        




#endif 
