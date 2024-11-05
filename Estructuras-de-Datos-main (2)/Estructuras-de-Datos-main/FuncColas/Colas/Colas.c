#include "Colas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Nodo* CrearNodo(char* dato) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevo == NULL) {
        return NULL;
    }
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

ListaDoble* crearListaDoble() {
    ListaDoble* lista = (ListaDoble*)malloc(sizeof(ListaDoble));
    if (lista == NULL) {
        perror("Error al crear lista doble");
        exit(EXIT_FAILURE);
    }
    lista->Cabeza = NULL;
    return lista;
}


void Push(ListaDoble* lista, char* dato) {
    Nodo* NuevoNodo = CrearNodo(dato);
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
        ultimo->siguiente = NuevoNodo;
        lista->Cabeza->anterior = NuevoNodo;
    }
}

void* Pop(ListaDoble* lista) {
    if (lista->Cabeza == NULL) {
        return NULL; 
    }
    
    Nodo* primero = lista->Cabeza;
    void* dato = primero->dato;  

    if (primero->siguiente == primero) {
        lista->Cabeza = NULL;
    } else {
        Nodo* ultimo = primero->anterior;
        lista->Cabeza = primero->siguiente;
        lista->Cabeza->anterior = ultimo;
        ultimo->siguiente = lista->Cabeza;
    }

    free(primero);
    return dato;  
}

void ImprimirCola(ListaDoble* lista) {
    if (lista->Cabeza == NULL) {
        printf("Cola vacía.\n");
        return;
    }
    Nodo* actual = lista->Cabeza;
    do {
        printf("%s ", (char *)actual->dato);
        actual = actual->siguiente;
    } while (actual != lista->Cabeza);
    printf("\n");
}

void LiberarCola(ListaDoble* lista) {
    if (lista->Cabeza == NULL) return;

    Nodo* actual = lista->Cabeza;
    Nodo* siguiente;
    do {
        siguiente = actual->siguiente;
        free(actual->dato);  
        free(actual);
        actual = siguiente;
    } while (actual != lista->Cabeza);
    free(lista); 
}

char* Peek(ListaDoble* lista) {
    if (lista->Cabeza == NULL) {
        return NULL; 
    }
    return (char*)lista->Cabeza->dato; 
}