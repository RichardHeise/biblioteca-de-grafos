#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

//------------------------------------------------------------------------------
grafo le_grafo(void) {

  grafo g = agread(stdin, NULL);
  if ( !g ) {
    perror("Erro ao ler o grafo, abortando.\n");
    exit(READ_ERROR);
  }

  return g; 
}
//------------------------------------------------------------------------------
void destroi_grafo(grafo g) {
  
  if ( !g ) {
    perror("Grafo nulo, abortando.\n");
    exit(GRAPH_ERROR);
  }

  return;
}
//------------------------------------------------------------------------------
grafo escreve_grafo(grafo g) {
  
  if ( !g ) {
    perror("Grafo nulo, abortando.\n");
    exit(GRAPH_ERROR);
  }

  return agwrite(g, stdout);
}

// -----------------------------------------------------------------------------
int n_vertices(grafo g) {
  
  if ( !g ) {
    perror("Grafo nulo, abortando.\n");
    exit(GRAPH_ERROR);
  }

  return agnnodes(g);
}

// -----------------------------------------------------------------------------
int n_arestas(grafo g) {
  
  if ( !g ) {
    perror("Grafo nulo, abortando.\n");
    exit(GRAPH_ERROR);
  }

  return agnedges(g);
}

// -----------------------------------------------------------------------------
int grau(vertice v, grafo g) {
  
  if ( !v ) {
    perror("Vértice nulo, abortando.");
    exit(NODE_ERROR);
  }

  if ( !g ) {
    perror("Grafo nulo, abortando.\n");
    exit(GRAPH_ERROR);
  }

  
  return agdegree(g, v, TRUE, TRUE);;
}

// -----------------------------------------------------------------------------
int grau_maximo(grafo g)  {
  
  if ( !g ) {
    perror("Grafo nulo, abortando.\n");
    exit(GRAPH_ERROR);
  }

  vertice aux;
  int grau_max = 0;
  int grau = 0;

  for (aux = agfstnode(g); aux; aux = agnxtnode(g, aux)) {
    grau = agdegree(g, aux, TRUE, TRUE);
    if ( grau_max < grau) {
      grau_max = grau;
    }
  }

  return grau_max;
}

// -----------------------------------------------------------------------------
int grau_minimo(grafo g)  {
  
  if ( !g ) {
    perror("Grafo nulo, abortando.\n");
    exit(GRAPH_ERROR);
  }

  vertice aux;
  int grau_min = 2147483647; // max int value
  int grau = 0;

  for (aux = agfstnode(g); aux; aux = agnxtnode(g, aux)) {
    grau = agdegree(g, aux, TRUE, TRUE);
    if ( grau_min > grau) {
      grau_min = grau;
    }
  }

  return grau_min;
}

// -----------------------------------------------------------------------------
int grau_medio(grafo g) {
  
  if ( !g ) {
    perror("Grafo nulo, abortando.\n");
    exit(GRAPH_ERROR);
  }

  vertice aux;
  int grau_medio = 0;
  int grau_soma = 0;

  for (aux = agfstnode(g); aux; aux = agnxtnode(g, aux)) {
    grau_soma += agdegree(g, aux, TRUE, TRUE);
  }

  grau_medio = ( grau_soma / agnnodes(g) );

  return grau_medio;
}

// -----------------------------------------------------------------------------
int regular(grafo g) {
  
  if ( !g ) {
    perror("Grafo nulo, abortando.\n");
    exit(GRAPH_ERROR);
  }

  vertice aux = agfstnode(g);
  int vertices = agnnodes(g)-1;

  while (vertices--) {
    if (agdegree(g, aux, TRUE, TRUE) != agdegree(g, agnxtnode(g, aux), TRUE, TRUE) ) return 0;
    aux = agnxtnode(g, aux);
  }

  return 1;
}

// -----------------------------------------------------------------------------
int completo(grafo g) {
  
  if ( !g ) {
    perror("Grafo nulo, abortando.\n");
    exit(GRAPH_ERROR);
  }

  int vertices = agnnodes(g);
  int max_arestas = ( (vertices * (vertices-1) ) / 2);

  return (agnedges(g) == max_arestas); 
}

// -----------------------------------------------------------------------------
int conexo(grafo g) {
  
  if ( !g ) {
    perror("Grafo nulo, abortando.\n");
    exit(GRAPH_ERROR);
  }

  return 0;
}

// -----------------------------------------------------------------------------
int bipartido(grafo g) {
  
  if ( !g ) {
    perror("Grafo nulo, abortando.\n");
    exit(GRAPH_ERROR);
  }

  return 0;
}

// -----------------------------------------------------------------------------
int n_triangulos(grafo g) {
  
  if ( !g ) {
    perror("Grafo nulo, abortando.\n");
    exit(GRAPH_ERROR);
  }

  return 0;
}

// -----------------------------------------------------------------------------
int **matriz_adjacencia(grafo g) {
  
  if ( !g ) {
    perror("Grafo nulo, abortando.\n");
    exit(GRAPH_ERROR);
  }

  long unsigned int tam = (long unsigned int)agnnodes(g);
  int **adj = malloc( tam * sizeof(int *));
  for (long unsigned int i = 0; i < tam; i++)
    adj[i] = malloc(sizeof(int)*tam);
  
  long unsigned int i = 0;
  long unsigned int j = 0;
  vertice aux;
  vertice aux2;

  for (aux = agfstnode(g); aux; aux = agnxtnode(g, aux)) {
    for(aux2 = agnxtnode(g, aux); aux2; aux2 = agnxtnode(g, aux2)) {
      adj[i][j] = ( (agedge(g, aux, aux2, NULL, FALSE)) ? 0 : 1 );
      j++;
    }
    i++;
  }
  
  for (i = 0; i < tam; i++) {
    for (j = 0; j < tam; j++) {
      printf("%d ", adj[i][j]);
    }
    printf("\n");
  }

  return adj;
}

// -----------------------------------------------------------------------------
grafo complemento(grafo g) {
  
  if ( !g ) {
    perror("Grafo nulo, abortando.\n");
    exit(GRAPH_ERROR);
  }

  return NULL;
}

