#include<stdio.h>
#include<time.h>
#include<stdlib.h>

struct camion{
    char modelo[30];
    int ruedas;
    float km;
    float precio;
};

int main(){
    struct camion fiat_600 ={"fiat 600",6,7547.12,15000};

    struct camion camion_usuario;

    printf("Ingrese modelo, numero de ruedas, kilometraje, y precio\n");
    scanf("%s", &camion_usuario.modelo);
    scanf("%d", &camion_usuario.ruedas);
    scanf("%f", &camion_usuario.km);
    scanf("%f", &camion_usuario.precio);
    printf("Modelo: %s, N° de ruedas: %d, Kilometraje: %d, Precio: %.2f\n",
    camion_usuario.modelo, camion_usuario.ruedas, camion_usuario.km, camion_usuario.precio);

    printf("Modelo: %s, N° de ruedas: %d, Kilometraje: %d, Precio: %.2f\n",
    fiat_600.modelo, fiat_600.ruedas, fiat_600.km, fiat_600.precio);

return 0;
}
