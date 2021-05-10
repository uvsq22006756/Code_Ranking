
void main(){   // define the main function

    int i,n;
    int taille =retourne_size();
    int arcs= retourne_arcs();
    
    double *delta, *nabla, *pagerank ;
    delta=(double *)malloc(sizeof(double)*taille);
    nabla=(double *)malloc(sizeof(double)*taille);

    Sommet *p, *q;

    double epsilon=1e-6;
    double alpha = 0.85;

    printf("\nLa taille de la matrice est : %d \n",taille);
    printf("\nLe nombre d'arcs  est de : %d \n", arcs);

    Sommet* notre_tableau=(Sommet *)malloc(sizeof(Sommet) * taille);
    assert(notre_tableau != NULL);

    int *f = (int *) malloc(sizeof(int) * taille);
    assert( f != NULL );

    double *vect=(double *)malloc(sizeof(double)*taille);
    assert( vect != NULL );

    initilaliser_case_du_tableau(taille,notre_tableau);
    init_vect(1.0/(taille * 1.0),vect,taille);

    les_predecesseurs_sommet(taille,notre_tableau,f);
    pagerank=iterations(vect,notre_tableau,taille, epsilon,f);
       
}


