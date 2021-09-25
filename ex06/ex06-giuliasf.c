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
int fluxoMaximo(int mtr[n][n])
{
    int i, j, u;

    // criar matrz para n vértices
    int grafo[n][n];

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            grafo[i][j] = mtr[i][j];
        }
    }

    // predecessor de cada vértice
    int *pred = malloc(n * sizeof(int));

    int maxFluxo = 0;

    int cont;

    int s = 0;
    int t = n - 1;

    while (buscaLargura(grafo, s, t, pred) != 0)
    {
        cont = -1;

        for (i = t; i != s; i = pred[i])
        {
            u = pred[i];
            if (grafo[u][i] < cont || cont == -1)
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
    int i, j, a, b, c;

    // receber n (num de vértices) e m (num de arestas)
    scanf("%d %d", &n, &m);

    // criar matrz para n vértices
    int mtzAdj[n][n];

    // inicializa matriz com 0 para todos os vértices
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            mtzAdj[i][j] = 0;
        }
    }

    // adiciona arestas na matriz
    for (i = 0; i < m; i++)
    {
        scanf("%d %d %d", &a, &b, &c);
        mtzAdj[a][b] = c;
    }

    // executa o algoritmo de prim para encontrar a AGM
    printf("%d\n", fluxoMaximo(mtzAdj));

    return 0;
}