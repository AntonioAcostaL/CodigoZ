#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ArbolesExp.h"

ArbolBinario* crearArbol() {
    ArbolBinario* arbol = (ArbolBinario*)malloc(sizeof(ArbolBinario));
    arbol->raiz = NULL;
    arbol->altura = 0;
    arbol->tam = 0;
    return arbol;
}

NodoBinario* crearNodoBinario(void* dato) {
    NodoBinario* nuevo = (NodoBinario*)malloc(sizeof(NodoBinario));
    nuevo->dato = dato; 
    nuevo->izq = NULL;
    nuevo->der = NULL;
    return nuevo;
}

Pila* crearPila() {
    Pila* pila = (Pila*)malloc(sizeof(Pila));
    pila->Cabeza = NULL;
    return pila;
}

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

void insertar(ArbolBinario* arbol, void* dato) {
    NodoBinario* nuevo = crearNodo(dato);
    if (arbol->raiz == NULL) {
        arbol->raiz = nuevo;
        arbol->tam++;
        return;
    }

    NodoBinario* actual = arbol->raiz;
    while (1) {
        if (*(int*)dato < *(int*)actual->dato) {
            if (actual->izq == NULL) {
                actual->izq = nuevo;
                arbol->tam++;
                break;
            }
            actual = actual->izq;
        } else {
            if (actual->der == NULL) {
                actual->der = nuevo;
                arbol->tam++;
                break;
            }
            actual = actual->der;
        }
    }
}

int buscar(ArbolBinario* arbol, void* dato) {
    NodoBinario* actual = arbol->raiz;
    while (actual != NULL) {
        if (*(int*)dato == *(int*)actual->dato) {
            return 1; // Encontrado
        } else if (*(int*)dato < *(int*)actual->dato) {
            actual = actual->izq;
        } else {
            actual = actual->der;
        }
    }
    return 0; // No encontrado
}

NodoBinario* eliminarNodo(NodoBinario* nodo, void* dato) {
    if (nodo == NULL) return nodo;

    if (*(int*)dato < *(int*)nodo->dato) {
        nodo->izq = eliminarNodo(nodo->izq, dato);
    } else if (*(int*)dato > *(int*)nodo->dato) {
        nodo->der = eliminarNodo(nodo->der, dato);
    } else {
        // Nodo encontrado
        if (nodo->izq == NULL) {
            NodoBinario* temp = nodo->der;
            free(nodo);
            return temp;
        } else if (nodo->der == NULL) {
            NodoBinario* temp = nodo->izq;
            free(nodo);
            return temp;
        }

        // Nodo con dos hijos: obtener el sucesor inorden
        NodoBinario* temp = nodo->der;
        while (temp && temp->izq != NULL) {
            temp = temp->izq;
        }
        nodo->dato = temp->dato; // Reemplazar dato
        nodo->der = eliminarNodo(nodo->der, temp->dato);
    }
    return nodo;
}

void eliminar(ArbolBinario* arbol, void* dato) {
    arbol->raiz = eliminarNodo(arbol->raiz, dato);
}

int obtenerTamano(ArbolBinario* arbol) {
    return arbol->tam;
}

int obtenerAltura(NodoBinario* nodo) {
    if (nodo == NULL) return -1;
    int izqAltura = obtenerAltura(nodo->izq);
    int derAltura = obtenerAltura(nodo->der);
    return (izqAltura > derAltura ? izqAltura : derAltura) + 1;
}

int altura(ArbolBinario* arbol) {
    return obtenerAltura(arbol->raiz);
}

void inOrderIterativo(ArbolBinario* arbol) {
    Pila* pila = crearPila();
    NodoBinario* actual = arbol->raiz;

    while (actual != NULL || !estaVacia(pila)) {
        while (actual != NULL) {
            Push(pila, actual->dato);
            actual = actual->izq;
        }
        if (!estaVacia(pila)) {
            actual = pop(pila);
            printf("%d ", *(int*)actual); // Asume que dato es un int
            actual = actual->der;
        }
    }
    Liberarpila(pila);
}

int maxSumaNivel(ArbolBinario* arbol) {
    if (arbol->raiz == NULL) return 0;

    int maxSuma = 0;
    int nivelMax = 0;
    int nivel = 0;
    int suma;
    Pila* pila = crearPila();
    Pila* niveles = crearPila();

    Push(pila, arbol->raiz);
    Push(niveles, (void*)(long)nivel); // Guardamos el nivel

    while (!estaVacia(pila)) {
        NodoBinario* nodo = pop(pila);
        nivel = (int)(long)pop(niveles);

        if (nodo) {
            suma += *(int*)nodo->dato; // Asumiendo que el dato es un int

            if (nodo->izq) {
                Push(pila, nodo->izq);
                Push(niveles, (void*)(long)(nivel + 1));
            }
            if (nodo->der) {
                Push(pila, nodo->der);
                Push(niveles, (void*)(long)(nivel + 1));
            }
        }
        if (suma > maxSuma) {
            maxSuma = suma;
            nivelMax = nivel;
        }
    }
    Liberarpila(pila);
    Liberarpila(niveles);
    return nivelMax;
}

NodoBinario* lca(NodoBinario* nodo, void* n1, void* n2) {
    if (nodo == NULL) return NULL;

    if (*(int*)nodo->dato == *(int*)n1 || *(int*)nodo->dato == *(int*)n2)
        return nodo;

    NodoBinario* izqLCA = lca(nodo->izq, n1, n2);
    NodoBinario* derLCA = lca(nodo->der, n1, n2);

    if (izqLCA && derLCA) return nodo;
    return (izqLCA != NULL) ? izqLCA : derLCA;
}

NodoBinario* obtenerLCA(ArbolBinario* arbol, void* n1, void* n2) {
    return lca(arbol->raiz, n1, n2);
}

