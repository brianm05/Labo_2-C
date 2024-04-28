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

int main(){
    int ** matriz=NULL;
}
