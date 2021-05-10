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
const double alpha = 0.85; 

typedef struct sommet{
    int valeur_sommet;
    double cout;
    struct sommet *listePredecesseur;
    
}Sommet;

int retourne_size(){
    /*---------------------------VARIABLES-------------------------------------------------------------*/
     /*PARTIE 1*/
    int size ; /*taille de la matrice carree*/

    /*PARTIE 2*/
    FILE *fichier;
    /*on determine une taille de chaine MAX des matrices*/
    char *tab_char= (char*)malloc(100* sizeof(char));



    /*------------------------------OUVERTURE DU FICHIER---------------------------------------------------*/

    fichier= fopen(PATH,"r");
    if(fichier ==NULL){
        perror("Error opening file");
        return(-1);
    }

     /*----------------------------LECTURE DE SIZE ------------------------------------------------*/

    /*On commence a lire le fichier*/

    /*On recupere size*/
    fgets(tab_char,100,fichier);
    size= atoi(tab_char);

    fclose(fichier);
    free(tab_char);

    return size;

}

int retourne_arcs(){

    /*-------------------------------------VARIABLES-------------------------------------------------------*/
    /*PARTIE 1*/
    int nb_arc; /*le nombre d'arcs*/


    /*PARTIE 2*/
    FILE *fichier;
    /*on determine une taille de chaine MAX des matrices*/
    char *tab_char= (char*)malloc( 100 * sizeof(char));

    char delim[] = " ";

    /*------------------------------OUVERTURE DU FICHIER---------------------------------------------------*/

    fichier= fopen(PATH,"r");
    if(fichier ==NULL){
        perror("Error opening file");
        return(-1);
    }

     /*----------------------------LECTURE DE SIZE ET NBARC------------------------------------------------*/

    /*On commence a lire le fichier*/
     /*On commence a lire le fichier*/
    fgets(tab_char, 100, fichier);
    
    /*On recup�re bn_arc*/

    fgets(tab_char, 100, fichier);
    nb_arc = atoi(tab_char);
    
    /*
    !!!!!!!!premier tab_char
    char *ptr = strtok(tab_char,delim);
    ptr=strtok(NULL,delim);

    if(ptr){
        nb_arc = atoi(ptr);
    }else{
        fgets(tab_char, 100, fichier);
        nb_arc = atoi(ptr);
    }
    */
    
    fclose(fichier);
    free(tab_char);

    return nb_arc;

}

void initilaliser_case_du_tableau(int taille, Sommet tab[]){
    for(int i=0; i<taille ; i++){
        tab[i].valeur_sommet=i+1;
        tab[i].cout=0;
        tab[i].listePredecesseur=NULL;
    }
}

void afficher_ListePredecesseurs(Sommet *listePredecesseurs){
    Sommet *p=listePredecesseurs;
    while (p)
    {
        printf("%d\t",p->valeur_sommet);
        p=p->listePredecesseur;
    }    
}

void ajout(Sommet *liste, Sommet *s ){
    s->listePredecesseur=liste->listePredecesseur;
    liste->listePredecesseur = s;
}

void remove_Char(char c[]){
    for(int i=0; i<strlen(c)-1; i++){
        if(c[i]=='\n'){
            c[i]= c[i+1];
        }
    }
}

bool isInteger(char *value){
    char *i=value; 
    
    while(isdigit(*i) && i < value + strlen(value)){
        i++;
    }
    return (i == value + strlen(value));
}

int les_predecesseurs_sommet(int taille, Sommet tab[], int f[], double nabla[], double delta[]){
    /*-------------------------------------VARIABLES-------------------------------------------------------*/

    /*PARTIE 2*/
    FILE *fichier;
    int MAX = 4*taille ;
    int nb_lignes_lues=0,temp1;
    bool creuse=false;
    double min=taille, max=0,val= (1.0 -alpha)/(taille*1.0),temp;
    int sommetD;
    double *precedent = (double*)malloc(taille * sizeof(double));

    int count=0;

    /*on determine une taille de chaine MAX des matrices*/
    char *tab_char= (char*)malloc( MAX * sizeof(char));
    Sommet* tampon;


    char delim[] = " ";
	char *ptr ;
    char* sommet, *successeur;
    double couts;

    
    int nb_voisins_parcourus=0;
    int degre ;
    
    /*------------------------------OUVERTURE DU FICHIER---------------------------------------------------*/

    fichier= fopen(PATH,"r");
    if(fichier ==NULL){
        perror("Error opening file");
        return -1 ;
    }

     /*----------------------------LECTURE DE SIZE ET NBARC------------------------------------------------*/

    fgets(tab_char,MAX,fichier);
    fgets(tab_char,MAX,fichier);
    
       
    /*---------------------------FAIT TABLEAU--------------------------------*/


    /*Lire les autres lignes (de 3 à size)*/
    
    while(nb_lignes_lues < taille){

        fgets(tab_char,MAX,fichier);
        //strncpy(c,tab_char,strlen(tab_char)-1); // Enlever le dernier ceractère qui est \n
        
        //remove_Char(tab_char);
       
        //printf("\n%s",tab_char);

        //printf("\n TAB_CHAR: %s",tab_char);
        
        ptr = strtok(tab_char, delim); // Mettre dans ptr le premier nombre de la ligne récupérée
        
        sommet=ptr; // Enregistrer le numéro de la ligne (le premier élément)

        ptr = strtok(NULL, delim);// On a pas besoin du degré du sommet 
        //printf("\n-(%s, %s)",sommet, ptr);
       
        //degre = atoi(ptr);
        //On rempli nabla et delta au même moment
        sommetD= atoi(sommet)-1;
        if( atoi(ptr) == 0 ){
            f[atoi(sommet)-1]=1;
            creuse=true;
        }else{
            f[atoi(sommet)-1]=0;
        }
        //On suppose on ne peut pas avoir la matrice nulle sinon nabla = 1/N
        nabla[atoi(sommet)-1]=val;
        sommetD= atoi(sommet);
        
        while (ptr != NULL )
        {
            ptr = strtok(NULL, delim);
            
            //On ajoute "Sommet" à la liste de Prédécesseurs de chaque Y successeur de "sommet"
            if( ptr!=NULL ){

                if(isInteger(ptr)){
                    successeur = ptr;
                    ptr = strtok(NULL, delim);//Le cout
                    couts = atof(ptr);

                }else{
                    couts = atof(ptr);// cout
                    ptr = strtok(NULL, delim);// sucesseur
                    successeur = ptr;

                }           

                
                if( successeur ){
                    
                    int s=atoi(successeur)-1;
                    if(delta[s] < couts){
                        delta[s] = couts;
                        precedent[s]= atoi(sommet)-1;
                    }

                    tampon = (Sommet*)malloc(sizeof(Sommet));
                    tampon->valeur_sommet = atoi(sommet);
                    tampon->cout = couts;
                    tampon->listePredecesseur = NULL;
                
                    ajout(&tab[s],tampon);
                }
    
            }
             
              
        }
        
        nb_lignes_lues++;
        //printf("%d\n",nb_lignes_lues);
        //free(tab_char);
        
        //strcpy(tab_char,"");// vider le buffer


    }

    
    for(int i=0; i<taille;i++){
        temp1=*(precedent+i);
        temp= alpha *delta[i] + f[temp1]*(alpha/taille) + ((1.0-alpha)/taille);
        delta[i]=temp;
        if(creuse){
            if(delta[i]<1.0/taille){
                delta[i]=1.0/taille;
            }
        }
 
    }
   
    fclose(fichier); // On ferme le fichier qui a �t� ouvert
    free(tab_char);
    return 0 ;
}

double* mutlplication_VectLigne_Matrix(double *x, Sommet *t , int taille){
    // on veut multiplier notre matrice par un vecteur ligne de taille éléments tous égaux à x
    double * tab= (double *)malloc(sizeof(double) * taille);
    Sommet *p;
    double resultat_somme_colonne;
    for(p=t;p<t+taille;p++){
        resultat_somme_colonne=0;
        //multiplication_Colonne_Par_Colonne(*(x+(p-t)),p);
        Sommet *q=p->listePredecesseur;
        while(q){
            resultat_somme_colonne+= q->cout * *(x+(q->valeur_sommet-1));
            q=q->listePredecesseur;
        }
        //p->cout=resultat_somme_colonne;
        *(tab + (p-t)) = resultat_somme_colonne;
    }
    return tab;
}

double val_abs(double x){
    return (x<0)?(-x):x;
}

bool test_De_Convergence(double *x, double *y, int taille, double epsilon){
    double som=0.0;
    for(int i=0; i<taille; i++){
        som+=val_abs(*(x+i) - *(y+i)); 
    }

    //printf("%.9lf", som);
    return (som<epsilon); // Retourne VRAI SI "som<epsilon" ET FAUX SINON
}

double multipication_vect_ligne_par_vect_colonne(double *x, int *f, int taille){
    double resultat=0;
    for (int i=0;i<taille;i++){
        resultat+= *(x+i) * *(f+i)*1.0;
    }
    return resultat;
}


// ------------------------------------------PAGE RANK NABLA-----------------------------------------------------------------

void afficher_vect(double *t, int taille){
    double *p;
    for(p=t;p<t+taille;p++){
        printf("%lf\t",*p);
    }
}

double norme_1(double *vect, int taille){
    double som=0.0;

    for(int i=0; i<taille; i++){
        som+= val_abs(*(vect + i));
    }
    return som;
}

double min(double x, double y){
    return (x<y)?(x):y;
}

double max(double x, double y){
    return (x<y)?(y):x;
}

void verify(double *pi, double *X, double *Y, int taille){

    double *p=pi; // Resultat PageRank
    double *x=X; // Xk
    double *y=Y; // Yk
    while ( p < (pi + taille)  && (*x <= *p && *p <= *y))
    {
        p++;
        x++;
        y++;
    }
    
    if( p==(pi + taille) ){
       printf("\nINÉGALITÉ VÉRIFIÉE");
    }else{
        printf("\nINÉGALITÉ NON VÉRIFIÉE");
    }
    
}

double* multipication_vect_ligne_par_vect_colonne_xy(double *x, double *y, int *f,int taille){
    double* res=(double*)malloc(2*sizeof(double));
    double resultat_x=0, resultat_y=0;
    for (int i=0;i<taille;i++){
        resultat_x+= *(x+i) * *(f+i)*1.0;
        resultat_y+= *(y+i) * *(f+i)*1.0;

    }
    res[0]=resultat_x;
    res[1]=resultat_y;
    return res;
}

void copy_xy(double *x_copie,double *y_copie, double *x,double *y, int taille){
    assert( x != NULL );
    assert( y != NULL );

    for(int i=0;i<taille;i++){
        *(x_copie+i)=*(x+i);
        *(y_copie+i)=*(y+i);

    }
}

void calcule_xk_yk(double *x,double *y, double * tab_x, double * tab_y, Sommet *t , int taille, int *f, double nabla[]){
    // on veut multiplier notre matrice par un vecteur ligne de taille éléments tous égaux à x
    double norme_x = norme_1(x,taille);
    double norme_y = norme_1(y,taille);
    double temp1,temp2;

    Sommet *p;
    double resultat_somme_colonne_x ,resultat_somme_colonne_y;

    //Pour xG les constantes
    double val_1 = (1.0 - alpha)/ (taille * 1.0);
    double val_2 = alpha / (taille * 1.0);
    double *resutlat_mult_des_vect_xy= multipication_vect_ligne_par_vect_colonne_xy(x,y, f, taille);
    double constante_x = ((val_1 * norme_x) + (val_2 * resutlat_mult_des_vect_xy[0]) );
    double constante_y = ((val_1 * norme_y) + (val_2 * resutlat_mult_des_vect_xy[1]) );

    for(p=t;p<t+taille;p++){
        resultat_somme_colonne_x=0;
        resultat_somme_colonne_y=0;

        //multiplication_Colonne_Par_Colonne(*(x+(p-t)),p);
        Sommet *q=p->listePredecesseur;
        while(q){

            resultat_somme_colonne_x+= q->cout * *(x+(q->valeur_sommet-1));
            resultat_somme_colonne_y+= q->cout * *(y+(q->valeur_sommet-1));
            q=q->listePredecesseur;
        }

        //On a XkG + ∇(1 − ||Xk||1 et Y kG + ∇(1 − ||Yk||1
        temp1 = alpha * resultat_somme_colonne_x +constante_x + nabla[p-t]*(1.0 - norme_x);
        temp2 = alpha * resultat_somme_colonne_y +constante_y + nabla[p-t]*(1.0 - norme_y);
   
        //Calcul de xk+1 yk+1
        *(tab_x + (p-t))= max(*(x+ (p-t)),temp1);
        *(tab_y + (p-t))= min(*(y+ (p-t)),temp2);   
        //printf("Tabxi \t Tabyi \t : %f et %f \n",*(tab_x + (p-t)) ,*(tab_y + (p-t)));


        
    }
    copy_xy(x,y,tab_x,tab_y,taille);
    
}

void iterations_nabla(Sommet *t, double * nabla, double * delta, int* f, int taille, double epsilon){

    double *x=(double *)malloc(sizeof(double)*taille);
    double *y=(double *)malloc(sizeof(double)*taille);
    double * tab_x= (double *)malloc(sizeof(double) * taille);
    double * tab_y= (double *)malloc(sizeof(double) * taille);

    //On instancie les valeurs de x et y depart
    copy_xy(x,y,nabla,delta,taille);
    
    int nb=0;
    while(! test_De_Convergence(x,y,taille,epsilon)){
        calcule_xk_yk(x,y,tab_x,tab_y,t,taille,f,nabla);
        nb ++;
    }
    printf("Le nombre d'execution %d\n", nb);
    
}

int main(){   // define the main function

    int i,n;
    int taille =retourne_size();
    int arcs= retourne_arcs();
    
    double *delta, *nabla; //*pagerank ;
    delta=(double *)malloc(sizeof(double)*taille);
    nabla=(double *)malloc(sizeof(double)*taille);

    Sommet *p, *q;

    double epsilon=1e-6;

    printf("\nLa taille de la matrice est : %d \n",taille);
    printf("\nLe nombre d'arcs  est de : %d \n", arcs);

    Sommet* notre_tableau=(Sommet *)malloc(sizeof(Sommet) * taille);
    assert(notre_tableau != NULL);

    int *f = (int *) malloc(sizeof(int) * taille);
    assert( f != NULL );

    initilaliser_case_du_tableau(taille,notre_tableau);
    

//Fichier
    les_predecesseurs_sommet(taille,notre_tableau,f, nabla,delta);

    iterations_nabla(notre_tableau,nabla,delta,f,taille,epsilon);
    
    free(f);
    free(notre_tableau);
    free(delta);
    free(nabla);

    return 0;
    
}


