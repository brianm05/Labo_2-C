//Nota: 9.6875
// corregir lo solicitado
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define N 5
#define M 6
#define T 30

//1. Crear un struct con los siguientes datos de los puntos de reparto.
struct puntoDeReparto{
int id;
char barrio[T];
float repartos_diarios[T];
// faltó: total_repartos_del_mes - tipo float (inicialmente campo vacío), corregir aquí y
// en las funciones correspondientes
float promedio;
float total_repartos_del_mes;
};
//6. Crear un struct con los siguientes datos de encargados.
struct encargados{
int id_encargado;
int id_punto_de_reparto;
char nombre_del_encargado[T];
};

void cargarRepartosDiarios(struct puntoDeReparto pR[]){
    srand(time(NULL));
    for(int i=0;i<N;i++)
        for(int j=0;j<T;j++)
        pR[i].repartos_diarios[j]= rand() % 15;
}
void emitirPuntosDeReparto(struct puntoDeReparto pR[]){
    printf("\nPUNTOS DE REPARTO:\n");
    for(int i=0;i<N;i++){
        printf("ID: %d\n",pR[i].id);
        printf("Barrio: %s\n",pR[i].barrio);
        printf("Repartos diarios: \n");
        for (int j=0;j<T;j++)
            printf("%.2f |",pR[i].repartos_diarios[j]);
        printf("\nPromedio: %.2f\n",pR[i].promedio);
        printf("---------\n");
    }
}
void emitirEncargados(struct encargados e[]){
    printf("\nDATOS DE ENCARGADOS:\n");
    for(int i=0;i<N;i++){
        printf("ID Encargado: %d\n",e[i].id_encargado);
        printf("ID Punto de reparto: %d\n",e[i].id_punto_de_reparto);
        printf("Nombre del encargado: %s\n",e[i].nombre_del_encargado);
        printf("---------\n");
    }
}

void crearArray(int *enteros){
    (*enteros) = (int *)malloc(N * sizeof(int));
}
void cargarArray(int* enteros){
    for(int i=0;i<N;i++){
        enteros[i]=-10;
    }
}
void emitirArray(int* enteros){
    printf("\nARRAY DE ENTEROS: \n");
    for(int i=0;i<N;i++){
        printf("%d |",enteros[i]);
    }
}

float ** crearMatriz(){
    float **matriz;
    matriz=(float **)malloc(N * sizeof(float*));

    for(int i=0;i<N;i++){
        matriz[i]=(float *)malloc(M * sizeof(float));
    }
return matriz;}

void cargarMatriz(float **m){
    srand(time(NULL));
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            m[i][j]= (float)(rand() % 15)+10;
        }
    }
}
void emitirMatriz(float **m){
    printf("\nMATRIZ:");
    for(int i=0;i<N;i++){
        printf("\n");
        for(int j=0;j<M;j++){
            printf("%.2f |",m[i][j]);
        }
    }
}
void liberarMemoria(int*e,float**m){
    free(e);

    for(int i=0;i<M;i++)
        free(m[i]);
    free(m);
}


int main(){
    int * enteros;
    float ** matriz;
 //1. 0.3125
 //2. Definir en main() un ‘vector de puntos de reparto’ de N struct.
 //0.625
 //3. 0.625
    struct puntoDeReparto puntosRepartos[N]={
        {0,"Barrio-1",{0},0,0},
        {1,"Barrio-2",{0},0,0},
        {2,"Barrio-3",{0},0,0},
        {3,"Barrio-4",{0},0,0},
        {4,"Barrio-5",{0},0,0}
    };
    //7. Definir en main() un ‘vector de encargados’ de N struct.
    //0.625
    //8. Cargar el array anterior con los datos definidos en el struct. La carga puede realizarse de 2 formas: estática o con una función
    //interactiva.
    //0.625
    struct encargados encargado[N]={
        {0,0,"Juan"},
        {1,1,"Pedro"},
        {2,2,"Martin"},
        {3,3,"Ezequiel"},
        {4,4,"Julian"}
    };

    //3. Cargar el vector anterior con los datos de ‘Id_ punto_de_reparto’ y ‘barrio’, considerar que el resto de los campos inicialmente
    //deben ser cargados con ceros (0). La carga puede realizarse de 2 formas: estática o con una función interactiva.
    for(int i=0;i<N;i++){
        for(int j=0;j<T;j++){
            puntosRepartos[i].repartos_diarios[j]=0;
        }
        puntosRepartos[i].promedio=0;
    }

    //4. Crear una función que cargue aleatoriamente los T ‘repartos_diarios’ en el vector.
    //0.625
    cargarRepartosDiarios(puntosRepartos);

    //5. Crear una función de emisión de datos este vector.
    // 0.625
    emitirPuntosDeReparto(puntosRepartos);
//6. 0.625

    //9. Crear una función de emisión de datos del este vector.
    //0.625
    emitirEncargados(encargado);

    //10. Crear una función que genere un vector dinámico de enteros de dimensión N, ( ‘vector dinámico de posiciones’).
    //0.625
    crearArray(enteros);

    //11. Crear una función de carga para el vector dinámico, que se inicializara, en cada posición, con -10
    //0.625
    cargarArray(enteros);

    //12. Crear una función de emisión de datos de este vector.
    // 0.625
    emitirArray(enteros);

    //13. Crear una función que genere una matriz dinámica de N filas por M columnas, (‘promedios de repartos de los 6 meses anteriores’)
    // 0.625
    matriz=crearMatriz();

    //14. Crear una función de carga aleatoria de la matriz dinámica.
    //0.625
    cargarMatriz(matriz);

    //15. Crear una función de emisión de datos de la matriz dinámica.
    // 0.625
    emitirMatriz(matriz);

    //16. Liberar la memoria dinámica.
    //0.625
    liberarMemoria(enteros,matriz); //muy bien!

return 0;}
