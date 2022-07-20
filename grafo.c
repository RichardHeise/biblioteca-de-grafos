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
  agwrite(g, stdout);

  return g;
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
static int **matriz_aloc(int tam) {
  
  int **matriz = malloc( tam * sizeof(int *));

  if (!(**matriz)) {
    perror("Erro ao alocar matriz de adjacência, abortando.\n");
    exit(MALLOC_ERROR);
  }

  for (int i = 0; i < tam; i++) {
    matriz[i] = malloc(sizeof(int)*tam);
    if (!matriz[i]) {
      perror("Erro ao alocar matriz de adjacência, abortando.\n");
      exit(MALLOC_ERROR);
    }
  }

  return matriz;
}

int n_triangulos(grafo g) {
  
  if ( !g ) {
    perror("Grafo nulo, abortando.\n");
    exit(GRAPH_ERROR);
  }

  int tam = agnnodes(g);

  int **m_adj = matriz_adjacencia(g);
  int **adj_quadrado = matriz_aloc(tam);
  int **adj_cubic = matriz_aloc(tam);

  int soma = 0;

  for (int i = 0; i < tam; i++) {
    for (int j = 0; j < tam; j++) {
      soma = 0;
      for (int k = 0; k < tam; k++) {
        soma += m_adj[i][k] * m_adj[k][j];
      }
      adj_quadrado[i][j] += soma;
    }
  }

  for (int i = 0; i < tam; i++) {
    for (int j = 0; j < tam; j++) {
      soma = 0;
      for (int k = 0; k < tam; k++) {
        soma += adj_quadrado[i][k] * m_adj[k][j];
      }
      adj_cubic[i][j] += soma;
    }
  }

  int traco = tam * adj_cubic[0][0];

  int num_tri = (traco / adj_cubic[i][tam-1]);

  for (int i = 0; i < tam; i++) {
    for (int j = 0; j < tam; j++) {
      printf("%d ", adj_cubic[i][j]);
    }
    printf("\n");
  }

  printf("TRIANGULOS: %d\n", num_tri);

  return 0;
}

// -----------------------------------------------------------------------------


int **matriz_adjacencia(grafo g) {
  
  if ( !g ) {
    perror("Grafo nulo, abortando.\n");
    exit(GRAPH_ERROR);
  }

  int **adj = matriz_aloc(agnnodes(g));
  
  int i = 0;
  int j = 0;
  vertice aux;
  vertice aux2;

  for (aux = agfstnode(g); aux; aux = agnxtnode(g, aux)) {
    j = 0;
    for(aux2 = agfstnode(g); aux2; aux2 = agnxtnode(g, aux2)) {
      adj[i][j] = ( (agedge(g, aux, aux2, NULL, FALSE)) ? 1 : 0 );
      j++;
    }
    i++;
  }

  return adj;
}

// -----------------------------------------------------------------------------

static grafo copia(grafo g) {

  if ( !g ) {
    perror("Grafo nulo, abortando.\n");
    exit(GRAPH_ERROR);
  }

  grafo grafo_cp = agopen("grafo_cp", Agstrictundirected, NULL);
  vertice aux;
  vertice aux2;
  
  for (aux = agfstnode(g); aux; aux = agnxtnode(g, aux)) {
    agnode(grafo_cp, agnameof(aux), TRUE);
  }

  for (aux = agfstnode(grafo_cp); aux; aux = agnxtnode(grafo_cp, aux)) {
    for(aux2 = agnxtnode(grafo_cp, aux); aux2; aux2 = agnxtnode(grafo_cp, aux2)) {
      agedge(grafo_cp, aux, aux2, NULL, TRUE);
    }
  }

  return grafo_cp;
}

grafo complemento(grafo g) {
  
  if ( !g ) {
    perror("Grafo nulo, abortando.\n");
    exit(GRAPH_ERROR);
  }

  grafo g_comp = copia(g);
  vertice aux;
  vertice aux2;
  Agedge_t* e;
  

  for (aux = agfstnode(g_comp); aux; aux = agnxtnode(g_comp, aux)) {
    for(aux2 = aux; aux2; aux2 = agnxtnode(g_comp, aux2)) {
      if (aux != aux2) {

        e = agedge(g_comp, aux, aux2, NULL, FALSE);
        if (e) {
          agdeledge( g_comp, e );
        } else {
          agedge(g_comp, aux, aux2, NULL, TRUE);
        }

      }
    }
  }

  return g_comp;
}

