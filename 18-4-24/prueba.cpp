#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TAM 2

struct struct_empleados{
    char apellido[15];
    char sexo;
    int horaTrabajadas;
    int sueldo;
};

void cargaDatos(struct struct_empleados v[]){
    for(int i=0;i<TAM;i++){
        printf("\nIngrese los datos del empleado %d:",i);
        printf("\nIngrese el apellido. ");
        gets(v[i].apellido);
        fflush(stdin);
        printf("Ingrese el genero. [F]/[M] ");
        scanf("%c",&v[i].sexo);
        fflush(stdin);
        printf("Ingrese las horas trabajadas. ");
        scanf("%d",&v[i].horaTrabajadas);
        fflush(stdin);
        printf("Ingrese el sueldo. ");
        scanf("%d",&v[i].sueldo);
        fflush(stdin);
        printf("\n");
    }
}
void emisionDatos(struct struct_empleados v[]){
    printf("\nEMISION DE DATOS.");
    for(int i=0;i<TAM;i++){
        printf("\nEmesion de datos del empleado: %d.",i);
        printf("\nApellido: %s.",v[i].apellido);
        printf("\nGenero: %c.",v[i].sexo);
        printf("\nHoras trabajadas: %d.",v[i].horaTrabajadas);
        printf("\nSueldo por hora: %d.",v[i].sueldo);
        printf("\n");
    }
}
void emisionDatos2(struct struct_empleados v[]){
    printf("\nEMISION DE DATOS.");
    for(int i=0;i<TAM;i++){
        printf("\nEmesion de datos del empleado: %d.",i);
        printf("\nApellido: %s.",v[i].apellido);
        printf("\nSueldo total: %d.",v[i].sueldo*v[i].horaTrabajadas);
        printf("\n");
    }
}
void menu(struct struct_empleados empleadosArray[]){
    int eleccion=1;

    while(eleccion!=0){
        printf("--BIENVENIDO AL MENU.--\n");
        printf("Digite 0 para salir.\n");
        printf("Digite 1 para ingresar datos.\n");
        printf("Digite 2 para emitir datos.\n");
        printf("Digite 3 para emitir solo nombre y sueldo de los empleados.\n");
        printf("Digite 4 para ver el total de pago para cada genero.\n");
        scanf("%d",&eleccion);
        fflush(stdin);

        switch(eleccion){
            case 0:
                printf("Adios.");
                break;
            case 1:
                cargaDatos(empleadosArray);
                break;
            case 2:
                emisionDatos(empleadosArray);
                break;
            case 3:
                emisionDatos2(empleadosArray);
                break;
            default:
                break;
        }
        printf("\n");
    }
}

int main(){
    int flag=0;
    struct struct_empleados empleadosArray[TAM];

    //cargaDatos(empleadosArray);
    //emisionDatos(empleadosArray);

    menu(empleadosArray);

return 0;}
