#include<stdio.h>

struct fecha{
int dia,mes,anio;
};

struct vuelo{
char origen[5];
char destino[5];
int duracion;
float precio;
struct fecha fec;
};


int main(){
    struct vuelo primer_vuelo={"ARG","URU",21,43.33,15,4,2024};

    printf("Datos del vuelo.\n");
    printf("Origen:%s\n",primer_vuelo.origen);
    printf("Destino:%s\n",primer_vuelo.destino);
    printf("Duracion:%d\n",primer_vuelo.duracion);
    printf("Precio:%f\n",primer_vuelo.precio);
    printf("Fecha:%d/%d/%d\n",primer_vuelo.fec.dia,primer_vuelo.fec.mes,primer_vuelo.fec.anio);

return 0;}
