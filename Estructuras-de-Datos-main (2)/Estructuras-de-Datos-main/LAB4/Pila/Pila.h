#pragma once

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
void push(ListaDoble* pila, char* palabra);
char* pop(ListaDoble* pila);
char* peek(ListaDoble* pila);
int estaVacia(ListaDoble* pila);
void printPila(ListaDoble* pila);
void inicializarMatrices(int** A, int** B, int size);
int** ProdSum(int** A, int** B, int size);
void liberarMatriz(int** matriz, int size);
void imprimirMatrizFinal(int** matriz, int size);
void liberarListaDoble(ListaDoble* lista);