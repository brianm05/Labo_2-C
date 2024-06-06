void bubble_sort(int* vector) //ordenamiento de butbuja
{
    int iteración = 0;
    bool permutation = true;
    int actual;

    while ( permutation) {
        permutation = false;
        iteración ++;
        for (actual=0;actual<20-iteración;actual++) {
            if (vector[actual]>vector[actual+1]){
                permutation = true;
                // Intercambiamos los dos elementos
                int temp = vector[actual];
                vector[actual] = vector[actual+1];
                vector[actual+1] = temp;
            }
        }
    }
}
void Insertion_sort(int* t) //inseciom
{
    int i, j;
    int actual;

    for (i = 1; i < 20; i++) {
        actual = t[i];
        for (j = i; j > 0 && t[j - 1] > actual; j--) {
            t[j] = t[j - 1];
        }
        t[j] = actual;
    }
}
void selection_sort(int *vector, int taille) //seleccion
{
     int actual, mas_pequeno, j, temp;

     for (actual = 0; actual < taille - 1; actual++)
     {
         mas_pequeno = actual;
         for (j = actual 1; j < taille; j++)
              if (vector[j] < vector[mas_pequeno])
                  mas_pequeno = j;
          temp = vector[actual];
          vector[actual] = vector[mas_pequeno];
          vector[mas_pequeno] = temp;
     }
}

void quick_sort (int *vector, int tamano) { //ordenamiento rapido
    int pared, actual, pivote, tmp;
    if (tamano < 2) return;
    // el elemento de pivote es la más a la derecha
    pivote = vector[tamano - 1];
    pared  = actual = 0;
    while (actual<tamano) {
        if (vector[actual] <= pivote) {
            if (pared != actual) {
                tmp=vector[actual];
                vector[actual]=vector[pared];
                vector[pared]=tmp;
            }
            pared ++;
        }
        actual ++;
    }
    quick_sort(vector, pared - 1);
    quick_sort(vector + pared - 1, tamano - pared + 1);
}
