# Trabalho de Implementação 2 - Biblioteca de Análise de Grafos
O objetivo deste trabalho foi o de complementar o trabalho anterior sobre uma biblioteca básica para análise de grafos com a função para detectar os componentes fortes de um grafo direcionado.
A seguinte função foi implementada:
- decompoe : acrescenta à lista de subgrafos de g cada um de seus componentes fortes.


## Dependências
Para a representação de grafos na entrada e saída ao longo da deste trabalho, foi utilizado a linguagem de descrição de grafos .dot que é implementada pelo pacote de software [GraphViz](http://www.graphviz.org/).

A biblioteca cgraph implementa (entre outras coisas) uma estrutura de dados para a manipulação de grafos e um interpretador ("parser") da linguagem dot.

O pacote GraphViz é distribuido livremente para diversas plataformas.

Em particular, nas distribuições de GNU/Linux baseadas na distribuição Debian, basta instalar o pacote libgraphviz-dev. Recomenda-se também instalar os pacotes graphviz (utilitários, especialmente para desenhar grafos) e graphviz-doc (documentação adicional).


## Obsevações Complementares
Ao longo do desenvolvimento deste trabalho, algumas funções foram desenvolvidas com o intuito de compor as principais funções que deveriam ser implementadas. São elas:


## AUTOR
- Mateus Felipe de Cássio Ferreira (GRR20176123).

### DISCIPLINA: CI165 - Algoritmos e Teoria dos Grafos
- Orientador: Renato do Carmo