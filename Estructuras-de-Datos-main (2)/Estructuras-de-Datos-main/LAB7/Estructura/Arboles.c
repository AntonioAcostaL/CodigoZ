#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Arboles.h"

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
    
    nuevo->dato = my_strdup(dato);
    if (nuevo->dato == NULL) {
        free(nuevo);
        return NULL;
    }
    
    nuevo->siguiente = NULL;
    nuevo->anterior = NULL;
    return nuevo;
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

void Push(Pila* pila, NodoBinario* nodo) {
    Nodo* NuevoNodo = CrearNodo((char*) nodo->dato); 
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

NodoBinario* pop(Pila* pila) {
    if (estaVacia(pila)) {
        return NULL;
    }
    Nodo* nodoRemovido = pila->Cabeza;
    NodoBinario* dato = (NodoBinario*) nodoRemovido->dato;

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


int estaVacia(Pila* pila) {
    return pila->Cabeza == NULL;
}

void insertar(ArbolBinario* arbol, void* dato) {
    NodoBinario* nuevo = crearNodoBinario(dato);
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

void inOrderIterativo(ArbolBinario* arbol) {
    if (arbol->raiz == NULL) return;

    Pila* pila = crearPila();
    NodoBinario* actual = arbol->raiz;

    while (actual != NULL || !estaVacia(pila)) {
        while (actual != NULL) {
            Push(pila, actual);
            actual = actual->izq;
        }
        if (!estaVacia(pila)) {
            actual = pop(pila);
            printf("%d ", *(int*)actual->dato); 
            actual = actual->der;
        }
    }
    Liberarpila(pila);
}

void imprimirPorNivel(NodoBinario* nodo, int nivel) {
    if (nodo == NULL) return;
    if (nivel == 0) {
        printf("%s ", (char*)nodo->dato);
    } else {
        imprimirPorNivel(nodo->izq, nivel - 1);
        imprimirPorNivel(nodo->der, nivel - 1);
    }
}

void buscarPorPrefijo(NodoBinario* nodo, const char* prefijo) {
    if (nodo == NULL) return;
    
    if (strncmp(nodo->dato, prefijo, strlen(prefijo)) == 0) {
        printf("%s ", (char*)nodo->dato);
    }
    
    buscarPorPrefijo(nodo->izq, prefijo);
    buscarPorPrefijo(nodo->der, prefijo);
}

void buscarPorContenido(NodoBinario* nodo, const char* contenido) {
    if (nodo == NULL) return;

    if (strstr(nodo->dato, contenido) != NULL) {
        printf("%s ", (char*)nodo->dato);
    }

    buscarPorContenido(nodo->izq, contenido);
    buscarPorContenido(nodo->der, contenido);
}

void liberarArbol(NodoBinario* nodo) {
    if (nodo == NULL) return;
    liberarArbol(nodo->izq);
    liberarArbol(nodo->der);
    free(nodo->dato);
    free(nodo);
}

void cargarPalabrasDesdeArchivo(ArbolBinario* arbol, const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    char palabra[100];
    while (fgets(palabra, sizeof(palabra), archivo)) {
        palabra[strcspn(palabra, "\n")] = '\0'; 
        insertar(arbol, my_strdup(palabra)); 
    }

    fclose(archivo);
}

char* my_strdup(const char* str) {
    size_t len = strlen(str) + 1; 
    char* dup = (char*)malloc(len);
    if (dup) {
        memcpy(dup, str, len);
    }
    return dup;
}

NodoBinario* eliminarNodo(NodoBinario* nodo, void* dato) {
    if (nodo == NULL) return nodo;

    int cmp = strcmp((char*)dato, (char*)nodo->dato);

    if (cmp < 0) {
        nodo->izq = eliminarNodo(nodo->izq, dato);
    } else if (cmp > 0) {
        nodo->der = eliminarNodo(nodo->der, dato);
    } else {
        if (nodo->izq == NULL) {
            NodoBinario* temp = nodo->der;
            free(nodo->dato); 
            free(nodo); 
            return temp;
        } 
        else if (nodo->der == NULL) {
            NodoBinario* temp = nodo->izq;
            free(nodo->dato); 
            free(nodo); 
            return temp;
        }

        NodoBinario* temp = nodo->der;
        while (temp && temp->izq != NULL) {
            temp = temp->izq;
        }

        free(nodo->dato);
        nodo->dato = my_strdup((char*)temp->dato);
        nodo->der = eliminarNodo(nodo->der, temp->dato);
    }
    return nodo;
}

void eliminar(ArbolBinario* arbol, void* dato) {
    arbol->raiz = eliminarNodo(arbol->raiz, dato);
}