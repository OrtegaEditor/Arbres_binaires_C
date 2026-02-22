#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct employe {
    int code;
    char nom[30];
    int salaire;
} EMPLOYE;

typedef struct noeud {
    EMPLOYE emp;
    struct noeud *fg;
    struct noeud *fd;
} *Arbre;

/* ================= CREATION ================= */

Arbre creer_noeud(EMPLOYE e) {
    Arbre a = (Arbre)malloc(sizeof(struct noeud));
    a->emp = e;
    a->fg = NULL;
    a->fd = NULL;
    return a;
}

/* ================= AFFICHAGE ================= */

void Affiche_E(EMPLOYE e) {
    printf("|%s|%d|%d|\n", e.nom, e.code, e.salaire);
}

void affiche_prefixe(Arbre a) {
    if (a == NULL) return;
    Affiche_E(a->emp);
    affiche_prefixe(a->fg);
    affiche_prefixe(a->fd);
}

void affiche_infixe(Arbre a) {
    if (a == NULL) return;
    affiche_infixe(a->fg);
    Affiche_E(a->emp);
    affiche_infixe(a->fd);
}

void affiche_suffixe(Arbre a) {
    if (a == NULL) return;
    affiche_suffixe(a->fg);
    affiche_suffixe(a->fd);
    Affiche_E(a->emp);
}

/* ================= PROPRIETES ================= */

int taille(Arbre a) {
    if (a == NULL) return 0;
    return 1 + taille(a->fg) + taille(a->fd);
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int hauteur(Arbre a) {
    if (a == NULL) return 0;
    return 1 + max(hauteur(a->fg), hauteur(a->fd));
}

int masse_salariale(Arbre a) {
    if (a == NULL) return 0;
    return a->emp.salaire +
           masse_salariale(a->fg) +
           masse_salariale(a->fd);
}

/* ================= RECHERCHE ================= */

Arbre search_DFS(Arbre a, int code) {
    Arbre b;
    if (a == NULL) return NULL;
    if (a->emp.code == code) return a;

    b = search_DFS(a->fg, code);
    if (b != NULL) return b;

    return search_DFS(a->fd, code);
}

/* ================= FILE POUR PARCOURS LARGEUR ================= */

typedef struct cellule {
    Arbre noeud;
    struct cellule *suivant;
} *File;

int file_vide(File f) {
    return (f == NULL);
}

File enfiler(File f, Arbre a) {
    File nouveau = (File)malloc(sizeof(struct cellule));
    nouveau->noeud = a;
    nouveau->suivant = NULL;

    if (f == NULL)
        return nouveau;

    File temp = f;
    while (temp->suivant != NULL)
        temp = temp->suivant;

    temp->suivant = nouveau;
    return f;
}

File defiler(File f) {
    if (f == NULL) return NULL;
    File temp = f;
    f = f->suivant;
    free(temp);
    return f;
}

void affiche_largeur(Arbre a) {
    if (a == NULL) return;

    File f = NULL;
    f = enfiler(f, a);

    while (!file_vide(f)) {
        Arbre courant = f->noeud;
        Affiche_E(courant->emp);

        if (courant->fg != NULL)
            f = enfiler(f, courant->fg);

        if (courant->fd != NULL)
            f = enfiler(f, courant->fd);

        f = defiler(f);
    }
}

/* ================= MAIN ================= */

int main() {
    EMPLOYE e1 = {3, "TAMO", 500000};
    EMPLOYE e2 = {4, "BROTTO", 900000};
    EMPLOYE e3 = {6, "NLONG", 3400};
    EMPLOYE e4 = {5, "NGOA", 800000};
    EMPLOYE e5 = {7, "AHMED", 700000};

    Arbre a1 = creer_noeud(e1);
    Arbre a2 = creer_noeud(e2);
    Arbre a3 = creer_noeud(e3);
    Arbre a4 = creer_noeud(e4);
    Arbre a5 = creer_noeud(e5);

    a1->fg = a2;
    a1->fd = a4;
    a2->fg = a3;
    a4->fd = a5;

    printf("Parcours infixe:\n");
    affiche_infixe(a1);

    printf("\nTaille : %d\n", taille(a1));
    printf("Hauteur : %d\n", hauteur(a1));
    printf("Masse salariale : %d\n", masse_salariale(a1));

    printf("\nParcours largeur:\n");
    affiche_largeur(a1);

    return 0;
}