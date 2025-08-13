#include <stdio.h>
#include <stdlib.h>

//Agrego la matriz, las filas y columnas
void leermatriz(int **matriz, int filas, int columnas, const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir %s\n", nombreArchivo);
        return;
    }
    
    for (int i = 0; i < filas; i++) { //Se crea ciclo para filas
        for(int j=0; j<columnas; j++) { //se crea ciclo para columnas
            fscanf(archivo, "%d", &matriz[i][j]); //escanea la matriz
        }
    }
    
    fclose(archivo);
}

//GUARDAR EL RESULTADO
void guardarmatriz(int **matriz, int filas,int columnas, const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "w");
    if (archivo == NULL) {
        printf("Error al guardar en %s\n", nombreArchivo);
        return;
    }
    for (int i = 0; i < filas; i++) {
        for(int j= 0; j < columnas; j++) {
            fprintf(archivo, "%d\n", matriz[i][j]);
        }
        fprintf(archivo, "\n"); //Imprimir matriz
    }
    fclose(archivo);
}

//sumar dos matrizes (se cambia vector por matriz,y el resultado con dos punteros**
// y se agregan enteros de filas y columnas)
void sumamatriz(int **m1, int **m2, int **resultado, int filas,int columnas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            resultado[i][j] = m1[i][j] + m2[i][j];
        }
    }
}

// Producto escalar de las dos matrizes(lo mismo que arriba, sacando resultado)
int productomatriz(int **m1, int **m2, int filas, int columnas) {
    int producto = 0;
    for (int i = 0; i < filas; i++) {
        for(int j= 0; j< columnas; j++) {
            producto += m1[i][j] * m2[i][j];
        }
    }
    return producto;
}

int main() {
    //matrizes
    int filas, columnas;
    
    printf("Ingrese el número de filas: ");
    scanf("%d",&filas);
    printf("Ingrese el número de columnas: ");
    scanf("%d",&columnas);
    
    //Memoria dinamica
    
    int **matriz1 = malloc(filas * sizeof(int*));
    int **matriz2 = malloc(filas * sizeof(int*));
    int **suma    = malloc(filas * sizeof(int*));
    
    for (int i = 0;i < filas; i++) {
        matriz1[i] = malloc(columnas * sizeof(int)); //sin puntero
        matriz2[i] = malloc(columnas * sizeof(int));
        suma[i]    = malloc(columnas * sizeof(int));
    }
    
    //LEER TXT DE VECTOR 1 Y 2
    
    leermatriz(matriz1,filas,columnas, "matriz1.txt");
    leermatriz(matriz2,filas,columnas, "matriz2.txt");
    

    //  PRODUCTO Y SUMA
    int producto = productomatriz(matriz1,matriz2,filas,columnas); //escalar
    
    sumamatriz(matriz1,matriz2, suma, filas,columnas);
    
    //guardar
    guardarmatriz(suma,filas,columnas, "suma.txt");
    
    //CREAR ARCHIVO Y ESCRIBIR RESULTADOS DE PRODUCTO Y SUMA
    FILE* archivo = fopen("resultado.txt", "w");
    if (archivo != NULL) {
        fprintf(archivo, "Producto escalar: %d\n", producto);
        fclose(archivo);
    } else {
        printf("Error al crear resultado.txt\n");
    }
    
    //liberar Memoria
    for(int i= 0 ;i < filas ; i++) {
        free(matriz1[i]);
        free(matriz2[i]);
        free(suma[i]);
    }
    
    free(matriz1);
    free(matriz2);
    free(suma);
    
    return 0;
}


//NOTAS DE ERRORES
//1) Colocar los punteros adelante(MAL: matriz**) pero es atrás (BIEN:**matriz)
//2) Olvidar algunos ";"
//3) Cuando cargo la memoria dinámica, las filas se cargan con ** atras del int..así:
//   **int matriz1 = malloc(filas * sizeof(**int));
//   en las columnas ES SIN **, y remplazando filas por columnas
//4) 
