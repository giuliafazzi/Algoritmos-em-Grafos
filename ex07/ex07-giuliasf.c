#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

// TAD que representa o nó da lista
typedef struct no
{
    int elem;
    struct no *prox;
} No;

typedef struct
{
    int tam;
    No *prox;
} Cabeca;

typedef Cabeca *Fila;

int n = 0;
int m = 0;
int k = 0;

void inicializaFila(Fila *f)
{
    // aloca espaço
    (*f) = (Cabeca *)malloc(sizeof(Cabeca));
    // inicializa fila com tamanho 0
    (*f)->tam = 0;
    (*f)->prox = NULL;
}

void insereFila(Fila f, int elem)
{
    // nó auxiliar para o elemento a ser inserido
    No *paux = (No *)malloc(sizeof(No));

    paux->elem = elem;
    paux->prox = NULL;

    // verifica se a fila está vazia
    if (f->tam == 0)
    {
        f->prox = paux;
    }
    else
    {
        No *pfim = f->prox;

        // percorre lista até o fim
        while (pfim->prox != NULL)
        {
            pfim = pfim->prox;
        }

        // insere nó no final da fila
        pfim->prox = paux;
    }

    // incrementa tamanho da fila
    f->tam++;
}

int removeFila(Fila f)
{
    // verifica se tem algo a ser removido (fila não vazia)
    if (f->tam != 0)
    {
        No *paux = f->prox;
        int elem = paux->elem;
        // remove o primeiro elemento da fila
        f->prox = paux->prox;
        // decrementa o tamanho da fila
        f->tam--;
        // retorna o elemento que foi removido
        return elem;
    }
    return 0;
}

int buscaLargura(int mtr[n][n], int s, int t, int pred[n])
{
    int v, i, u;
    Fila f;

    // vetor para indicar quais vértices já foram visitados
    // 0 para não visitado - 1 para visitado - 2 explorado
    int *cor = malloc(n * sizeof(int));

    // vetor para marcar a distância
    int *dist = malloc(n * sizeof(int));

    // inicializa uma fila vazia
    inicializaFila(&f);

    // marcar todos os vértices ccomo não visitados, todas as distâncias como infinitas
    for (i = 1; i < n; i++)
    {
        dist[i] = -1;
        cor[i] = 0;
    }

    // marca raiz como visitada
    cor[s] = 1;

    // marca distância da raiz como 0
    dist[s] = 0;

    // marca predecessor como nulo
    pred[s] = -1;

    // insere raiz na fila
    insereFila(f, s);

    // repete enquanto houver vértices na fila
    while (f->tam != 0)
    {
        // remove primeiro vértice da fila
        u = removeFila(f);

        for (v = 0; v < n; v++)
        {
            // verifica se é adj e se ainda não foi visitado
            if (mtr[u][v] != 0 && cor[v] == 0)
            {
                // soma distância
                dist[v] = dist[u] + 1;

                // marca vértice como visitado
                cor[v] = 1;

                // insere vértice na fila
                insereFila(f, v);

                // indica pred
                pred[v] = u;
            }
        }

        // marca vértice como explorado
        cor[u] = 2;
    }

    return cor[t];
}

// para a implementação deste problema, será utilizado o algoritmo de Ford-Fulkerson
int fluxoMaximo(int mtr[n][n], int s, int t)
{
    int i, j, u;

    // criar matrz para n + k + 1 vértices
    int grafo[t + 1][t + 1];

    for (i = 0; i < t + 1; i++)
    {
        for (j = 0; j < t + 1; j++)
        {
            grafo[i][j] = mtr[i][j];
        }
    }

    // predecessor de cada vértice
    int *pred = malloc((t + 1) * sizeof(int));

    int maxFluxo = 0;

    int cont;

    int a;

    while (a = buscaLargura(grafo, s, t, pred) != 0)
    {
        // printf("busca %d\n", a);
        cont = -1;

        for (i = t; i != s; i = pred[i])
        {
            u = pred[i];
            if (grafo[u][i] != -1 && (grafo[u][i] < cont || cont == -1))
            {
                cont = grafo[u][i];
            }
        }

        for (i = t; i != s; i = pred[i])
        {
            u = pred[i];
            grafo[u][i] -= cont;
            grafo[i][u] += cont;
        }

        maxFluxo += cont;
    }

    return maxFluxo;
}

int main()
{
    int i, j, a, b;

    // receber n (num de vértices) e m (num de arestas)
    scanf("%d %d %d", &n, &k, &m);

    // adiciona mais dois vértices, um para fonte e outro para o sorvedouro
    int font = n + k;
    int sorv = font + 1;

    // criar matrz para n vértices
    int mtzAdj[sorv + 1][sorv + 1];

    // inicializa matriz com 0 para todos os vértices
    for (i = 0; i < sorv + 1; i++)
    {
        for (j = 0; j < sorv + 1; j++)
        {
            mtzAdj[i][j] = 0;
        }
    }

    // adiciona arestas na matriz
    for (i = 0; i < m; i++)
    {
        scanf("%d %d", &a, &b);
        // infinito para os dois vértices
        mtzAdj[a][b] = -1;
        // aresta ligando fonte ao vértice a
        mtzAdj[font][a] = 1;
        // aresta ligando vértice b ao sorvedouro
        mtzAdj[b][sorv] = 1;
    }

    // executa o algoritmo de prim para encontrar a AGM
    printf("%d\n", fluxoMaximo(mtzAdj, font, sorv));

    return 0;
}