#pragma once
#include <stddef.h>

typedef struct Nodo {
    char* palabra;
    struct Nodo* siguiente;
    struct Nodo* anterior;
} Nodo;

typedef struct {
    Nodo* Cabeza;
} ListaDoble;

Nodo* CrearNodo(char* palabra);
ListaDoble* crearListaDoble();
void PushFront(ListaDoble* lista, char* palabra);
void PushBack(ListaDoble* lista, char* palabra);
void PushPos(ListaDoble* lista, char* palabra, int pos);
void ImprimirLista(ListaDoble* lista);
void LiberarLista(ListaDoble* lista);
ListaDoble* filtro(const char* texto, size_t longitud);

