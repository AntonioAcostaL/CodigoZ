#pragma once

typedef struct Nodo {
    char* palabra;              
    struct Nodo* siguiente;    
    struct Nodo* anterior;      
} Nodo;

typedef struct ListaDoble {
    Nodo* Cabeza;
    Nodo* Cola;
} ListaDoble;


void imprimirLOG(ListaDoble* log[], size_t* longitudes, size_t numListas); 
char** SepCadenas(const char* str, size_t* numpalabras);
ListaDoble* filtro(const char* texto, size_t longitud);
ListaDoble* crearListaDoble();
void PushFront(ListaDoble* lista, const char* palabra);
void PushBack(ListaDoble* lista, const char* palabra);
void PushPos(ListaDoble* lista, char* palabra, int pos);
void ImprimirLista(ListaDoble* lista);
void LiberarLista(ListaDoble* lista);

/*
ListaDoble* crearListaDoble() {
    ListaDoble* lista = (ListaDoble*)malloc(sizeof(ListaDoble));
    if (lista == NULL) {
        perror("Error al reservar memoria para la lista");
        exit(EXIT_FAILURE);
    }
    
    // Inicializar cabeza y cola de la lista
    lista->Cabeza = NULL;
    lista->Cola = NULL;
    
    return lista;
}

void PushFront(ListaDoble* lista, char* palabra) {
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));  // Crear un nuevo nodo con malloc
    if (nuevoNodo != NULL) {
        nuevoNodo->palabra = palabra;
        nuevoNodo->siguiente = lista->Cabeza;
        nuevoNodo->anterior = NULL;

        if (lista->Cabeza != NULL) {
            lista->Cabeza->anterior = nuevoNodo;
        } else {
            lista->Cola = nuevoNodo;
        }

        lista->Cabeza = nuevoNodo;
    }
}

void PushBack(ListaDoble* lista, char* palabra) {
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo));  // Crear un nuevo nodo con malloc
    if (nuevoNodo != NULL) {
        nuevoNodo->palabra = palabra;
        nuevoNodo->siguiente = NULL;
        if (lista->Cola != NULL) {
            lista->Cola->siguiente = nuevoNodo;  // Insertar al final de la lista
            nuevoNodo->anterior = lista->Cola;
            lista->Cola = nuevoNodo;
        } else {
            lista->Cabeza = nuevoNodo;
            lista->Cola = nuevoNodo;
            nuevoNodo->anterior = NULL;
        }
    }
}

void LiberarLista(ListaDoble* lista) {
    Nodo* actual = lista->Cabeza;
    while (actual != NULL) {
        Nodo* siguiente = actual->siguiente;
        free(actual->palabra);  // Libera solo si palabra fue asignada dinámicamente
        free(actual);
        actual = siguiente;
    }
    free(lista);
}

void ImprimirLista(ListaDoble* lista) {
    Nodo* actual = lista->Cabeza;
    while (actual != NULL) {
        printf("%s ", actual->palabra);
        actual = actual->siguiente;
    }
    printf("\n");
}
*/