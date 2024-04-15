/*Se desea comparar el tiempo del funcionamiento de los diferentes m�todos de b�squeda. Para ello se pretende buscar el
n�mero 27 en el siguiente vector: 1 4 5 12 25 27 31 42 43 56 73 76 78 80 99. Construye las funciones para la:
a) B�squeda secuencial.
b) B�squeda binaria.
Investiga c�mo devolver el tiempo que demora cada proceso e implementa l�s funciones correspondientes.*/


#include<stdio.h>
#include <ctime>


#define TAM 15
#define NUM 27

void busqSec(int *vec){
    printf("Metdodo Sec:\n");
    for(int i=0;i<TAM;i++)
        if (vec[i]==NUM){
            printf("Se encontro el %d en la posicion %d\n",NUM, i);
            printf("El programa tuvo %d iteraciones\n",i);
        }
}

void busqBin(int *vec){
    printf("Metdodo Bin:\n");
    int flag=0;
    int i=0;

    int mitad=TAM/2;
    while(flag==0){
        if(NUM==vec[mitad]){
            printf("Se encontro el %d en la posicion %d\n",NUM,mitad);
            flag=1;}
        else if (NUM<vec[mitad])
            mitad=mitad/2;
        else if (NUM>vec[mitad])
            mitad=mitad+((mitad/2))+1;
        i++;
}
    printf("El programa tuvo %d iteraciones",i);
}

int main(){
    int vec[TAM]={1,4,5,12,25,27,31,42,43,56,73,76,78,80,99};

    //for(int i =0; i<TAM;i++)
    //    printf("%d, ",vec[i]);
    int t0 = time();
    busqSec(vec);
    int t1 = time();
    int milisegundos_totales = t1 - t0;
    printf("tiempo de busqueda secuencial: %d\n",milisegundos_totales);

    busqBin(vec);
return 0;
}
