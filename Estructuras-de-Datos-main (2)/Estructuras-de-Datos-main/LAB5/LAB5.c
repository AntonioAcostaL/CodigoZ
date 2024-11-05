#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Colas/Colas.h"

int main() {
    srand(time(NULL));
    Cola* colas[3];

    for (int i = 0; i < 3; i++) {
        colas[i] = crearCola();
    }

    Cola* filaGeneral = crearCola();
    Cola* filaAuxiliar = crearCola();
    int totalTicks = 0;
    int ticksAcumulados = 0;

    while (ticksAcumulados < 100000) { 
        if (totalTicks % 100 == 0 && totalTicks != 0) {
            char nombre[20];
            snprintf(nombre, sizeof(nombre), "Cliente %d", (totalTicks / 100) + 1);
            int ticks = rand() % 100 + 1; 
            Cliente* nuevoCliente = CrearCliente(nombre, ticks);

            if (contarClientes(filaGeneral) < 25) {
                Push(filaGeneral, nuevoCliente); 
                printf("%s se ha unido a la fila general.\n", nuevoCliente->nombre);
            } else if (contarClientes(filaAuxiliar) < 25) {
                Push(filaAuxiliar, nuevoCliente);
                printf("%s se ha enviado a la fila auxiliar.\n", nuevoCliente->nombre);
            } else {
                printf("No se pudo agregar a %s a la fila general ni a la auxiliar. Ambas están llenas.\n", nuevoCliente->nombre);
                LiberarCliente(nuevoCliente);
            }
            printf("Ticks acumulados: %d\n", ticksAcumulados);
        }

        for (int j = 0; j < 3; j++) {
            if (filaGeneral->Cabeza != NULL) {
                Cliente* clienteFila = Pop(filaGeneral);
                int cajaAleatoria = rand() % 3;

                if (contarClientes(colas[cajaAleatoria]) < 3) {
                    Push(colas[cajaAleatoria], clienteFila);
                    printf("%s se ha unido a la caja %d.\n", clienteFila->nombre, cajaAleatoria + 1);
                } else {
                    printf("%s no puede ser atendido en la caja %d porque ya está llena.\n", clienteFila->nombre, cajaAleatoria + 1);
                    Push(filaAuxiliar, clienteFila); 
                    printf("%s se ha enviado a la fila auxiliar.\n", clienteFila->nombre);
                }
            }

            ticksAcumulados += AtenderCaja(colas[j], j + 1);
        }
        
        totalTicks++;
    }

    while (filaAuxiliar->Cabeza != NULL) {
        Cliente* clienteAux = Pop(filaAuxiliar);
        LiberarCliente(clienteAux);
    }

    while (filaGeneral->Cabeza != NULL) {
        Cliente* clienteGen = Pop(filaGeneral);
        LiberarCliente(clienteGen);
    }

    printf("Total de ticks acumulados: %d\n", ticksAcumulados);
    for (int i = 0; i < 3; i++) {
        LiberarCola(colas[i]);
    }
    
    LiberarCola(filaGeneral);
    LiberarCola(filaAuxiliar);

    return 0;
}
