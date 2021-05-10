#include "Projet_Ranking_PageRank.h"


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


int les_predecesseurs_sommet_2(int taille, Sommet tab[], int f[]){
    /*-------------------------------------VARIABLES-------------------------------------------------------*/

    /*PARTIE 2*/
    FILE *fichier;
    int size=retourne_size();
    int MAX = 7 * size  ;
    int nb_lignes_lues=0;

    /*on determine une taille de chaine MAX des matrices*/
    char *tab_char= (char*)malloc( MAX * sizeof(char));
    Sommet* tampon;



    char delim[] = " ";
	char *ptr ;
    char *sommet, *successeur, *value, *q;
    double couts;
    
    
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
    

    while(nb_lignes_lues < size){

        fgets(tab_char,MAX,fichier);
        //strncpy(c,tab_char,strlen(tab_char)-1); // Enlever le dernier ceractère qui est \n
        remove_Char(tab_char);
       
        //printf("\n%s",tab_char);

        //printf("\n TAB_CHAR: %s",tab_char);
        q=tab_char;
        ptr = strchr(q, ' ');
        sommet = (char*)malloc(sizeof(char) * (ptr - q + 1) );
        strncpy(sommet, q, ptr - q ); // Enregistrer le numéro de la ligne (le premier élément)
        q = ptr + 1;

        ptr = strchr(q, ' ');
        
        if(ptr==NULL){
            f[atoi(sommet)-1]=1;
        }else{
            f[atoi(sommet)-1]=0;
        }
        
        while (ptr != NULL)
        {
            ptr = strchr(q, ' ');
            
            //On ajoute "Sommet" à la liste de Prédécesseurs de chaque Y successeur de "sommet"
            if(ptr!=NULL){
                value = (char*)malloc(sizeof(char) * (ptr - q + 1) );
                successeur = (char*)malloc(sizeof(char) * (ptr - q + 1) );
                strncpy(value, q, ptr - q );
                q = ptr + 1;

                if(isInteger(value)){
                    strcpy(successeur, value);
                    free(value);

                    ptr = strchr(q, ' ');
                    value = (char*)malloc(sizeof(char) * (ptr - q + 1) );
                    strncpy(value, q, ptr - q );
                    q = ptr + 1;

                    couts=atof(value);
                    free(value);

                }else{
                    couts=atof(value);// cout
                    free(value);
                    
                    ptr = strchr(q, ' ');
                    value = (char*)malloc(sizeof(char) * (ptr - q + 1) );
                    strncpy(value, q, ptr - q );
                    q = ptr + 1;

                    strcpy(successeur, value);
                    free(value);
                    
                }           

                tampon=(Sommet*)malloc(sizeof(Sommet));
                tampon->valeur_sommet=atoi(sommet);
                tampon->cout=couts;
                tampon->listePredecesseur=NULL;

                if(successeur){
                    ajout(&tab[atoi(successeur)-1],tampon);
                }
                
            } 
              
        }
        nb_lignes_lues++;
        //strcpy(tab_char,"");// vider le buffer

    }
    
    fclose(fichier); // On ferme le fichier qui a �t� ouvert
    free(tab_char);
    return 0 ;
}


int les_predecesseurs_sommet(int taille, Sommet tab[], int f[]){
    /*-------------------------------------VARIABLES-------------------------------------------------------*/

    /*PARTIE 2*/
    FILE *fichier;
    int size=retourne_size();
    int MAX = 4 * size ;
    int nb_lignes_lues=0;

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
    
    while(nb_lignes_lues < size){

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
        if( atoi(ptr) == 0 ){
            f[atoi(sommet)-1]=1;
        }else{
            f[atoi(sommet)-1]=0;
        }
        
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
                    tampon = (Sommet*)malloc(sizeof(Sommet));
                    tampon->valeur_sommet = atoi(sommet);
                    tampon->cout = couts;
                    tampon->listePredecesseur = NULL;

                    ajout(&tab[atoi(successeur)-1],tampon);
                }
                
            } 
              
        }
        nb_lignes_lues++;
        //free(tab_char);
        
        //strcpy(tab_char,"");// vider le buffer

    }
    
    fclose(fichier); // On ferme le fichier qui a �t� ouvert
    //free(tab_char);
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


double* take_x(Sommet *t, int taille){
    double *x=(double *)malloc(sizeof(double)*taille);
    assert( x != NULL );
    for(Sommet *p=t;p<t+taille;p++){
        *(x+(p-t))=p->cout;
    }
    return x;
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

double test_De_Convergence_(double *x, double *y, int taille){
    double som=0.0;
    for(int i=0; i<taille; i++){
        som+=val_abs(*(x+i) - *(y+i)); 
    }
    return som; 
}


double* copy(double *y, int taille){
    double *x=(double *)malloc(sizeof(double)*taille);
    assert( x != NULL );
    for(double *p=y;p<y+taille;p++){
        *(x+(p-y))=*(p);
    }
    return x;

}

double multipication_vect_ligne_par_vect_colonne(double *x, int *f, int taille){
    double resultat=0;
    for (int i=0;i<taille;i++){
        resultat+= *(x+i) * *(f+i)*1.0;
    }
    return resultat;
}

void page_rank_amelioration(double *x, double *x_precedent, int taille, int *f, double alpha ){
    // xG = αxP + [(1 − α)(1/N) + α(1/N)(x*ft)]e
    // xG = αxP + (1 − α)(1/N)e + α(1/N)(x*ft)e
    double val_1 = (1.0 - alpha)/ (taille * 1.0);
    double val_2 = alpha / (taille * 1.0);
    double resutlat_mult_des_vect= multipication_vect_ligne_par_vect_colonne(x_precedent, f, taille);
    double constante = (val_1 + (val_2 * resutlat_mult_des_vect) );
    for(int i = 0; i < taille; i++){
        *(x+i) = *(x+i) * alpha + constante;
    }

}


void contruction_de_G_(Sommet *t, int *f, double alpha, int taille ){
    //À vérifier
    // G= αP  + α(1 /N) f t e+(1−α)(1/N)e t e
    double val_1 = (1.0 - alpha)/ (taille * 1.0);
    double val_2 = alpha / (taille * 1.0);

    Sommet *p;
    for(p=t;p<t+taille;p++){
        Sommet *q=p->listePredecesseur;
        while(q){
            q->cout = q->cout * alpha + val_2 * *(f + (q->valeur_sommet - 1)) + val_1;     
            q=q->listePredecesseur;
        }
    }
    
}


double* iterations(double *x, Sommet tab[], int taille, double epsilon, int *f){
    double *y, *temp;
    int n=1;
    
    y = mutlplication_VectLigne_Matrix(x,tab,taille);
    page_rank_amelioration(y,x,taille,f,0.85); 
    /*
    for(int i=0; i<taille; i++){
        printf("%lf\t",*(y+i));
        
    }
    */

    while (!test_De_Convergence(x,y,taille,epsilon))
    {   
        n++;
        free(x);
        x=y; 
        y = mutlplication_VectLigne_Matrix(x, tab, taille);
        page_rank_amelioration(y,x,taille,f,0.85);    
    }
    
    printf("\nNbre d'itérations: %d ", n);
    return y;
}


void init_vect(double x,double *vect, int taille){
    for (int i=0; i<taille;i++){
        *(vect+i) = x;
    }
}


void contruction_de_G(Sommet *t, int *f, double alpha, int taille ){

    //on calcule les constantes
    double val_1 = alpha / (taille * 1.0);
    double val_2 = (1.0 - alpha)/ (taille * 1.0);
    Sommet *tampon;
  
    //liste des manquants on initialise tous à 1 ils sont tous manquants 
    int *manquant=(int *)malloc(sizeof(int)*taille);
    for(int i=0; i<taille;i++){
        *(manquant+i)=1;
        //printf("On a manquants initialisé %d\n",*(manquant+i));
    }

    //on maj les predecesseurs
    Sommet *p, *q;
    for(p=t;p<t+taille;p++){
        /*
        for(int i=0; i<taille;i++){
            *(manquant+i)=1;
            //printf("On a manquants initialisé %d\n",*(manquant+i));
        }

        */
        q=p->listePredecesseur;
        while(q){
            q->cout = q->cout * alpha + val_1 * *(f + (q->valeur_sommet - 1)) + val_2;     
            *(manquant + (q->valeur_sommet - 1) )= 0;
            q=q->listePredecesseur;
            //printf("On a les non manquants i =%d\n",q->valeur_sommet - 1);
        }

        //on ajoute les manquants
        for(int i=0; i<taille;i++){
            if (*(manquant+i)==1){
                tampon = (Sommet*)malloc(sizeof(Sommet));
                tampon->valeur_sommet = i +1 ;
                tampon->cout = val_1 * *(f + i) + val_2; 
                tampon->listePredecesseur = NULL;
                ajout(p,tampon); 
            }        
            *(manquant+i)=1;
         }
    }
    free(manquant);
    
}


void contruction_nabla_delta(Sommet *t,int taille,int *f, double alpha, double * delta, double * nabla){
    //on fait delta et nabla en meme temps => COMPLEXITE !!!!

    //on construit G
    contruction_de_G(t, f,alpha,taille);
    //On cherche les min ou max de chaque colonne
    double min=1.0;
    double max=0.0;
        
    //on parcours
    Sommet *p;
    for(p=t;p<t+taille;p++){
        
        Sommet *q=p->listePredecesseur;
        while(q){
            if(min>=q->cout){
                min=q->cout;
            }
            if(max<=q->cout){
                max=q->cout;
            }
            q=q->listePredecesseur;
        }

        //On a le vecteur 
        *(nabla+(p-t))=min;
        *(delta+(p-t))=max;

        //on re initialise
        min=1.0;
        max=0.0;
    }
}

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


void affichage_G(Sommet *G, int taille){

    for(Sommet *g=G;g<G+taille;g++){
            Sommet *q=g->listePredecesseur;
            while(q){
                printf("(ligne:%d, Colonne: %d, valeur: %lf)\t",q->valeur_sommet,g->valeur_sommet,q->cout);
                    q=q->listePredecesseur;
                }
                printf("\n");
    }
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


void iterations_vect_nabla(Sommet * G, double * nabla, double * delta, double* pagerank, int taille, double epsilon){


    printf("\n PAGERANK\n ");
    for(int i=0; i<taille; i++){
            printf("%.9lf\t",*(pagerank+i));
    }

    double *X = copy(nabla,taille); //X0=∇.
    double *Y = copy(delta,taille); // Y0= ∆

    /*Faire une boucle sur k
        a)Xk+1=max(Xk, XkG + ∇(1−||Xk||1) 
        (b)Yk+1=min(Yk,YkG+∇(1−||Yk||1)
    jusqu’`a ce que||Xk−Yk||1< £
    */
    
   
   double *tampon_X =(double *)malloc(sizeof(double)*taille);
   double *tampon_Y =(double *)malloc(sizeof(double)*taille);

   double *tab_X =(double *)malloc(sizeof(double)*taille);
   double *tab_Y =(double *)malloc(sizeof(double)*taille);
   

   double norme_X, norme_Y;

   
   // Affichage DELTA & NABLA
   printf("\n NABLA\n ");
    for(int i=0; i<taille; i++){
            printf("%.9lf\t",*(X+i));
    }

    printf("\n DELTA\n");
    for(int i=0; i<taille; i++){
            printf("%.9lf\t",*(Y+i));
    }
    verify(pagerank,X,Y,taille);
    printf("\n");
   
   int nb= 0;

   printf(" \n||X -Y|| =  %lf\n",test_De_Convergence_(X, Y, taille));

   while (!test_De_Convergence(X, Y, taille, epsilon) && nb!=6)
   {    

       free(tampon_X);
       free(tampon_Y);
       
       tampon_X=copy(X,taille);
       tampon_Y=copy(Y,taille);

       norme_X = 1- norme_1(X, taille);
       norme_Y = 1- norme_1(Y, taille);
        
        Sommet *g;
        double resultat_somme_colonne_X, resultat_somme_colonne_Y;
        
        for(g=G;g<G+taille;g++){

            resultat_somme_colonne_X=0;
            resultat_somme_colonne_Y=0;

            Sommet *q=g->listePredecesseur;

            while(q){
                resultat_somme_colonne_X+= q->cout * *(tampon_X+(q->valeur_sommet-1));
                resultat_somme_colonne_Y+= q->cout * *(tampon_Y+(q->valeur_sommet-1));
                q=q->listePredecesseur;
            }


            *(X + (g-G)) = max(resultat_somme_colonne_X + (norme_X * *(nabla + (g-G))), *(tampon_X + (g-G)));
            *(Y + (g-G)) = min(resultat_somme_colonne_Y + (norme_Y * *(nabla + (g-G))), *(tampon_Y + (g-G)));
            
        }

        printf("\n\n ITERATION %d\n ",nb+1);
        printf(" \nX\n");
        for(int i=0; i<taille; i++){
                printf("%.9lf\t",*(X+i));
        }
        printf(" \nY\n");
        for(int i=0; i<taille; i++){
                printf("%.9lf\t",*(Y+i));
        } 

        printf(" \n||X -Y|| =  %lf\n",test_De_Convergence_(X, Y, taille));
        verify(pagerank,X,Y,taille);
        nb++;      

   }

   
}


void contruction_nabla_delta_amelioration(Sommet *t, double alpha, int *f, int taille, double *delta, double *nabla){
    //G= αP  + α(1 /N) fte + (1−α)(1/N)ete
    //Parcourir t  et déterminer les min, max
    double min=1.0;
    double max=0.0;

    
    double val_1 = alpha / (taille * 1.0);
    double val_2 = (1.0 - alpha)/ (taille * 1.0);

    double M0, M1;
    double tampon;

    //liste des manquants on initialise tous à 1 ils sont tous manquants 
    int *manquant=(int *)malloc(sizeof(int)*taille);
    for(int i=0; i<taille;i++){
        *(manquant+i)=1;
        //printf("On a manquants initialisé %d\n",*(manquant+i));
    }

    // M = α(1 /N) fte+ (1−α)(1/N)e t e

    Sommet *p;
    printf("\n");
    for(p=t;p<t+taille;p++){
        M0 = 0.0;
        M1 = 0.0;
        Sommet *q=p->listePredecesseur;
        int tailleListeAdjacence=0;
        while(q){
            tampon = (q->cout * alpha) + val_1 * *(f + (q->valeur_sommet - 1)) + val_2;
            *(manquant + (q->valeur_sommet - 1) ) = 0;
            if(min>=tampon){
                min=tampon;
            }

            if(max<=tampon){
                max=tampon;
            }
            
            q=q->listePredecesseur;
            tailleListeAdjacence++;
        }
        //G= αP  + α(1 /N) fte + (1−α)(1/N)ete
        if(taille > tailleListeAdjacence){
            // Supposons que dans la colonne i on n'a pas k
            //Deux cas de figures sont possibles:
            // deg+(K) = 0 ==> f(k) = 1 ou bien 
            // deg+(K) # 0 ==> f(k) = 0 et l'arc (k, i) n'existe pas i.e K n'est pas prédécesseur de i
            //on ajoute les manquants
            for(int i=0; i<taille; i++){
                if (*(manquant+i)==1){
                    if (*(f + i) == 1){
                        // 1er cas f(k) = 1 donc le q->cout pour ce point = val_1 + val_2 = 1/N
                        M1 = val_1 + val_2; 
                    }  
                    else
                    {
                        // 2 ème cas f(k) = 0 donc le q->cout pour ce point = val_2 = (1-α)/N 
                        M0 = val_2;
                    }
                }        
                *(manquant+i)=1;

                /*
                if(M0 && M1){
                    break;
                } 
                */ 
            }

            if (M0 && M1)
            {
                *(nabla+(p-t)) = (min>M0)?M0:min;
                *(delta+(p-t)) = (max<M1)?M1:max;

            }else if (M0 && !M1)
            {
                *(nabla+(p-t)) = (min>M0)?M0:min;
                *(delta+(p-t)) = (max<M0)?M0:max;
                
            }else if (!M0 && M1)
            {
                
                *(nabla+(p-t)) = (min>M1)?M1:min;
                *(delta+(p-t)) = (max<M1)?M1:max;

            }else
            {
                
                *(nabla+(p-t))=min;
                *(delta+(p-t))=max;

            }
            
        }
         
        //on re-initialise
        min=1.0;
        max=0.0;
        
    }

}

void xkG_norme(Sommet *P, double *x_precedent, double *y_precedent, double *X, double *Y , int taille, int *f, double alpha,double *nabla ){
    // XkG = αXkP + [(1 − α)(1/N) + α(1/N)(Xk f t)]e
    free(X);
    free(Y);
    X = mutlplication_VectLigne_Matrix(x_precedent,P,taille);
    Y = mutlplication_VectLigne_Matrix(y_precedent,P,taille);

    double resutlat_mult_des_vect_x= multipication_vect_ligne_par_vect_colonne(x_precedent, f, taille);
    double resutlat_mult_des_vect_y= multipication_vect_ligne_par_vect_colonne(y_precedent, f, taille);

    double val_1 = (1.0 - alpha)/ (taille * 1.0);
    double val_2 = alpha / (taille * 1.0);
    double constante_x = (val_1 + (val_2 * resutlat_mult_des_vect_x));
    double constante_y = (val_1 + (val_2 * resutlat_mult_des_vect_y)); 

    for(int i = 0; i < taille; i++){
        double xk = (*(X+i) * alpha + constante_x) + ((1.0 - norme_1(x_precedent,taille)) * nabla[i]);
        double yk = (*(Y+i) * alpha + constante_y) + ((1.0 - norme_1(y_precedent,taille)) * nabla[i]);
        *(X+i) = max(*(x_precedent+i), xk );
        *(Y+i) = min(*(y_precedent+i), yk );
    }

}


void iterations_vect_nabla_amelioration(Sommet *t, double * nabla, double * delta, int* f, double* pagerank, int taille, double epsilon){

    double *X = copy(nabla,taille); //X0=∇.
    double *Y = copy(delta,taille); // Y0= ∆

    printf("\nNABLA\n");
    afficher_vect(nabla, taille);
    printf("\nDELTA\n");
    afficher_vect(delta, taille);


   /* 
   // Affichage DELTA & NABLA
   printf("\n NABLA\n ");
    for(int i=0; i<taille; i++){
            printf("%.9lf\t",*(X+i));
    }

    printf("\n DELTA\n");
    for(int i=0; i<taille; i++){
            printf("%.9lf\t",*(Y+i));
    }
    */

    verify(pagerank,X,Y,taille);
    printf("\nPAGERANK\n");
    afficher_vect(pagerank, taille);
    //printf("\n");

   //printf(" \n||X -Y|| =  %lf\n",test_De_Convergence_(X, Y, taille));

    /*Faire une boucle sur k
        a)Xk+1=max(Xk, XkG + ∇(1−||Xk||1)) 
        (b)Yk+1=min(Yk,YkG+∇(1−||Yk||1))
    jusqu’`a ce que||Xk−Yk||1< £
    */
    
    double *tampon_X =(double *)malloc(sizeof(double)*taille);
    double *tampon_Y =(double *)malloc(sizeof(double)*taille);
    int nb = 0;

   while (!test_De_Convergence(X, Y, taille, epsilon) &&  nb!=5)
   {    
       
       tampon_X=copy(X,taille);
       tampon_Y=copy(Y,taille);
       
       //free(Y);
       //free(X);
       
       xkG_norme(t,tampon_X, tampon_Y,X,Y,taille,f,0.85,nabla);
       printf("\nXK\n");
       afficher_vect(X, taille);
       printf("\nYK\n");
       afficher_vect(Y,taille);

       verify(pagerank,X,Y,taille);
       free(tampon_X);
       free(tampon_Y);
       nb++;
        
   }
   
}

