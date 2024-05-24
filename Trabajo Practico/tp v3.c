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

#define CSV "creditos.csv"
#define DAT "creditos.dat"

struct structCSV{
    int orden;
    char cliente[20];
    int importe;
    char electro[20];
    int dia,mes,anio,cuotas;
    float importeCuotas,iva,totCuota;
    char valido;
};

//listar creditos.csv
void listarCSV(){
    FILE*csvArch;
    struct structCSV datos;
    char c,aux[20];
    int i=0,col=0,flag=0;
    csvArch=fopen(CSV,"r");

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
    if ((archBin=fopen(DAT,"w+b"))==NULL)
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
    csvArch=fopen(CSV,"r");

    FILE *archBin;
    archBin=fopen(DAT,"w+b");

    char c,aux[20];
    int i=0,col=0,j=0;
    while (!feof(csvArch)){
        c = fgetc(csvArch); //leemos caracter a caracter
        if(col==11){  //si la columna es 11, se hace un salto de linea y volver a empezar
            col=0;
            fseek(archBin,(datos.orden-1)*sizeof(struct structCSV),SEEK_SET);
            fwrite(&datos,sizeof(struct structCSV),1,archBin);//guardamops los datos en el archivo.dat
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
                    strcpy(datos.electro,strupr(aux));
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

    fclose(csvArch);
    fclose(archBin);
}

//listar creditos.dat
void listarDat(){
    struct structCSV datos;
    int resultado=0,cantData=0;
    char eleccion=0,electroEleccion[20];

    FILE *archBin;
    archBin=fopen(DAT,"rb");

    fseek(archBin, 0, SEEK_END);
    cantData = ftell(archBin)/sizeof(struct structCSV);
    fseek(archBin, 0, SEEK_SET);//calculamos la cantidad de lineas de datos para usarlos en los structs

    while(eleccion!='A' && eleccion!='a' && eleccion!='B' && eleccion!='b'){
        printf("%cComo quiere emitir la lista?\n",168);
        printf("[A] Listar todos (activos y inactivos).\n");
        printf("[B] El ingreso por teclado de un tipo de electro.\n");
        eleccion=getchar();
        fflush(stdin);
    }

    if(eleccion=='A' || eleccion=='a'){
        printf("ORDEN\tCLIENTE\t\tIMPORTE\tELECTRO\t\tDIA/MES/ANIO\tN.CUOT\tIMPORT CUOTAS\tIVA\tTOT CUOTAS\tACTIVO\n");
        for (int i=0;i<cantData;i++){
            fread(&datos,sizeof(struct structCSV),1,archBin);
            printf("%d\t%.15s\t%d\t%.19s\t%d/%d/%d\t%d\t%.2f\t\t%.2f\t%.2f\t\t%c\n",datos.orden,
                datos.cliente,datos.importe,datos.electro,datos.dia,datos.mes,datos.anio,
                datos.cuotas,datos.importeCuotas,datos.iva,datos.totCuota,datos.valido);
        }
    }else{

        printf("%cQue tipo de electro quiere buscar?\n",168);
        gets(electroEleccion);
        fflush(stdin);

        printf("ORDEN\tCLIENTE\t\tIMPORTE\tELECTRO\t\tDIA/MES/ANIO\tN.CUOT\tIMPORT CUOTAS\tIVA\tTOT CUOTAS\tACTIVO\n");

        int flag=0;
        for (int i=0;i<cantData;i++){
            fread(&datos,sizeof(struct structCSV),1,archBin);

            resultado=strcmp(strupr(datos.electro),strupr(electroEleccion));

            if (resultado==0){
                flag=1;
                printf("%d\t%.15s\t%d\t%.19s\t%d/%d/%d\t%d\t%.2f\t\t%.2f\t%.2f\t\t%c\n",datos.orden,
                    datos.cliente,datos.importe,datos.electro,datos.dia,datos.mes,datos.anio,
                    datos.cuotas,datos.importeCuotas,datos.iva,datos.totCuota,datos.valido);
            }
        }
        if(flag==0)
            printf("No se encontraron concidencias con el electro: %s.\n",electroEleccion);
    }
    fclose(archBin);
}


int detectarOrden(int orden){
    struct structCSV datos;
    char c,aux[20];
    int col,i=0;

    FILE *csvArch;
    csvArch=fopen(CSV,"r+");

    while (!feof(csvArch)){
        c = fgetc(csvArch); //leemos caracter a caracter
        if(col==11){  //si la columna es 11, se hace un salto de linea y volver a empezar
            col=0;
            if(orden==datos.orden)
                return 0;
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
            }
            col++;
        }
    }
    fclose(csvArch);
    return 1;
}

//dar de alta a un cliente
void alta(){
    struct structCSV datos;
    char c,linea[200]={},aux[20];
    int resultado=0;


    while(datos.orden<0 || resultado==0){
        printf("Ingrese numero de orden:\n");
        scanf("%d",&datos.orden);
        fflush(stdin);
        if(datos.orden<=0)
            printf("El numero de orden tiene que ser mayor que 0.\n");

        resultado=detectarOrden(datos.orden);
        if(!resultado){
            printf("No se pudo registrar. Ese numero de orden ya esta en uso.\n");
            return;
        }
    }
    printf("Ingrese nombre y apellido:\n");
    gets(datos.cliente);
    fflush(stdin);

    do{
        printf("Ingrese importe:\n");
        scanf("%d",&datos.importe);
        fflush(stdin);
        if(!(datos.importe>0))
            printf("El importe debe ser mayor a 0.\n");
    }while(datos.importe<=0);

    do{
        printf("Seleccione el electro.\n[H]Para heladera.\n[L]Para lavarropas\n[T]Para televisor.\n");
        scanf("%c",&c);
        fflush(stdin);
    }while((c!='H') && (c!='h') && (c!='L') && (c!='l') && (c!='T') && (c!='t'));
    switch(c){
        case 'H':
        case 'h':
            strcpy(datos.electro,"Heladera");
            break;
        case 'L':
        case 'l':
            strcpy(datos.electro,"Lavarropa");
            break;
        case 'T':
        case 't':
            strcpy(datos.electro,"Televisor");
            break;
    }

    do{
        printf("Ingrese el numero de cuotas:\n");
        scanf("%d",&datos.cuotas);
        fflush(stdin);
        if(!(datos.cuotas>0))
            printf("El numero de cuotas debe ser mayor a 0.\n");
    }while(datos.cuotas<=0);

    datos.importeCuotas=datos.importe/datos.cuotas;
    datos.iva=datos.importeCuotas*21/100;
    datos.totCuota=datos.importe+datos.iva;

    FILE *csvArch;
    csvArch=fopen(CSV,"a+");

    //fseek(csvArch, datos.orden*sizeof(struct structCSV), SEEK_END);

    fprintf(csvArch,"%d;%s;%d;%s;%d;%d;%d;%d;%.2f;%.2f;%.2f",datos.orden,datos.cliente,
            datos.importe,datos.electro,datos.dia,datos.mes,datos.anio,datos.cuotas,
            datos.importeCuotas,datos.iva,datos.totCuota);

        /*
        c=';';
        strcpy(linea, "");//asegurarse de que linea esta vacio

        //agregar los datos al string linea con el formato de .csv
        sprintf(aux, "%d", datos.orden);
        strcat(linea, aux);
        strcat(linea, &c);

        strcat(linea, datos.cliente);
        strcat(linea, &c);

        sprintf(aux, "%.2f", datos.importe);
        strcat(linea, aux);
        strcat(linea, &c);

        strcat(linea, datos.electro);
        strcat(linea, &c);

        sprintf(aux, "%d/%d/%d", datos.dia, datos.mes, datos.anio);
        strcat(linea, aux);
        strcat(linea, &c);

        sprintf(aux, "%d", datos.cuotas);
        strcat(linea, aux);
        strcat(linea, &c);

        sprintf(aux, "%.2f", datos.importeCuotas);
        strcat(linea, aux);
        strcat(linea, &c);

        sprintf(aux, "%.2f", datos.iva);
        strcat(linea, aux);
        strcat(linea, &c);

        sprintf(aux, "%.2f", datos.totCuota);
        strcat(linea, aux);

        //guardamops los datos con formato csv en creditos.csv
        fputs(linea,csvArch);
        */
    fclose(csvArch);
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
        fflush(stdin);

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
                alta();
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
