#include "kdtree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

int main()
{
    int i;
    struct kd_node_t vetDefinidoTestes[] = {
     {{2, 1}}, {{5, 1}}, {{1, 2}}, {{10, 2}}, {{6, 3}}, {{9, 3}},
    {{3, 4}}, {{7, 4}}, {{4, 5}}, {{8, 5}}, {{2, 6}}, {{5, 6}},
    {{1, 7}}, {{10, 7}}, {{6, 8}}, {{9, 8}}, {{3, 9}}, {{7, 9}},
    {{4, 10}}, {{8, 10}}
	};

    clock_t tempo;
    struct kd_node_t testNode = {{5, 4}};
    struct kd_node_t *raiz, *encontrada = NULL, *milhaoAleatorios;
    tipoDado melhorDistancia;
    heapNo pontosProxHeapMin[100];

    tempo = clock();
    raiz = criarArvoreKDTree(vetDefinidoTestes, sizeof(vetDefinidoTestes) / sizeof(vetDefinidoTestes[1]), 0, 2); //passa como parametro, o vetor com nos, a qtd de nos, ref x, dim
    printf("\nTempo Total Para Criar a Arvore Com %d Nos : %lfs (REF TIME)\n", sizeof(vetDefinidoTestes) / sizeof(vetDefinidoTestes[1]), (tipoDado) (clock() - tempo)  / CLOCKS_PER_SEC);


    tempo = clock();
    int visitados = 0;
    pontosMaisProximos(raiz, &testNode, 0, 2, &encontrada, &melhorDistancia, pontosProxHeapMin, &visitados);
    printf("Tempo Total Para visitar %d Nos: %gs\n", visitados, (tipoDado) (clock() - tempo)  / CLOCKS_PER_SEC);
    printf("\n>Melhor Valor Encontrado Para a Cordenada(%g, %g) Is (%g, %g) .:.Com  Distancia %g\nForam Visitados %d Nos\n\n",
           testNode.x[0], testNode.x[1], encontrada->x[0], encontrada->x[1], sqrt(melhorDistancia), visitados);

    criarHeapMin(pontosProxHeapMin, visitados);
    //Quick(pontosProxHeapMin, 0, visitados - 1); // se quiser ordenar em ordem crescente
    imprimirPontosEncontrados(pontosProxHeapMin, visitados);
    imprimirQtdPontos(pontosProxHeapMin, 2, visitados);

    /*
     * Analisando MILHOES DE PONTOS 2D
     */
    milhaoAleatorios =(struct kd_node_t*) calloc(N, sizeof(struct kd_node_t)); //aloca um espaco de 100000 de KDnos
    srand(time(NULL));

    tempo = clock();
    for (i = 0; i < N; i++) rand_pt(milhaoAleatorios[i]);
    printf("\nTempo Total Para gerar(%d Milhao) De Pontos 2D: %lfs\n" , D, (tipoDado) (clock() - tempo)  / CLOCKS_PER_SEC);

    tempo = clock();
    raiz = criarArvoreKDTree(milhaoAleatorios, N, 0, 2);
    printf("\nTempo Total Para Criar a Arvore Com %d Nos : %lfs (REF TIME)\n", sizeof(milhaoAleatorios) / sizeof(milhaoAleatorios[1]), (tipoDado) (clock() - tempo)  / CLOCKS_PER_SEC);
    rand_pt(testNode);

    encontrada = NULL;
    tempo = clock();

    pontosMaisProximos(raiz, &testNode, 0, 2, &encontrada, &melhorDistancia, pontosProxHeapMin, &visitados);
    printf("Tempo Total Para visitar %d Nos : %lf\n\n", visitados, (tipoDado) (clock() - tempo)  / CLOCKS_PER_SEC);

     printf(">>Arvore de Milhao\n>Melhor Valor Encontrado Para Cordenada(%g, %g) Is"
            "(%g, %g) Com distancia %g\nForam Visitados %d Nos\n\n", testNode.x[0], testNode.x[1], encontrada->x[0], encontrada->x[1],
            sqrt(melhorDistancia), visitados);

        criarHeapMin(pontosProxHeapMin, visitados);
        imprimirPontosEncontrados(pontosProxHeapMin, visitados);
        imprimirQtdPontos(pontosProxHeapMin, 5, visitados);

    return 0;
}
