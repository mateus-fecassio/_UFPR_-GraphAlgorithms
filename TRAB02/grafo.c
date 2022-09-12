#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "grafo.h"

//------------------------------------------------------------------------------
// DECLARAÇÕES - FUNÇÕES AUXILIARES
int **aloca_matriz(int size);
void conferencia(grafo g, int seq);
void multiply(int size, int **A, int **B, int **C);
int coloreGrafo(int size, int **G, int *color, int pos, int c);
grafo copy_graph(grafo g, char *name, int edges);
void dfs(grafo g, vertice n, int *visited);

void profundidade(grafo g, vertice r, int *t, Agnode_t **order, int *index);
Agnode_t** buscaProfundidade(grafo g);
void decompor(grafo g, vertice r, int c);


// IMPLEMENTAÇÕES - FUNÇÕES AUXILIARES
int **aloca_matriz(int size) {
    int **matriz = (int**) malloc((size_t) size * sizeof(int*));

    for (int i=0; i < size; ++i) {
        matriz[i] = calloc((size_t) size, sizeof(int)); //aloca preenchendo com '0' 
    }
    return matriz;
} //FINALIZADO

void conferencia(grafo g, int seq) {
    int size = n_vertices(g);
    // print da sequencia de vertices
    if (seq){
        vertice v;
        for (v = agfstnode(g); v; v = agnxtnode(g,v)) {
            printf("name = %s\n", agnameof(v));
        }
    }
    
    int **matriz = matriz_adjacencia(g);
    // print da matriz
    for (int i=0; i < size; ++i){ 
        for (int j=0; j < size; ++j)
            printf("%d ", matriz[i][j]);
        printf("\n");
    }
} //FINALIZADO

void multiply(int size, int **A, int **B, int **C) {
    for (int i=0; i < size; ++i) {
        for (int j=0; j < size; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < size; k++)
                C[i][j] += A[i][k]*B[k][j];
        }
    }
} //FINALIZADO

int coloreGrafo(int size, int **G, int *color, int pos, int c) {
    if(color[pos] != -1 && color[pos] !=c)
        return 0;
         
    color[pos] = c;
    int ans = 1;
    for (int i=0; i < size; ++i) {
        if(G[pos][i]) {
            if (color[i] == -1)
                ans &= coloreGrafo(size,G,color,i,1-c);
                 
            if (color[i] !=-1 && color[i] != 1-c)
                return 0;
        }
        if (!ans)
            return 0;
    }
    return 1;
} //FINALIZADO

grafo copy_graph(grafo g, char *name, int edges) {
    Agdesc_t type;

    // verifica o tipo do grafo
    if (agisdirected(g)) {
        if (agisstrict(g))
            type = Agstrictdirected;
        else
            type = Agdirected;
    } else if (agisundirected(g)){
        if (agisstrict(g))
            type = Agstrictundirected;
        else
            type = Agundirected;
    }

    grafo comp;
    comp = agopen(name, type, NULL);

    // adiciona os vértices
    vertice v;
    for (v = agfstnode(g); v; v = agnxtnode(g,v)) {
        agnode(comp, agnameof(v), TRUE);
    }

    if (edges) {
        // adiciona as arestas
        vertice l_v, c_v, nd1, nd2;
        for (l_v = agfstnode(g); l_v; l_v = agnxtnode(g,l_v)) {
            for (c_v = l_v; c_v; c_v = agnxtnode(g,c_v)) {
                if (c_v != l_v) {
                    if ((agedge(g,l_v,c_v,NULL,FALSE)) || (agedge(g,c_v,l_v,NULL,FALSE)) ) {
                        nd1 = agnode(comp, agnameof(l_v), FALSE);
                        nd2 = agnode(comp, agnameof(c_v), FALSE);
                        agedge(comp,nd1,nd2,NULL,TRUE);
                }
                }
            }
        }
    }
    return comp;
} //FINALIZADO

void dfs(grafo g, vertice n, int *visited) {
    char type[10] = "color";
    char color[10] = "red";
    agset(n, type, color);
    (*visited)++;

    for (Agedge_t *ed = agfstedge(g, n); ed; ed = agnxtedge(g,ed,n)) {
        vertice neighbour = aghead(ed);
        char *v_color = agget(neighbour, type);
        if (strcmp(v_color, color)) //se esse vértice não foi visitado (red) (diferente de zero)
            dfs(g, neighbour, visited);
    }   
} //FINALIZADO

void profundidade(grafo g, vertice r, int *t, Agnode_t **order, int *index) {
    char temp[10];
    char state[10] = "state";
    char pre[10] = "pre";
    char pos[10] = "pos";

    char value[10] = "0";

    // r.pre <- ++t
    (*t)++;
    sprintf(temp, "%d", (*t));
    agset(r, pre, temp);
    temp[0] = '\0'; // limpa a string

    // r.state <- 1
    sprintf(temp, "%d", 1);
    agset(r, state, temp); 
    temp[0] = '\0'; // limpa a string


    // para cada v E V(G)
    vertice v;
    for (Agedge_t *ed = agfstout(g,r); ed; ed = agnxtout(g,ed)) {
        v = aghead(ed); // para cada v E vizinhança(r) , O -> X
        char *v_state = agget(v, state);

        if (!strcmp(v_state, value)) { //se v.estado = 0
            profundidade(g, v, t, order, index);
        }
    }

    // r.state <- 2
    sprintf(temp, "%d", 2);
    agset(r, state, temp); 
    temp[0] = '\0'; // limpa a string


    // r.pos <- ++t
    (*t)++;
    sprintf(temp, "%d", (*t));
    agset(r, pos, temp);
    temp[0] = '\0'; // limpa a string

    order[(*index)] = r;
    (*index)--;
} //FINALIZADO

Agnode_t** buscaProfundidade(grafo g) {
    char state[10] = "state";
    char pre[10] = "pre";
    char pos[10] = "pos";

    char value[10] = "0";

    vertice v;

    int index = n_vertices(g);
    Agnode_t **order = (Agnode_t **) malloc((size_t) index * sizeof(Agnode_t *));

    index --;
    
    // para cada v E V(G)
    agattr(g,AGNODE,state,value); // v.estado <- 0
    agattr(g,AGNODE,pre,value); // v.pre <- 0
    agattr(g,AGNODE,pos,value); // v.pos <- 0

    // para cada v E V(G)
    int t = 0;
    for (v = agfstnode(g); v; v = agnxtnode(g,v)) {
        char *v_state = agget(v, state);
        if (!strcmp(v_state, value)) { //se v.estado = 0
            profundidade(g, v, &t, order, &index);
        }
    }

    return order;
} //FINALIZADO

void decompor(grafo g, vertice r, int c) {
    char temp[10];
    char state[10] = "state";
    char comp[10] = "comp";

    char value[10] = "0";

    // r.state <- 1
    sprintf(temp, "%d", 1);
    agset(r, state, temp); 
    temp[0] = '\0'; // limpa a string

    // para cada v E vizinhanca(r)
    vertice v;
    for (Agedge_t *ed = agfstin(g,r); ed; ed = agnxtin(g,ed)) {
        v = agtail(ed); 
        char *v_state = agget(v, state);

        if (!strcmp(v_state, value)) { //se v.estado = 0
            decompor(g,v,c);
        }
    }

    // r.state <- 2
    sprintf(temp, "%d", 2);
    agset(r, state, temp); 
    temp[0] = '\0'; // limpa a string

    // r.comp <- c
    sprintf(temp, "%d", c);
    agset(r, comp, temp);
    temp[0] = '\0'; // limpa a string
} //FINALIZADO

//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
grafo le_grafo(void) {
    grafo g;

    g = (Agraph_t *) malloc(sizeof(Agraph_t));

    if (!g) {
        fprintf(stderr, "Não foi possível alocar espaço em memória para comportar esse grafo.");
        exit(-1);
    }

    g = agread(stdin, NULL);

    return g;
} //FINALIZADO

//------------------------------------------------------------------------------
void destroi_grafo(grafo g) {
    agclose(g);
} //FINALIZADO

//------------------------------------------------------------------------------
grafo escreve_grafo(grafo g) {
    if (g)
        agwrite(g, stdout);
    return g;
} //FINALIZADO

// -----------------------------------------------------------------------------
int n_vertices(grafo g) {
    return agnnodes(g);
} //FINALIZADO

// -----------------------------------------------------------------------------
int n_arestas(grafo g) {
    return agnedges(g);
} //FINALIZADO

// -----------------------------------------------------------------------------
int grau(vertice v, grafo g) {
    return agdegree(g,v,TRUE,TRUE);
} //FINALIZADO

// -----------------------------------------------------------------------------
int grau_maximo(grafo g)  {
    vertice n;
    int degree, max_degree = INT_MIN;
    
    for (n = agfstnode(g); n; n = agnxtnode(g,n)) {
        degree = grau(n,g);
        if (degree > max_degree) {
            max_degree = degree;
        }

    }
    return max_degree;
} //FINALIZADO

// -----------------------------------------------------------------------------
int grau_minimo(grafo g)  {
    vertice n;
    int degree, min_degree = INT_MAX;
    
    for (n = agfstnode(g); n; n = agnxtnode(g,n)) {
        degree = grau(n,g);
        if (degree < min_degree) {
            min_degree = degree;
        }
    }
    return min_degree;
} //FINALIZADO

// -----------------------------------------------------------------------------
int grau_medio(grafo g) {
    int e_g = n_arestas(g);
    int v_g = n_vertices(g);
    return (int)((2*e_g)/v_g);
} //FINALIZADO

// -----------------------------------------------------------------------------
int regular(grafo g) {
    vertice n;
    int degree, dge = 0;

    n = agfstnode(g);
    degree = grau(n,g);
    
    for (n = agfstnode(g); n; n = agnxtnode(g,n)) {
        dge = grau(n,g);
        if (dge != degree) {
            return 0;
        }
    }
    return 1;
} //FINALIZADO

// -----------------------------------------------------------------------------
int completo(grafo g) {
    vertice n;
    int degree, check = 0;

    n = agfstnode(g);
    degree = grau(n,g);

    check = n_vertices(g) - 1;

    if (regular(g) && degree == check)
        return 1;
    return 0;
} //FINALIZADO

// -----------------------------------------------------------------------------
int conexo(grafo g) {
    int n_v = n_vertices(g);
    int n_e = n_arestas(g);

    // qualquer grafo simples com n vértices e mais do que (n − 1)(n − 2)/2 arestas é conexo.
    if (n_e > ((n_v - 1)*(n_v - 2))/2)
        return 1;
    
    char name[10] = "Copy";
    grafo copy = copy_graph(g, name, 1);
    vertice n;    
    
    char type[10] = "color";
    char color[10] = "blue";
    agattr(copy,AGNODE,type,color);

    n = agfstnode(copy);
    int visited = 0;
    dfs(copy, n, &visited);
    destroi_grafo(copy);

    if (n_v != visited)
        return 0;
    return 1;
} //FINALIZADO

// -----------------------------------------------------------------------------
int bipartido(grafo g) {
    int vertices = n_vertices(g);
    int arestas = n_arestas(g);

    // um grafo bipartido de n vértices tem no máximo n^2/4 arestas
    if (arestas > (vertices*vertices)/4)
        return 0;

    int *color = (int *) malloc((size_t) vertices * sizeof(int));
    for (int i=0; i < vertices; ++i)
        color[i] = -1;
         
    int pos = 0;
    int **matrix = matriz_adjacencia(g);
    return coloreGrafo(vertices,matrix,color,pos,1);
} //FINALIZADO

// -----------------------------------------------------------------------------
int n_triangulos(grafo g) {
    int size = n_vertices(g);
    int **graph = matriz_adjacencia(g);

    // graph^2
    int **aux2 = aloca_matriz(size);
  
    // graph^3
    int **aux3 = aloca_matriz(size);

    multiply(size, graph, graph, aux2);
    multiply(size, graph, aux2, aux3);

    int trace = 0;
    for (int i=0; i < size; ++i)
        trace += aux3[i][i];
  
    return (int) trace / 6;
} //FINALIZADO

// -----------------------------------------------------------------------------
int **matriz_adjacencia(grafo g) {
    int size = n_vertices(g);
    int **m_adjacencia = aloca_matriz(size);
    
    // ATRIBUIÇÃO DE VALORES
    vertice l_v, c_v;
    int l_index, c_index;

    l_index = 0;
    for (l_v = agfstnode(g); l_v; l_v = agnxtnode(g,l_v)) {
        c_index = 0;
        for (c_v = agfstnode(g); c_v; c_v = agnxtnode(g,c_v)) {
            if (agedge(g,l_v,c_v,NULL,FALSE)) {
                m_adjacencia[l_index][c_index] = 1;
            }
            c_index ++;
        }
        l_index ++;
    }
    return m_adjacencia;
} //FINALIZADO

// -----------------------------------------------------------------------------
grafo complemento(grafo g) {
    char name[15] = "Complemento";
    grafo comp = copy_graph(g, name, 0);

    // adiciona as arestas
    vertice l_v, c_v, nd1, nd2;
    for (l_v = agfstnode(g); l_v; l_v = agnxtnode(g,l_v)) {
        for (c_v = l_v; c_v; c_v = agnxtnode(g,c_v)) {
            if (c_v != l_v) {
                if (!(agedge(g,l_v,c_v,NULL,FALSE)) || !(agedge(g,c_v,l_v,NULL,FALSE)) ) {
                    nd1 = agnode(comp, agnameof(l_v), FALSE);
                    nd2 = agnode(comp, agnameof(c_v), FALSE);
                    agedge(comp,nd1,nd2,NULL,TRUE);
            }
            }
        }
    }
    return comp;
} //FINALIZADO

// -----------------------------------------------------------------------------
grafo decompoe(grafo g) {
    if (agisdirected(g)) {
        char temp[10];
        char state[10] = "state";
        char components[12] = "components";
        char comp[10] = "comp";
        char value[10] = "0";

        agattr(g,AGRAPH,components,value); // g.components <- 0

        Agnode_t **order = buscaProfundidade(g); //vetor de vertices no inverso da pos-ordem
        // printf("pos ordem invertida:\n");
        // for (int i=0; i < n_vertices(g); ++i)
        //     printf("%s",agnameof(order[i]));

        // para cada v E V(G)
        vertice v;
        agattr(g,AGNODE,comp,value); // v.comp <- 0
        for (v = agfstnode(g); v; v = agnxtnode(g,v)) {
            agset(v, state, value); // v.estado <- 0
        }

        int c = 0;
        for (int i=0; i < n_vertices(g); ++i) {
            v = order[i];
            char *v_state = agget(v, state);

            if (!strcmp(v_state, value)) { //se v.estado = 0
                decompor(g,v,++c);

                // r.comp <- c
                sprintf(temp, "%d", c);
                agset(g, components, temp);
                temp[0] = '\0'; // limpa a string
            }
        }
        // printf("TOTAL DE COMPONENTES = %d\n", c);

        // ------- ADICIONA OS SUGRAFOS A g
        // para cada um dos componentes
        grafo h;
        char *r_comp;
        char *v_comp;
        for (int i = 1; i <= c; ++i) {
            temp[0] = '\0';
            char name[20] = "component_"; 

            sprintf(temp, "%d", i);

            // cria o subgrafo do componente i
            strcat(name, temp);
            h = agsubg(g,name,TRUE);


            // adiciona os vertices
            vertice r;
            for (r = agfstnode(g); r; r = agnxtnode(g,r)) {
                r_comp = agget(r, comp);
                if (!strcmp(r_comp, temp)) {
                    agsubnode(h, r, TRUE);
                }
            }


            //adiciona as arestas
            for (r = agfstnode(g); r; r = agnxtnode(g,r)) {
                r_comp = agget(r, comp);
                for (v = agfstnode(g); v; v = agnxtnode(g,v)) {
                    v_comp = agget(v, comp);
                    
                    if (!strcmp(r_comp, temp) && !strcmp(v_comp, temp)) { // se r e v pertencem a um mesmo componente
                        if (agedge(g,r,v,NULL,FALSE)) { // se existe um arco entre r e v
                            agsubedge(h, agedge(g,r,v,NULL,FALSE), TRUE);
                            // agedge(g,r,v,NULL,TRUE); // evita arestas "repetidas" em g. ao descomentar essa linha é possível observar essas arestas
                        }    
                    }
                }
            }
        }
    }
    return g;
}