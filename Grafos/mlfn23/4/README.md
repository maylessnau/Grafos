
# Modificações Realizadas
- Incluídos os campos:
  - `peso` na struct `t_aresta`, para representar o peso de cada aresta.
  - `grau` na struct `t_vertice`, para representar o grau de cada vértice.
  
- Removida a função `grau`, sendo substituída por um método `grau`, que 
  realiza o retorno do grau diretamente via encapsulamento.

- Criada uma nova função `atualiza_peso` que é responsável por atualizar o 
  peso das arestas, tanto em operações de inserção quanto de remoção.

# Limitações
- A lógica não permite escolher se o grafo vai ser ou não ponderado, ele 
  sempre é feito da mesma forma, as arestas com peso da soma dos graus de suas 
  pontas.

- Também não é possível "escolher" o peso de cada aresta sem alterá-lo 
  manualmente.
