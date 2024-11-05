#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lib/Listas/liblista_doble.h"


ListaDoble* filtro(const char* texto, size_t longitud) {
    size_t numpalabras;
    char** palabras = SepCadenas(texto, &numpalabras);

    ListaDoble* lista = crearListaDoble();

    for (size_t i = 0; i < numpalabras; ++i) {
        if (strlen(palabras[i]) == longitud) {
            PushBack(lista, palabras[i]);
        }
        free(palabras[i]);
    }
    free(palabras);

    return lista;
}

char** SepCadenas(const char* str, size_t* numpalabras) {
    size_t capacidad = 10;
    *numpalabras = 0;
    char** palabras = (char**)malloc(capacidad * sizeof(char*));
    if (palabras == NULL) {
        perror("Error al reservar memoria");
        exit(EXIT_FAILURE);
    }

    const char* limites = " \n\t,.!?";

    size_t longitud = strlen(str) + 1;
    char* strCopy = (char*)malloc(longitud * sizeof(char));
    if (strCopy == NULL) {
        perror("Error al reservar memoria para la copia de la cadena");
        exit(EXIT_FAILURE);
    }
    memcpy(strCopy, str, longitud);

    char* token = strtok(strCopy, limites);

    while (token != NULL) {
        if (*numpalabras >= capacidad) {
            capacidad *= 2;
            palabras = (char**)realloc(palabras, capacidad * sizeof(char*));
            if (palabras == NULL) {
                perror("Error al redimensionar memoria");
                exit(EXIT_FAILURE);
            }
        }

        size_t token_length = strlen(token) + 1;
        palabras[*numpalabras] = (char*)malloc(token_length * sizeof(char));
        if (palabras[*numpalabras] == NULL) {
            perror("Error al reservar memoria para la palabra");
            exit(EXIT_FAILURE);
        }

        memcpy(palabras[*numpalabras], token, token_length);
        (*numpalabras)++;
        token = strtok(NULL, limites);
    }

    free(strCopy);

    return palabras;
}

void imprimirLOG(ListaDoble* log[], size_t* longitudes, size_t numListas) {
    for (size_t i = 0; i < numListas; ++i) {
        printf("[pos %zu] Palabras de %zu letras\n", i, longitudes[i]);
        ImprimirLista(log[i]);
        printf("\n");
    }
}

int main(void) {
    char* texto = "derrotarlo es mediante el sacrificio de un Invocador, quien debe completar una peregrinación para invocar al Aeon Supremo que traerá la Calma, un periodo temporal de paz antes de que Sin regrese.La historia comienza con Tidus en su ciudad natal de Zanarkand, donde es una estrella de blitzball. Durante un partido, Sin ataca la ciudad y Tidus es arrastrado a una version de Spira 1000 años en el futuro. Tidus se encuentra con Auron, quien revela estar ligado a Sin, y pronto son arrastrados por el monstruo a Spira. Al despertar, Tidus se da cuenta de que Zanarkand ya no existe y que ha sido destruida hace 1000 años durante una guerra que involucró el uso de machina.Tidus es rescatado por un grupo de Al Bhed, donde conoce a Rikku, quien le explica la naturaleza de Sin y lo que le ha ocurrido. Luego de otro ataque de Sin, Tidus se separa de los Al Bhed y llega a la isla de Besaid, donde conoce a Yuna y sus guardianes, Lulu, Wakka y Kimahri. Yuna está iniciando su peregrinación para derrotar a Sin, siguiendo los pasos de su padre, y Tidus se une al grupo en la esperanza de encontrar una manera de regresar a Zanarkand.El viaje también explora las tensiones entre las diferentes razas y culturas de Spira, como los Al Bhed, quienes son marginados por su rechazo a las enseñanzas de Yevon. Rikku se une al grupo más tarde en la historia, lo que genera tensiones con Wakka, un ferviente creyente en Yevon que desconfía de los Al Bhed y de su uso de tecnología prohibida.Durante la peregrinación, el grupo también se encuentra repetidamente con Sin, quien parece tener un interés especial en Tidus. Finalmente, Auron revela a Tidus que Sin es, de hecho, Jecht, el padre de Tidus, quien se convirtió en Sin después de acompañar a Braska en su peregrinación una década antes. Esto explica por qué Sin parece estar conectado con Tidus y Auron.A medida que avanzan, el grupo comienza a cuestionar las enseñanzas de Yevon, especialmente después de que descubren que el Alto Clero de Yevon está corrupto y que el ciclo de destrucción de Sin es, en parte, perpetuado por la propia religion. En Bevelle, la ciudad capital y sede de Yevon, el grupo descubre que los líderes de Yevon no son sinceros acerca de la posibilidad de derrotar permanentemente a Sin. El Aeon Supremo, que los Invocadores buscan para derrotar a Sin, en realidad solo destruye temporalmente a Sin, después de lo cual el Invocador sacrifica su vida y Sin vuelve a renacer. Esta revelación destruye la fe de Yuna en Yevon, pero ella sigue adelante con su peregrinación, decidida a encontrar una manera de romper el ciclo sin sacrificarse. A lo largo del viaje, Tidus lucha con la realidad de que su padre es Sin y con su deseo de salvar tanto a Yuna como a Spira.El grupo finalmente llega a Zanarkand, donde descubren que la ciudad es ahora una ruina. Aquí, se revela la verdadera naturaleza de Spira y Sin. Yu Yevon, una entidad espiritual, es el verdadero creador de Sin y el responsable de su renacimiento constante. Los Invocadores que buscan derrotar a Sin están, sin saberlo, perpetuando el ciclo, ya que el Aeon Supremo se convierte en el nuevo recipiente de Yu Yevon, quien reencarna en un nuevo Sin.Yuna, Tidus y el resto del grupo deciden que ya no seguirán el plan tradicional de sacrificar a Yuna para derrotar a Sin. En cambio, elaboran un plan para derrotar a Yu Yevon y poner fin al ciclo de destrucción de una vez por todas. Con la ayuda de los Aeons y los recuerdos del padre de Tidus, Jecht, el grupo enfrenta a Sin y lo destruye, liberando a Spira de su terror cíclico.Sin embargo, en el proceso, Tidus descubre que él también es parte de una ilusión. Zanarkand, la ciudad de la que proviene, era en realidad una sueño creado por los Sueños de los Fayth, un grupo de espíritus que ha estado manteniendo la existencia de la ciudad como una forma de resistencia contra Yu Yevon. Al derrotar a Yu Yevon, los Sueños de los Fayth finalmente pueden descansar, lo que significa que Zanarkand y todo lo que proviene de ella, incluyendo a Tidus, dejarán de existir.";

    if (texto == NULL) {
        fprintf(stderr, "No se pudo cargar el archivo\n");
        return EXIT_FAILURE;
    }

    size_t numListas = 4; // Cambia el número de listas si es necesario
    size_t longitudes[numListas];

    srand((unsigned int)time(NULL)); // Inicializar la semilla para números aleatorios

    // Generar longitudes aleatorias entre 1 y 10
    for (size_t i = 0; i < numListas; ++i) {
        longitudes[i] = (rand() % 9) + 1;
    }

    ListaDoble* log[numListas];
    for (size_t i = 0; i < numListas; ++i) {
        log[i] = filtro(texto, longitudes[i]);
    }

    imprimirLOG(log, longitudes, numListas);

    for (size_t i = 0; i < numListas; ++i) {
        LiberarLista(log[i]);
    }

    return EXIT_SUCCESS;
}
