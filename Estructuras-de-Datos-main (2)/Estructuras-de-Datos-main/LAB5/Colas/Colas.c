#include "Colas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <unistd.h>

Nodo* CrearNodo(Cliente* dato) {
    Nodo* nuevo = (Nodo*)malloc(sizeof(Nodo));
    if (nuevo == NULL) {
        return NULL;
    }
    nuevo->dato = dato; 
    nuevo->siguiente = NULL;
    nuevo->anterior = NULL;
    return nuevo;
}

Cola* crearCola() {
    Cola* lista = (Cola*)malloc(sizeof(Cola));
    if (lista == NULL) {
        perror("Error al crear lista doble");
        exit(EXIT_FAILURE);
    }
    lista->Cabeza = NULL;
    return lista;
}


void Push(Cola* lista, Cliente* cliente) {
    Nodo* NuevoNodo = CrearNodo(cliente);
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
        ultimo->siguiente = NuevoNodo;
        lista->Cabeza->anterior = NuevoNodo;
    }
}

Cliente* Pop(Cola* lista) {
    if (lista->Cabeza == NULL) {
        return NULL; 
    }
    
    Nodo* primero = lista->Cabeza;
    Cliente* cliente = (Cliente*)primero->dato;  

    if (primero->siguiente == primero) {
        lista->Cabeza = NULL;
    } else {
        Nodo* ultimo = primero->anterior;
        lista->Cabeza = primero->siguiente;
        lista->Cabeza->anterior = ultimo;
        ultimo->siguiente = lista->Cabeza;
    }

    free(primero);
    return cliente;  
}

void ImprimirCola(Cola* lista) {
    if (lista->Cabeza == NULL) {
        printf("Cola vacía.\n");
        return;
    }
    Nodo* actual = lista->Cabeza;
    do {
        printf("%s ", (char *)actual->dato);
        actual = actual->siguiente;
    } while (actual != lista->Cabeza);
    printf("\n");
}

void LiberarCola(Cola* lista) {
    if (lista == NULL) return; 

    Nodo* actual = lista->Cabeza;
    if (actual == NULL) { 
        free(lista);
        return;
    }

    Nodo* siguiente = NULL;
    do {
        siguiente = actual->siguiente;
        LiberarCliente((Cliente*)actual->dato); 
        free(actual);
        actual = siguiente; 
    } while (actual != lista->Cabeza);

    free(lista); 
}

char* Peek(Cola* lista) {
    if (lista->Cabeza == NULL) {
        return NULL; 
    }
    return (char*)lista->Cabeza->dato; 
}

void agregarElemento(Cola* cola, Cliente* cliente) {
    if (cola->Cabeza != NULL && cola->Cabeza->siguiente != cola->Cabeza && cola->Cabeza->anterior->siguiente != cola->Cabeza) {
        printf("La cola ya está llena. No se puede agregar '%s'.\n", cliente->nombre);
        return;
    }
    Push(cola, cliente);
    printf("Agregado '%s' a la cola.\n", cliente->nombre);
}

Cliente* CrearCliente(char* nombre, int ticks) {
    Cliente* nuevo = (Cliente*)malloc(sizeof(Cliente));
    nuevo->nombre = (char*)malloc(strlen(nombre) + 1);
    strcpy(nuevo->nombre, nombre);
    nuevo->ticks = ticks;
    return nuevo;
}

void LiberarCliente(Cliente* cliente) {
    free(cliente->nombre);
    free(cliente);
}

int AtenderCaja(Cola* caja, int id) {
    if (caja->Cabeza != NULL) {
        Cliente* cliente = (Cliente*)Pop(caja);
        printf("Caja %d atendiendo a %s, tardará %d ticks.\n", id, cliente->nombre, cliente->ticks);
        
        /*
        descomentar si es necesario revisar cada tick(no lo recomiendo profe tarda mucho)
        for (int tick = 1; tick <= cliente->ticks; tick++) {
            // Simular el paso del tiempo
            usleep(50000); 0.05 segundos
            printf("Caja %d: Tick %d para %s.\n", id, tick, cliente->nombre);
        }
        */
        
        int ticksUsados = cliente->ticks; 
        LiberarCliente(cliente);            
        return ticksUsados;                 
    }
    return 0; 
}

int contarClientes(Cola* cola) {
    int contador = 0;
    Nodo* actual = cola->Cabeza;
    if (actual == NULL) return 0;

    do {
        contador++;
        actual = actual->siguiente;
    } while (actual != cola->Cabeza);
    return contador;
}