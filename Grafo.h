#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

typedef struct grafo Grafo;

Grafo *cria_grafo(int n_vertice,int eh_digrafo);
int insere_aresta(Grafo *g,int v1,int v2,int P);
int remove_aresta(Grafo *g,int v1,int v2);
int verifica_aresta(Grafo *g,int v1,int v2);
int conferirExiste(Grafo *g,int v1,int v2);
int consulta_aresta(Grafo *g,int v1,int v2);
void libera_grafo(Grafo *g);
void mostrar_adjacente(Grafo *g,int v);
void mostrar_grafo(Grafo *g);
void Dijkstra(Grafo *g,int origem, int destino);

#endif // GRAFO_H_INCLUDED
