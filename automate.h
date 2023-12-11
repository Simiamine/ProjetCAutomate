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
        Automate* initAutomate(int , int);
        Automate* remplirAEF(Automate* );
        Automate* saisirAutomate();
        int verifieEntree(int , int, int );
        void remplirEvenement(Automate* );
        int rechercheEvenement(char , int , char* );
        void afficherAEF(Automate* );
        void freeAutomate(Automate* );

        //Modification d'automate
        void ajouterEtat(Automate* , char );
        void ajouterEvent(Automate* , char );
        int trouverindiceEvent(Automate* , char );
        void modifierTransition(Automate* , int , int , char );
        void transition(Automate* , int , int , char ); // utilise nulle part 
        void ajouterEtatInitial(Automate* , int );
        void ajouterEtatFinal(Automate* , int );
        void ModifierAutomate(Automate* );


        //Manipulation de fichier json
        void enregistrerAutomate(Automate* );
        Automate* chargerAutomate();


        // operation 
        Automate* unionAutomate(Automate* , Automate* );//jcp ce que c'est ni ou le mettre

        // Mot, complet, deterministe
        bool motValide(Automate* automate, char* mot);
        bool estDeterministe(Automate* automate);
        bool estComplet(Automate* automate);
        Automate* rendreDeterministe(Automate* automate);
        void operationsAutomate();

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