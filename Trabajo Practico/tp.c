#include<stdio.h>>
#include<stdlib.h>
#include<string.h>



void menu(){
    int eleccion=1;

    while(eleccion!=0){
        printf("-------MENU.-------\n");
        printf("Digite 1 para 'Listar csv'.\n");
        printf("Digite 2 para 'Crear archivo creditos.dat'.\n");
        printf("Digite 3 para 'Migrar datos de .csv a .dat'.\n");
        printf("Digite 4 para 'Listar .dat'.\n");
        printf("Digite 5 para 'Dar de Alta a un nuevo cliente'.\n");
        printf("Digite 6 para 'Buscar cliente'.\n");
        printf("Digite 7 para 'Modificar importe de credito'.\n");
        printf("Digite 8 para 'Dar de Baja Logica'.\n");
        printf("Digite 9 para 'Dar de Baja Fisica'.\n");
        printf("Digite 10 para 'Listar archivo tipo .xyz'.\n");
        printf("Digite 0 para salir.\n");
        scanf("%d",&eleccion);

        switch(eleccion){
            case 1:
                printf("Llamar a 'Listar csv'\n");
                break;
            case 2:
                printf("Llamar a 'Crear archivo creditos.dat'\n");
                break;
            case 3:
                printf("Llamar a 'Migrar datos de .csv a .dat'n");
                break;
            case 4:
                printf("Llamar a 'Listar .dat'\n");
                break;
            case 5:
                printf("Llamar a 'Dar de Alta a un nuevo cliente'.\\n");
                break;
            case 6:
                printf("Llamar a 'Buscar cliente'\n");
                break;
            case 7:
                printf("Llamar a 'Modificar importe de credito'\n");
                break;
            case 8:
                printf("Llamar a 'Dar de Baja Logica'\n");
                break;
            case 9:
                printf("Llamar a 'Dar de Baja Fisica'\n");
                break;
            case 10:
                printf("Llamar a 'Listar archivo tipo .xyz'\n");
                break;
            case 0:
                printf("Adios.\n");
                break;
            default:
                printf("No se encontro la opcion.\n");
                break;
        }
    }
}
int main(){
    menu();
return 0;}
