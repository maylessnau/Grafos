/*******************************************
 * Implementação de biblioteca para grafos.
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#ifndef _GRAFO_
#define _GRAFO_

#include "lista.h"
#include <stdio.h>
#include <stdlib.h>

//defines para diferenciar os tipos de obj
#define VERTICE 0
#define ARESTA 1

typedef struct t_vertice *vertice;
typedef struct t_aresta *aresta;
typedef struct t_grafo *grafo;

typedef struct t_vertice {
	int id;
	lista fronteira;
	//guarda o grau do vertice
	int grau;
	//define se eh uma aresta ou um vertice
	int tipo;
} t_vertice;

typedef struct t_aresta {
	int id;
	vertice u, v;
	//alteração para o grafo ser ponderado
	int peso;	
	//define se eh uma aresta ou um vertice
	int tipo;		
} t_aresta;

typedef struct t_grafo {
  lista vertices;
  lista arestas;
} t_grafo ;

//---------------------------------------------------------
// getters:

int vertice_id(vertice v);
int grau(vertice v);
lista fronteira(vertice v);
int aresta_id(aresta e);
int aresta_peso(aresta e);
vertice vertice_u(aresta e);
vertice vertice_v(aresta e);
lista vertices(grafo G);
lista arestas(grafo G);

//---------------------------------------------------------
// funcoes para manipular as listas

//devolve a chave do objeto c
int f_chave (obj c);

//imprime o objeto c
void imprime (obj c);

//---------------------------------------------------------
// funcoes para construcao/desconstrucao do grafo:

// cria grafo vazio e o retorna
grafo cria_grafo();

// destroi grafo G (desaloca toda a memoria)
void destroi_grafo(grafo G);

// cria novo vertice com id <id> e adiciona ao grafo G
void adiciona_vertice(int id, grafo G);

// remove vertice com id <id> do grafo G e o destroi
// [deve remover e destruir tambem as arestas incidentes]
void remove_vertice(int id, grafo G);

//atualiza o peso das arestas na fronteira de v
void atualiza_peso(vertice v);

// cria aresta com id <id> incidente a vertices com
// ids <u_id> e <v_id> e adiciona ao grafo G
void adiciona_aresta(int id, int u_id, int v_id, grafo G);

// remove aresta com id <id> do grafo G e a destroi
void remove_aresta(int id, grafo G);

//---------------------------------------------------------
// funcoes para operacoes com o grafo pronto:

// imprime o grafo G
void imprime_grafo(grafo G);

// imprime o vertice v
void imprime_vertice(vertice v);

// imprime a aresta e
void imprime_aresta(aresta e);

#endif
