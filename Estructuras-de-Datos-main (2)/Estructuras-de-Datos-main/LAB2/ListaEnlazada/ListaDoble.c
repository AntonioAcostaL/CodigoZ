#include "ListaDoble.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Nodo* CrearNodo(char* palabra) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevo == NULL) {
        return NULL;
    }
    nuevo->palabra = (char*)malloc(strlen(palabra) + 1);
    if (nuevo->palabra == NULL) {
        free(nuevo);
        return NULL;
    }
    strcpy(nuevo->palabra, palabra);  
    nuevo->siguiente = NULL;
    nuevo->anterior = NULL;
    return nuevo;
}

ListaDoble* crearListaDoble() {
    ListaDoble* lista = (ListaDoble*)malloc(sizeof(ListaDoble));
    if (lista == NULL) {
        perror("Error al crear lista doble");
        exit(EXIT_FAILURE);
    }
    lista->Cabeza = NULL;
    return lista;
}

void PushFront(ListaDoble* lista, char* palabra) {
    Nodo* NuevoNodo = CrearNodo(palabra);
    if (NuevoNodo == NULL) {
        return;
    }
    if (lista->Cabeza == NULL) {
        NuevoNodo->siguiente = NuevoNodo;
        NuevoNodo->anterior = NuevoNodo;
        lista->Cabeza = NuevoNodo;
    } else {
        Nodo* ultimo = lista->Cabeza->anterior;
        NuevoNodo->siguiente = lista->Cabeza;
        NuevoNodo->anterior = ultimo;
        lista->Cabeza->anterior = NuevoNodo;
        ultimo->siguiente = NuevoNodo;
        lista->Cabeza = NuevoNodo;
    }
}

void PushBack(ListaDoble* lista, char* palabra) {
    Nodo* NuevoNodo = CrearNodo(palabra);
    if (NuevoNodo == NULL) {
        return;
    }
    if (lista->Cabeza == NULL) {
        NuevoNodo->siguiente = NuevoNodo;
        NuevoNodo->anterior = NuevoNodo;
        lista->Cabeza = NuevoNodo;
    } else {
        Nodo* ultimo = lista->Cabeza->anterior;
        NuevoNodo->siguiente = lista->Cabeza;
        NuevoNodo->anterior = ultimo;
        lista->Cabeza->anterior = NuevoNodo;
        ultimo->siguiente = NuevoNodo;
    }
}

void PushPos(ListaDoble* lista, char* palabra, int pos) {
    if (pos < 0) return; 
    Nodo* NuevoNodo = CrearNodo(palabra);
    if (NuevoNodo == NULL) {
        return;
    }

    if (lista->Cabeza == NULL || pos == 0) {
        PushFront(lista, palabra);
        return;
    }

    Nodo* actual = lista->Cabeza;
    int i;
    for (i = 0; i < pos - 1 && actual->siguiente != lista->Cabeza; ++i) {
        actual = actual->siguiente;
    }

    if (actual->siguiente == lista->Cabeza) {
        PushBack(lista, palabra);
    } else {
        Nodo* siguiente = actual->siguiente;
        NuevoNodo->siguiente = siguiente;
        NuevoNodo->anterior = actual;
        actual->siguiente = NuevoNodo;
        siguiente->anterior = NuevoNodo;
    }
}

void ImprimirLista(ListaDoble* lista) {
    if (lista->Cabeza == NULL) {
        printf("Lista vacía.\n");
        return;
    }
    Nodo* actual = lista->Cabeza;
    do {
        printf("%s ", (char *)actual->palabra);;
        actual = actual->siguiente;
    } while (actual != lista->Cabeza);
    printf("\n");
}

void LiberarLista(ListaDoble* lista) {
    if (lista->Cabeza == NULL) return;

    Nodo* actual = lista->Cabeza;
    Nodo* siguiente;
    do {
        siguiente = actual->siguiente;
        free(actual->palabra);  
        free(actual);
        actual = siguiente;
    } while (actual != lista->Cabeza);
    free(lista); 
}
