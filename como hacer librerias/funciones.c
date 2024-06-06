#include <stdio.h>
#include <stdlib.h>
#include "misfunciones.h"

int main()
{
int numero, resultado, total;
float n1, n2, n3, res;

printf("Introduzca un n%cmero:\n", 163);
scanf("%i",&numero);
resultado=par(numero);

if (resultado==1)
   printf("Es par.\n");
else
    printf("Es impar.\n");

printf("Introduzca un n%cmero real:\n", 163);
scanf("%f",&n1);
printf("Introduzca otro n%cmero real:\n", 163);
scanf("%f",&n2);
res=media2(n1,n2);
printf("La media es: %.2f.\n",res);


printf("Introduzca un n%cmero real:\n", 163);
scanf("%f",&n1);
printf("Introduzca otro n%cmero real:\n", 163);
scanf("%f",&n2);
printf("Introduzca otro n%cmero real:\n", 163);
scanf("%f",&n3);

media3(n1,n2,n3);

numero=pedir();
total =triple(numero);
printf("El triple de %i es: %i\n",numero, total);

system ("pause") ;
return 0;
 }
