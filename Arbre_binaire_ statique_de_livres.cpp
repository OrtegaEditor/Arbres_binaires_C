#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct livre {
    int numero;
    char titre[15];
} livre;

typedef struct ARBRE {
    livre *tab;
    int taille;
} ARBRE;

static struct livre nul = {0, ""};

ARBRE *creer_arbre(int n) {
    int i;
    ARBRE *a = (ARBRE*)malloc(sizeof(ARBRE));
    a->tab = (livre*)malloc(sizeof(livre) * n);
    a->taille = n;
    for (i = 0; i < n; i++)
        a->tab[i] = nul;
    return a;
}

int egal_livre(livre l1, livre l2) {
    if (l1.numero == l2.numero && strcmp(l1.titre, l2.titre) == 0)
        return TRUE;
    return FALSE;
}

int arbre_vide(ARBRE a) {
    return egal_livre(a.tab[0], nul);
}

int sous_arbre_vide(ARBRE a, int i) {
    if (i <= 0 || i > a.taille)
        return TRUE;
    if (egal_livre(a.tab[i - 1], nul))
        return TRUE;
    return FALSE;
}

livre affiche_livre(livre l) {
    printf("%d\t%s\n", l.numero, l.titre);
    return l;
}

void affiche_arbre(ARBRE a) {
    int i;
    printf("numero\ttitre\n");
    for (i = 0; i < a.taille; i++)
        affiche_livre(a.tab[i]);
}

int taille_arbre(ARBRE a, int i) {
    if (sous_arbre_vide(a, i))
        return 0;
    return 1 + taille_arbre(a, 2 * i) + taille_arbre(a, 2 * i + 1);
}

int arbre_plein(ARBRE a) {
    return (a.taille == taille_arbre(a, 1));
}

void affiche_prefixe(ARBRE a, int i) {
    if (sous_arbre_vide(a, i))
        return;
    printf("pos %d : ", i);
    affiche_livre(a.tab[i - 1]);
    affiche_prefixe(a, 2 * i);
    affiche_prefixe(a, 2 * i + 1);
}

void affiche_infixe(ARBRE a, int i) {
    if (sous_arbre_vide(a, i))
        return;
    affiche_infixe(a, 2 * i);
    printf("pos %d : ", i);
    affiche_livre(a.tab[i - 1]);
    affiche_infixe(a, 2 * i + 1);
}

void affiche_surfixe(ARBRE a, int i) {
    if (sous_arbre_vide(a, i))
        return;
    affiche_surfixe(a, 2 * i);
    affiche_surfixe(a, 2 * i + 1);
    printf("pos %d : ", i);
    affiche_livre(a.tab[i - 1]);
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int hauteur(ARBRE a, int i) {
    if (sous_arbre_vide(a, i))
        return 0;
    return 1 + max(hauteur(a, 2 * i), hauteur(a, 2 * i + 1));
}

int egal_arbre(ARBRE a, ARBRE b, int i, int j) {
    if (sous_arbre_vide(a, i) && sous_arbre_vide(b, j))
        return TRUE;
    if (sous_arbre_vide(a, i) || sous_arbre_vide(b, j))
        return FALSE;
    if (!egal_livre(a.tab[i - 1], b.tab[j - 1]))
        return FALSE;
    return egal_arbre(a, b, 2 * i, 2 * j) &&
           egal_arbre(a, b, 2 * i + 1, 2 * j + 1);
}

int main() {
    ARBRE *a = creer_arbre(14);

    a->tab[0].numero = 10;
    strcpy(a->tab[0].titre, "toto");

    a->tab[1].numero = 11;
    strcpy(a->tab[1].titre, "tata");

    a->tab[2].numero = 355;
    strcpy(a->tab[2].titre, "titi");

    a->tab[3].numero = 12;
    strcpy(a->tab[3].titre, "tito");

    a->tab[5].numero = 133;
    strcpy(a->tab[5].titre, "tatu");

    a->tab[7].numero = 187;
    strcpy(a->tab[7].titre, "tato");

    a->tab[8].numero = 87;
    strcpy(a->tab[8].titre, "tati");

    a->tab[9].numero = 14;
    strcpy(a->tab[9].titre, "tortu");

    a->tab[11].numero = 16;
    strcpy(a->tab[11].titre, "titu");

    printf("Affichage infixe :\n");
    affiche_infixe(*a, 1);

    printf("\nHauteur : %d\n", hauteur(*a, 1));
    printf("Taille : %d\n", taille_arbre(*a, 1));

    return 0;
}