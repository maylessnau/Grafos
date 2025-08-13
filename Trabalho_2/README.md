# Manipulação e Análise de Redes Metabólicas

## Objetivo do Trabalho

Este projeto visa a manipulação e análise de redes metabólicas, que são 
representadas por grafos direcionados. As redes metabólicas, compostas por 
metabólitos, enzimas e reações, são modeladas em um grafo onde as direções dos 
arcos indicam interações específicas entre esses elementos. Este programa lê 
uma rede metabólica de um arquivo e permite análise das reações e 
enzimas necessárias para gerar metabólitos com base em substratos iniciais.

## Descrição das Funcionalidades

O programa realiza as seguintes tarefas:

1. **Leitura de Redes Metabólicas**: Carrega a rede metabólica de um arquivo 
`.met`, identificando reações, substratos e enzimas.
2. **Construção de Grafo 3-Partido**: Cria um grafo onde os vértices representam 
metabólitos, reações e enzimas, com arcos direcionais de acordo com a relação 
entre esses elementos.
3. **Análise de Reações Necessárias**: A partir de substratos iniciais 
informados pelo usuário, o programa identifica as reações e enzimas necessárias 
para gerar cada metabólito, com a menor quantidade possível de enzimas por meio 
de uma adaptação do Algoritmo de Dijkstra.
4. **Impressão dos Resultados**: Exibe o conjunto de reações necessárias para 
cada metabólito gerado a partir dos substratos iniciais.

## Compilação e Execução

Para compilar e executar o programa:

1. Compile o programa com o `Makefile`:
   ```bash
   make
   ``` 
2. Execute o programa com um arquivo de rede e uma entrada de substratos: 
	```bash
    ./analise rede.met < substratos.in > resultado.out
	``` 
## Estrutura do Grafo e Algoritmo

### Adaptação do Algoritmo de Dijkstra

Para calcular o caminho mínimo (que utiliza o menor número de enzimas) para
geração de metabólitos, foi feita uma adaptação do Algoritmo de Dijkstra que 
considera a natureza específica das redes metabólicas. Nesse caso:

- **Fronteira da Fronteira**: Ao calcular o caminho, o algoritmo ignora as 
reações como "vizinhos diretos" dos metabólitos e as considera apenas como 
representações dos custos (enzimas) associados às transições. Assim, o custo de 
uma reação (a quantidade de enzimas que ela exige) é utilizado como peso da 
"aresta" que conecta um metabólito ao próximo. Dessa forma, o algoritmo explora 
a "fronteira da fronteira" do metabólito — ou seja, ele atravessa uma reação 
e considera diretamente o metabólito de destino.

- **Inicialização de Custos**: Durante a inicialização, os custos das reações 
são calculados e atribuídos como pesos nas transições entre os metabólitos. 
Esse custo representa o número de enzimas necessárias para que uma reação 
ocorra e produza o metabólito de destino.

Essa abordagem permite otimizar a geração dos produtos da rede metabólica com o 
menor número possível de enzimas, simulando o "peso das arestas" como custo das 
reações.

### Estrutura do Grafo 3-Partido

O grafo construído é dividido em três tipos de vértices:

- **Metabólitos (M)**: Representam as substâncias que servem de substrato ou 
produto em reações.
- **Reações (R)**: Representam processos que transformam substratos em produtos. 
As reações servem como nós intermediários, apenas para representar os custos 
das transições entre metabólitos.
- **Enzimas (E)**: Necessárias para catalisar reações específicas, cada enzima 
associada a uma reação contribui ao custo total dessa reação.

### Mudanças nas Bibliotecas

1. Para implementar essa lógica, adaptamos as bibliotecas de grafos do Trabalho 1, 
unindo as duas bibliotecas para extrair o que havia de melhor. As principais 
mudanças incluem:

- **adiciona_vertice**: Adaptamos as últimas versões para que os novos campos 
da estrutura do vértice fossem inicializados.

- **remove_vertice**: Modificado para percorrer as duas fronteiras do vértice — 
a de entrada e a de saída — removendo as arestas ligadas a esse vértice.

- **adiciona_aresta**: Alterado para empilhar a aresta na fronteira de entrada 
do vértice `v` e na fronteira de saída do vértice `u`.

- **remove_aresta**: Atualizado para também remover a aresta da fronteira de 
entrada do vértice `v` e da fronteira de saída do vértice `u`.

2. Na biblioteca `lista.h` foi adicionada uma função `tamanho` que retorna o 
tamanho da lista passada pelo parâmetro, ela foi usada para garantir que nenhuma
aresta recebesse um id já existente na função `adiciona_reacao_falsa`.

## Arquivos de Entrada

### Arquivo `.met`

Arquivo que define a rede metabólica. Cada linha representa uma reação e 
**PRECISA** seguir o formato:

```plaintext
R1 M1 + _E1 => M2 .
```
No exemplo acima:
    `R1` é a reação
    `M1` é o metabólito inicial
    `_E1` é a enzima necessária
    `M2` é o metabólito produzido

O arquivo termina com a linha FIM, indicando o fim da rede.

### Arquivo `substratos.in`

```plaintext
M2 M3 FIM
```
Lista de substratos iniciais disponíveis para o cálculo de reações. **DEVE** 
terminar com FIM e ser separado por espaços.

## Estrutura de Arquivos

- **grafo.c** e **grafo.h**: Implementam a estrutura do grafo, incluindo a 
adaptação para direção e cálculo de custos.
- **analise.c**: Código principal que executa a leitura da rede, a construção 
do grafo e a análise dos caminhos mínimos.
- **rede_metabolica.c** e **rede_metabolica.h**: Estruturas específicas para a 
modelagem de redes metabólicas.
- **lista.c** e **lista.h**: Estruturas auxiliares de listas para manipulação 
dos vértices.

## Limitações do Programa

Uma limitação conhecida do programa ocorre ao calcular caminhos mínimos com 
substratos iniciais que não são suficientes para gerar todos os metabólitos da 
rede. 

No algoritmo de Dijkstra adaptado que usamos, a lista de fronteira `F` é 
inicializada com todos os metabólitos do grafo. Isso significa que, ao final da 
execução, o programa calcula e exibe caminhos mínimos para todos eles, 
independentemente de serem alcançáveis ou não a partir dos substratos iniciais 
fornecidos. 

Esse comportamento resulta em uma atribuição de caminhos mínimos aos metabólitos 
"inalcançáveis", mesmo que eles não possam ser gerados com os substratos 
disponíveis. Em resumo, o programa não distingue entre caminhos válidos e 
inválidos para determinados metabólitos, o que pode levar à exibição de caminhos 
mínimos para vértices que, na prática, não são acessíveis.

## Autores

- Barbara Reis dos Santos `GRR20222538`
- Mayara Lessnau de Figueiredo Neves `GRR20235083`
