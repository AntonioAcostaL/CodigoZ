#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Pila.h"

Nodo* CrearNodo(char* dato) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevo == NULL) return NULL;
    
    nuevo->dato = (char*)malloc(strlen(dato) + 1);
    if (nuevo->dato == NULL) {
        free(nuevo);
        return NULL;
    }
    strcpy(nuevo->dato, dato);
    
    nuevo->siguiente = NULL;
    nuevo->anterior = NULL;
    return nuevo;
}

Pila* crearPila() {
    Pila* pila = (Pila*)malloc(sizeof(Pila));
    pila->Cabeza = NULL;
    return pila;
}

void PrintPila(Pila* pila) {
    if (pila->Cabeza == NULL) {
        printf("pila vacía.\n");
        return;
    }
    Nodo* actual = pila->Cabeza;
    do {
        printf("%s ", (char *)actual->dato);
        actual = actual->siguiente;
    } while (actual != pila->Cabeza);
    printf("\n");
}

void Liberarpila(Pila* pila) {
    if (pila->Cabeza == NULL) return;

    Nodo* actual = pila->Cabeza;
    Nodo* siguiente;
    do {
        siguiente = actual->siguiente;
        free(actual->dato);
        free(actual);
        actual = siguiente;
    } while (actual != pila->Cabeza);
    free(pila);
}

void Push(Pila* pila, char* dato) {
    Nodo* NuevoNodo = CrearNodo(dato);
    if (NuevoNodo == NULL) return;
    if (pila->Cabeza == NULL) {
        NuevoNodo->siguiente = NuevoNodo;
        NuevoNodo->anterior = NuevoNodo;
        pila->Cabeza = NuevoNodo;
    } else {
        Nodo* ultimo = pila->Cabeza->anterior;
        NuevoNodo->siguiente = pila->Cabeza;
        NuevoNodo->anterior = ultimo;
        pila->Cabeza->anterior = NuevoNodo;
        ultimo->siguiente = NuevoNodo;
        pila->Cabeza = NuevoNodo;
    }
}

char* pop(Pila* pila) {
    if (estaVacia(pila)) {
        return NULL;
    }
    Nodo* nodoRemovido = pila->Cabeza;
    char* dato = nodoRemovido->dato;

    if (nodoRemovido->siguiente == nodoRemovido) {
        pila->Cabeza = NULL;
    } else {
        Nodo* ultimo = nodoRemovido->anterior;
        pila->Cabeza = nodoRemovido->siguiente;
        pila->Cabeza->anterior = ultimo;
        ultimo->siguiente = pila->Cabeza;
    }

    free(nodoRemovido);
    return dato;
}

char* peek(Pila* pila) {
    if (estaVacia(pila)) {
        return NULL; 
    }
    return pila->Cabeza->dato; 
}

int estaVacia(Pila* pila) {
    return pila->Cabeza == NULL;
}