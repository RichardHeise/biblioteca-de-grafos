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

    agfree(g, NULL);

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

    
    return agdegree(g, v, TRUE, TRUE);
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

    // Caminha nos nodos buscando o de maior grau
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

    // Caminha nos nodos buscando o de menor grau
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

    // enquanto há um próximo vértice
    while (agnxtnode(g, origem)) {
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

    // número de vértices score 2 expandido e sem fatoriais
    int max_arestas = ( (vertices * (vertices-1) ) / 2);

    return (agnedges(g) == max_arestas); 
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Função local para buscar um vértice em um vetor de vértices de tamanho arbitrário
// custo linear
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

    // pilha de vertices
    int i = 0;
    vertice pilha[tam];
    pilha[i] = agfstnode(g);
    i++;

    // vetor de visitados
    int j = 0;
    vertice visitados[tam];
    
    // contador de vizinhos empilhados
    int c = 0;
    while (i) {

        // desempilha o topo
        i--;
        vertice topo = pilha[i];

        // BFS
        // se não visitamos o topo ainda
        if ( !buscaVetor(visitados, topo, i) ) {

        // buscamos os vizinhos do topo
        for (vertice ver1 = topo; ver1; ver1 = agnxtnode(g, ver1)) {
            if ( agedge(g, topo, ver1, NULL, FALSE)) {

                // se não visitamos os vizinhos, visitaremos ainda
                if ( !buscaVetor(visitados, ver1, j) ) {
                    pilha[i] = ver1; 
                    c++; // incremento do contador de vizinhos
                    i++;
                }
            }
        }

        // vizinho visitado
        visitados[j] = topo;
        j++;

        }
    }

    // se nosso contador de vizinhos foi todos os vizinhos, 
    // o grafo é conexo. Senão, não é.
    return (c == tam-1);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int bipartido(grafo g) {
  
    if ( !g ) {
        perror("Grafo nulo, abortando.\n");
        exit(GRAPH_ERROR);
    }

    // struct local com nodo e cor do nodo
    typedef struct nodo_s {
        vertice n;
        short cor;
    } nodo_t;

    int tam = agnnodes(g);
    int i = 0;

    // vetor auxiliar de nodos
    nodo_t nodos[tam];

    for (vertice origem = agfstnode(g); origem; origem = agnxtnode(g, origem)) {
        nodos[i].n = origem;
        nodos[i].cor = 0;
        i++;
    }

    // pilha de nodos
    i = 0;
    nodo_t pilha[tam];

    // para todo nodo, funciona para grafos disconectados e conectados
    for (int k = 0; k < tam; k++) {

        // se o nodo em questão não foi colorido, colorimos e o empilhamos
        if (!nodos[k].cor) {
            nodos[k].cor = 1;
            pilha[i] = nodos[k];
            i++;
        }

        // enquanto a pilha não estiver vazia
        while (i) {

        // desempilha o topo
        i--;
        nodo_t topo = pilha[i];

        // busca por vizinhos do topo
        for (int j = 0; j < tam; j++) {
            if ( agedge(g, topo.n, nodos[j].n, NULL, FALSE) ) {
            
                // se o vizinho não for colorido
                if (!nodos[j].cor) {

                    // colorimos com uma cor diferente ao do topo
                    nodos[j].cor = topo.cor + 1;

                    // empilhamos o vizinho
                    pilha[i] = nodos[j]; 
                    i++;

                // se o vizinho tem a mesma cor do topo, o grafo não é bipartido
                } else if (nodos[j].cor == topo.cor) return 0;
            } 
        }
        }
    }
    
    // todos os vizinhos foram coloridos somente com duas cores
    // então o grafo é bipartido
    return 1;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Função local para alocação dinâmica de matrizes de tamanho tam
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

// Função local para liberação de memória de matrizes m de tamanho tam
static void matriz_free(int **m, int tam) {
    for (int i = 0; i < tam; i++)
        free(m[i]);
    free(m);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Função local que multiplica matrizes quadradas m1 e m2 de tamanho tam
static int **mult_matriz(int tam, int **m1, int **m2) {

    int **mat = matriz_aloc(tam);

    int soma = 0;

    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            mat[i][j] = 0;
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

// Função local para printar matriz de adjacência
static void print_adj(int **m, int tam) {

    for (int i = 0; i < tam; i++) {
        for (int j = 0; j < tam; j++) {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }

}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


// uma explicação detalhada do funcionamento dessa função pode ser encontrada aqui
// https://www.geeksforgeeks.org/number-of-triangles-in-a-undirected-graph/
int n_triangulos(grafo g) {
    
    if ( !g ) {
        perror("Grafo nulo, abortando.\n");
        exit(GRAPH_ERROR);
    }

    int tam = agnnodes(g);

    int **m_adj = matriz_adjacencia(g);
    int **m_aux = matriz_adjacencia(g);

    // pegamos o cubo da matriz de adjacência em m_aux
    m_aux = mult_matriz(tam, m_adj, m_aux);
    m_aux = mult_matriz(tam, m_adj, m_aux);

    // pegamos o traço da matriz cúbica de adjacência
    int traco = 0;
    for (int i = 0; i < tam; i++) {
        traco += m_aux[i][i];
    }

    // dividindo o traço por 2, pois o grafo é não-direcionado
    // e depois por 3, pois são ciclos de tamanho 3
    int num_tri = (traco / 6);

    matriz_free(m_adj, tam);
    matriz_free(m_aux, tam);

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

  // caminha por todos os vértices encontrando todas as arestas
  // e atribuindo 1s ou 0s na matriz de adjacência
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

// função local para copiar um grafo g, retorna o grafo copiado
static grafo copia(grafo g) {

  if ( !g ) {
    perror("Grafo nulo, abortando.\n");
    exit(GRAPH_ERROR);
  }

  grafo grafo_cp = agopen("grafo_cp", Agstrictundirected, NULL);
  vertice origem;
  vertice destino;

  // copia vértices
  for (origem = agfstnode(g); origem; origem = agnxtnode(g, origem)) {
    agnode(grafo_cp, agnameof(origem), TRUE);
  }

  // copia arestas
  for (origem = agfstnode(g); origem; origem = agnxtnode(g, origem)) {
    for (destino = agnxtnode(g, origem); destino; destino = agnxtnode(g, destino)) {
        if ( agedge(g, origem, destino, NULL, FALSE) ) {
            agedge(grafo_cp, agnode(grafo_cp, agnameof(origem), FALSE), agnode(grafo_cp, agnameof(destino), FALSE), NULL, TRUE);
        }
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
  vertice origem;
  vertice destino;
  

  // inverte as arestas do grafo copiado: se o original tinha uma aresta entre dois nodos
  // o complementar não tem e vice-versa
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

