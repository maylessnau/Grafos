# Modificações Realizadas
- Mantidas todas as alterações do subdiretório anterior:
  - Inclusão dos campos `tipo` nas structs `t_aresta` e `t_vertice`.
  - Definições de macros para `ARESTA` e `VERTICE`.
  - Funções de impressão adaptadas.

- Inclusão de duas novas funções no arquivo `grafo.h` para uso delas na main:
  - `f_chave`: Função responsável por extrair as chaves de vértices e arestas.
  - `imprime`: Função para imprimir o conteudo dos objetos.

# Limitações
- A lógica principal de manipulação de grafos segue a mesma. Não foram feitas 
  alterações adicionais significativas em termos de performance ou otimização.
- Pode ser uma operação muito custosa em termos de tempo e memória a 
  transformação de G em G[X], sendo pouco eficiente para grafos muito grandes.
