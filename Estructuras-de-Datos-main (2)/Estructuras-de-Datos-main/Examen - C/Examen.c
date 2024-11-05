#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Estructuras/Estructuras.h"

int main() {
    srand(time(NULL));

    Pila* clinica = crearPila();
    Cola* filaGeneral = crearCola();
    int count = 1;

    while (count <= 100) {
        char nombre[20];
        snprintf(nombre, sizeof(nombre), "Paciente %d", count);
        int severidad = rand() % 3 + 1;  

        Paciente* nuevoPaciente = CrearPaciente(nombre, severidad);
        Push(filaGeneral, nuevoPaciente);
        printf("%s se ha unido a la fila general con %d de severidad.\n", nuevoPaciente->nombre, severidad);

        while (contarPila(clinica) < 5 && contarPacientes(filaGeneral) > 0) {
            Nodo* actual = filaGeneral->Cabeza;
            Nodo* pacientePrioritario = actual;

            do {
                Paciente* pacienteActual = (Paciente*)actual->dato;
                Paciente* pacientePrior = (Paciente*)pacientePrioritario->dato; 
                if (pacienteActual->severidad > pacientePrior->severidad) {
                    pacientePrioritario = actual;
                }
                actual = actual->siguiente;
            } while (actual != filaGeneral->Cabeza);
            Paciente* pacienteFila = (Paciente*)pacientePrioritario->dato; 
            if (pacientePrioritario == filaGeneral->Cabeza) {
                Pop(filaGeneral); 
            } else {
                pacientePrioritario->anterior->siguiente = pacientePrioritario->siguiente;
                pacientePrioritario->siguiente->anterior = pacientePrioritario->anterior;
                if (pacientePrioritario == filaGeneral->Cabeza->anterior) {
                    filaGeneral->Cabeza->anterior = pacientePrioritario->anterior;
                }
                free(pacientePrioritario);
            }
            PushPila(clinica, pacienteFila);
        }

        count++;
    }

    while (!estaVaciaPila(clinica)) {
        Paciente* pacienteAtendido = popPila(clinica);
        if (pacienteAtendido) {
            printf("%s ha terminado de ser atendido.\n", pacienteAtendido->nombre);
            LiberarPaciente(pacienteAtendido);
        }
    }

    LiberarCola(filaGeneral);
    LiberarPila(clinica);
    return 0;
}


