#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

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

int *buscaLargura(int mtr[n][n], int raiz)
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
    cor[raiz] = 1;

    // marca distância da raiz como 0
    dist[raiz] = 0;

    // insere raiz na fila
    insereFila(f, raiz);

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
            }
        }

        // marca vértice como explorado
        cor[u] = 2;
    }

    return cor;
}

bool verificaFortementeConexo(int mtr[n][n])
{
    int i, j;
    bool grafoFortementeConexo = true;

    // vetor para indicar quais vértices já foram visitados
    // 0 para não visitado - 1 para visitado - 2 explorado
    int *cor = malloc(n * sizeof(int));

    // marcar todos os vértices ccomo não visitados
    for (i = 0; i < n; i++)
    {
        cor[i] = 0;
    }

    for (j = 0; j < n; j++)
    {
        cor = buscaLargura(mtr, j);

        // verifica se algum vértice não foi visitado
        for (i = 0; i < n; i++)
        {
            if (cor[i] != 2)
            {
                grafoFortementeConexo = false;
                break;
            }
        }
    }

    return grafoFortementeConexo;
}

int main()
{
    int i, j, a, b, d;

    // receber n (num de vértices/cruzamentos) e m (num de arestas/trechos)
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
        scanf("%d %d %d", &a, &b, &d);
        mtzAdj[a][b] = 1;
        if (d == 2)
        {
            mtzAdj[b][a] = 1;
        }
    }

    bool fortementeConexo = verificaFortementeConexo(mtzAdj);

    if (fortementeConexo)
    {
        printf("Adequado.\n");
    }
    else
    {
        printf("Inadequado.\n");
    }

    return 0;
}