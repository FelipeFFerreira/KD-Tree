/*
 * kdtree.h
 *
 * Definição do TAD  da Árvore Bidimensional (KD-Tree) e protótipo de suas operações.
 *
 * Para a criaçao da arvore balanceada, é tomado com referencia o valor pre ordenado da mediana.

 * Felipe Ferreira.
 * Versao: 1.0
 * Versao: 2.0 Melhorar possiveis formas diferentes da criacao da arvore KDTree
 * 09/jan/2020
 */

#ifndef _KDTREE_H
#define _KDTREE_H

#include <stdlib.h>

#define MAX_DIM 2
#define MAX_VISITAS 100
#define MAX_HEAP 100

#define D 1
#define N  D  * 1000000
#define rand1() (rand() / (tipoDado)RAND_MAX)
#define rand_pt(v) { v.x[0] = rand1(); v.x[1] = rand1();}

typedef double tipoDado;

/*TAD NoHeap*/
typedef struct {

    tipoDado x;
    tipoDado y;
    tipoDado dist;

}heapNo;

/*TAD KD No */
struct kd_node_t{
    tipoDado x[MAX_DIM];
    struct kd_node_t *esq, *dir;
};

/*Funcao para calculo da distancia, dado dois pontos no espaco e sua dimensao*/
tipoDado dist(struct kd_node_t *a, struct kd_node_t *b, int dim);

/*Funcao que troca dois pontos bidimensionais*/
void trocar(struct kd_node_t *x, struct kd_node_t *y);

/*Funcao que retorna a mediana de um vetor de pontos*/
struct kd_node_t* cordenadaCentral(struct kd_node_t *inicio, struct kd_node_t *final, int idx);

/*Funcao que receber o vetor de cordenadas*/
struct kd_node_t* criarArvoreKDTree(struct kd_node_t *t, int len, int i, int dim);

/*Funcao de calculo de ponto mais proximo*/
void pontosMaisProximos(struct kd_node_t *root, struct kd_node_t *nd, int i, int dim, struct kd_node_t **best, tipoDado *best_dist, heapNo * p, int * visitados);

/*Imprimir arvore em  pre_ordem (RED)*/
void pre_ordem(struct kd_node_t * t);

/*Criar Heap Min*/
void criarHeapMin(heapNo a[], int n);

void imprimirPontosEncontrados(heapNo * pontosProxHeapMin, int );

void imprimirQtdPontos(heapNo * pontosProximos , int, int);

void Quick(heapNo vetor[], int inicio, int fim);

#endif


