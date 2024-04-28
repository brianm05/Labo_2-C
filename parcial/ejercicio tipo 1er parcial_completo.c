#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

#define FIL 4
#define COL 6
#define T 30

/*
1. Una organización de torneos de natación, tiene inscriptos competidores, cada uno
representa provincias del país. Para ello, se define un array de FIL (dimensión) struct
con los siguientes datos:
*/

struct competidor{
  int id;
  char provincia[30];
  float tiempo[T];
  float prommes;
  float maxprom;
};
/*
2. Además se define un array con datos de los instructores responsables:
*/

struct instructor{
    int id;
    char nombrecompetidor[30];
    char instructor[30];
};

// punto 3. Y se define y carga dinámicamente un tercer array de enteros de dimensión = FIL
// que se inicializará con – 1.
// creación, carga, emisión y liberación de memoria del array auxiliar
void creoVecAux(int ** vaux){
    if ((*vaux = (int *)malloc(FIL * sizeof(int))) == NULL) {
        printf("Insuficiente espacio de memoria\n");
        exit(-1);
    }
}

void cargoVecAux(int * vaux){
int i;
    for ( i = 0; i < FIL; i++ ) vaux[i]=-1;

}

void emitoVecAux(int * vaux){
int i;
    for ( i = 0; i < FIL; i++ ) printf("%d | ", vaux[i]=-1);
printf("\n");
}

void liberoMemVecAux(int * vaux){
    free(vaux);
}

/*punto 4.Por otra parte, se almacenan en una array bidimensional de FIL filas
por COL columnas, los promedios mensuales -obtenidos con anterioridad-
por competidor (carga aleatoria)*/
void creoMatriz(float *** ppa){
    int f,c;
    if ((*ppa = (float **)malloc(FIL * sizeof(float *))) == NULL) {
        printf("Insuficiente espacio de memoria\n");
        exit(-1);
    }

    for (f = 0; f < FIL; f++) {
        if (( (*ppa)[f] = (float *)malloc(COL * sizeof(float))) == NULL) {
            printf("Insuficiente espacio de memoria\n");
            exit(-1);
        }
    }
}

void cargoMatriz(float ** ppa) {
    int f,c;
    srand(time(NULL));
    for ( f = 0; f < FIL; f++ )  {
        for ( c = 0; c < COL; c++ )
           *(*(ppa+f)+c) = rand() % 50;
    }
}

void emitoMatriz(float ** ppa){
    int f,c;
    for ( f = 0; f < FIL; f++ ) {
        printf("\n");
        for ( c = 0; c < COL; c++ )
            printf("%.2f | ",*(ppa[f] + c));
    }
}

void liberoMemMatriz(float ** ppa){
    int f;
    for ( f = 0; f < FIL; f++ ) free(ppa[f]);
    free(ppa);
}

/*carga en forma aleatoria los tiempos de cada competidor del struct*/
void cargaTiempos(struct competidor a[]){
    int i,j;
    for (i=0;i<FIL ;i++ ){
        for (j=0;j<T;j++ )
        {
            a[i].tiempo[j]= rand() % 90;
        }
    }
}

/*emite datos competidor*/
void emiteComp(struct competidor a[]){
    int i,j;
    printf("Competidores:\n");
    printf("-------------\n");
    for (i=0;i<FIL ;i++ ) {
        printf("ID competidor: %d, ",a[i].id);
        printf("Provincia: %s",a[i].provincia);
        printf("\nTiempos: ");

        for (j=0;j<T;j++ ){
            printf ("%.2f - ",a[i].tiempo[j]);
        }
        printf("\nPromedio de tiempos del mes: %.2f\n",a[i].prommes);
        printf("Máximo promedio: %.2f\n",a[i].maxprom);
        printf("______________________________\n");
    }
}

/*emite datos instructores*/
void emiteInst(struct instructor b[]){
    int i,j;
    printf("Instructores:\n");
    printf("------------\n");
    for (i=0;i<FIL ;i++ ) {
        printf("ID competidor: %d, ",b[i].id);
        printf("Nombre del competidor: %s, ",b[i].nombrecompetidor);
        printf ("Nombre del instructor: %s\n",b[i].instructor);
        printf("______________________________\n");
    }
}

/*punto 5.Función que reciba  el vector de competidores y
/cargue en el campo ‘prommes’, el promedio del array ‘tiempo’*/
void promedioMes(struct competidor a[]){
    int i,j;
    float sum;

    for (i=0;i<FIL;i++){
        sum=0;
        for (j=0;j<T;j++){
            sum+=a[i].tiempo[j];
        }
        a[i].prommes=sum/T;
    }
}

/*punto 6.Función que reciba  el vector de competidores, la matriz de tiempos
mensuales y cargue en el campo 'maxprom’, el máximo promedio de los tiempos
de los meses procesados.*/
void maximoPromedio(struct competidor a[],float ** promensual){
    int i,j;
    float max;

    for (i=0;i<FIL;i++){
        max=-9999;
        for(j=0;j<COL;j++){
            if (promensual[i][j]>max){
                max = promensual[i][j];
            }
        }
        a[i].maxprom=max;
    }
}

/*punto 7.Función que reciba  el vector de competidores, el vector de enteros
y cargue en este vector, las posiciones de los registros del vector de competidores,
 cuyo  ‘prommes‘ no supere al ‘maxprom’. Los datos deben almacenarse en forma contigua.*/
int noSupera(struct competidor a[],int vauxiliar[]){
    int i,j=0;
    for (i=0;i<FIL;i++ ) {
        if (a[i].prommes < a[i].maxprom) {
            vauxiliar[j]=i;
            j++;
        }
    }
    return j;
}

/* punto 8.Función que reciba  el vector de competidores, vector de
instructor, vector de posiciones
 y la cantidad retornada en la función anterior y emita el campo ‘provincia’ de los competidores
 y el campo ‘instructor’.*/
void emiteProvincia(struct competidor a[],struct instructor b[],int vauxiliar[],int cant){
    int i, j;
    printf("Las provincias donde el promedio de tiempos del mes "
           "no superaron el promedio general fueron:\n");
        for(i=0;i<cant;i++){
            for (j = 0; j < FIL; j++)
            if ( a[ vauxiliar[i] ].id == b[j].id)
            printf("%s - cuyo instructor fue: %s y su competidor fue %s\n",a[vauxiliar[i]].provincia,b[vauxiliar[i]].instructor, b[vauxiliar[i]].nombrecompetidor);
        }
}

/* punto 9.Función que reciba el vector de competidores y lo ordene por provincia
en forma ascendente.*/
void ordenar(struct competidor a[]){
    int i,j,flag;
    struct competidor aux;

    for (i=0;i<FIL-1;i++) {
        flag = 0;
        for (j = 0; j < FIL-(i+1); j++)    {
            if (strcmp(a[j].provincia,a[j+1].provincia) > 0) {
                aux = a[j];
                a[j] = a[j+1];
                a[j+1] = aux;
                flag = 1;
            }
        }
    }
}

int main(){
   // carga estática del array de struct de competidores punto 1 de la consigna
    struct competidor c[FIL]={{1,"La Pampa",0,0,0},{2,"Entre Rios",0,0,0},{3,"San Luis",0,0,0},{4,"Corrientes",0,0,0}};
    // carga estática del array de struct de instructores punto 2 de la consigna
    struct instructor i[FIL]={{1,"Sergio","Martin"},{2,"Ariel","Rosa"},{3,"Clara","Pedro"},{4,"Mercedes","Violeta"}};

    float ** promensual=NULL;
    int * vauxiliar=NULL;
    int cant;
    srand(time(NULL));

//emite datos de struct cargados antes de empezar el proceso
    emiteComp(c);
    emiteInst(i);
    getchar();

//cargamos en forma aleatoria los 10 tiempos de cada competidor del struct
    cargaTiempos(c);
    emiteComp(c);
    getchar();

//creo, cargo y emito vector auxiliar
    creoVecAux(&vauxiliar);
    cargoVecAux(vauxiliar);
    emitoVecAux(vauxiliar);
    getchar();

//punto 4.
    creoMatriz(&promensual);
    cargoMatriz(promensual);
    emitoMatriz(promensual);
    getchar();

//punto 5.
    printf("**Punto 5**\n");
    promedioMes(c);
    emiteComp(c);
    getchar();

// punto 6.
    printf("**Punto 6**\n");
    maximoPromedio(c,promensual);
    emiteComp(c);
    getchar();

// punto 7.
    printf("**Punto 7**\n");
    cant=noSupera(c,vauxiliar);
    printf("Cantidad detectada: %d", cant);
    getchar();

// punto 8.
    printf("**Punto 8**\n");
    emiteProvincia(c,i,vauxiliar,cant);
    getchar();

// punto 9.
    printf("**Punto 9**\nArray de competidores ordenado:\n");
    ordenar(c);
    emiteComp(c);
    getchar();

    liberoMemMatriz(promensual);
    liberoMemVecAux(vauxiliar);
    return 0;
}











