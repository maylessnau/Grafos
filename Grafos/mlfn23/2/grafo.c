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
};
lista fronteira(vertice v) {
  return v->fronteira;
};
int aresta_id(aresta e) {
  return e->id;
};
vertice vertice_u(aresta e) {
  return e->u;
};
vertice vertice_v(aresta e) {
  return e->v;
};
lista vertices(grafo G) {
  return G->vertices;
};
lista arestas(grafo G) {
  return G->arestas;
};

//--------------------------------------------------------
//funções para manipular as listas

// devolve a chave do objeto c
int f_chave (obj c) {
  //retorna -1 caso o objeto seja invalido
  if (!c) return -1;

  //acessa o tipo do objeto (campo na struct)
  int* tipo = (int*) c;

  if (*tipo == VERTICE) 
	return vertice_id ((vertice) c); 
  return aresta_id ((aresta) c);
}

//imprime o objeto c
void imprime(obj c) {
  int* tipo = (int*) c;
  if (*tipo == VERTICE) 
	imprime_vertice ((vertice)c);
  else
	imprime_aresta ((aresta)c);	
}

//---------------------------------------------------------
// funcoes para construcao/desconstrucao do grafo:

// cria grafo vazio e o retorna
grafo cria_grafo() {
  grafo G = (grafo) malloc(sizeof(t_grafo));
  if (!G)
    exit(_ERRO_MALLOC_);
  G->vertices = cria_lista();
  G->arestas = cria_lista();
  return G;
}

// destroi grafo G (desaloca toda a memoria)
void destroi_grafo(grafo G) {

  // verifica se existem vertices validos
  if (vazio (vertices(G))) {
	free (G->vertices);
    (G->vertices) = NULL;
    free (G->arestas);
    (G->arestas) = NULL;
    free (G);
	G = NULL;
	return;
  }
  
  no prox;
  no aux = primeiro_no (vertices(G));
  
  // destroi a lista de vertices (remove todos eles)
  while (aux != NULL) {
	prox = proximo(aux);
	remove_vertice (f_chave (conteudo(aux)), G);
	aux = prox;	
  }

  free (G->vertices);
  G->vertices = NULL;
  free (G->arestas);
  (G->arestas) = NULL;

  // destroi grafo
  free(G);
  G = NULL;
}

// cria novo vertice com id <id> e adiciona ao grafo G
void adiciona_vertice(int id, grafo G) {

  vertice v = (vertice) malloc (sizeof(t_vertice));
  if (!v) 
	exit(_ERRO_MALLOC_);

  v->id = id;
  v->fronteira = cria_lista();
  v->tipo = VERTICE;
  empilha(v, vertices(G));
}

// remove vertice com id <id> do grafo G e o destroi
// [deve remover e destruir tambem as arestas incidentes]
void remove_vertice(int id, grafo G) {
 
  vertice v;
  v = (vertice) remove_chave (id, vertices(G), (int_f_obj) f_chave);

  // se não encontrou o vertice
  if (!v) return;

  // verifica se existem arestas validas na fronteira
  if (!(vazio (fronteira(v)))) {
	no prox;
 	no aux = primeiro_no (fronteira(v));
  
	// destroi a fronteira
	while (aux != NULL) {
	  prox = proximo(aux);
	  remove_aresta (f_chave (conteudo(aux)),G);
	  aux = prox;
 	}
  }
  free (v->fronteira);
  v->fronteira = NULL;

  free(v);
  v = NULL;
}

// cria aresta com id <id> incidente a vertices com
// ids <u_id> e <v_id> e adiciona ao grafo G
void adiciona_aresta(int id, int u_id, int v_id, grafo G) {

  aresta a = (aresta) malloc (sizeof (t_aresta));
  if (!a)
	exit(_ERRO_MALLOC_);
  
  a->id = id;

  //insere a aresta na fronteira do vertice u
  vertice u = (vertice) busca_chave (u_id, vertices(G), (int_f_obj) f_chave);
  a->u = u;
  empilha(a, fronteira(u));

  //insere a aresta na fronteira do vertice v
  vertice v = (vertice) busca_chave (v_id, vertices(G), (int_f_obj) f_chave);
  a->v = v;
  empilha(a, fronteira(v));

  a->tipo = ARESTA;

  empilha(a, arestas(G));
}

// remove aresta com id <id> do grafo G e a destroi
void remove_aresta (int id, grafo G) {
 
  aresta a;
  a = (aresta) remove_chave (id, arestas(G), (int_f_obj) f_chave);
  if(!a) return;
 
  //remove a aresta da fronteira do vertice u
  remove_chave (id, fronteira(vertice_u(a)), (int_f_obj) f_chave);
  //remove a aresta da fronteira do vertice v
  remove_chave (id, fronteira(vertice_v(a)), (int_f_obj) f_chave);

  free (a);
  a = NULL;
}

//---------------------------------------------------------
// funcoes para operacoes com o grafo pronto:

// calcula e devolve o grau do vertice v
int grau(vertice v) {
  int d_v = 0;
  for (no n = primeiro_no(fronteira(v)); n; n = proximo(n))
    ++d_v;
  return d_v;
}

// imprime o grafo G
void imprime_grafo(grafo G) {
  printf("\nVertices: <id> - [grau]( <fronteira> )");
  printf("\nVertices: \n");
  printf(" ");
  imprime_lista(vertices(G), (void_f_obj) imprime_vertice);
  printf("\nArestas: <id>:{u,v}");
  printf("\nArestas: ");
  imprime_lista(arestas(G), (void_f_obj) imprime_aresta);
  printf("\n");
}

// imprime o vertice v
void imprime_vertice(vertice v) {
  printf("%d - [%d]( ", vertice_id(v), grau(v));
  imprime_lista(fronteira(v), (void_f_obj) imprime_aresta);
  printf(")\n");
}

// imprime a aresta e
void imprime_aresta(aresta e) {
  int u_id = vertice_id(vertice_u(e));
  int v_id = vertice_id(vertice_v(e));
  printf("%d:{%d,%d}", aresta_id(e), u_id, v_id);
}
