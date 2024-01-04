#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>
#include "automate.h"



/**
 * enregistrer l'automate dans un fichier .json en demandant a l'utilisateur le nom du fichier et en verifiant si le fichier existe deja ou pas
 * input : un automate 
 * output : rien
**/
void enregistrerAutomate(Automate* automate) {
    char nomFichier[100];
    printf("Quel est le nom du fichier ?\n");
    scanf("%s", nomFichier);
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier != NULL) {
        printf("Erreur : le fichier existe deja\n");
        fclose(fichier);
    } else {
        fichier = fopen(nomFichier, "w");
        fprintf(fichier, "{\n");
        fprintf(fichier, "\t\"nombreEtats\" : %d,\n", automate->nombreEtats);
        fprintf(fichier, "\t\"nombreEvent\" : %d,\n", automate->nombreEvent);
        fprintf(fichier, "\t\"listeEvent\" : [\n");
        for (int i = 0; i < automate->nombreEvent; i++) {
            fprintf(fichier, "\t\t\"%c\"", automate->listeEvent[i]);
            if (i < automate->nombreEvent - 1) {
                fprintf(fichier, ",");
            }
            fprintf(fichier, "\n");
        }
        fprintf(fichier, "\t],\n");
        fprintf(fichier, "\t\"etatsInitiaux\" : [\n");
        for (int i = 0; i < automate->nombreEtats; i++) {
            fprintf(fichier, "\t\t%d", automate->etatsInitiaux[i]);
            if (i < automate->nombreEtats - 1) {
                fprintf(fichier, ",");
            }
            fprintf(fichier, "\n");
        }
        fprintf(fichier, "\t],\n");
        fprintf(fichier, "\t\"etatsFinaux\" : [\n");
        for (int i = 0; i < automate->nombreEtats; i++) {
            fprintf(fichier, "\t\t%d", automate->etatsFinaux[i]);
            if (i < automate->nombreEtats - 1) {
                fprintf(fichier, ",");
            }
            fprintf(fichier, "\n");
        }
        fprintf(fichier, "\t],\n");
        fprintf(fichier, "\t\"matriceTransition\" : [\n");
        for (int i = 0; i < automate->nombreEtats; i++) {
            fprintf(fichier, "\t\t[\n");
            for (int j = 0; j < automate->nombreEvent; j++) {
                fprintf(fichier, "\t\t\t[");
                for (int k = 0; k < automate->nombreEtats; k++) {
                    fprintf(fichier, "%d", automate->matriceTransition[i][j][k]);
                    if (k < automate->nombreEtats - 1) {
                        fprintf(fichier, ",");
                    }
                }
                fprintf(fichier, "]");
                if (j < automate->nombreEvent - 1) {
                    fprintf(fichier, ",");
                }
                fprintf(fichier, "\n");
            }
            fprintf(fichier, "\t\t]");
            if (i < automate->nombreEtats - 1) {
                fprintf(fichier, ",");
            }
            fprintf(fichier, "\n");
        }
        fprintf(fichier, "\t]\n");
        fprintf(fichier, "}");
        fclose(fichier);
    }
}




//   
/**
 * charger un automate a partir d'un fichier .json en demandant a l'utilisateur le nom du fichier et en verifiant si le fichier existe ou pas
 * input : rien 
 * output : un automate
**/
Automate* chargerAutomate() {
    char nomFichier[100];
    printf("Quel est le nom du fichier ?\n");
    scanf("%s", nomFichier);
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Erreur : le fichier n'existe pas\n");
        return NULL;
    } else {
        int nombreEtats, nombreEvent;
        fscanf(fichier, "{\n");
        fscanf(fichier, "\t\"nombreEtats\" : %d,\n", &nombreEtats);
        fscanf(fichier, "\t\"nombreEvent\" : %d,\n", &nombreEvent);
        fscanf(fichier, "\t\"listeEvent\" : [\n");
        char* listeEvent = calloc(nombreEvent, sizeof(char));
        for (int i = 0; i < nombreEvent; i++) {
            fscanf(fichier, "\t\t\"%c\"", &(listeEvent[i]));
            if (i < nombreEvent - 1) {
                fscanf(fichier, ",");
            }
            fscanf(fichier, "\n");
        }
        fscanf(fichier, "\t],\n");
        fscanf(fichier, "\t\"etatsInitiaux\" : [\n");
        int* etatsInitiaux = calloc(nombreEtats, sizeof(int));
        for (int i = 0; i < nombreEtats; i++) {
            fscanf(fichier, "\t\t%d", &(etatsInitiaux[i]));
            if (i < nombreEtats - 1) {
                fscanf(fichier, ",");
            }
            fscanf(fichier, "\n");
        }
        fscanf(fichier, "\t],\n");
        fscanf(fichier, "\t\"etatsFinaux\" : [\n");
        int* etatsFinaux = calloc(nombreEtats, sizeof(int));
        for (int i = 0; i < nombreEtats; i++) {
            fscanf(fichier, "\t\t%d", &(etatsFinaux[i]));
            if (i < nombreEtats - 1) {
                fscanf(fichier, ",");
            }
            fscanf(fichier, "\n");
        }
        fscanf(fichier, "\t],\n");
        fscanf(fichier, "\t\"matriceTransition\" : [\n");
        int*** matriceTransition = malloc(sizeof(int**) * nombreEtats);
        for (int i = 0; i < nombreEtats; i++) {
            matriceTransition[i] = malloc(sizeof(int*) * nombreEvent);
            fscanf(fichier, "\t\t[\n");
            for (int j = 0; j < nombreEvent; j++) {
                matriceTransition[i][j] = calloc(nombreEtats, sizeof(int));
                fscanf(fichier, "\t\t\t[");
                for (int k = 0; k < nombreEtats; k++) {
                    fscanf(fichier, "%d", &(matriceTransition[i][j][k]));
                    if (k < nombreEtats - 1) {
                        fscanf(fichier, ",");
                    }
                }
                fscanf(fichier, "]");
                if (j < nombreEvent - 1) {
                    fscanf(fichier, ",");
                }
                fscanf(fichier, "\n");
            }
            fscanf(fichier, "\t\t]");
            if (i < nombreEtats - 1) {
                fscanf(fichier, ",");
            }
            fscanf(fichier, "\n");
        }
        fscanf(fichier, "\t]\n");
        fscanf(fichier, "}");
        fclose(fichier);
    //l'automate a ete charge
        Automate* automate = initAutomate(nombreEtats, nombreEvent);
        automate->listeEvent = listeEvent;
        automate->etatsInitiaux = etatsInitiaux;
        automate->etatsFinaux = etatsFinaux;
        automate->matriceTransition = matriceTransition;

        //message de reussite
        printf("L'automate a ete charge avec succes\n");

        return automate;

    }
}