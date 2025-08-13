/*******************************************
 * Biblioteca para manipulação de redes
 * metabólicas.
 *
 * Algoritmos em Grafos e Otimização
 * Departamento de Informática - UFPR
 * prof. Guilherme Derenievicz
 *******************************************/

#include "grafo.h"
#include "rede_metabolica.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 50
#define MAX_LINE_LENGTH 256

// Cria grafo G e lê a rede metabólica do arquivo apontado por <f_met>,
// adicionando em G as reações, enzimas e metabólitos, com as respectivas conexões.
// Devolve o grafo G.
grafo le_rede_metabolica(FILE *f_met) {

  // inicialização das variáveis
  grafo G = cria_grafo(1);
  int id_vert = 1, id_aresta = 1;
  int id_reacao = 1, id_metabolito_entrada, id_metabolito_saida, id_enzima;
  vertice v;
  char line[MAX_LINE_LENGTH];

  // enquanto há linhas para ler do arquivo
  while (fgets(line, sizeof(line), f_met)) {

 	// encerra ao ler FIM
	if (strncmp(line, "FIM", 3) == 0) break;
    
	char reacao[MAX_NAME_LENGTH];
    char metabolito_entrada[MAX_NAME_LENGTH];
    char enzima[MAX_NAME_LENGTH];
    char metabolito_saida[MAX_NAME_LENGTH];

    // le a reação
    char *token = strtok(line, " ");
    strcpy(reacao, token);

    // adiciona a reação como vértice
    adiciona_vertice(id_vert, reacao, REACAO, G);
    id_reacao = id_vert;
    id_vert++;

    // processar metabólitos de entrada e enzimas
    while ((token = strtok(NULL, " ")) && strcmp(token, "=>") != 0) {

	  if (strcmp(token, "+") == 0) continue;

      // caso encontre um _ quer dizer que está lendo um enzima
      if (token[0] == '_') { 

      	strcpy(enzima, token);
		// garante que a enzima ainda não tenha sido adicionada
        v = busca_chave_str(enzima, vertices(G), (str_f_obj) vertice_rotulo);
        if (!v) {  // se não existe, cria o vértice da enzima
          adiciona_vertice(id_vert, enzima, ENZIMA, G);
          id_enzima = id_vert;
          id_vert++;
        } else {
          id_enzima = vertice_id(v);
        }
        // adicionar aresta entre a enzima e a reação
        adiciona_aresta(id_aresta++, id_enzima, id_reacao, G);

	  } else {  // não é uma enzima, então é metabólito de entrada

        strcpy(metabolito_entrada, token);
		// garante que o metabólito ainda não exista
        v = busca_chave_str(metabolito_entrada, vertices(G), (str_f_obj)vertice_rotulo);
        if (!v) {  // se não existe, cria o vértice do metabólito de entrada
          adiciona_vertice(id_vert, metabolito_entrada, METABOLITO, G);
          id_metabolito_entrada = id_vert;
          id_vert++;
       	} else {
          id_metabolito_entrada = vertice_id(v);
        }
        // adicionar aresta entre metabólito de entrada e reação
          adiciona_aresta(id_aresta++, id_metabolito_entrada, id_reacao, G);
      }
    }

    // processa metabólitos de saída
    while ((token = strtok(NULL, " ")) && strcmp(token, ".") != 0) {

	  // se encontrou um . é o fim da linha
      if (strncmp(token, ".", 1) == 0) break;
      if (strcmp(token, "+") == 0) continue;

      strcpy(metabolito_saida, token);

	  // garante que o metabólito ainda não exista
      v = busca_chave_str(metabolito_saida, vertices(G), (str_f_obj)vertice_rotulo);
      if (!v) {  // se não existe, cria o vértice do metabólito de saída
        adiciona_vertice(id_vert, metabolito_saida, METABOLITO, G);
        id_metabolito_saida = id_vert;
        id_vert++;
      } else {
        id_metabolito_saida = vertice_id(v);
      }
      // adiciona aresta entre a reação e o metabólito de saída
      adiciona_aresta(id_aresta++, id_reacao, id_metabolito_saida, G);
    }
  }
  return G;
}

// Cria lista L e lê da entrada padrão os substratos iniciais, adicionando
// em L os vértices que representam os substratos.
// Devolve a lista de vértices L.
lista le_substratos(grafo G) {

  lista L = cria_lista();
  char substrato[4];
  scanf ("%s", substrato);

  // enquanto não achou FIM
  while (strcmp (substrato, "FIM") != 0) {
	// cria um ponteiro novo para cada substrato para não sobrescrver
    char *novo_substrato = malloc(strlen(substrato) + 1);
    if (novo_substrato == NULL) {
      fprintf(stderr, "Erro ao alocar memória\n");
      return NULL;
    }
    strcpy(novo_substrato, substrato); 
	// adiciona o substrato lido na lista
    empilha (novo_substrato, L);
  	scanf ("%s", substrato);
  }

  return L;
}

// Função auxiliar que adiciona na rede metabólica uma reação falsa que gera
// todos os substratos iniciais (dado pela lista de vértices <substratos>).
// Deve adicionar um novo vértice com rótulo "SF" representando o substrato
// falso inicial e um novo vértice com rótulo "RF" representando a reação falsa.
// Deve também adicionar as arestas necessárias.
// ATENÇÃO: os rótulos "SF" e "RF" são usados no método imprime_reacoes_minimas().
void adiciona_reacao_falsa(lista substratos, grafo G) {

  //adiciona vertices falsos  
  adiciona_vertice (-1, "SF", METABOLITO, G);
  adiciona_vertice (0, "RF", REACAO, G);

  // adiciona as arestas novas sem utilizar id's existentes
  int aresta_id = tamanho(arestas(G));

  //adiciona aresta entre SF e RF
  adiciona_aresta(aresta_id, -1, 0, G);
  aresta_id++;

  int v_id;

  // faz um laço percorrendo a lista de substratos e adiciona as arestas
  while (!vazio(substratos)) {
	char *sub = desempilha(substratos);
	// procura o id do substrato desempilhado na lista de vertices
	vertice substrato = busca_chave_str(sub, vertices(G), (str_f_obj)vertice_rotulo);
	if (!substrato) {
	  printf("O substrato %s não existe na rede metabólica fornecida.\n", sub);
	  free(substratos);
	  substratos = NULL;
	  free (sub);
	  sub = NULL;
	  destroi_grafo(G);
	  exit(1);
	}
	v_id = vertice_id(substrato);
    // adiciona aresta entre a reação falsa e o substrato da lista
	adiciona_aresta(aresta_id, 0, v_id, G);
	aresta_id++;
	// libera a memória alocada para o substrato da lista
	free (sub);
	sub = NULL;
  }
}

// função auxiliar que calcula o custo de uma reação 
int custo_reacao (vertice reacao) {
  aresta a;
  int custo = 0;
  //percorre a fronteira de entrada da reação procurando enzimas
  no aux = primeiro_no(fronteira_entrada(reacao));
  while (aux) {
	a = conteudo(aux);
	//se o vizinho de entrada de v for uma enzima
	if (vertice_particao(vertice_u(a)) == ENZIMA)
	  custo++; //incrementa o custo da reação
	aux = proximo(aux);	
  }
  return custo;
}

// Função auxiliar que inicializa os custos e pais dos vértices do grafo G para
// iniciar busca em largura. O custo de uma reação é a quantidade de enzimas que
// a cataliza.
// Devolve uma lista de vértices para ser a Fila inicial do algoritmo de busca.
lista inicializa_custos(grafo G) {

  lista F = cria_lista();
  no n = primeiro_no(vertices(G));
  vertice v;

  while (n) {
	v = conteudo(n);
	//inicializa só os metabólitos (reações e enzimas não tem custo)
	if (vertice_particao(v) == METABOLITO) {
	  v->custo = INT_MAX;
	  // empilha apenas os metabólitos na lista
	  empilha (v, F);
	}
	//se o vertice for uma reação, inicializa o custo com a quantidade de enzimas
	else if (vertice_particao(v) == REACAO) {
	  v->custo = custo_reacao(v);
    }
	// inicializa os pais e estado para todos
	v->pai = NULL;
	v->estado = ABERTO;
	n = proximo(n);
  }

  return F;
}

// função auxiliar que verifica se os vizinhos de entrada da reação já foram
// fechados (tem um custo certo)
// retorna 1 se sim e 0 se não
int entradas_fechadas (vertice reacao, vertice metabolito_atual) {

  vertice metabolito;
  // percorre a fronteira de entrada da reação
  for (no n = primeiro_no((fronteira_entrada(reacao))); n; n = proximo(n)) {
	// pega o vértice de entrada da reação (vértice u (u -> v))
	metabolito = vertice_u(conteudo(n));
	if (vertice_particao(metabolito) != ENZIMA) {
      // se estiver aberto ainda não podemos calcular o valor da reação
	  if (estado(metabolito) == ABERTO) 
	    return 0;
      // se o metabólito estiver processado (custo ainda indefinido)
  	  if (estado(metabolito) == PROCESSADO) {
	    // desconsidera o metabólito atual (está sendo processado agora)
	    if (vertice_id(metabolito) !=	vertice_id(metabolito_atual)) return 0;  	
	  }
	}
  }
  return 1;
}

// Algoritmo variante de Dijkstra que encontra o conjunto de reações de custo
// mínimo (número de enzimas) que produz todos os metabólitos da rede, considerando
// como substratos iniciais os metabólitos representados pelos vértices na lista
// substratos.
// Ao final do algoritmo, cada metabólito deve ter como pai (na estrutura vértice->pai)
// a reação "ótima" que o produz.
void processa(lista substratos, grafo G) {
  
  // adiciona uma reação falsa para iniciar a busca
  adiciona_reacao_falsa(substratos, G);
  
  // inicializa custos, pais e fila inicial da busca F
  lista F = inicializa_custos(G);
 
  // inicializa o metabólito falso com custo 0 para ser o primeiro
  vertice s = busca_chave_str ("SF", F, (str_f_obj) vertice_rotulo);
  s->custo = 0;
  s->estado = PROCESSADO;

  vertice metabolito, vizinho, reacao;
  aresta aresta_meta, aresta_reacao;

  // variante do Algoritmo de Dijkstra para resolver o problema
  while (!vazio(F)) {
    metabolito = remove_min (F, (int_f_obj) custo);
  	//percorre a fronteira de saida do metabolito (reações)
 	no aux_meta = primeiro_no(fronteira_saida(metabolito));
  	while (aux_meta) {
	  aresta_meta = conteudo(aux_meta);
	  // pega o vizinho de saída do metabolito, que é sempre uma reação
	  reacao = vertice_v(aresta_meta);
	  // só processa os metabólitos de saída da reação, se os metabólitos de 
	  // entrada já tiverem custo definido (estado fechado)
	  if (entradas_fechadas(reacao, metabolito)) {
	    //percorre a fronteira de saída da reação (metabólitos gerados por ela)
	    no aux_reacao = primeiro_no(fronteira_saida(reacao));
	    while (aux_reacao) {
		  aresta_reacao = conteudo(aux_reacao);
		  // pega um metabólito gerado por essa reação
		  vizinho = vertice_v(aresta_reacao);
		  if (estado(vizinho) == PROCESSADO) {
		    // o custo de um metabólito é a soma do custo do metabólito que entra 
		    // na reação + o custo da reação
		    if (custo(metabolito) + custo(reacao) < custo(vizinho)) {
			  vizinho->pai = reacao;
			  vizinho->custo = custo(metabolito) + custo(reacao);
		    }
		  }
		  if (estado(vizinho) == ABERTO) {
		    vizinho->pai = reacao;
		    vizinho->custo = custo(metabolito) + custo(reacao);
		    vizinho->estado = PROCESSADO;
		  }
		  // prossegue na fronteira da reação
		  aux_reacao = proximo(aux_reacao);
	    }
	  }
	  // prossegue na fronteira do metabólito que estamos olhando na iteração
	  aux_meta = proximo(aux_meta);	
    }
	// acabaram as reações geradas por esse metabólito
	metabolito->estado = FECHADO;
  }

  free(F);
  F = NULL;
}

// Imprime resultados com base nos pais dos vértices (na estrutura vértice->pai),
// calculados pelo método processa().
void imprime_reacoes_minimas(grafo G) {
 
  printf ("\n"); 
  // Para cada metabólito, imprime as reações "ótimas"
  for (no n = primeiro_no(vertices(G)); n; n = proximo(n)) {
    vertice v = conteudo(n);
	//printf ("vertice %s e pai %s\n", vertice_rotulo(v), vertice_rotulo(pai(v)));
    if (vertice_particao(v) == METABOLITO && pai(v)) {
      printf("%s: ", vertice_rotulo(v));
      
      // cria lista de reações necessárias para sua produção
      lista R = cria_lista();
      empilha(pai(v), R);
      
      // seta todas as reações como ABERTOS, para não repetir
      for (no p = primeiro_no(vertices(G)); p; p = proximo(p)) {
        vertice w = conteudo(p);
        if (vertice_particao(w) == REACAO)
          w->estado = ABERTO;
      }
      
      // Enquanto tiver reações ainda não processadas, imprime
      while (!vazio(R)) {
        vertice w = desempilha(R);
        // não inclui a reação falsa
        if (estado(w) == ABERTO && strcmp(vertice_rotulo(w), "RF")) { 
          printf("%s ", vertice_rotulo(w));
          w->estado = FECHADO;
          
          // coloca na lista as reações antecessoras
          for (no p = primeiro_no(fronteira_entrada(w)); p; p = proximo(p)) {
            aresta e = conteudo(p);
            vertice u = vertice_u(e);
            if (vertice_particao(u) == METABOLITO && pai(u))
              empilha(pai(u), R);
          }
        }
      }
      printf("\n");
      free(R);
    }
  }
}
