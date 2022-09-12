# Trabalho de Implementação 2 - Biblioteca de Análise de Grafos
O objetivo deste trabalho foi o de complementar o trabalho anterior sobre uma biblioteca básica para análise de grafos com a função para detectar os componentes fortes de um grafo direcionado.
A seguinte função foi implementada:
- decompoe : acrescenta à lista de subgrafos de g cada um de seus componentes fortes. Essa função foi implementada baseando-se no Algoritmo de Kosaraju. É importante ressaltar que a saída do grafo resultante não considera repetição das arestas que estão em algum subgrafo de g. Para observar essa repetição de arestas, a linha 547 deve ser descomentada. Ainda, a informação de estado, índices de pré e pós ordem e componente estão sinalizadas nos atributos de cada um dos vértices.


## Dependências
Para a representação de grafos na entrada e saída ao longo da deste trabalho, foi utilizado a linguagem de descrição de grafos .dot que é implementada pelo pacote de software [GraphViz](http://www.graphviz.org/).

A biblioteca cgraph implementa (entre outras coisas) uma estrutura de dados para a manipulação de grafos e um interpretador ("parser") da linguagem dot.

O pacote GraphViz é distribuido livremente para diversas plataformas.

Em particular, nas distribuições de GNU/Linux baseadas na distribuição Debian, basta instalar o pacote libgraphviz-dev. Recomenda-se também instalar os pacotes graphviz (utilitários, especialmente para desenhar grafos) e graphviz-doc (documentação adicional).


## Obsevações Complementares
Ao longo do desenvolvimento deste trabalho, algumas funções foram desenvolvidas com o intuito de compor a principal função que deveria ser implementada. São elas:
- buscaProfundidade : esse algoritmo faz uma busca em profundidade no grafo dado, retornando o inverso do índice de pós-ordem que é utilizado em uma das etapas do Algoritmo de Kosaraju. Aqui foi considerado que o inverso de uma pós-ordem em G é equivalente a uma pós-ordem em Gt, onde Gt é o grafo transposto a G;
- profundidade : versão recursiva que é chamada pela função buscaProfundidade;
- decompor : versão recursiva que é utilizada na chamada da função decompoe.


## AUTOR
- Mateus Felipe de Cássio Ferreira (GRR20176123).

### DISCIPLINA: CI165 - Algoritmos e Teoria dos Grafos
- Orientador: Renato do Carmo