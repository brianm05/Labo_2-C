#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define TAM 3

struct struct_empleados{
    char apellido[15];
    char sexo;
    int horaTrabajadas;
    float sueldo;
};

void cargaDatos(struct struct_empleados v[]){
    bool verificacion=false;
    for(int i=0;i<TAM;i++){
        printf("\nIngrese los datos del empleado %d:",i);

        printf("\nIngrese el apellido. ");
        gets(v[i].apellido);
        fflush(stdin);
        v[i].apellido[0]=toupper(v[i].apellido[0]);

        verificacion=false;
        while(verificacion==false){
            printf("Ingrese el genero. [F]/[M] ");
            scanf("%c",&v[i].sexo);
            fflush(stdin);
                switch(v[i].sexo){
                    case 'm':
                    case 'M':
                    case 'f':
                    case 'F':
                        verificacion=true;
                        break;
                    default:
                        break;
                }
        }
        verificacion=false;
        while(verificacion==false){
            printf("Ingrese las horas trabajadas. ");
            scanf("%d",&v[i].horaTrabajadas);
            fflush(stdin);
            if((v[i].horaTrabajadas>0) && (v[i].horaTrabajadas<=50)){
                verificacion=true;
            }
        }
        verificacion=false;
        while(verificacion==false){
            printf("Ingrese el sueldo. ");
            scanf("%f",&v[i].sueldo);
            fflush(stdin);
            if(v[i].sueldo>=10.2f){
                verificacion=true;
            }
        }
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
        printf("\nSueldo por hora: %f.",v[i].sueldo);
        printf("\n");
    }
}
void emisionDatos2(struct struct_empleados v[]){
    printf("\nEMISION DE DATOS (SIMPLIFICADO).");
    for(int i=0;i<TAM;i++){
        printf("\nEmesion de datos del empleado: %d.",i);
        printf("\nApellido: %s.",v[i].apellido);
        printf("\nSueldo total: %f.",v[i].sueldo*v[i].horaTrabajadas);
        printf("\n");
    }
}
void emisionTotalPago(struct struct_empleados v[]){
    int contadorF=0,contadorM=0,totalSueldoF=0,totalSueldoM=0;
    printf("\nEMISION TOTAL PAGO POR GENERO.");
    for(int i=0;i<TAM;i++){
        if((v[i].sexo=='m') || (v[i].sexo=='M')){
            contadorM++;
            totalSueldoM=totalSueldoM+(v[i].sueldo*v[i].horaTrabajadas);
        }
        else if ((v[i].sexo=='f') || (v[i].sexo=='F')){
            contadorF++;
            totalSueldoF=totalSueldoF+(v[i].sueldo*v[i].horaTrabajadas);
        }
    }
    printf("\nEmpleados femeninos: %d.",contadorF);
    printf("\nTotal de pago para empleados femeninos: %d.",totalSueldoF);
    printf("\nEmpleados masculinos: %d.",contadorM);
    printf("\nTotal de pago para empleados masculinos: %d.",totalSueldoM);
    printf("\n");
}
void emisionSueldoPromedio(struct struct_empleados v[]){
    int contadorF=0,contadorM=0,totalSueldoF=0,totalSueldoM=0;
    printf("\nEMISION DE SUELDO PROMEDIO POR GENERO.");
    for(int i=0;i<TAM;i++){
        if((v[i].sexo=='m') || (v[i].sexo=='M')){
            contadorM++;
            totalSueldoM=totalSueldoM+(v[i].sueldo*v[i].horaTrabajadas);
        }
        else if ((v[i].sexo=='f') || (v[i].sexo=='F')){
            contadorF++;
            totalSueldoF=totalSueldoF+(v[i].sueldo*v[i].horaTrabajadas);
        }
    }
    if(contadorF!=0){
        printf("\nEmpleados femeninos: %d.",contadorF);
        printf("\nSueldo promedio para empleados femeninos: %d.",totalSueldoF/contadorF);
    }else{printf("\nNo hay empleados femeninos.");}
    if(contadorM!=0){
        printf("\nEmpleados masculinos: %d.",contadorM);
        printf("Sueldo promedio para empleados masculinos: %d.",totalSueldoM/contadorM);
    }else{printf("\nNo hay empleados masculinos.");}
    printf("\n");
}

void menu(struct struct_empleados empleadosArray[]){
    int eleccion=1;

    while(eleccion!=0){
        printf("------BIENVENIDO AL MENU.------\n");
        printf("Digite 0 para salir.\n");
        printf("Digite 1 para ingresar datos.\n");
        printf("Digite 2 para emitir datos.\n");
        printf("Digite 3 para emitir solo nombre y sueldo de los empleados.\n");
        printf("Digite 4 para ver el total de pago para cada genero.\n");
        printf("Digite 5 para ver el sueldo promedio para cada genero.\n");
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
            case 4:
                emisionTotalPago(empleadosArray);
                break;
            case 5:
                emisionSueldoPromedio(empleadosArray);
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

    menu(empleadosArray);

return 0;}
