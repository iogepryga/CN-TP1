#include <stdio.h>
#include <stdlib.h>

#include "math.h"
#include "arbrebin.h"
#include "fap.h"

typedef struct {
    int lg;
    float p;
    int code[256];
} code_char;

code_char HuffmanCode[256];

Arbre ConstruireArbre(fap f) {
    while(!est_fap_vide(f)) {
        Arbre b,c;
        float bb,cc;
        f = extraire(f,&b,&bb);
        if(est_fap_vide(f))
            return b;
        f = extraire(f,&c,&cc);
        printf("<---------------------------->\nOn prend : \n");
        AfficherArbre(b);
        printf("-- et :\n");
        AfficherArbre(c);
        printf("----- et on obtient :\n");
        Arbre a = NouveauNoeud(b,-1,c);
        AfficherArbre(a);
        printf("<---------------------------->\n");
        if(est_fap_vide(f))
            return a;
        f = inserer(f,a,bb+cc);
    }
    return ArbreVide();
}

void Parcourir_profondeur(Arbre a, code_char c) {
    if(a != NULL) {
        if(Etiq(a) == -1) {
            c.code[c.lg] = 0; c.lg++;
            Parcourir_profondeur(FilsGauche(a),c); c.lg--;
            c.code[c.lg] = 1; c.lg++;
            Parcourir_profondeur(FilsDroit(a),c);
        } else {
            HuffmanCode[Etiq(a)].lg = c.lg;
            for(int i = 0 ; i < c.lg; i++ )
                HuffmanCode[Etiq(a)].code[i] = c.code[i];
        }
    }
}

void Construire_Code(Arbre huff) {
    code_char a; a.lg = 0;
    Parcourir_profondeur(huff,a);
}

int main (int argc, char**argv) {
    if(argc != 2) {printf("pas ou trop d'argument\n");return -1;}
    FILE *file ;
    int i;
    float ftmp1, ftmp2 , entropie = 0, moyenne = 0;
    Arbre atmp1;
    fap f = creer_fap_vide();

    file = fopen (argv[1], "r") ;
    for (i = 0; fscanf (file, "%f", &ftmp1) != EOF; i++) {
        entropie += ftmp1 * log2(ftmp1);
        atmp1 = NouveauNoeud(NULL,i,NULL);
        f = inserer(f,atmp1,ftmp1);
        HuffmanCode[i].p = ftmp1;
    }
    entropie = -1 * entropie;



    fap faptmp = creer_fap_vide();
    while(!est_fap_vide(f)) {
        f = extraire(f,&atmp1,&ftmp1);
        printf("Feuille d'evenement %d avec la probalibité %f :\n",atmp1->etiq,ftmp1);
        AfficherArbre(atmp1);
        faptmp = inserer(faptmp,atmp1,ftmp1);
    }
    /*while(!est_fap_vide(faptmp)) {
        faptmp = extraire(faptmp,&atmp1,&ftmp1);
        f = inserer(f,atmp1,ftmp1);
    }*/


    Arbre arbre = ConstruireArbre(faptmp);
    printf("||||||||||||||||||||||||||||||||||||||||\n            Arbre final :\n");
    AfficherArbre(arbre);
    printf("||||||||||||||||||||||||||||||||||||||||\n            Codage final :\n");
    Construire_Code(arbre);
    printf("Event\tCode\tLongueur\n");
    for(int j = 0; j < i ; j++) {
        printf("%d\t",j);
        for(int k = 0; k < HuffmanCode[j].lg; k++){
            printf("%d",HuffmanCode[j].code[k]);
        }
        printf("\t%d\n", HuffmanCode[j].lg);
        moyenne += HuffmanCode[j].lg*HuffmanCode[j].p;
    }
    printf("Entropie : %f\n",entropie);
    printf("Longueur moyenne : %f\n",moyenne);
    // detruire_fap(faptmp);
    // detruire_fap(f);
    fclose (file) ;
}