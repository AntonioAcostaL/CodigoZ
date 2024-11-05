#pragma once

typedef struct NodoBinario {
    void* dato;
    struct NodoBinario* izq;
    struct NodoBinario* der;
} NodoBinario;

typedef struct ArbolBinario {
    NodoBinario* raiz;
    int altura;
    int tam;
} ArbolBinario;

typedef struct Nodo {
    char* dato;
    struct Nodo* siguiente;
    struct Nodo* anterior;
} Nodo;

typedef struct {
    Nodo* Cabeza;
} Pila;

ArbolBinario* crearArbol();
NodoBinario* crearNodoBinario(void* dato);
Pila* crearPila();
Nodo* CrearNodo(char* dato);
void PrintPila(Pila* pila);
void Liberarpila(Pila* pila);
void Push(Pila* pila, char* dato);
char* pop(Pila* pila);
char* peek(Pila* pila);
int estaVacia(Pila* pila);
void insertar(ArbolBinario* arbol, void* dato);
int buscar(ArbolBinario* arbol, void* dato);
NodoBinario* eliminarNodo(NodoBinario* nodo, void* dato);
void eliminar(ArbolBinario* arbol, void* dato);
int obtenerTamano(ArbolBinario* arbol);
int obtenerAltura(NodoBinario* nodo);
int altura(ArbolBinario* arbol);
void inOrderIterativo(ArbolBinario* arbol);
int maxSumaNivel(ArbolBinario* arbol);
NodoBinario* lca(NodoBinario* nodo, void* n1, void* n2);
NodoBinario* obtenerLCA(ArbolBinario* arbol, void* n1, void* n2);