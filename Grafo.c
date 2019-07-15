#include <stdio.h>
#include <stdlib.h>
#include "Grafo.h"

struct no{
    int vertice;
    int peso;
    struct no *prox;
};

struct grafo{
    int n_vertice,n_aresta;
    int *grau;
    int eh_digrafo;
    struct no **aresta;
};

Grafo *cria_grafo(int n_vertice,int eh_digrafo){
    int i;
    if(n_vertice<1 || eh_digrafo<0 || eh_digrafo>1)return NULL;
    Grafo *g = (Grafo *)malloc(sizeof(Grafo));
    if(g != NULL){
        g->n_vertice = n_vertice;
        g->n_aresta = 0;
        g->eh_digrafo = eh_digrafo;
        g->grau = (int *)malloc(n_vertice*sizeof(int));
        for(i=0; i<n_vertice;i++){
            g->grau[i] = 0;
        }
        g->aresta = (struct no **)malloc(n_vertice*sizeof(struct no*));
        if(g->aresta != NULL){
            for(i=0;i<n_vertice;i++){
                g->aresta[i] = NULL;
            }
        }
    }
    return g;
}

int insere_aresta(Grafo *g,int v1,int v2,int P){
    if(g == NULL || v1<0 || v1>=g->n_vertice || v2<0 || v2>=g->n_vertice)return -1;
    struct no *aux;
    aux = g->aresta[v1];
    while(aux != NULL && aux->vertice != v2){
        aux = aux->prox;
    }
    if(g->eh_digrafo == 0){
            if(v1 == v2)return 0;
    }
    if(aux != NULL)return 0;
    struct no *n;
    n = malloc(sizeof(struct no));
    if(n != NULL){
        n->vertice = v2;
        n->peso = P;
        n->prox = g->aresta[v1];
        g->aresta[v1] = n;
    }
    g->n_aresta++;
    g->grau[v1]++;
    g->grau[v2]++;
    if(g->eh_digrafo == 0 && conferirExiste(g,v2,v1) == 0){
        g->n_aresta--;
        g->grau[v1]--;
        g->grau[v2]--;
        insere_aresta(g,v2,v1,P);
    }
    return 1;
}

int verifica_aresta(Grafo *g,int v1,int v2){
    if(g == NULL || v1<0 || v1>=g->n_vertice || v2<0 || v2>=g->n_vertice)return -1;
    struct no *aux;
    aux = g->aresta[v1];
    while(aux != NULL && aux->vertice != v2){
        aux = aux->prox;
    }
    if(aux == NULL)return 0;
    else return 1;
}

int remove_aresta(Grafo *g,int v1,int v2){
    if(g == NULL || v1<0 || v1>=(g->n_vertice) || v2<0 || v2>=(g->n_vertice))return -1;
    struct no *aux;
    struct no *ant;
    aux = g->aresta[v1];
    ant = NULL;
    while(aux != NULL && aux->vertice != v2){
        ant = aux;
        aux = aux->prox;
    }
    if(aux == NULL)return 0;
    if(ant == NULL) g->aresta[v1] = aux->prox;
    else {
        ant->prox = aux->prox;
    }
    free(aux);
    g->n_aresta--;
    g->grau[v1]--;
    g->grau[v2]--;
    if(g->eh_digrafo == 0 && conferirExiste(g,v2,v1) == 1){
        g->n_aresta++;
        g->grau[v1]++;
        g->grau[v2]++;
        remove_aresta(g,v2,v1);
    }
    return 1;
}

int consulta_aresta(Grafo *g,int v1,int v2){
    if(g == NULL || v1<0 || v1>=(g->n_vertice) || v2<0 || v2>=(g->n_vertice))return -1;
    struct no *aux;
    aux = g->aresta[v1];
    while(aux != NULL && aux->vertice != v2){
        aux = aux->prox;
    }
    if(aux == NULL)return 0;
    return aux->peso;
}

void libera_grafo(Grafo *g){
    int i;
    struct no *aux,*ant;
    for(i=0;i<g->n_vertice;i++){
        aux = g->aresta[i];
        while(aux != NULL){
            ant = aux;
            aux = aux->prox;
            free(ant);
        }
    }
    free(g->aresta);
    free(g->grau);
    free(g);
}

void mostrar_adjacente(Grafo *g,int v){
    if(g == NULL || v<0 || v>=(g->n_vertice)){
        printf("Grafo inexistente ou vertice invalido\n");
        return;
    }
    struct no *aux;
    aux = g->aresta[v];
    if(aux == NULL)printf("O vertice %d nao tem adjacentes\n",v);
    while(aux != NULL){
        printf("%d --> %d | peso: %d\n",v,aux->vertice,aux->peso);
        aux = aux->prox;
    }
}

void mostrar_grafo(Grafo *g){
    if(g == NULL){
        printf("Grafo inexistente");
        return;
    }
    int i;
    if(g->eh_digrafo == 0)printf("Grafo nao direcionado\n");
    else printf("Grafo direcionado\n");

    for(i=0;i<g->n_vertice;i++){
        printf("\nVertice %d\n",i);
        mostrar_adjacente(g,i);
    }
}

int conferirExiste(Grafo *g,int v1,int v2){
    struct no *aux;
    aux = g->aresta[v1];
    while(aux != NULL && aux->vertice != v2){
        aux = aux->prox;
    }
    if(aux == NULL)return 0;
    return 1;
}

void Dijkstra(Grafo *g,int origem, int destino){
    int i,vert,k, min, NovaDist, *L;
    int *M, *A, *caminho;
    M = (int *)malloc(g->n_vertice*sizeof(int));
    L = (int *)malloc(g->n_vertice*sizeof(int));
    A = (int *)malloc(g->n_vertice*sizeof(int));
    caminho = (int *)malloc(g->n_vertice*3*sizeof(int));

    for (i=0; i<g->n_vertice; i++){
        M[i] = 0;
        A[i] = -1;
        L[i] = 300000;
    }
    vert = origem;
    L[vert] = 0;
    while (/*vert != destino &&*/ vert != -1){
    for(i=0;i<g->n_vertice; i++)
        if (conferirExiste(g,vert,i) != 0 && M[i]==0){
            NovaDist = L[vert] + consulta_aresta(g,vert,i);
            if (NovaDist < L[i]){
                L[i] = NovaDist;
                A[i] = vert;
            }
        }
    M[vert] = 1;
    min = 300000;
    vert = -1;
    for (i=0; i<g->n_vertice; i++)
        if (M[i]==0 && L[i] < min){
            min = L[i];
            vert = i;
        }
    }
    /*if (vert == destino){
        printf("caminho mais curto entre %d e %d - Tempo total: %.3fs\n",origem, destino, L[destino] );
        caminho[0] = destino;
        k = 1;
        while (vert != origem){
            caminho[k]= A[vert];
            vert = A[vert];
            k++;
        }
        for (i=k-1; i>=0; i--)printf("%d\n", caminho[i]);
    }
    else printf("nao exite caminho entre %d e %d\n", origem, destino);*/
    printf("Caminho mais curto de %d ate: \n",origem);
    for(i=0;i<g->n_vertice;i++){
        printf("%d - Peso total: %d\n",i,L[i]);
    }
}
