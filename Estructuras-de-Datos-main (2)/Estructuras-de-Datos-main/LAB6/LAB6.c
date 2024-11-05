#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Estructura/Arboles.h"

int main() {
    ArbolBinario* arbol = crearArbol();

    char* palabras[] = {
        "Amor", "Azul", "Casa", "Broma", "Cielo",
        "Dedal", "Esfera", "Florido", "Generoso", "Aguacates"
    };

    for (int i = 0; i < sizeof(palabras) / sizeof(palabras[0]); i++) {
        insertar(arbol, my_strdup(palabras[i])); 
    }

    cargarPalabrasDesdeArchivo(arbol, "words_list.txt");

    
    printf("palabras:\n");
    for (int nivel = 0; nivel < 10; nivel++) { 
        imprimirPorNivel(arbol->raiz, nivel);
        printf("\n");
    }
    

    char prefijo[100];
    char contenido[100];

    printf("Ingresa hasta 3 letras para buscar por prefijo: ");
    scanf("%s", prefijo);
    buscarPorPrefijo(arbol->raiz, prefijo);

    printf("\nIngresa letras para buscar por contenido: ");
    scanf("%s", contenido);
    buscarPorContenido(arbol->raiz, contenido);

    liberarArbol(arbol->raiz);
    free(arbol);

    return 0;
}
