#include "arbrebin.h"
#include <stdio.h>
#include <stdlib.h>

/* implementation des operateurs de l'Arbre binaire */

/***************************************
 * ArbreVide                           *
 * parametres : aucun                  *
 * resultat : un Arbre                 *
 * description : renvoie un arbre vide *
 * effet de bord :aucun                *
 ***************************************/
Arbre ArbreVide() { return NULL; }

/**********************************************************************
 * NouveauNoeud                                                       *
 * parametres : les donnees : un Arbre g, un caractere c, un Arbre d  *
 * resultat : un Arbre                                                *
 * description : renvoie un nouvel Arbre dont la racine est etiquetee *
 * par c, de fils gauche g et de fils droit d                         *
 * effet de bord : une nouvelle cellule est allouee                   *
 **********************************************************************/
Arbre NouveauNoeud(Arbre g, int c, Arbre d) {
    Arbre a = (Arbre)malloc(sizeof(struct cellule));

    a->etiq = c;
    a->fg = g;
    a->fd = d;

    return a;
}

/********************************************
 * EstVide                                  *
 * parametres : un Arbre a                  *
 * resultat : un booleen                    *
 * description : renvoie vrai si a est vide *
 * effet de bord : aucun                    *
 ********************************************/
int EstVide(Arbre a) { return (a == NULL); }

/******************************************
 * Etiq                                   *
 * parametres : un Arbre a                *
 * precondition : a non vide              *
 * resultat : un int                      *
 * description : renvoie l'etiquette de a *
 * effet de bord : aucun                  *
 ******************************************/
int Etiq(Arbre a) { return a->etiq; }

/*********************************************
 * FilsGauche                                *
 * parametres : un Arbre a                   *
 * precondition : a non vide                 *
 * resultat : un arbre                       *
 * description : renvoie le fils gauche de a *
 * effet de bord : aucun                     *
 *********************************************/
Arbre FilsGauche(Arbre a) { return a->fg; }

/********************************************
 * FilsDroit                                *
 * parametres : un Arbre a                  *
 * precondition : a non vide                *
 * resultat : un arbre                      *
 * description : renvoie le fils droit de a *
 * effet de bord : aucun                    *
 ********************************************/
Arbre FilsDroit(Arbre a) { return a->fd; }

/********************************************
 * LibererArbre                             *
 * parametres : un Arbre a                  *
 * resultat : aucun                         *
 * description : libere l'arbre a           *
 * effet de bord : a est detruit            *
 ********************************************/
void LibererArbre(Arbre a) {
    if (!EstVide(a)) {
        LibererArbre(FilsGauche(a));
        LibererArbre(FilsDroit(a));
        free(a);
    }
}

/*********************************************************************
 * AfficherArbre                                                     *
 * parametres : un arbre a                                           *
 * resultat : aucun                                                  *
 * description : affiche l'arbre a sur la sortie standard            *
 * effet de bord : un arbre est affiche                              *
 *********************************************************************/
void afficher_arbre_r(Arbre a, int niveau) {
  if (a != NULL) {
    afficher_arbre_r(a->fd,niveau+1) ;
    for (int i = 0; i < niveau; i++) {
      printf("\t") ;
    }
    printf(" %d (%d)\n\n", Etiq(a), niveau) ;
    afficher_arbre_r(a->fg, niveau+1) ;
  }
  return ;
}

void AfficherArbre(Arbre a) { afficher_arbre_r(a, 0); }
