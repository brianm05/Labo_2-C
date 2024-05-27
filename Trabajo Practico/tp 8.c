//TRABAJO PRACTICO DE LABORATORIO DE COMPUTACION II
//BRIAN MILOWSKI
//Fecha de entrega: 27-5-2024
/*
Archivos correspondientes al programa:
tp.c
creditos.csv
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define CSV "creditos.csv"
#define DAT "creditos.dat"

//Creamos el struct con las variables necesarias para guardar los datos de los clientes.
struct structCSV{
    int orden;
    char cliente[20];
    int importe;
    char electro[20];
    int dia,mes,anio,cuotas;
    float importeCuotas,iva,totCuota;
    char valido;
};

//Funcion que retorna 1 en caso de confirmar, 0 en caso contrario.
int confimar(){
    int eleccion;
    printf("%cEst%c seguro de continuar con esta acci%cn?\n[S] Para confirmar.\n",168,160,162);
    scanf("%c",&eleccion);
    if(eleccion=='S' || eleccion=='s'){
        printf("[S]\n");
        return 1;
    }else{
        printf("No se complet%c la acci%cn.\n",162,162);
        return 0;
    }
}

//Funcion que verifica que el numero ingresado sea mayor que 0 y lo retorna.
int mayorQueCero(){
    int num;
    scanf("%d",&num);
    fflush(stdin);
    while(num<=0){
        printf("El n%cmero ingresado debe ser mayor que 0.\n",163);
        printf("Ingrese nuevamente.\n");
        scanf("%d",&num);
        fflush(stdin);
    }
return num;}

//Funcion que obtiene la fecha y la devuelve en el char fec[20].
void obtenerFecha(char fec[20]){
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);

    strftime(fec,128,"%d-%m-%Y",tlocal);
}

//Funcion que recibe 3 int y verifica que sea una fecha valida, retornando 1 si es valida y 0 en caso contrario.
int verificarFecha(int dia,int mes,int anio){
    int flag=0;

    if(mes>=1 && mes<=12)
        switch (mes){
            case 1:
            case 3:
            case 5:
            case 7:
            case 8:
            case 10:
            case 12:
                if(dia>=1 && dia<=31)
                    flag = 1;
                    break;
            case 4:
            case 6:
            case 9:
            case 11:
                if (dia>=1 && dia<=30)
                    flag = 1;
                    break;
            case 2:
                if(anio%4==0 && anio%100!=0 || anio%400==0){
                    if (dia>=1 && dia <= 29)
                        flag = 1;
                }else if (dia>=1 && dia <=28)
                    flag = 1;
        }

    if (flag==1)
        return 1;
    else
        return 0;
}

//Funcion para mostrar por pantalla la lista del archivo creditos.csv
void listarCSV(){
    FILE*csvArch;
    struct structCSV datos;
    char c,aux[20];
    int i=0,col=0,flag=0;
    csvArch=fopen(CSV,"r");

    if (csvArch!=NULL){
        printf("ORDEN\tCLIENTE\t\tIMPORTE\tELECTRO\t\tDIA/MES/ANIO\tN.CUOT\tIMPORT CUOTAS\tIVA\tTOT CUOTAS\n");//Imprimir indices
        while (!feof(csvArch)){

            c = fgetc(csvArch);             //Leemos caracter a caracter.

            if(col==11){                    //Si la columna es 11, se hace un salto de linea y se vuelve a empezar.
                col=0;
                if(flag==1)                 //Se crea la variable flag (inicializada en 0) y se usa
                                            //para poder ver si es el primer salto de linea, ya que los indices se imprimen aparte.
                    printf("%d\t%.15s\t%d\t%.19s\t%d/%d/%d\t%d\t%.2f\t\t%.2f\t%.2f\n",datos.orden,
                           datos.cliente,datos.importe,datos.electro,datos.dia,datos.mes,datos.anio,
                           datos.cuotas,datos.importeCuotas,datos.iva,datos.totCuota);
                flag=1;
            }

            if (c!=';' && c!='\n'){     //Si el caracter no es un cambio de columna del .csv -> compiamos el caracter en el string auxiliar.
                aux[i]=c;
                i++;
            }else{                      //Si el caracter es un cambio de columna del csv:
                aux[i]='\0';            //Ponemos un barra0 al final del string aux.
                i=0;
                switch(col){            //Guardamos los datos en el struct para cada columna.
                    //int:
                    case 0:datos.orden=atoi(aux); break;
                    case 2:datos.importe=atoi(aux); break;
                    case 4:datos.dia=atoi(aux); break;
                    case 5:datos.mes=atoi(aux); break;
                    case 6:datos.anio=atoi(aux); break;
                    case 7:datos.cuotas=atoi(aux); break;
                    //string:
                    case 1:strcpy(datos.cliente,aux); break;
                    case 3:strcpy(datos.electro,aux); break;
                    //float:
                    case 8:datos.importeCuotas=atof(aux); break;
                    case 9:datos.iva=atof(aux); break;
                    case 10:datos.totCuota=atof(aux); break;

                    //La funcion atoi() convierte Ascii to int
                    //La funcion sytcpy() copia el string aux en datos.x
                    //La funcion atof() convierte Ascii to float
                }
                col++;
            }
        }
        printf("\n");

    fclose(csvArch);
    }else
        printf("No se pudo abrir el archivo.\n");
}

//Funcion para crear el archivo creditos.dat
void crearBin(){
    FILE *archBin;
    if ((archBin=fopen(DAT,"w+b"))==NULL)
        printf("Error al crear el archivo.\n");
    else{
        printf("Archivo creado exitosamente.\n");
        fclose(archBin);
    }
}

//Funcion para migrar los datos de creditos.csv a creditos.dat
void migrar(){
    struct structCSV datos;

    char c,aux[20];
    int i=0,col=0,j=0;

    FILE*csvArch;
    csvArch=fopen(CSV,"r");
    FILE *archBin;
    archBin=fopen(DAT,"w+b");

    while (!feof(csvArch)){
        c = fgetc(csvArch);                 //Leemos caracter a caracter.
        if(col==11){                        //Si la columna es 11, se hace un salto de linea
                                            //y guardamos los datos recopilados en el archivo binario.
            col=0;
            fseek(archBin,(datos.orden-1)*sizeof(struct structCSV),SEEK_SET);   //Reubicamos el cursor.
            fwrite(&datos,sizeof(struct structCSV),1,archBin);                  //Guardamos los datos en el archivo binario.
        }
        if (c!=';' && c!='\n'){     //Si el caracter no es un cambio de columna del .csv -> compiamos el caracter en el string auxiliar.
            aux[i]=c;
            i++;
        }else{                      //Si el caracter es un cambio de columna del csv:
            aux[i]='\0';            //Ponemos un barra0 al final del string aux.
            i=0;
            datos.valido='S';
            switch(col){            //Guardamos los datos en el struct para cada columna.
                //int:
                case 0:datos.orden=atoi(aux); break;
                case 2:datos.importe=atoi(aux); break;
                case 4:datos.dia=atoi(aux); break;
                case 5:datos.mes=atoi(aux); break;
                case 6:datos.anio=atoi(aux); break;
                case 7:datos.cuotas=atoi(aux); break;
                //string:
                case 1:strcpy(datos.cliente,aux); break;
                case 3:strcpy(datos.electro,aux); break;
                //float:
                case 8:datos.importeCuotas=atof(aux); break;
                case 9:datos.iva=atof(aux); break;
                case 10:datos.totCuota=atof(aux); break;

                //La funcion atoi() convierte Ascii to int
                //La funcion sytcpy() copia el string aux en datos.x
                //La funcion atof() convierte Ascii to float
            }
            col++;
        }
    }
    fclose(csvArch);
    fclose(archBin);
}

//Funcion para mostrar por pantalla la lista del archivo creditos.dat
void listarDat(){
    struct structCSV datos;
    int resultado=0,cantData=0;
    char eleccion=0,electroEleccion[20];

    FILE *archBin;
    archBin=fopen(DAT,"rb");

    fseek(archBin, 0, SEEK_END);                            //Situamos el cursor al final del archivo.
    cantData = ftell(archBin)/sizeof(struct structCSV);     //Usamos la funcion ftell para calcular la cantidad de
    fseek(archBin, 0, SEEK_SET);                            //datos y poder usarlos en los structs.

    while(eleccion!='A' && eleccion!='a' && eleccion!='B' && eleccion!='b'){
        printf("%cC%cmo quiere emitir la lista?\n",168,162);
        printf("[A] Listar todos (activos y inactivos).\n");
        printf("[B] El ingreso por teclado de un tipo de electro.\n");
        eleccion=getchar();
        fflush(stdin);
    }

    if(eleccion=='A' || eleccion=='a'){
        //Imprimimos el indice.
        printf("ORDEN\tCLIENTE\t\tIMPORTE\tELECTRO\t\tDIA/MES/ANIO\tN.CUOT\tIMPORT CUOTAS\tIVA\tTOT CUOTAS\tACTIVO\n");
        //Leemos e imprimos los datos de forma secuencial.
        for (int i=0;i<cantData;i++){
            fread(&datos,sizeof(struct structCSV),1,archBin);
            printf("%d\t%.15s\t%d\t%.19s\t%d/%d/%d\t%d\t%.2f\t\t%.2f\t%.2f\t\t%c\n",datos.orden,
                datos.cliente,datos.importe,datos.electro,datos.dia,datos.mes,datos.anio,
                datos.cuotas,datos.importeCuotas,datos.iva,datos.totCuota,datos.valido);
        }
    }else{

        printf("%cQu%c tipo de electro quiere buscar?\n",168,130);
        gets(electroEleccion);
        fflush(stdin);

        //Imprimimos el indice.
        printf("ORDEN\tCLIENTE\t\tIMPORTE\tELECTRO\t\tDIA/MES/ANIO\tN.CUOT\tIMPORT CUOTAS\tIVA\tTOT CUOTAS\tACTIVO\n");

        //Leemos de forma secuencial e imprimos SOLO los datos donde el string ingresado por el usuario y el de electro sean iguales.
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
            printf("0 concidencias con el electro: %s.\n",electroEleccion);
    }
    fclose(archBin);
}

//Funcion que retorna 0 si se encuentra el mismo numero de orden, caso contrario retorna 1.
int detectarOrden(int orden){
    struct structCSV datos;
    char c,aux[20];
    int col,i=0;

    FILE *csvArch;
    csvArch=fopen(CSV,"r+");

    while (!feof(csvArch)){
        c = fgetc(csvArch);             //Leemos caracter a caracter
        if(col==11){                    //Si la columna es 11, se hace un salto de linea y vuelve a empezar
            col=0;
            if(orden==datos.orden)      //Se encontro el mismo numero de orden, significa que ya esta siendo usado.
                return 0;
        }
        if (c!=';' && c!='\n'){         //Si el caracter no es un cambio de columna del .csv -> compiamos el caracter en el string auxiliar
            aux[i]=c;
            i++;
        }else{                          //Si el caracter es un cambio de columna del csv:
            aux[i]='\0';                //Sonemos un barra0 al final del string aux
            i=0;
            switch(col){                //Guardamos los datos en la variable del struct para compararla.
                case 0:
                    datos.orden=atoi(aux);
                    break;
            }
            col++;
        }
    }
    fclose(csvArch);
    return 1;
}

//Funcion que retorna 1 si se encuentra el mismo numero de orden, caso contrario retorna 0.
int detectarOrdenBinario(int orden){
    struct structCSV datos;
    int cantData,flag=0;

    FILE *archBin;
    archBin=fopen(DAT,"rb");

    fseek(archBin, 0, SEEK_END);                            //Situamos el cursor al final del archivo.
    cantData = ftell(archBin)/sizeof(struct structCSV);     //Usamos la funcion ftell para calcular la cantidad de
    fseek(archBin, 0, SEEK_SET);                            //datos y poder usarlos en los structs.

    for (int i=0;i<cantData;i++){
        fread(&datos,sizeof(struct structCSV),1,archBin);
        if(orden==datos.orden){
            flag=1;
            return 1;
        }
    }
    return 0;
}

//Funcion para dar de alta a un cliente.
void alta(){
    struct structCSV datos;
    struct structCSV auxDatos;
    char c,linea[200]={},aux[20];
    int resultado=0;
    int dia,mes,anio,fechaValida;

    printf("Ingrese n%cmero de orden:\n",163);
    datos.orden=mayorQueCero();

    resultado=detectarOrdenBinario(datos.orden);
    if (resultado==1){
        printf("Error al registrar. Ese n%cmero de orden ya esta en uso.\n",163);
        return;
    }

    printf("Ingrese el nombre y apellido:\n");
    fgets(datos.cliente, sizeof(datos.cliente), stdin);     //Leemod todo lo que escriba el usuario (incluido el '\n').
    datos.cliente[strcspn(datos.cliente, "\n")] = '\0';     //strcspn() busca el '\n' y lo igualamos a '\0'.

    printf("Ingrese el importe:\n");
    datos.importe=mayorQueCero();

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
        printf("Ingrese el d%ca.\n",161);
        scanf("%d",&dia);
        fflush(stdin);
        printf("Ingrese el mes.\n");
        scanf("%d",&mes);
        fflush(stdin);
        printf("Ingrese el a%co.\n",164);
        scanf("%d",&anio);
        fflush(stdin);
        fechaValida=verificarFecha(dia,mes,anio);
        if(fechaValida==0)
            printf("Fecha invalida, ingrese nuevamente.\n");
    }while(fechaValida==0);

    datos.dia=dia;
    datos.mes=mes;
    datos.anio=anio;

    printf("Ingrese el numero de cuotas:\n");
    datos.cuotas=mayorQueCero();

    datos.importeCuotas=datos.importe/datos.cuotas;
    datos.iva=(datos.importeCuotas*21)/100;
    datos.totCuota=datos.importe+datos.iva;

    datos.valido='S';

    FILE *archBin;
    archBin=fopen(DAT,"rb+");

    if (datos.orden == 1){
        fseek(archBin,0,SEEK_SET);
        fwrite(&datos,sizeof(struct structCSV),1,archBin);}
    else {
        fseek(archBin,(datos.orden-1)*sizeof(struct structCSV),SEEK_SET);
        fwrite(&datos,sizeof(struct structCSV),1,archBin);
        }

    fclose(archBin);

    //TODO EL SIGUIENTE CODIGO COMENTADO REGISTRABA AL USUARIO EN EL CSV. FINALMENTE DECIDI DAR DE ALTA EN EL ARCHIVO BINARIO.
    /*
    struct structCSV datos;
    struct structCSV auxDatos;
    char c,linea[200]={},aux[20];
    int resultado=0;

    printf("Ingrese numero de orden:\n");
    datos.orden=mayorQueCero();

    //Estas lineas verifican que ese numero de orden no esta siendo usado en el .csv
    resultado=detectarOrden(datos.orden);
    if(!resultado){
        printf("No se pudo registrar. Ese numero de orden ya esta en uso.\n");
        return;
    }

    printf("Ingrese nombre y apellido:\n");
    fgets(datos.cliente, sizeof(datos.cliente), stdin);     //Leemod todo lo que escriba el usuario (incluido el '\n').
    datos.cliente[strcspn(datos.cliente, "\n")] = '\0';     //strcspn() busca el '\n' y lo igualamos a '\0'.

    printf("Ingrese importe:\n");
    datos.importe=mayorQueCero();

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

    printf("Ingrese el numero de cuotas:\n");
    datos.cuotas=mayorQueCero();

    datos.importeCuotas=datos.importe/datos.cuotas;
    datos.iva=(datos.importeCuotas*21)/100;
    datos.totCuota=datos.importe+datos.iva;

    datos.dia=0;
    datos.mes=0;
    datos.anio=2024;

    FILE *csvArch;
    csvArch=fopen(CSV,"a+");

    fprintf(csvArch,"%d;%s;%d;%s;%d;%d;%d;%d;%.2f;%.2f;%.2f\n",
        datos.orden,datos.cliente,datos.importe,datos.electro,
        datos.dia,datos.mes,datos.anio,datos.cuotas,
        datos.importeCuotas,datos.iva,datos.totCuota);

    fclose(csvArch);
    */
}

//Funcion para buscar a un cliente.
void buscarCliente(){
    struct structCSV datos;
    int resultado=0,cantData=0,orden;
    char eleccion=0,apellido[20];

    FILE *archBin;
    archBin=fopen(DAT,"rb");

    fseek(archBin, 0, SEEK_END);                            //Situamos el cursor al final del archivo.
    cantData = ftell(archBin)/sizeof(struct structCSV);     //Usamos la funcion ftell para calcular la cantidad de
    fseek(archBin, 0, SEEK_SET);                            //datos y poder usarlos en los structs.

    while(eleccion!='A' && eleccion!='a' && eleccion!='B' && eleccion!='b'){
        printf("%cC%cmo quiere buscar a los clientes?\n",168,162);
        printf("[A] Por n%cmero de orden.\n",163);
        printf("[B] Por apellido.\n");
        eleccion=getchar();
        fflush(stdin);
    }

    if(eleccion=='A' || eleccion=='a'){
        printf("Ingrese n%cmero de orden:\n",163);
        datos.orden=mayorQueCero();

        //Imprimimos el indice.
        printf("ORDEN\tCLIENTE\t\tIMPORTE\tELECTRO\t\tDIA/MES/ANIO\tN.CUOT\tIMPORT CUOTAS\tIVA\tTOT CUOTAS\tACTIVO\n");

        //El siguiente for recorre secuencialmente el archivo binario. Si encuentra el n de orden, lo imprime y activa el flag
        //si no lo encuentra, con el flag apagado se le comunica al usuario que el numero de orden no fue encontrado.
        int flag=0;
        for (int i=0;i<cantData;i++){
            fread(&datos,sizeof(struct structCSV),1,archBin);
            if(orden==datos.orden){
                flag=1;
                printf("%d\t%.15s\t%d\t%.19s\t%d/%d/%d\t%d\t%.2f\t\t%.2f\t%.2f\t\t%c\n",datos.orden,
                    datos.cliente,datos.importe,datos.electro,datos.dia,datos.mes,datos.anio,
                    datos.cuotas,datos.importeCuotas,datos.iva,datos.totCuota,datos.valido);
            }
        }
        if (flag==0)
            printf("0 concidencias con el numero de orden: %d.\n",orden);
    }else{
        printf("Ingrese el nombre y apellido a buscar.\n");
        gets(apellido);
        fflush(stdin);

        printf("ORDEN\tCLIENTE\t\tIMPORTE\tELECTRO\t\tDIA/MES/ANIO\tN.CUOT\tIMPORT CUOTAS\tIVA\tTOT CUOTAS\tACTIVO\n");

        int flag=0;
        for (int i=0;i<cantData;i++){
            fread(&datos,sizeof(struct structCSV),1,archBin);

            //Leemos de forma secuencial e imprimos SOLO los datos donde el string ingresado por el usuario y el de apelldo sean iguales.
            resultado=strcmp(strupr(datos.cliente),strupr(apellido));
            if (resultado==0){
                flag=1;
                printf("%d\t%.15s\t%d\t%.19s\t%d/%d/%d\t%d\t%.2f\t\t%.2f\t%.2f\t\t%c\n",datos.orden,
                    datos.cliente,datos.importe,datos.electro,datos.dia,datos.mes,datos.anio,
                    datos.cuotas,datos.importeCuotas,datos.iva,datos.totCuota,datos.valido);
            }
        }
        if(flag==0)
            printf("0 concidencias con el apellido: %s.\n",apellido);
    }
    fclose(archBin);
}

//Funcion para modificar el importe.
void modificarImporte(){
    struct structCSV datos;
    int resultado;
    FILE * archBin;
    archBin=fopen(DAT,"r+b");

    printf("%cQu%c n%cmero de orden quiere modificar?\n",168,130,163);
    datos.orden=mayorQueCero();

    //Leemos los datos del cliente para mostrarlos en pantalla
    fseek(archBin,0,SEEK_SET);
    fseek(archBin,(datos.orden-1)*sizeof(struct structCSV ),SEEK_SET);
    fread(&datos,sizeof(struct structCSV ),1,archBin);

    printf("Usted va a modificar el importe de:\n");
    printf("Nombre y apellido: %s, Orden: %d\n",datos.cliente, datos.orden);
    printf("Ingrese nuevo precio\n");
    datos.importe=mayorQueCero();

    resultado=detectarOrden(datos.orden);
    if(!resultado){
        printf("Error intentando terminar la operacion. Ese numero de orden no esta en uso.\n");
        return;
    }
    datos.importeCuotas=datos.importe/datos.cuotas;
    datos.iva=(datos.importeCuotas*21)/100;
    datos.totCuota=datos.importe+datos.iva;

    fseek(archBin,-sizeof(struct structCSV),SEEK_CUR);
    fwrite(&datos,sizeof(struct structCSV),1,archBin);

    fclose(archBin);
}

//Funcion para dar de baja logica a un cliente.
void bajaLogica(){
    struct structCSV datos;
    int orden,resultado;

    FILE * archBin;
    archBin=fopen(DAT,"r+b");

    printf("%cQu%c n%cmero de orden quiere dar de baja logica?\n",168,130,163);
    datos.orden=mayorQueCero();

    resultado=detectarOrdenBinario(datos.orden);
    if(resultado==0){
        printf("Error al intentar terminar la operacion. Ese numero de orden no esta en uso.\n");
        return;
    }

    //Leemos los datos del cliente para mostrarlos en pantalla
    fseek(archBin,0,SEEK_SET);
    fseek(archBin,(datos.orden-1)*sizeof(struct structCSV),SEEK_SET);
    fread(&datos,sizeof(struct structCSV),1,archBin);

    printf("Usted va a dar de baja a:\n");
    printf("%d\t%.15s\t%d\t%.19s\t%d/%d/%d\t%d\t%.2f\t\t%.2f\t%.2f\t\t%c\n",datos.orden,
        datos.cliente,datos.importe,datos.electro,datos.dia,datos.mes,datos.anio,
        datos.cuotas,datos.importeCuotas,datos.iva,datos.totCuota,datos.valido);

    int eleccion=confimar();

    if(eleccion==1){
        printf("Usted dio de baja a:\n");
        printf("%d\t%.15s\t%d\t%.19s\t%d/%d/%d\t%d\t%.2f\t\t%.2f\t%.2f\t\t%c\n",datos.orden,
            datos.cliente,datos.importe,datos.electro,datos.dia,datos.mes,datos.anio,
            datos.cuotas,datos.importeCuotas,datos.iva,datos.totCuota,'N');
        datos.valido = 'N';
        fseek(archBin,-sizeof(struct structCSV),SEEK_CUR);
        fwrite(&datos,sizeof(struct structCSV),1,archBin);
    }
    fclose(archBin);
}

//Funcion para dar de baja fisica a un cliente.
void bajaFisica(){
    struct  structCSV datos;

    FILE*archBin;
    archBin=fopen(DAT,"rb");
    if (archBin == NULL) {
        printf("Error al abrir el archivo %s.\n", DAT);
        return;
    }
    //Se crea un archivo temporal que luego va a ser el principal.
    FILE*temp;
    temp=fopen("dat.temp","w+b");
    if (temp==NULL){
        printf("Error de archivos.\n");
        fclose(archBin);
        return;
    }
    //Las siguientes lineas son para determinar el nombre del archivo .xyz
    //Se crean varios string y se concatenan en nombreBajas.
    //Se usa la funcion obtenerFecha para conseguir un string con la fecha de hoy.
    char clientes[]="clientes_bajas_";
    char fecha[20];
    obtenerFecha(fecha);
    char fin[]=".xyz";
    char nombreBajas[40]={};

    strcat(nombreBajas,clientes);
    strcat(nombreBajas,fecha);
    strcat(nombreBajas,fin);

    FILE*archXYZ;
    archXYZ=fopen(nombreBajas,"a+b");

    fseek(archBin,0,SEEK_SET);

    while(fread(&datos,sizeof(struct structCSV),1,archBin)==1){
        if(datos.valido == 'S'){
            //Si el cliente no esta de baja, se guardan sus datos en un archivo temporal.
            fwrite(&datos,sizeof(struct structCSV),1,temp);
        }else if(datos.valido == 'N'){
            //Si el cliente esta de baja se guardan sus datos en el archivo .xyz
            fwrite(&datos,sizeof(struct structCSV),1,archXYZ);
/*
            //Si el cliente esta de baja se restablecen sus datos en el archivo .dat
            datos.orden=0;
            datos.cliente[0]='\0';
            datos.importe=0;
            datos.electro[0]='\0';
            datos.dia=0;
            datos.mes=0;
            datos.anio=0;
            datos.cuotas=0;
            datos.importeCuotas=0;
            datos.iva=0;
            datos.totCuota=0;
            datos.valido='\0';
            fwrite(&datos,sizeof(struct structCSV),1,temp);
*/
            //struct structCSV datosVacios = {0};
            //Se guardan los datos vacíos en el archivo temporal.
            //fwrite(&datos, sizeof(struct structCSV), 1, temp);
        }
    }
    //Se cierran los archivos.
    fclose(archBin);
    fclose(archXYZ);
    fclose(temp);

    remove(DAT);                //Borramos el archivo clentes.dat anterior
    rename("dat.temp",DAT);     //Renombramos el archivo temporal a clientes.dat para que sea el nuevo archivo principal.
    remove("dat.temp");         //Borramos el archivo temporal.
}

//Funcion para mostrar por pantalla la lista del archivo .xyz
void listarDatXYZ(){
    struct structCSV datos;
    int cantData=0;

    //Las siguientes lineas son para determinar el nombre del archivo .xyz
    //Se crean varios string y se concatenan en nombreBajas.
    //Se usa la funcion obtenerFecha para conseguir un string con la fecha de hoy.
    char clientes[]="clientes_bajas_";
    char fecha[20];
    obtenerFecha(fecha);
    char fin[]=".xyz";
    char nombreBajas[40]={};

    strcat(nombreBajas,clientes);
    strcat(nombreBajas,fecha);
    strcat(nombreBajas,fin);

    FILE *archXYZ;
    archXYZ=fopen(nombreBajas,"rb");

    fseek(archXYZ, 0, SEEK_END);                            //Situamos el cursor al final del archivo.
    cantData = ftell(archXYZ)/sizeof(struct structCSV);     //Usamos la funcion ftell para calcular la cantidad de
    fseek(archXYZ, 0, SEEK_SET);                            //datos y poder usarlos en los structs.

    printf("ORDEN\tCLIENTE\t\tIMPORTE\tELECTRO\t\tDIA/MES/ANIO\tN.CUOT\tIMPORT CUOTAS\tIVA\tTOT CUOTAS\tACTIVO\n");
    while(!feof(archXYZ)){
        fread(&datos,sizeof(struct structCSV),1,archXYZ);
        printf("%d\t%.15s\t%d\t%.19s\t%d/%d/%d\t%d\t%.2f\t\t%.2f\t%.2f\t\t%c\n",datos.orden,
            datos.cliente,datos.importe,datos.electro,datos.dia,datos.mes,datos.anio,
            datos.cuotas,datos.importeCuotas,datos.iva,datos.totCuota,datos.valido);
    }
    fclose(archXYZ);
}


void menu(){
    int eleccion=1;

    while(eleccion!=0){
        printf("-------MEN%c.-------\n",233);
        printf("Digite 1 para 'Listar csv'.\n");
        printf("Digite 2 para 'Crear archivo creditos.dat'.\n");
        printf("Digite 3 para 'Migrar datos de .csv a .dat'.\n");
        printf("Digite 4 para 'Listar .dat'.\n");
        printf("Digite 5 para 'Dar de Alta a un nuevo cliente'.\n");
        printf("Digite 6 para 'Buscar cliente'.\n");
        printf("Digite 7 para 'Modificar importe de cr%cdito'.\n",130);
        printf("Digite 8 para 'Dar de Baja L%cgica'.\n",162);
        printf("Digite 9 para 'Dar de Baja F%csica'.\n",161);
        printf("Digite 10 para 'Listar archivo tipo .xyz'.\n");
        printf("Digite 0 para salir.\n");
        scanf("%d",&eleccion);
        fflush(stdin);

        switch(eleccion){
            case 1:
                //printf("Llamar a 'Listar csv'\n");
                listarCSV();
                break;
            case 2:
                //printf("Llamar a 'Crear archivo creditos.dat'\n");
                crearBin();
                break;
            case 3:
                //printf("Llamar a 'Migrar datos de .csv a .dat'\n");
                migrar();
                break;
            case 4:
                //printf("Llamar a 'Listar .dat'\n");
                listarDat();
                break;
            case 5:
                //printf("Llamar a 'Dar de Alta a un nuevo cliente'.\n");
                alta();
                break;
            case 6:
                //printf("Llamar a 'Buscar cliente'\n");
                buscarCliente();
                break;
            case 7:
                //printf("Llamar a 'Modificar importe de credito'\n");
                modificarImporte();
                break;
            case 8:
                //printf("Llamar a 'Dar de Baja Logica'\n");
                bajaLogica();
                break;
            case 9:
                //printf("Llamar a 'Dar de Baja Fisica'\n");
                bajaFisica();
                break;
            case 10:
                //printf("Llamar a 'Listar archivo tipo .xyz'\n");
                listarDatXYZ();
                break;
            case 0:
                printf("Adios.\n");
                break;
            default:
                printf("No se encontr%c la opci%cn.\n",162,162);
                break;
        }
    }
}

int main(){
    menu();
return 0;}
