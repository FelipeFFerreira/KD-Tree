#include "kdtree.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

tipoDado dist(struct kd_node_t *a, struct kd_node_t *b, int dim)
{
    tipoDado t, d = 0;
    while (dim--) {
        t = a->x[dim] - b->x[dim];
        d += t * t;
    }
    return d;
}
void trocar(struct kd_node_t *x, struct kd_node_t *y) {
    tipoDado tmp[MAX_DIM];
    memcpy(tmp,  x->x, sizeof(tmp));
    memcpy(x->x, y->x, sizeof(tmp));
    memcpy(y->x, tmp,  sizeof(tmp));
}

/* metodo quickselect*/
struct kd_node_t* cordenadaCentral(struct kd_node_t *inicio, struct kd_node_t *final, int idx)
{
    if (final <= inicio) return NULL;
    if (final == inicio + 1)
        return inicio;

    struct kd_node_t *p, *store, *md = inicio + (final - inicio) / 2; //Captura a mediana do vetores de pontos
    tipoDado pivot;
    while (1) {
        pivot = md->x[idx]; //Na mediana, valor da cordenada x
        trocar(md, final - 1); //troca, mediana pelo uultimo valor do vetor de cordenadas
        for (store = p = inicio; p < final; p++) {
            if (p->x[idx] < pivot) {
                if (p != store)
                    trocar(p, store);
                store++;
            }
        }
        trocar(store, final - 1);

        if (store->x[idx] == md->x[idx])
            return md;

        if (store > md) final = store;
        else        inicio = store;
    }
}

struct kd_node_t* criarArvoreKDTree(struct kd_node_t *t, int len, int i, int dim)
{
    struct kd_node_t *n; //*aux;

    if (!len) return 0;
    if ((n = cordenadaCentral(t, t + len, i))) { //avalia len - 1 (passa o vetor de nos, referencia a uma posicao dps do  ultimo no, ref
        i = (i + 1) % dim;
        n->esq     = criarArvoreKDTree(t, n - t, i, dim);
        n->dir = criarArvoreKDTree(n + 1, t + len - (n + 1), i, dim);
    }
    return n;
}

void pontosMaisProximos(struct kd_node_t *raiz, struct kd_node_t *nd, int i, int dim, struct kd_node_t **melhor, tipoDado *melhorDistancia, heapNo * p, int * visitados)
{
    tipoDado d, dx, dx2;
    if (!raiz) return;
    d = dist(raiz, nd, dim);
    dx = raiz->x[i] - nd->x[i];
    dx2 = dx * dx;
    p[*visitados].x = raiz->x[0];
    p[*visitados].y = raiz->x[1];
    p[*visitados].dist = d;
    (*visitados)++;


    if (!*melhor || d < *melhorDistancia) {
        *melhorDistancia = d;
        *melhor = raiz;
    }

    if (!*melhorDistancia) return;

    if (++i >= dim) i = 0;

    pontosMaisProximos(dx > 0 ? raiz->esq : raiz->dir, nd, i, dim, melhor, melhorDistancia, p, visitados);
    if (dx2 >= *melhorDistancia){
            return;
    }
    pontosMaisProximos(dx > 0 ? raiz->dir : raiz->esq, nd, i, dim, melhor, melhorDistancia, p, visitados);
}

/* Realiza o percurso pré­-ordem da árvore binária kd-tree */
void pre_ordem(struct kd_node_t * t)
{
    if (t != NULL) {
        printf("\n(%g , %g)\n", t->x[0], t->x[1]); // processa a raiz
        if(t->esq == NULL)printf("esq null\n");
        pre_ordem(t->esq); // visita a subárvore esquerda
        pre_ordem(t->dir); // visita a subárvore direita
        if(t->dir == NULL)printf("dir null\n");
    }

}
void criarHeapMin(heapNo a[], int n)
{
    int e = n/2, i, j, d = n-1; // índice do último
    heapNo x;
    while(e > 0)
    {
        e--;
        i = e;
        j = 2 * e + 1; // índice do filho esquerdo
        x = a[e]; // novo elemento
        if (j < d && a[j + 1].dist < a[j].dist) j++;
        while (j <= d && a[j].dist < x.dist)
        {
            a[i] = a[j];
            i = j;
            j = 2 * j + 1;
            if(j < d && a[j + 1].dist < a[j].dist) j++;
        }
        a[i] = x;
    }
}

void Quick(heapNo vetor[], int inicio, int fim) {

    int i, j, meio;
    heapNo aux;
    tipoDado pivo;

    i = inicio;
    j = fim;

    meio = (int) ((i + j) / 2);
    pivo = vetor[meio].dist;

    do {
      while (vetor[i].dist < pivo) i = i + 1;
      while (vetor[j].dist > pivo) j = j - 1;

      if(i <= j){
         aux = vetor[i];
         vetor[i] = vetor[j];
         vetor[j] = aux;
         i = i + 1;
         j = j - 1;
      }
   } while(j > i);

   if(inicio < j) Quick(vetor, inicio, j);
   if(i < fim) Quick(vetor, i, fim);

}

void imprimirPontosEncontrados(heapNo * pontosProxHeapMin, int visitados)
{
    printf("\n----------------------------------------------------------\n");
    printf("\n>Vizinhos De Maiores alcanse Na Ramificacao(HeapMin):\n");
    int i;
    for(i = 0; i < visitados; i++)printf("\n[%d](%g, %g) dist %g\n", i, pontosProxHeapMin[i].x, pontosProxHeapMin[i].y, sqrt(pontosProxHeapMin[i].dist));
    printf("\n----------------------------------------------------------\n");

}

void imprimirQtdPontos(heapNo * pontosProximos, int qtd, int visitados)
{
    int i;
    printf("\n----------------------------------------------------------\n");
    printf("\n>%d Vizinhos de maiores alcanse:\n", qtd);
    if(qtd <= visitados)
        for(i = 0; i < qtd; i++)printf("\n[%d](%g, %g) dist %g\n", i, pontosProximos[i].x, pontosProximos[i].y, sqrt(pontosProximos[i].dist));
    else printf("\nQuantidade Solicitada Maior Que Quantidade de Busca Encontrada\n");
    printf("\n----------------------------------------------------------\n");
}
