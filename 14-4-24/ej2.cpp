//Crea un array dinámico de enteros.
//Luego define una función que reciba un vector de enteros V y su tamaño TAM y devuelva
//“True” si está ordenado o “False” si no está ordenado.

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

#define TAM 5
/*
void insercion(int* vaux){
    int i, j;
    int actual;
    bool flag;

    for (i = 1; i < TAM; i++) {
        actual = vaux[i];
        for (j = i; j > 0 && vaux[j - 1] > actual; j--) {
            vaux[j] = vaux[j - 1];
        }
        vaux[j] = actual;
        //printf("%d",vaux[i]);
        }
    if (flag==true)
        printf("Desordenado");

}*/

void burbuja(int* vaux)
{
    int i = 0;
    bool permutation = true,flag=false;
    int actual;

    while ( permutation) {
        permutation = false;
        i++;
        for (actual=0;actual<TAM-i;actual++) {
            if (vaux[actual]>vaux[actual+1]){
                permutation = true;
                flag=true;
                // Intercambiamos los dos elementos
                /*int temp = vaux[actual];
                vaux[actual] = vaux[actual+1];
                vaux[actual+1] = temp;*/
            }
        }
    }
    if (flag==true)
        printf("\nArray desordenado.");
    else
        printf("\nArray ordenado.");
}

void cargoVecAux(int *vaux){
    for(int i=0 ; i<TAM; i++){
        printf("ingrese 5 valores:\n");
        scanf("%d",&vaux[i]);
    }
}

void emitoVacAux(int*vaux){
    printf("\nArray actual: ");
    for(int i=0 ; i<TAM; i++)
        printf("[%d]",vaux[i]);
}


int *creoVecAux(){
    int *vaux;
    if ((vaux=(int*)malloc(sizeof(int)))==NULL){
        printf("Insuficiente espacio de memoria\n");
        exit(-1);
    }
    else{
        printf("dentro de la funcion de creacion\n",vaux);
    }


return vaux;
}

int main(){
    int *vauxiliar=NULL;

    printf("antes de crear el array %d\n", vauxiliar);
    vauxiliar=creoVecAux();
    printf("luego de crear el array %d\n", vauxiliar);

    cargoVecAux(vauxiliar);
    emitoVacAux(vauxiliar);
    burbuja(vauxiliar);
    emitoVacAux(vauxiliar);


return 0;}
