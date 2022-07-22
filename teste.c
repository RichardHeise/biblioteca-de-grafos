#include <stdio.h>
#include "grafo.h"

//------------------------------------------------------------------------------

int main(void) {

  grafo g = le_grafo();

  printf("Número de vértices: %d\n", n_vertices(g) );

  printf("Número de arestas: %d\n", n_arestas(g) );

  printf("Vértice escolhido foi: %s\n", agnameof(agfstnode(g)));

  printf("Grau do vértice a é: %d\n", grau(agnode(g, agnameof(agfstnode(g)), FALSE), g));

  printf("O grau máximo do grafo g é: %d\n", grau_maximo(g));

  printf("O grau mínimo do grafo g é: %d\n", grau_minimo(g));

  printf("O grau médio do grafo g é: %d\n", grau_medio(g));

  printf("Regularidade: %d\n", regular(g));

  printf("Completude: %d\n", completo(g));

  printf("Triangulos: %d\n", n_triangulos(g));
  
  printf("Original:");
  escreve_grafo(g);
  printf("\n");

  grafo h = complemento(g);

  printf("Complementar:");
  escreve_grafo(h);
  printf("\n");

  printf("Conexo: %d\n", conexo(g));
  
  destroi_grafo(g);

  return 0;
}
