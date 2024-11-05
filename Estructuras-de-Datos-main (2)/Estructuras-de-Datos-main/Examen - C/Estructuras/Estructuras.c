#include "Estructuras.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <unistd.h>

Pila* crearPila() {
    Pila* pila = (Pila*)malloc(sizeof(Pila));
    pila->Cabeza = NULL;
    return pila;
}

void PushPila(Pila* pila, Paciente* paciente) {
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->dato = paciente;
    if (pila->Cabeza == NULL) {
        nuevoNodo->siguiente = nuevoNodo;
        nuevoNodo->anterior = nuevoNodo;
        pila->Cabeza = nuevoNodo;
    } else {
        Nodo* ultimo = pila->Cabeza->anterior;
        nuevoNodo->siguiente = pila->Cabeza;
        nuevoNodo->anterior = ultimo;
        pila->Cabeza->anterior = nuevoNodo;
        ultimo->siguiente = nuevoNodo;
        pila->Cabeza = nuevoNodo;
    }
}

Paciente* popPila(Pila* pila) {
    if (estaVaciaPila(pila)) {
        return NULL;
    }
    Nodo* nodoRemovido = pila->Cabeza;
    Paciente* dato = (Paciente*)nodoRemovido->dato;

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

int estaVaciaPila(Pila* pila) {
    return pila->Cabeza == NULL;
}

Cola* crearCola() {
    Cola* cola = (Cola*)malloc(sizeof(Cola));
    cola->Cabeza = NULL;
    return cola;
}

void Push(Cola* cola, Paciente* paciente) {
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    nuevoNodo->dato = paciente;

    if (cola->Cabeza == NULL) {
        nuevoNodo->siguiente = nuevoNodo;
        nuevoNodo->anterior = nuevoNodo;
        cola->Cabeza = nuevoNodo;
    } else {
        Nodo* actual = cola->Cabeza;
        while (actual->severidad >= paciente->severidad && actual->siguiente != cola->Cabeza) {
            actual = actual->siguiente;
        }
        
        nuevoNodo->siguiente = actual->siguiente;
        nuevoNodo->anterior = actual;

        actual->siguiente->anterior = nuevoNodo;
        actual->siguiente = nuevoNodo;

        if (actual == cola->Cabeza->anterior && paciente->severidad < cola->Cabeza->severidad) {
            cola->Cabeza = nuevoNodo; 
        }
    }
}

Paciente* Pop(Cola* cola) {
    if (cola->Cabeza == NULL) {
        return NULL; 
    }
    Nodo* primero = cola->Cabeza;
    Paciente* paciente = (Paciente*)primero->dato;

    if (primero->siguiente == primero) {
        cola->Cabeza = NULL; 
    } else {
        Nodo* ultimo = primero->anterior;
        cola->Cabeza = primero->siguiente;
        cola->Cabeza->anterior = ultimo;
        ultimo->siguiente = cola->Cabeza;
    }
    free(primero);
    return paciente;
}


int contarPacientes(Cola* cola) {
    int contador = 0;
    Nodo* actual = cola->Cabeza;
    if (actual == NULL) return 0;

    do {
        contador++;
        actual = actual->siguiente;
    } while (actual != cola->Cabeza);
    return contador;
}

int contarPila(Pila* cola) {
    int contador = 0;
    Nodo* actual = cola->Cabeza;
    if (actual == NULL) return 0;

    do {
        contador++;
        actual = actual->siguiente;
    } while (actual != cola->Cabeza);
    return contador;
}

Paciente* CrearPaciente(char* nombre, int severidad) {
    Paciente* nuevo = (Paciente*)malloc(sizeof(Paciente));
    nuevo->nombre = (char*)malloc(strlen(nombre) + 1);
    strcpy(nuevo->nombre, nombre);
    nuevo->severidad = severidad;
    return nuevo;
}

void LiberarPaciente(Paciente* paciente) {
    free(paciente->nombre);
    free(paciente);
}

void LiberarCola(Cola* cola) {
    Nodo* actual = cola->Cabeza;
    if (actual == NULL) {
        free(cola);
        return;
    }
    do {
        Nodo* siguiente = actual->siguiente;
        LiberarPaciente((Paciente*)actual->dato);
        free(actual);
        actual = siguiente;
    } while (actual != cola->Cabeza);
    free(cola);
}

void LiberarPila(Pila* pila) {
    while (!estaVaciaPila(pila)) {
        Paciente* paciente = popPila(pila);
        LiberarPaciente(paciente);
    }
    free(pila);
}
