### Trabalho 1 de grafos ###

Autor: Richard Fernando Heise Ferreira GRR20191053


Esse relatório visa apensar comentar o que é pertinente para facilitar a correção do professor, detalhes aprofundados da implementação estão comentados no código.

As implementações das função de número de vértices e arestas, leitura, escrita, destruição de grafos foram triviais: precisaram meramente de uma chamada da biblioteca cgraph.

As demais funções tiveram lógica associada, em especial as funções de checagem de conexidade, completude e bipartição.


Completude: é previsto que não haja laços no grafo e nem duas arestas entre os mesmos vértices para que funcione.

Conexidade: foi implementada uma busca em largura (BFS) usando pilha e uma lista de vizinhos.

Bipartição: foi implementada uma coloração de vértices que funciona para grafos desconectados, usando pilha e uma struct local com vértice e cor.

Triangulos: foi implementado um algoritmo que pega o cubo da matriz de adjacência, tira o traço da matriz e o divide por 6 a fim de descobrir o número de triangulos.


Também foram criadas funções locais (static) para auxiliar algumas funções, elas serão listadas abaixo e espera-se que o nome de cada uma seja autoexplicativo.

static int buscaVetor(vertice vetor[], vertice elem, int tam);
static int **matriz_aloc(int tam);
static void matriz_free(int **m, int tam);
static int **mult_matriz(int tam, int **m1, int **m2);
static void print_adj(int **m, int tam);
static grafo copia(grafo g);

Caso, contudo, o professor não ache autoexplicativo há comentários no código para facilitar o entendimento.

Por último, o código compila com muitos warnings devido às opções de compilação deixadas no Makefile pelos professores. Nenhuma delas, porém, é grave:
em boa parte são resultado da própria biblioteca cgraph e sua resolução seria trivial, porém deselegante, a exemplo do warning de / "char *" instead of "const char *" /
que simplesmente espera que o programador declare um vetor estático com uma string para atribuir um nome à um grafo na função agopen, sendo que a simples passagem da string
direto como argumento da função também funciona e é muito mais direto.

Grato pela atenção.