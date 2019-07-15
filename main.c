#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

int main(){
    int i,*P = malloc(sizeof(int));
    Grafo *g = cria_grafo(3,0);

    insere_aresta(g,0,1,5);
    insere_aresta(g,0,2,4);
    insere_aresta(g,1,2,3);
    verifica_aresta(g,1,0);
    insere_aresta(g,2,1,7);

    Dijkstra(g,0,1);

    mostrar_grafo(g);
    libera_grafo(g);
}
