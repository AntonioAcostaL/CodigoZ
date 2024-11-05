#pragma once

typedef struct Nodo {
    void* dato;
    struct Nodo* siguiente;
    struct Nodo* anterior;
} Nodo;

typedef struct {
    Nodo* Cabeza;
} Cola;

typedef struct Cliente {
    char* nombre;
    int ticks;
} Cliente;

Nodo* CrearNodo(Cliente* dato);
Cola* crearCola();
void Push(Cola* lista, Cliente* cliente);
Cliente* Pop(Cola* lista);
void ImprimirCola(Cola* lista);
void LiberarCola(Cola* lista);
void agregarElemento(Cola* cola, Cliente* cliente);
int AtenderCaja(Cola* caja, int id);
void LiberarCliente(Cliente* cliente);
Cliente* CrearCliente(char* nombre, int ticks);
int contarClientes(Cola* cola);