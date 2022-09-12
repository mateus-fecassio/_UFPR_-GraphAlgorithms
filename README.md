# Trabalho de Implementação - Biblioteca de Análise de Grafos
O objetivo deste trabalho foi o de desenvolver uma biblioteca básica para análise de grafos. As seguintes funções foram implementadas:
- le_grafo : devolve o grafo lido da entrada padrão (formato dot);
- destroi_grafo : desaloca o grafo;
- escreve_grafo : escreve o grafo na saída padrão em formato dot;
- n_vertices : devolve o número de vértices de grafo;
- n_arestas : devolve o número de arestas do grafo;
- grau : devolve o grau de um vértice em um grafo;
- grau_maximo : devolve o grau máximo do grafo;
- grau_minimo : devolve o grau mínimo do grafo;
- grau_medio : devolve o grau médio do grafo;
- regular : verifica se o grafo é regular;
- completo : verifica se o grafo é completo;
- conexo : verifica se o grafo é conexo;
- bipartido : verifica se o grafo é bipartido;
- triangulos : devolve o número de triângulos (subgrafos completos de 3 vértices) em um grafo;
- matriz_adjacencia : devolve uma matriz de adjacência do grafo;
- complemento : devolve o grafo complementar a um outro grafo;
- decompoe : acrescenta à lista de subgrafos de g cada um de seus componentes fortes. Essa função foi implementada baseando-se no Algoritmo de Kosaraju. É importante ressaltar que a representação gráfica do grafo resultante não considera repetição das arestas que estão em algum subgrafo de g.

---

## Dependências
Para a representação de grafos na entrada e saída ao longo da deste trabalho, foi utilizado a linguagem de descrição de grafos .dot que é implementada pelo pacote de software [GraphViz](http://www.graphviz.org/).

A biblioteca cgraph implementa (entre outras coisas) uma estrutura de dados para a manipulação de grafos e um interpretador ("parser") da linguagem dot.

O pacote GraphViz é distribuido livremente para diversas plataformas.

Em particular, nas distribuições de GNU/Linux baseadas na distribuição Debian, basta instalar o pacote libgraphviz-dev. Recomenda-se também instalar os pacotes graphviz (utilitários, especialmente para desenhar grafos) e graphviz-doc (documentação adicional).

---

## Obsevações Complementares
Ao longo do desenvolvimento deste trabalho, algumas funções foram desenvolvidas com o intuito de compor as principais funções que deveriam ser implementadas. São elas:

- aloca_matriz : devolve uma matriz quadrada de inteiros;
- conferencia : imprime, se preciso, o conjunto dos vértices seguido da matriz de adjacência;
- multiply : faz a multiplicação entre duas matries (A, B) e armazena o resultado em C. Essa função foi necessária para calcular a matriz_adjacencia<sup>3</sup> para o cáculo da quantidade de triângulos em um grafo;
- coloreGrafo : função para colorir o grafo com apenas duas cores. Foi necessária para verificar se um determinado grafo é bipartido ou não;
- copy_graph : copia um determinado grafo para um outro;
- dfs : implementa o Depth First Search, utiliado para verificar se, a partir de um vértice, é possível atingir todos os outros vértices e determinar, assim, se um determinado grafo é conexo;
- buscaProfundidade : esse algoritmo faz uma busca em profundidade no grafo dado, retornando o inverso do índice de pós-ordem que é utilizado em uma das etapas do Algoritmo de Kosaraju. Aqui foi considerado que o inverso de uma pós-ordem em G é equivalente a uma pós-ordem em Gt, onde Gt é o grafo transposto a G;
- profundidade : versão recursiva que é chamada pela função buscaProfundidade;
- decompor : versão recursiva que é utilizada na chamada da função decompoe.

---

## AUTOR
- Mateus Felipe de Cássio Ferreira (GRR20176123).

### DISCIPLINA: CI165 - Algoritmos e Teoria dos Grafos
- Orientador: Renato do Carmo