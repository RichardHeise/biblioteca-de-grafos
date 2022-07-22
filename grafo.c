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

  vertice origem;
  int grau_max = 0;
  int grau = 0;

  for (origem = agfstnode(g); origem; origem = agnxtnode(g, origem)) {
    grau = agdegree(g, origem, TRUE, TRUE);
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

  vertice origem;
  int grau_min = 2147483647; // max int value
  int grau = 0;

  for (origem = agfstnode(g); origem; origem = agnxtnode(g, origem)) {
    grau = agdegree(g, origem, TRUE, TRUE);
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

  vertice origem;
  int grau_medio = 0;
  int grau_soma = 0;

  for (origem = agfstnode(g); origem; origem = agnxtnode(g, origem)) {
    grau_soma += agdegree(g, origem, TRUE, TRUE);
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

  vertice origem = agfstnode(g);
  int vertices = agnnodes(g)-1;

  while (vertices--) {
    if (agdegree(g, origem, TRUE, TRUE) != agdegree(g, agnxtnode(g, origem), TRUE, TRUE) ) return 0;
    origem = agnxtnode(g, origem);
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

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int conexo(grafo g) {
  
  if ( !g ) {
    perror("Grafo nulo, abortando.\n");
    exit(GRAPH_ERROR);
  }

  int tam = agnnodes(g);

  int i = 0;
  vertice pilha[tam];
  pilha[i] = agfstnode(g);
  i++;

  int j = 0;
  vertice visitados[tam];
  
  while (i) {
    i--;
    vertice origem = pilha[i];

    // BFS
    if ( !buscaVetor(visitados, origem, i) ) {

        for (vertice ver1 = agfstnode(g); ver1; ver1 = agnxtnode(g, ver1)) {

          if ( agedge(g, origem, ver1, NULL, FALSE)) {
            if ( !buscaVetor(visitados, ver1, j) ) {
              pilha[i] = ver1; 
              i++;
            }
          }
      }
      visitados[j] = origem;
      j++;
    }
  }

  return (j == tam-1) ? 0 : 1;
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

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

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
  vertice origem;
  vertice destino;

  for (origem = agfstnode(g); origem; origem = agnxtnode(g, origem)) {
    j = 0;
    for(destino = agfstnode(g); destino; destino = agnxtnode(g, destino)) {
      adj[i][j] = ( (agedge(g, origem, destino, NULL, FALSE)) ? 1 : 0 );
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
  vertice origem;
  vertice destino;

  int **adj = matriz_adjacencia(g);
  int tam = agnnodes(g);
  int i = 0;
  int j = 0;

  for (origem = agfstnode(g); origem; origem = agnxtnode(g, origem)) {
    agnode(grafo_cp, agnameof(origem), TRUE);
  }

  for (origem = agfstnode(grafo_cp); origem && i < tam; origem = agnxtnode(grafo_cp, origem)) {
    j = i+1;
    for (destino = agnxtnode(grafo_cp, origem); destino && j < tam; destino = agnxtnode(grafo_cp, destino)) {
      if (adj[i][j]) {
        agedge(grafo_cp, origem, destino, NULL, TRUE);
      }
      j++;
    }
    i++;
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
  vertice origem;
  vertice destino;
  

  for (origem = agfstnode(g_comp); origem; origem = agnxtnode(g_comp, origem)) {
    for(destino = agnxtnode(g_comp, origem); destino; destino = agnxtnode(g_comp, destino)) {
      if (origem != destino) {

        aresta e = agedge(g_comp, origem, destino, NULL, FALSE);
        if (e == NULL) {
          agedge(g_comp, origem, destino, NULL, TRUE);
        } else {
          agdeledge( g_comp, e );
        }
      }
    }
  }

  return g_comp;
}

