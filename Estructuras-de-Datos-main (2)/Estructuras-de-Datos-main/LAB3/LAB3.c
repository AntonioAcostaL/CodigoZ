#include "ListaEnlazada/ListaCircular.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    ListaDobleCircular* lista1 = CrearLista();
    char* datos1[] = {"I", "N", "G", "E", "N", "I", "E", "R", "O"};
    for (int i = 0; i < 9; i++) {
        PushBack(lista1, datos1[i]);
    }
    ListaDobleCircular* lista2 = CrearLista();
    char* datos2[] = {"S", "O", "F", "T", "W", "A", "R", "E"};
    for (int i = 0; i < 8; i++) {
        PushBack(lista2, datos2[i]);
    }
    ListaDobleCircular* lista3 = ConcatInicio(lista2, lista1);
    printf("Lista concatenada al inicio:\n");
    ImprimirLista(lista3);
    ListaDobleCircular* lista4 = ConcatFinal(lista2, lista1);
    printf("Lista concatenada al final:\n");
    ImprimirLista(lista4);
    ListaDobleCircular* lista5 = ConcatPos(lista1, lista2, 3);
    printf("Lista concatenada en la posición 3:\n");
    ImprimirLista(lista5);
    LiberarLista(lista1);
    LiberarLista(lista2);
    LiberarLista(lista3);
    LiberarLista(lista4);
    LiberarLista(lista5);

    return 0;
}