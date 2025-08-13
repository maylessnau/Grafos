/*******************************************
 * Implementação de biblioteca para grafos.
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>

//---------------------------------------------------------
// getters:

int vertice_id(vertice v) {
  return v->id;
}
char* vertice_rotulo(vertice v) {
  return v->rotulo;
}
int vertice_particao(vertice v) {
  return v->particao;
}
int custo(vertice v) {
  return v->custo;
}
int estado(vertice v) {
  return v->estado;
}
vertice pai(vertice v) {
  return v->pai;
}
lista fronteira_entrada(vertice v) {
  return v->fronteira_entrada;
}
lista fronteira_saida(vertice v) {
  return v->fronteira_saida;
}
int aresta_id(aresta e) {
  return e->id;
}
vertice vertice_u(aresta e) {
  return e->u;
}
vertice vertice_v(aresta e) {
  return e->v;
}
int grafo_id(grafo G) {
  return G->id;
}
lista vertices(grafo G) {
  return G->vertices;
}
lista arestas(grafo G) {
  return G->arestas;
}

//---------------------------------------------------------
// funcoes para construcao/desconstrucao do grafo:


// cria grafo vazio e o retorna
grafo cria_grafo(int id) {
  grafo G = (grafo) malloc(sizeof(t_grafo));
  if (!G)
    exit(_ERRO_MALLOC_);
  G->vertices = cria_lista();
  G->arestas = cria_lista();
  G->id = id;
  return G;
}

// destroi grafo G (desaloca toda a memoria)
void destroi_grafo(grafo G) {
  
  vertice v;                                                                  
  no n, proximo_no;                                                           
                                                                                  
  n = primeiro_no(vertices(G));                                               
  while (n != NULL) { 
    // armazena o próximo nó antes de remover o vértice 
    proximo_no = proximo(n); 
    v = conteudo(n);                                                        
    remove_vertice(vertice_id(v), G);
    // avança para o próximo nó                                      
    n = proximo_no;                              
  }                                                                           
                                                                                  
  // libera listas de vértices e arestas                                      
  free(vertices(G));                                                          
  G->vertices = NULL;
  free(arestas(G));  
  G->arestas = NULL;                                                         
                                                                                  
  free(G);                                                                    
  G = NULL;  
}

// cria novo vertice com id <id>, rotulo <rotulo>, particao <particao>
// e adiciona ao grafo G
void adiciona_vertice(int id, char *rotulo, int particao, grafo G) {

  // aloca memória para o novo vértice
  vertice v = (vertice) malloc (sizeof(t_vertice));
  if (!v) 
	exit(_ERRO_MALLOC_);

  v->id = id;
  // copia o conteúdo de 'rotulo' para 'v->rotulo', com tamanho máximo de 9 caracteres
  strncpy(v->rotulo, rotulo, sizeof(v->rotulo) - 1);
  
  // assegura que `v->rotulo` seja terminado em `\0`
  v->rotulo[sizeof(v->rotulo) - 1] = '\0';
  v->particao = particao;
  v->fronteira_entrada = cria_lista();
  v->fronteira_saida = cria_lista();

  // adiciona o vértice criado na lista de vértices do grafo
  empilha(v,vertices(G));
}

// remove vertice com id <id> do grafo G e o destroi
// [deve remover e destruir tambem as arestas incidentes]
void remove_vertice(int id, grafo G) {

  // remove o vértice da lista de vértices do grafo, armazenando-o em v
  vertice v = remove_chave_int(id, vertices(G), (int_f_obj) vertice_id);           
  if (v == NULL) {                                                            
	printf("Vertice %d não encontrado.\n", id);                             
	return;                                                                 
  }                                                                  

  // remove as arestas da fronteira de entrada do vértice do grafo
  while (!vazio(fronteira_entrada(v))) {                                             
    remove_aresta(aresta_id(desempilha(fronteira_entrada(v))), G);                  
  }
  // libera a memória alocada para a fronteira de entrada do vértice
  free(fronteira_entrada(v));                                                       
  
  // faz o mesmo procedimento para a fronteira de saída do vértice 
  while (!vazio(fronteira_saida(v))) {                                             
    remove_aresta(aresta_id(desempilha(fronteira_saida(v))), G);                  
  }                                                                        
  free(fronteira_saida(v));
   
  // libera a memória do vértice                                                   
  free(v);                                      
  v = NULL; 
}

// cria aresta com id <id> incidente a vertices com ids
// <u_id> e <v_id> e adiciona ao grafo G
void adiciona_aresta(int id, int u_id, int v_id, grafo G) {

  vertice u,v;

  // aloca memória para a aresta
  aresta a = (aresta) malloc(sizeof(t_aresta));
  if(!a)
    exit(_ERRO_MALLOC_);

  // busca os vértices que serão as pontas dessa aresta
  u = busca_chave_int(u_id,vertices(G),(int_f_obj) vertice_id);
  v = busca_chave_int(v_id,vertices(G),(int_f_obj) vertice_id);

  if(u == NULL || v == NULL) {
    printf("Um ou ambos os vertices nao existem.\n");
    free(a);
    return;
  }

  a->id = id;
  a->u = u;
  a->v = v;
  
  // empilha a aresta tanto nas respectivas fronteiras das pontas (u -> v), 
  // quanto na lista de arestas do grafo
  empilha(a,fronteira_entrada(v));
  empilha(a,fronteira_saida(u));
  empilha(a,arestas(G));
}


// remove aresta com id <id> do grafo G e a destroi
void remove_aresta(int id, grafo G) {
	
  // remove a aresta da lista de arestas do grafo, armazenando-a em a
  aresta a = remove_chave_int (id, arestas(G), (int_f_obj) aresta_id);
  if (!a) {
	printf("Aresta com id %d não encontrada\n", id);
	return;
  }

  // remove a aresta das fronteiras de suas pontas
  remove_chave_int (id, fronteira_entrada(vertice_v(a)),(int_f_obj) aresta_id);
  remove_chave_int (id, fronteira_saida(vertice_u(a)),(int_f_obj) aresta_id);
  
  // libera a memória da aresta
  free(a);
  a = NULL;
}

//---------------------------------------------------------
// funcoes para operacoes com o grafo pronto:

// calcula e devolve os graus do vertice v
int grau_entrada(vertice v) {
  int d_v = 0;
  for (no n = primeiro_no(fronteira_entrada(v)); n; n = proximo(n))
    ++d_v;
  return d_v;
}
int grau_saida(vertice v) {
  int d_v = 0;
  for (no n = primeiro_no(fronteira_saida(v)); n; n = proximo(n))
    ++d_v;
  return d_v;
}

// imprime o grafo G
void imprime_grafo(grafo G) {
  /* imprimindo apenas a estrutura do grafo
  printf("%d\n", grafo_id(G));
  printf("\nVertices: ");
  imprime_lista(vertices(G), (void_f_obj) imprime_vertice);
  printf("\nArestas: ");
  imprime_lista(arestas(G), (void_f_obj) imprime_aresta);
  printf("\n");
  printf("\nEstrutura:\n");
  */
  printf (" ");
  imprime_lista(arestas(G), (void_f_obj) imprime_estrutura_aresta);
}

// imprime o vertice v
void imprime_vertice(vertice v) {
  printf("(id:%d, rotulo:%s, grau_entrada:%d, fronteira_entrada:{ ", 
  vertice_id(v), vertice_rotulo(v), grau_entrada(v));

  imprime_lista(fronteira_entrada(v), (void_f_obj) imprime_aresta);
  printf("}, grau_saida:%d, fronteira_saida:{ ", grau_saida(v));
  imprime_lista(fronteira_saida(v), (void_f_obj) imprime_aresta);
  printf("})");
}

// imprime a aresta e
void imprime_aresta(aresta e) {
  int u_id = vertice_id(vertice_u(e));
  int v_id = vertice_id(vertice_v(e));
  printf("(id:%d {%d,%d})", aresta_id(e), u_id, v_id);
}

// imprime aresta e no formato de entrada para
// https://graphonline.ru/en/create_graph_by_edge_list
void imprime_estrutura_aresta(aresta e) {
  char *u_rot = vertice_rotulo(vertice_u(e));
  char *v_rot = vertice_rotulo(vertice_v(e));
  int u_id = vertice_id(vertice_u(e));
  int v_id = vertice_id(vertice_v(e));
  printf("%d:%s > %d:%s\n", u_id, u_rot, v_id, v_rot);
}
