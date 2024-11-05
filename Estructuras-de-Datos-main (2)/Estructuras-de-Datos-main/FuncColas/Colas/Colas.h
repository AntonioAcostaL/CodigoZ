#pragma once

typedef struct Nodo {
    void* dato;
    struct Nodo* siguiente;
    struct Nodo* anterior;
} Nodo;

typedef struct {
    Nodo* Cabeza;
} ListaDoble;

Nodo* CrearNodo(char* dato);
ListaDoble* crearListaDoble();
void Push(ListaDoble* lista, char* dato);
void* Pop(ListaDoble* lista);
void ImprimirCola(ListaDoble* lista);
void LiberarCola(ListaDoble* lista);