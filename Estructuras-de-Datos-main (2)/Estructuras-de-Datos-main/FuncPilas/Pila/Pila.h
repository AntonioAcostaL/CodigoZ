#pragma once

typedef struct Nodo {
    char* dato;
    struct Nodo* siguiente;
    struct Nodo* anterior;
} Nodo;

typedef struct {
    Nodo* Cabeza;
} Pila;

Nodo* CrearNodo(char* dato);
Pila* crearPila();
void Liberarpila(Pila* pila);
void Push(Pila* pila, char* dato);
char* pop(Pila* pila);
char* peek(Pila* pila);
int estaVacia(Pila* pila);
void PrintPila(Pila* pila);
void liberarPila(Pila* pila);