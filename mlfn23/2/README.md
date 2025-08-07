# Modificações Realizadas
- Adicionado o campo `tipo` nas structs `t_aresta` e `t_vertice` para 
  diferenciar arestas e vértices.
- Definidos os macros `ARESTA` e `VERTICE` com o comando `#define` para 
  facilitar a identificação do tipo.
- Alteradas as funções de impressão apenas para formatação ficar mais limpa.

# Limitações
- As funções `f_chave` e `imprime` ainda podem ser melhoradas para 
  manipular cenários mais complexos com grandes quantidades de vértices e com 
  outras especificações, como por exemplo cor.
- As funções no geral servem para manipulação de grafos simples, outros tipos
  de grafo (hipergrafos, multigrafos, etc.) precisariam de alterações na lógica
  principal do programa para serem representados' adequadamente.


