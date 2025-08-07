#include "grafo.h"
#include <stdio.h>
#include <stdlib.h>

int devolve_chave (obj c) {
	return *(int*)c; 
}

void destroi_lista (lista l) {

	no aux;
	no prox;
	aux = primeiro_no(l);
	obj c;

	while (aux) {
		prox = proximo(aux);
		c = remove_chave ((*(int*)conteudo(aux)), l, (int_f_obj)devolve_chave);
		free(c);
		c = NULL;
		aux = prox;
	}

	free(l);
	l = NULL;
}

// lê um conjunto X de vértices e os empilha, retorna a pilha
lista le_conjunto (grafo G) {

	lista X = cria_lista();
	int v;

	printf ("Digite um conjunto de vértices X, terminado em 0: ");
	scanf ("%d", &v);

	while (v) {
		//aloca memoria para passar o inteiro para um obj (void *)
		int *id = (int*) malloc (sizeof(int));
		if (!id) 
			exit (_ERRO_MALLOC_);	
		*id = v;
		empilha (id, X);
		scanf("%d", &v);
	}

	return X;
}

//transforma o grafo G no grafo G[X]
void indutor_de_grafos (grafo G, lista X) {

	no i;
	no aux;
	no prox;

	//i itera pelo conjunto X de vertices
	i = primeiro_no (X);
	//aux itera pelos vertices de G
	aux = primeiro_no (vertices(G));

	// percorre todos os vertices de G, excluindo os que não fazem parte de X
	while (aux) {
		prox = proximo(aux);
		//busca o vertice de G atual no conjunto X
		while (i && f_chave(conteudo(aux)) != (*(int*)conteudo(i))) {
			i = proximo(i);	
		}
		//remove o vertice se não encontrou
		if (!i) {
			remove_vertice(f_chave(conteudo(aux)), G);
		}
		i = primeiro_no(X);
		aux = prox;
	}
}

int main () {
	
	//criando grafo G
	grafo G = cria_grafo();

	int n;
	printf("Digite a quantidade de vértices de G: ");
	scanf("%d", &n);

	for (int i = 1; i <= n; ++i)
		adiciona_vertice(i, G);

	int id = 1;
	int u, v;
	printf("Digite pares de vértices {u,v}, termine com 0 0:\n");
	scanf("%d %d", &u, &v);

	//termina quando digitar 0 0
	while (u && v) {
		adiciona_aresta(id, u, v, G);
		++id;
		scanf("%d %d", &u, &v);		
	}
	
	lista X = le_conjunto(G);

	printf ("\nGrafo G:\n");
	imprime_grafo(G);
	printf ("\n");

	indutor_de_grafos(G, X);
	
	printf("Grafo G[X]:\n");
	imprime_grafo(G);
	printf ("\n");
	
	destroi_lista(X);
	destroi_grafo(G);

	return 0;
}
