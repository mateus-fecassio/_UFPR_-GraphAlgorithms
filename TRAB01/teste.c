#include <stdio.h>
#include "grafo.h"
void conferencia(grafo g, int seq);

//------------------------------------------------------------------------------

int main(void) {
  int number;

  grafo g = le_grafo();
  //vertice v;

  fprintf(stdout, "Grafo:\n");
  escreve_grafo(g);

  number = n_vertices(g);
  fprintf(stdout, "Quantidade de Vértices: %d\n", number);
  
  number = n_arestas(g);
  fprintf(stdout, "Quantidade de Arestas: %d\n", number);

  //number = grau(v,g);
  //fprintf(stdout, "Grau da Aresta %s: %d\n", v, number);

  number = grau_maximo(g);
  fprintf(stdout, "Grau MÁXIMO: %d\n", number);

  number = grau_minimo(g);
  fprintf(stdout, "Grau MÍNIMO: %d\n", number);

  number = grau_medio(g);
  fprintf(stdout, "Grau MÉDIO: %d\n", number);

  number = regular(g);
  fprintf(stdout, "Regular: %d\n", number);

  number = completo(g);
  fprintf(stdout, "Completo: %d\n", number);

  number = conexo(g);
  fprintf(stdout, "Conexo: %d\n", number);

  number = bipartido(g);
  fprintf(stdout, "Bipartido: %d\n", number);

  number = n_triangulos(g);
  fprintf(stdout, "Triângulos: %d\n", number);

  fprintf(stdout, "Matriz de Adjacência: \n");
  matriz_adjacencia(g);
  //conferencia(g,0);

  fprintf(stdout, "Complemento: \n");
  grafo comp;
  comp = complemento(g);
  //conferencia(comp,0);

  destroi_grafo(g);
  return 0;
}