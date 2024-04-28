#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define N 4
#define M 6

struct sucursal{
    int id_sucursal;
    char ciudad[30];
    float descuentos_del_mes[30];
    float total_descuentos_del_mes;
    float promedio_descuentos;
};
struct gerente{
    int id_sucursal;
    char nombre_gerente[30];
};

void crearMatriz(int*** m){
    *m = (int **)malloc(N * sizeof(int *));
    srand(time(NULL));

    for (int i = 0; i < N; i++){
        (*m)[i] = (int *)malloc(M * sizeof(int));
        for (int j = 0; j < M; j++){
            (*m)[i][j] = (rand() % 55)+90; //(rand() % 50) <--|numero aleatorio entre 0-55| y |+90|--> para que sea entre 90-145
        }
    }
}
void emitoMatriz(int**m){
    printf("Emitir Matriz:");
    for(int i=0;i<N;i++){
        printf("\n");
        for(int j=0;j<M;j++)
            //printf("%.2d | ",*(*(m+i)+j));
            printf("%.3d | ",m[i][j]);
    }
    printf("\n");
}
void liberarMatriz(int**m){
    for (int i=0;i<M;i++)
        free(m[i]);
    free(m);
}

void tot_descuentos_del_mes(struct sucursal s[]){
    float total=0;
    for(int i=0;i<N;i++){
        for(int j=0;j<30;j++){
            s[i].descuentos_del_mes[j]=rand()%10;
            //printf("%f\n",s[i].descuentos_del_mes[j]);
        }
    }//cargarmos

}
void promedioDescuentos(struct sucursal s[],int **m){
float promedio;
    for(int i=0;i<N;i++){
        promedio=0;
        //printf("\n");
        for(int j=0;j<M;j++){
            //printf("%.2d |",m[i][j]);
            promedio=promedio+m[i][j];
        }
        //printf("Promedio: %.2f",promedio/M);
        s[i].promedio_descuentos=promedio/M;
    }
}
void ver_tot_descuentos_del_mes(struct sucursal s[]){
    float total=0;
    for(int i=0;i<N;i++){
        total=0;
        for(int j=0;j<30;j++)
            total=total+s[i].descuentos_del_mes[j];

        printf("Total de descuentos de la sucursal %d: %.2f.\n",i,total);
        s[i].total_descuentos_del_mes=total;
    }
}
void emitirStructSucursal(struct sucursal s[]){
    for(int i=0;i<N;i++){
        printf("ID sucursal: %d.\n",s[i].id_sucursal);
        printf("Ciudad: %s.\n",s[i].ciudad);
        printf("Descuentos del mes: ");
        for(int j=0;j<30;j++)
            printf("%.1f|",s[i].descuentos_del_mes[j]);
        printf("\n");
        printf("descuentos de mes: %f.\n",s[i].total_descuentos_del_mes);
        printf("promedio descuentos: %f.\n",s[i].promedio_descuentos);
        printf("\n");
    }
}
void emitirSucursal(struct sucursal s[],int n){
    printf("ID sucursal: %d.\n",s[n].id_sucursal);
    printf("Ciudad: %s.\n",s[n].ciudad);
    printf("Descuentos del mes: ");
    for(int j=0;j<30;j++)
        printf("%.1f|",s[n].descuentos_del_mes[j]);
    printf("\n");
    printf("descuentos de mes: %f.\n",s[n].total_descuentos_del_mes);
    printf("promedio descuentos: %f.\n",s[n].promedio_descuentos);
    printf("\n");
}

void emitirStructGerente(struct gerente g[]){
    for(int i=0;i<N;i++){
        printf("ID sucursal: %d.\n",g[i].id_sucursal);
        printf("Nombre del gerente: %s.\n",g[i].nombre_gerente);
        printf("\n");
    }
}
void ordenarSucursales(struct sucursal s[]){
    /*char mas_grande[30]={0};
    int n=0;
    struct sucursal aux[N];

    for(int i=0;i<N;i++){
        if(s[i].ciudad[0]>mas_grande[0]){
            strcpy(mas_grande,s[i].ciudad);
            n=s[i].id_sucursal;
        }
    }

    printf("Ciudad: %s.\n",mas_grande);
    emitirSucursal(s,n);*/
    char actual, mas_pequeno, temp[30];
    struct sucursal aux;
    for (actual=0;actual<N-1;actual++){
        mas_pequeno = actual;
        for (int j=actual;j<N;j++)
            if (s[j].ciudad[0]< s[j].ciudad[mas_pequeno])
                mas_pequeno=j;
        /*
        //temp=s[actual].ciudad[0];
        strcpy(temp,s[actual].ciudad);
        //s[actual].ciudad[0]=s[mas_pequeno].ciudad[0];
        strcpy(s[actual].ciudad,s[mas_pequeno].ciudad);
        //s[mas_pequeno].ciudad[0]=temp;
        strcpy(s[mas_pequeno].ciudad,temp);
        */

        aux=s[actual];
        s[actual]=s[mas_pequeno];
        s[mas_pequeno]=aux;
    }
    emitirStructSucursal(s);
}

void menu(int**m,struct sucursal s[],struct gerente g[]){
    int eleccion;

    do{
        printf("--------MENU--------\n");
        printf("Ingrese 0 para salir.\n");
        printf("Ingrese 1 para emitir matriz de sucursales/meses.\n");
        printf("Ingrese 2 para calcular el total de descuentos del mes de cada sucursal.\n");
        printf("Ingrese 3 para calcular el promedio de descuentos de cada sucursal.\n");
        printf("Ingrese 4 para emitir datos de las sucursales.\n");
        printf("Ingrese 5 para emitir datos de los gerentes.\n");
        printf("Ingrese 6 para ordenar las sucursales de forma ascendente.\n");
        scanf("%d",&eleccion);

        switch(eleccion){
            case 1:
            emitoMatriz(m);
            break;
            case 2:
            ver_tot_descuentos_del_mes(s);
            break;
            case 3:
            promedioDescuentos(s,m);
            break;
            case 4:
            emitirStructSucursal(s);
            break;
            case 5:
            emitirStructGerente(g);
            break;
            case 6:
            ordenarSucursales(s);
            break;
            default:
            break;
        }
    }while(eleccion!=0);

}

int main(){
    struct sucursal sucursales[N]={
    {0,"CABA",{0},0,0},
    {1,"Jose Leon Suarez",{0},0,0},
    {2,"Villa Ballester",{0},0,0},
    {3,"San Martin",{0},0,0}
    };
    struct gerente gerentes[N]={
    {0,"Pedro"},
    {1,"Ezequiel"},
    {2,"Fausto"},
    {3,"Juan"}
    };
    int enteros[N]; //definimos un array de enteros
    for(int i=0;i<N;i++)
        enteros[i]=-1; //lo inicilizamos con -1.

    //array bidimensional
    int ** matriz=NULL;
    crearMatriz(&matriz);
    tot_descuentos_del_mes(sucursales);

    menu(matriz,sucursales,gerentes);

    liberarMatriz(matriz);
return 0;
}
