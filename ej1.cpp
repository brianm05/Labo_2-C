//Se ingresa en un vector 20 valores float en forma aleatoria y la computadora los ordena y emite.
//a) por selección
//b) por burbujeo mejorado
//c) por inserción

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define VAL 20

void carga_vector(float v[VAL]){
    int i;
    for(i=0;i<VAL;i++)
        v[i]=rand()%100;
}

void emito_vector(float v[VAL]){
    int i;
    for(i=0;i<VAL;i++)
        printf("%f\n",v[i]);
}

void burbuja(float* vector){
    int iteracion = 0;
    bool permutation = true;
    int actual;

    while ( permutation) {
        permutation = false;
        iteracion ++;
        for (actual=0;actual<20-iteracion;actual++) {
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

void insercion(float* t)
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

void seleccion(float *vector, int taille)
{
     int actual, mas_pequeno, j, temp;

     for (actual = 0; actual < taille - 1; actual++)
     {
         mas_pequeno = actual;
         for (j = actual; j < taille; j++){
              if (vector[j] < vector[mas_pequeno])
                  mas_pequeno = j;
         }
          temp = vector[actual];
          vector[actual] = vector[mas_pequeno];
          vector[mas_pequeno] = temp;
     }
}

int main(){
    srand (time(NULL));
    float vec[VAL];

    carga_vector(vec);
    printf("SIN ORGANIZAR:\n");
    emito_vector(vec);

    seleccion(vec,VAL);
    printf("\n");
    printf("ORGANICAZION POR SELECCION:\n");
    emito_vector(vec);

    burbuja(vec);
    printf("\n");
    printf("ORGANICAZION DE BURBUJA:\n");
    emito_vector(vec);

    insercion(vec);
    printf("\n");
    printf("ORGANICAZION POR INSERCION:\n");
    emito_vector(vec);

return 0;
}
