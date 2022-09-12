#include <stdio.h>
#include "grafo.h"
//------------------------------------------------------------------------------

int main(void) {
    grafo g = le_grafo();
    //vertice v;

    fprintf(stdout, "Grafo:\n");
    escreve_grafo(g);

    fprintf(stdout, "DECOMPOSIÇÃO:\n");
    decompoe(g);
    

    // for (grafo sub = agfstsubg(g); sub; sub = agnxtsubg(sub)) {
    //     escreve_grafo(sub);
    // }

  
    escreve_grafo(g);
    destroi_grafo(g);
    return 0;
}