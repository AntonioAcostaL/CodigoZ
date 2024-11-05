#include "ListaCircular.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

Nodo* CrearNodo(char* data) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevo == NULL) {
        return NULL;
    }
    nuevo->data = (char*)malloc(strlen(data) + 1);
    if (nuevo->data == NULL) {
        free(nuevo);
        return NULL;
    }
    strcpy(nuevo->data, data);  
    nuevo->siguiente = NULL;
    nuevo->anterior = NULL;
    return nuevo;
}

ListaDobleCircular* CrearLista() {
    ListaDobleCircular* lista = (ListaDobleCircular*)malloc(sizeof(ListaDobleCircular));
    if (lista == NULL) {
        return NULL;
    }
    lista->Cabeza = NULL;
    return lista;
}

void PushFront(ListaDobleCircular* lista, char* data) {
    Nodo* NuevoNodo = CrearNodo(data);
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
        lista->Cabeza->anterior = NuevoNodo;
        ultimo->siguiente = NuevoNodo;
        lista->Cabeza = NuevoNodo;
    }
}

void PushBack(ListaDobleCircular* lista, char* data) {
    Nodo* NuevoNodo = CrearNodo(data);
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
        lista->Cabeza->anterior = NuevoNodo;
        ultimo->siguiente = NuevoNodo;
    }
}

void PushPos(ListaDobleCircular* lista, char* data, int pos) {
    if (pos < 0) return; 
    Nodo* NuevoNodo = CrearNodo(data);
    if (NuevoNodo == NULL) {
        return;
    }

    if (lista->Cabeza == NULL || pos == 0) {
        PushFront(lista, data);
        return;
    }

    Nodo* actual = lista->Cabeza;
    int i;
    for (i = 0; i < pos - 1 && actual->siguiente != lista->Cabeza; ++i) {
        actual = actual->siguiente;
    }

    if (actual->siguiente == lista->Cabeza) {
        PushBack(lista, data);
    } else {
        Nodo* siguiente = actual->siguiente;
        NuevoNodo->siguiente = siguiente;
        NuevoNodo->anterior = actual;
        actual->siguiente = NuevoNodo;
        siguiente->anterior = NuevoNodo;
    }
}

void ImprimirLista(ListaDobleCircular* lista) {
    if (lista->Cabeza == NULL) {
        printf("Lista vacía.\n");
        return;
    }
    Nodo* actual = lista->Cabeza;
    do {
        printf("%s ", (char *)actual->data);;
        actual = actual->siguiente;
    } while (actual != lista->Cabeza);
    printf("\n");
}

void LiberarLista(ListaDobleCircular* lista) {
    if (lista->Cabeza == NULL) return;

    Nodo* actual = lista->Cabeza;
    Nodo* siguiente;
    do {
        siguiente = actual->siguiente;
        free(actual->data);  
        free(actual);
        actual = siguiente;
    } while (actual != lista->Cabeza);
    free(lista); 
}

ListaDobleCircular* ConcatInicio(const ListaDobleCircular* lista1, const ListaDobleCircular* lista2) {
    ListaDobleCircular* nuevaLista = CrearLista();
    if (nuevaLista == NULL) {
        return NULL;
    }

    if (lista2->Cabeza != NULL) {
        Nodo* actual = lista2->Cabeza;
        do {
            PushBack(nuevaLista, actual->data);
            actual = actual->siguiente;
        } while (actual != lista2->Cabeza);
    }

    if (lista1->Cabeza != NULL) {
        Nodo* actual = lista1->Cabeza;
        do {
            PushBack(nuevaLista, actual->data);
            actual = actual->siguiente;
        } while (actual != lista1->Cabeza);
    }

    return nuevaLista;
}

ListaDobleCircular* ConcatFinal(const ListaDobleCircular* lista1, const ListaDobleCircular* lista2) {
    ListaDobleCircular* nuevaLista = CrearLista();
    if (nuevaLista == NULL) {
        return NULL;
    }

    if (lista1->Cabeza != NULL) {
        Nodo* actual = lista1->Cabeza;
        do {
            PushBack(nuevaLista, actual->data);
            actual = actual->siguiente;
        } while (actual != lista1->Cabeza);
    }

    if (lista2->Cabeza != NULL) {
        Nodo* actual = lista2->Cabeza;
        do {
            PushBack(nuevaLista, actual->data);
            actual = actual->siguiente;
        } while (actual != lista2->Cabeza);
    }

    return nuevaLista;
}

ListaDobleCircular* ConcatPos(const ListaDobleCircular* lista1, const ListaDobleCircular* lista2, int pos) {
    ListaDobleCircular* nuevaLista = CrearLista();
    if (nuevaLista == NULL) {
        return NULL;
    }

    Nodo* actual = lista1->Cabeza;
    int i;
    for (i = 0; i < pos && actual != NULL; ++i) {
        PushBack(nuevaLista, actual->data);
        actual = actual->siguiente;
    }

    if (lista2->Cabeza != NULL) {
        Nodo* actual2 = lista2->Cabeza;
        do {
            PushBack(nuevaLista, actual2->data);
            actual2 = actual2->siguiente;
        } while (actual2 != lista2->Cabeza);
    }
    for (; actual != NULL && actual != lista1->Cabeza; actual = actual->siguiente) {
        PushBack(nuevaLista, actual->data);
    }

    return nuevaLista;
}
