#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liblista_doble.h"

ListaDoble* crearListaDoble() {
    ListaDoble* lista = (ListaDoble*)malloc(sizeof(ListaDoble));
    if (lista == NULL) {
        perror("Error al reservar memoria para la lista");
        exit(EXIT_FAILURE);
    }
    
    // Inicializar cabeza y cola de la lista
    lista->Cabeza = NULL;
    lista->Cola = NULL;
    
    return lista;
}


void PushFront(ListaDoble* lista, const char* palabra) {
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevoNodo != NULL) {
        size_t longitud = strlen(palabra) + 1;
        nuevoNodo->palabra = (char*)malloc(longitud * sizeof(char));
        if (nuevoNodo->palabra != NULL) {
            memcpy(nuevoNodo->palabra, palabra, longitud);
        } else {
            free(nuevoNodo);
            return; // O manejar error
        }
        nuevoNodo->siguiente = lista->Cabeza;
        nuevoNodo->anterior = NULL;

        if (lista->Cabeza != NULL) {
            lista->Cabeza->anterior = nuevoNodo;
        } else {
            lista->Cola = nuevoNodo;
        }

        lista->Cabeza = nuevoNodo;
    }
}

void PushBack(ListaDoble* lista, const char* palabra) {
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevoNodo != NULL) {
        size_t longitud = strlen(palabra) + 1;
        nuevoNodo->palabra = (char*)malloc(longitud * sizeof(char));
        if (nuevoNodo->palabra != NULL) {
            memcpy(nuevoNodo->palabra, palabra, longitud);
        } else {
            free(nuevoNodo);
            return; // O manejar error
        }
        nuevoNodo->siguiente = NULL;
        if (lista->Cola != NULL) {
            lista->Cola->siguiente = nuevoNodo;
            nuevoNodo->anterior = lista->Cola;
            lista->Cola = nuevoNodo;
        } else {
            lista->Cabeza = nuevoNodo;
            lista->Cola = nuevoNodo;
            nuevoNodo->anterior = NULL;
        }
    }
}

void LiberarLista(ListaDoble* lista) {
    Nodo* actual = lista->Cabeza;
    while (actual != NULL) {
        Nodo* siguiente = actual->siguiente;
        free(actual->palabra); // Asumiendo que `palabra` fue asignada dinámicamente
        free(actual); // Liberar el nodo
        actual = siguiente;
    }
    free(lista); // Liberar la estructura de la lista
}

void ImprimirLista(ListaDoble* lista) {
    Nodo* actual = lista->Cabeza;
    while (actual != NULL) {
        printf("%s ", actual->palabra);
        actual = actual->siguiente;
    }
    printf("\n");
}
