#pragma once

typedef struct Paciente {
    char* nombre;
    int severidad;
} Paciente;

typedef struct Nodo {
    void* dato;
    struct Nodo* siguiente;
    struct Nodo* anterior;
    int severidad;
} Nodo;

typedef struct Cola {
    Nodo* Cabeza;
} Cola;

typedef struct Pila {
    Nodo* Cabeza;
} Pila;


// Funciones de la pila
Pila* crearPila();
void PushPila(Pila* pila, Paciente* paciente);
Paciente* popPila(Pila* pila);
int estaVaciaPila(Pila* pila);
int contarPila(Pila* cola);

// Funciones de la cola
Cola* crearCola();
void Push(Cola* cola, Paciente* paciente);
Paciente* Pop(Cola* cola);
int contarPacientes(Cola* cola);

// Funciones de pacientes
Paciente* CrearPaciente(char* nombre, int severidad);
void LiberarPaciente(Paciente* paciente);

// Funciones para liberar memoria
void LiberarCola(Cola* cola);
void LiberarPila(Pila* pila);