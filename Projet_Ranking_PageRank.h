#include "stdlib.h"
#include "stdio.h"
#include "math.h"
#include "limits.h"
#include "string.h"
#include "stdbool.h"
#include "assert.h"
#include "ctype.h"
#include "time.h"


//web4.txt
//petit_graphe.txt
//petit_graphe_aleatoire_regulier.txt
//graphe_intermediaire.txt
//large_graphe_aleatoire_regulier.txt
//wb-cs-stanford.txt
//Stanford.txt
//Stanford_BerkeleyV2.txt
//in_2004v2.txt 
//wikipedia-20051105V2.txt
//wb-edu.txt


#define PATH  "/home/aristo_/Bureau/Data/wb-edu.txt"

/*Dans un premier temps on ecrit la structure de la liste des sommets*/

typedef struct sommet{
    int valeur_sommet;
    double cout;
    struct sommet *listePredecesseur;
    
}Sommet;


int retourne_size();
int retourne_arcs();
void initilaliser_case_du_tableau(int taille, Sommet tab[]);
void afficher_ListePredecesseurs(Sommet *listePredecesseurs);
void ajout(Sommet *liste, Sommet *s );
void remove_Char(char c[]);
bool isInteger(char *value);
char* slice_line(char *x);
int les_predecesseurs_sommet_2(int taille, Sommet tab[], int f[]);
int les_predecesseurs_sommet(int taille, Sommet tab[], int f[]);
double* mutlplication_VectLigne_Matrix(double *x, Sommet *t , int taille);
double* take_x(Sommet *t, int taille);
double val_abs(double x);
bool test_De_Convergence(double *x, double *y, int taille, double epsilon);
double test_De_Convergence_(double *x, double *y, int taille);
double* copy(double *y, int taille);
double multipication_vect_ligne_par_vect_colonne(double *x, int *f, int taille);
void page_rank_amelioration(double *x, double *x_precedent, int taille, int *f, double alpha );
void contruction_de_G_(Sommet *t, int *f, double alpha, int taille );
double* iterations(double *x, Sommet tab[], int taille, double epsilon, int *f);
void init_vect(double x,double *vect, int taille);
void contruction_de_G(Sommet *t, int *f, double alpha, int taille );
void contruction_nabla_delta(Sommet *t,int taille,int *f, double alpha, double * delta, double * nabla);
void afficher_vect(double *t, int taille);
double norme_1(double *vect, int taille);
double min(double x, double y);
double max(double x, double y);
void affichage_G(Sommet *G, int taille);
void verify(double *pi, double *X, double *Y, int taille);
void iterations_vect_nabla(Sommet * G, double * nabla, double * delta, double* pagerank, int taille, double epsilon);
void contruction_nabla_delta_amelioration(Sommet *t, double alpha, int *f, int taille, double *delta, double *nabla);
void xkG_norme(Sommet *P, double *x_precedent, double *y_precedent, double *X, double *Y , int taille, int *f, double alpha,double *nabla );
void iterations_vect_nabla_amelioration(Sommet *t, double * nabla, double * delta, int* f, double* pagerank, int taille, double epsilon);

