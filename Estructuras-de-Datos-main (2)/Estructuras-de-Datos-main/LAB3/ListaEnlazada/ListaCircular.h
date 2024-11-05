#pragma once

#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    void* data;                
    struct Nodo* siguiente;
    struct Nodo* anterior;
} Nodo;

typedef struct ListaDobleCircular {
    Nodo* Cabeza;               
} ListaDobleCircular;

Nodo* CrearNodo(char* data);
void PushFront(ListaDobleCircular* lista, char* data);
void PushBack(ListaDobleCircular* lista, char* data);
void PushPos(ListaDobleCircular* lista, char* data, int pos);
void ImprimirLista(ListaDobleCircular* lista);
void LiberarLista(ListaDobleCircular* lista);
ListaDobleCircular* CrearLista();
ListaDobleCircular* ConcatInicio(const ListaDobleCircular* lista1, const ListaDobleCircular* lista2);
ListaDobleCircular* ConcatFinal(const ListaDobleCircular* lista1, const ListaDobleCircular* lista2);
ListaDobleCircular* ConcatPos(const ListaDobleCircular* lista1, const ListaDobleCircular* lista2, int pos);