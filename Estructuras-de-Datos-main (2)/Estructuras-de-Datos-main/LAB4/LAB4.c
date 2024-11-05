#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Pila/Pila.h"
#define SIZE 10000

int main() {
    srand(time(NULL));

    // Inicialización de matrices A y B
    int** A = (int**)malloc(SIZE * sizeof(int*));
    int** B = (int**)malloc(SIZE * sizeof(int*));
    for (int i = 0; i < SIZE; i++) {
        A[i] = (int*)malloc(SIZE * sizeof(int));
        B[i] = (int*)malloc(SIZE * sizeof(int));
    }
    
    inicializarMatrices(A, B, SIZE);

    // Creación de la pila
    ListaDoble* pila = crearListaDoble();

    // Procesamiento en submatrices
    int subSize = SIZE / 2;

    // Matriz final para almacenar resultados
    int** matrizFinal = (int**)malloc(SIZE * sizeof(int*));
    for (int i = 0; i < SIZE; i++) {
        matrizFinal[i] = (int*)calloc(SIZE, sizeof(int)); // Inicializa en 0
    }

    // Se generan los productos suma de las submatrices
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            int** subA = (int**)malloc(subSize * sizeof(int*));
            int** subB = (int**)malloc(subSize * sizeof(int*));
            for (int k = 0; k < subSize; k++) {
                subA[k] = (int*)malloc(subSize * sizeof(int));
                subB[k] = (int*)malloc(subSize * sizeof(int));
            }
            
            // Copia de las submatrices
            for (int k = 0; k < subSize; k++) {
                for (int l = 0; l < subSize; l++) {
                    subA[k][l] = A[i * subSize + k][j * subSize + l];
                    subB[k][l] = B[i * subSize + k][j * subSize + l];
                }
            }

            // Realiza el producto suma y almacena en la matriz final
            int** result = ProdSum(subA, subB, subSize);

            // Combinar resultados en la matriz final
            for (int k = 0; k < subSize; k++) {
                for (int l = 0; l < subSize; l++) {
                    matrizFinal[i * subSize + k][j * subSize + l] = result[k][l];
                }
            }

            // Liberar submatrices
            liberarMatriz(subA, subSize);
            liberarMatriz(subB, subSize);
            liberarMatriz(result, subSize);
        }
    }

    // Imprimir la matriz final
    printf("Matriz resultante:\n");
    imprimirMatrizFinal(matrizFinal, SIZE);

    // Liberar memoria
    LiberarLista(pila);
    liberarMatriz(A, SIZE);
    liberarMatriz(B, SIZE);
    liberarMatriz(matrizFinal, SIZE);
    liberarListaDoble(pila);
    return 0;
}