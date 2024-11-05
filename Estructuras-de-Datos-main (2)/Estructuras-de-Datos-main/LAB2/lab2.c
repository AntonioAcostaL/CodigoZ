#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "ListaEnlazada/ListaDoble.h"

int main() {
    srand(time(NULL));  

    ListaDoble blogList = {NULL, NULL};

    GenerarComentarios(&blogList, 100);

    printf("Lista original:\n");
    ImprimirLista(&blogList);

    OrdenarPorLongitudComentario(&blogList);
    printf("Lista ordenada por longitud del comentario:\n");
    ImprimirLista(&blogList);

    FiltrarComentariosCortos(&blogList, 20); 
    printf("Lista después de filtrar comentarios de 20 letras o menos:\n");
    ImprimirLista(&blogList);

    EliminarUsuariosLargos(&blogList);
    printf("Lista después de eliminar usuarios con más de 3 letras:\n");
    ImprimirLista(&blogList);

    printf("Lista original en reversa:\n");
    ImprimirListaReversa(&blogList);

    LiberarLista(&blogList);

    return 0;
}
