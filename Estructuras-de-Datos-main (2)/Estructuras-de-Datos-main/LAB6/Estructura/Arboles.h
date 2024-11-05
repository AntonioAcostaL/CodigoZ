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
void Liberarpila(Pila* pila);
void Push(Pila* pila, NodoBinario* nodo);
NodoBinario* pop(Pila* pila);
int estaVacia(Pila* pila);
void insertar(ArbolBinario* arbol, void* dato);
void inOrderIterativo(ArbolBinario* arbol);
void imprimirPorNivel(NodoBinario* nodo, int nivel);
void buscarPorPrefijo(NodoBinario* nodo, const char* prefijo);
void buscarPorContenido(NodoBinario* nodo, const char* contenido);
void liberarArbol(NodoBinario* nodo);
void cargarPalabrasDesdeArchivo(ArbolBinario* arbol, const char* nombreArchivo);
char* my_strdup(const char* str); 
