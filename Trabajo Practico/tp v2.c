//TRABAJO PRACTICO DE LABORATORIO DE COMPUTACION II
//BRIAN MILOWSKI
/*
Archivos correspondientes al programa:
tp.c
creditos.csv
ventas.csv
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct structCSV{
    int orden;
    char cliente[20];
    int importe;
    char electro[20];
    int dia,mes,anio,cuotas;
    float importeCuotas,iva,totCuota;
    char valido;
};

//listar csv
void listarCSV(){
    FILE*csvArch;
    struct structCSV datos;
    char c,aux[20];
    int i=0,col=0,flag=0;
    csvArch=fopen("creditos.csv","r");

    if (csvArch!=NULL){
        printf("ORDEN\tCLIENTE\t\tIMPORTE\tELECTRO\t\tDIA/MES/ANIO\tN.CUOT\tIMPORT CUOTAS\tIVA\tTOT CUOTAS\n");
        while (!feof(csvArch)){

            c = fgetc(csvArch); //leemos caracter a caracter

            if(col==11){ //si la columna es 11, se hace un salto de linea y volver a empezar
                col=0;
                if(flag==1)//se crea la variable flag (inicializada en 0) para poder ver si es el primer salto de linea, ya que los indices se imprimen aparte
                    printf("%d\t%.15s\t%d\t%.19s\t%d/%d/%d\t%d\t%.2f\t\t%.2f\t%.2f\n",datos.orden,
                           datos.cliente,datos.importe,datos.electro,datos.dia,datos.mes,datos.anio,
                           datos.cuotas,datos.importeCuotas,datos.iva,datos.totCuota);
                flag=1;
            }

            if (c!=';' && c!='\n'){ // si el caracter no es un cambio de columna del .csv -> compiamos el caracter en el string auxiliar
                aux[i]=c;
                i++;
            }else{ //si el caracter es un cambio de columna del csv:
                aux[i]='\0'; //ponemos un barra0 al final del string aux
                i=0;
                switch(col){ // guardar los datos en el struct para cada columna.
                    //int:
                    case 0://orden
                        datos.orden=atoi(aux);
                        break;
                    case 2://importe
                        datos.importe=atoi(aux);
                        break;
                    case 4://dia
                        datos.dia=atoi(aux);
                        break;
                    case 5://mes
                        datos.mes=atoi(aux);
                        break;
                    case 6://anio
                        datos.anio=atoi(aux);
                        break;
                    case 7://nroCuotas
                        datos.cuotas=atoi(aux);
                        break;
                    //string:
                    case 1://cliente
                        strcpy(datos.cliente,aux);
                        break;
                    case 3://electro
                        strcpy(datos.electro,aux);
                        break;
                    //float:
                    case 8:
                        datos.importeCuotas=atoi(aux);
                        break;
                    case 9:
                        datos.iva=atoi(aux);
                        break;
                    case 10:
                        datos.totCuota=atoi(aux);
                        break;
                }
                col++;
            }
        }
        printf("\n");
    fclose(csvArch);
    }else
        printf("No se pudo abrir el archivo.\n");
}

//crear creditos.dat
void crearbin(){
    FILE *archBin;
    if ((archBin=fopen("creditos.dat","w+b"))==NULL)
        printf("No pudo crearse el archivo.\n");
    else{
        printf("Archivo creado exitosamente.\n");
        fclose(archBin);
    }
}

//migrar datos de creditos.csv a creditos.dat
void migrar(){
    struct structCSV datos;

    FILE*csvArch;
    csvArch=fopen("creditos.csv","r");

    FILE *archBin;
    archBin=fopen("creditos.dat","w+b");
/*
    int contador=0;char c=0; //calculamos la cantidad de datos para el struct
    while(c!=EOF){
        c=getc(csvArch);
        if(c=='\n')
            contador++;
    }
    contador--; //le restamos el indice
    printf("%d",contador);*/

    char c,aux[20];
    int i=0,col=0,j=0;
    while (!feof(csvArch)){
        c = fgetc(csvArch); //leemos caracter a caracter
        if(col==11){  //si la columna es 11, se hace un salto de linea y volver a empezar
            col=0;
            datos.valido='S';
            fseek(archBin,(datos.orden-1)*sizeof(struct structCSV),SEEK_SET);
            fwrite(&datos,sizeof(struct structCSV),1,archBin);
        }
        if (c!=';' && c!='\n'){ // si el caracter no es un cambio de columna del .csv -> compiamos el caracter en el string auxiliar
            aux[i]=c;
            i++;
        }else{ //si el caracter es un cambio de columna del csv:
            aux[i]='\0'; //ponemos un barra0 al final del string aux
            i=0;
            switch(col){ // guardar los datos en el struct para cada columna.
                //int:
                case 0://orden
                    datos.orden=atoi(aux);
                    break;
                case 2://importe
                    datos.importe=atoi(aux);
                    break;
                case 4://dia
                    datos.dia=atoi(aux);
                    break;
                case 5://mes
                    datos.mes=atoi(aux);
                    break;
                case 6://anio
                    datos.anio=atoi(aux);
                    break;
                case 7://nroCuotas
                    datos.cuotas=atoi(aux);
                    break;
                //string:
                case 1://cliente
                    strcpy(datos.cliente,aux);
                    break;
                case 3://electro
                    strcpy(datos.electro,aux);
                    break;
                //float:
                case 8:
                    datos.importeCuotas=atoi(aux);
                    break;
                case 9:
                    datos.iva=atoi(aux);
                    break;
                case 10:
                    datos.totCuota=atoi(aux);
                    break;
            }
            col++;
        }
    }
    fseek(archBin,(datos.orden-1)*sizeof(struct structCSV),SEEK_SET);
    fwrite(&datos,sizeof(struct structCSV),1,archBin);

    fclose(csvArch);
    fclose(archBin);
}

//listar creditos.dat
void listarDat(){
    struct structCSV datos;
    int i=0, cantData;

    FILE *archBin;
    archBin=fopen("creditos.dat","rb");

    fseek(archBin, 0, SEEK_END);
    cantData = ftell(archBin) / sizeof(struct structCSV);
    fseek(archBin, 0, SEEK_SET);//calculamos la cantidad de lineas de datos para usarlos en los structs

    //printf("CANTIDAD DE DATAA!!!!   %d\n",cantData);

    for (i=0;i<cantData;i++){
        fread(&datos,sizeof(struct structCSV),1,archBin);
        printf("%d\t%.15s\t%d\t%.19s\t%d/%d/%d\t%d\t%.2f\t\t%.2f\t%.2f\t%c\n",datos.orden,
            datos.cliente,datos.importe,datos.electro,datos.dia,datos.mes,datos.anio,
            datos.cuotas,datos.importeCuotas,datos.iva,datos.totCuota,datos.valido);
    }
    fclose(archBin);
}
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
                listarCSV();
                break;
            case 2:
                printf("Llamar a 'Crear archivo creditos.dat'\n");
                crearbin();
                break;
            case 3:
                printf("Llamar a 'Migrar datos de .csv a .dat'\n");
                migrar();
                break;
            case 4:
                printf("Llamar a 'Listar .dat'\n");
                listarDat();
                break;
            case 5:
                printf("Llamar a 'Dar de Alta a un nuevo cliente'.\n");
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
