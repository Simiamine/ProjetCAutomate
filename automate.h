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
        int verifieEntree(int , int, int ); // utiliser pour controler les entrees de nombres positif
        Automate* saisirAutomate(); // recupere les informations de base et execute les fonctions de creation d'automate
        Automate* initAutomate(int , int); // initialise l'automate
        int rechercheEvenement(char , int , char* ); // recherche un evenement parmi ceux deja cree jusqu'à l'indice indiqué
        void remplirEvenement(Automate* ); 
        void remplirAEF(Automate* ); 
        void afficherAEF(Automate* ); 
        void freeAutomate(Automate* );  

        //Modification d'automate
        int* ajouterValeur(int* , int , int );
        void ajouterEtat(Automate * ); 
        void suppEtat(Automate* );
        void ajoutEvent(Automate* );  
        void suppEvent(Automate* );
        int trouverindiceEvent(Automate* , char ); // retourne indice de l'evenement ou -1 sinon   
        void ajoutTransition(Automate* ); 
        void suppTransition(Automate* ); 
        void transition(Automate* , int , int , char ); //NON UTILISE va dire si la transition existe ou pas 
        void ajouterEtatInitial(Automate*);
        void suppEtatInitial(Automate* ) ; 
        void ajouterEtatFinal(Automate* ); 
        void suppEtatFinal(Automate* ) ; 
        


        //Manipulation de fichier json
        void enregistrerAutomate(Automate* );  
        Automate* chargerAutomate(); 

        


        
        // Mot, complet, deterministe
        int motValide(Automate* automate, char* mot); // OK attendre rendre deter
        int estDeterministe(Automate* automate); 
        int estComplet(Automate* automate); 
        Automate* rendreDeterministe(Automate* automate); // En cours
        Automate* rendreComplet(Automate* automate); 

        //operation
        Automate* complementAEF(Automate* );
        Automate* mirroirAEF(Automate* );
        

        
        




#endif 
