#include "misfunciones.h"
#include <stdio.h>
/*----------------------------------------------------------------------------*/
/* Función par: Devuelve un valor indicando si un número entero es par o no. */
int par(int numero){
printf("Funci%cn par\n", 162);
if((numero%2)==0)
                 return(1);
else
                 return(0);
}
/*----------------------------------------------------------------------------*/
/* Función media2: Devuelve la media de 2 números.*/
float media2(float n1, float n2)
{printf("Funci%cn media\n", 162);
float resultado;
      resultado=(n1+n2)/2;
return(resultado);
}
/*----------------------------------------------------------------------------*/
/* Función negativo: Devuelve 1 si es negativo el número entero
pasado como parámetro, o 0 si no lo es. */
int negativo(int numero)
{
    printf("Funci%cn negativo\n", 162);
    int res;
    if (numero<0)
        res=1;
    else
        res=0;
    return(res);
}
/*---------------------------------------------------------------------------*/
/*Función media3: Informa de la media de 3 números*/
void media3(float n1, float n2, float n3){
    printf("Funci%cn media\n", 162);
float resultado;
      resultado=(n1+n2+n3)/3;
printf("La media es:%f\n",resultado);
}
/*----------------------------------------------------------------------------*/
// Función pedir: Pide un número entero.*/
int pedir(){
int n;
    printf("Introduzca un número entero:\n");
    scanf("%i",&n);
return(n);
}
/*----------------------------------------------------------------------------*/
/*Función triple: devuelve el triple del parámetro.*/
int triple(int num){
    printf("Funci%cn triple\n", 162);
int n;
    n=3*num;
return(n);
}

