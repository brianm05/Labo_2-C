#include<stdio.h>
#include<stdlib.h>

#define NUM 4
#define FILA 4
#define COLUMNA 6


struct sucursales{
    int id_sucursal=0;
    char ciudad[30];
    float descuentos_del_mes[30]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,8,9,0,1,2,3,4,5,6,7,8,9,0};
    float total_de_descuentos=0;
    float promedio_descuentos=0;
};
struct gerentes{
    int id_sucursal=0;
    char nombre_gerente[30];
};

void cargaTotalDescuentos(struct sucursales v[]){

    for(int i=0;i<NUM;i++){
        printf("Sucursal: %d.\n",i);
        for(int j=0;j<30;j++){
            v[i].total_de_descuentos=v[i].total_de_descuentos+v[i].descuentos_del_mes[j];
        }
        printf("Total descuento: %.2f\n",v[i].total_de_descuentos);
    }
}

void cargaPromedioDescuentos(struct sucursales v[],float descuentos[FILA][COLUMNA]){
    float total=0;
    for(int j=0;j<FILA;j++){
        for(int k=0;k<COLUMNA;k++){
            total=total+descuentos[j][k];
        }
    v[j].promedio_descuentos=total/COLUMNA;
    printf("Promedio de descuentos de la sucursal %d: %.2f\n",j,v[j].promedio_descuentos);
    total=0;
    }
}
int sucursales_descuento(){
int resultado=0;





return resultado;}

int main(){
    int sucursalesMuchoDescuento=0;
    struct sucursales sucursal[NUM];

    int enteros[NUM]={-1};
    float descuentos_anteriores[FILA][COLUMNA]={100,150,180,210,150,230,
                                                400,200,300,250,20,150,
                                                150,200,140,450,150,320,
                                                180,190,320,60,180,140};

    cargaTotalDescuentos(sucursal);
    cargaPromedioDescuentos(sucursal,descuentos_anteriores);

    sucursalesMuchoDescuento=sucursales_descuento(sucursal,enteros);
    printf("Sucursales con descuento mayor al promedio: %d",sucursalesMuchoDescuento);
/*
3. Función que reciba el array de sucursales, el array de enteros y cargue en este array, las
posiciones de los registros del array de sucursales cuyo ‘Total_de_descuentos_del mes supere al
‘Promedio_ Descuentos’. Los datos deben almacenarse en forma contigua. Esta función debe retornar
la cantidad de sucursales detectada.
*/
return 0;
}
