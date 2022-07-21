#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

grafo le_grafo(void) {

  grafo g = agread(stdin, NULL);
  if ( !g ) {
    perror("Erro ao ler o grafo, abortando.\n");
    exit(READ_ERROR);
  }

  return g; 
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void destroi_grafo(grafo g) {
  
  if ( !g ) {
    perror("Grafo nulo, abortando.\n");
    exit(GRAPH_ERROR);
  }

  return;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

grafo escreve_grafo(grafo g) {
  
  if ( !g ) {
    perror("Grafo nulo, abortando.\n");
    exit(GRAPH_ERROR);
  }
  agwrite(g, stdout);

  return g;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int n_vertices(grafo g) {
  
  if ( !g ) {
    perror("Grafo nulo, abortando.\n");
    exit(GRAPH_ERROR);
  }

  return agnnodes(g);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int n_arestas(grafo g) {
  
  if ( !g ) {
    perror("Grafo nulo, abortando.\n");
    exit(GRAPH_ERROR);
  }

  return agnedges(g);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
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

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
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

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
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

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
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

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
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

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int completo(grafo g) {
  
  if ( !g ) {
    perror("Grafo nulo, abortando.\n");
    exit(GRAPH_ERROR);
  }

  int vertices = agnnodes(g);
  int max_arestas = ( (vertices * (vertices-1) ) / 2);

  return (agnedges(g) == max_arestas); 
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static int buscaVetor(vertice vetor[], vertice elem, int tam) {
  for (int i = 0; i < tam; i++) {
    if (vetor[i] == elem) {
      return 1;
    }
  }

  return 0;
}

int conexo(grafo g) {
  
  if ( !g ) {
    perror("Grafo nulo, abortando.\n");
    exit(GRAPH_ERROR);
  }

  int tam = agnnodes(g);
  int i = 0;
  int c = 0;

  vertice visitados[tam];
  visitados[i] = agfstnode(g);
  i++;
  
  while (i) {
    vertice aux = visitados[i];
    i--;

    // BFS
    //if ( !buscaVetor(visitados, aux, i) ) {
      for (vertice ver1 = aux; ver1; ver1 = agnxtnode(g, ver1)) {
        for (vertice ver2 = agfstnode(g); ver2; ver2 = agnxtnode(g, ver2)) {
          if ( agedge(g, ver1, ver2, NULL, FALSE) ) {
            if ( !buscaVetor(visitados, ver2, i) ) {
              visitados[i] = ver2; 
              i++;
              c++;
            }
          }
        }
      }
    //}
  }

  printf("valor do c: %d\n", c);
  return 0;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int bipartido(grafo g) {
  
  if ( !g ) {
    perror("Grafo nulo, abortando.\n");
    exit(GRAPH_ERROR);
  }

  return 0;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

static int **matriz_aloc(int tam) {
  
  int **matriz = malloc( tam * sizeof(int *));

  if (!matriz) {
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

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static int **mult_matriz(int tam, int **m1, int **m2) {

  int **mat = matriz_aloc(tam);

  int soma = 0;

  for (int i = 0; i < tam; i++) {
    for (int j = 0; j < tam; j++) {
      soma = 0;
      for (int k = 0; k < tam; k++) {
        soma += m1[i][k] * m2[k][j];
      }
      mat[i][j] += soma;
    }
  }

  return mat;
}

int n_triangulos(grafo g) {
  
  if ( !g ) {
    perror("Grafo nulo, abortando.\n");
    exit(GRAPH_ERROR);
  }

  int tam = agnnodes(g);

  int **m_adj = matriz_adjacencia(g);
  int **m_aux = matriz_adjacencia(g);

  m_aux = mult_matriz(tam, m_adj, m_aux);
  m_aux = mult_matriz(tam, m_adj, m_aux);

  int traco = tam * m_aux[0][0];
  int num_tri = (traco / 6);

  return num_tri;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


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

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

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

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

grafo complemento(grafo g) {
  
  if ( !g ) {
    perror("Grafo nulo, abortando.\n");
    exit(GRAPH_ERROR);
  }

  grafo g_comp = copia(g);
  vertice aux;
  vertice aux2;
  

  for (aux = agfstnode(g_comp); aux; aux = agnxtnode(g_comp, aux)) {
    for(aux2 = agnxtnode(g_comp, aux); aux2; aux2 = agnxtnode(g_comp, aux2)) {
      if (aux->mainsub.node != aux2->mainsub.node) {

        aresta e = agedge(g_comp, aux, aux2, NULL, FALSE);
        if (e == NULL) {
          agedge(g_comp, aux, aux2, NULL, TRUE);
        } else {
          agdeledge( g_comp, e );
        }

      }
    }
  }

  return g_comp;
}

