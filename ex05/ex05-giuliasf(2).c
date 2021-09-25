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

// bool verificaFortementeConexo(int mtr[n][n])
// {
//     int i, j;
//     bool grafoFortementeConexo = true;

//     // vetor para indicar quais vértices já foram visitados
//     // 0 para não visitado - 1 para visitado - 2 explorado
//     int *cor = malloc(n * sizeof(int));

//     // marcar todos os vértices ccomo não visitados
//     for (i = 0; i < n; i++)
//     {
//         cor[i] = 0;
//     }

//     for (j = 0; j < n; j++)
//     {
//         cor = buscaLargura(mtr, j);

//         // verifica se algum vértice não foi visitado
//         for (i = 0; i < n; i++)
//         {
//             if (cor[i] != 2)
//             {
//                 grafoFortementeConexo = false;
//                 break;
//             }
//         }
//     }

//     return grafoFortementeConexo;
// }

// void dijkstra(int r)
// {
//     Fila f;

//     // vetor para marcar a distância
//     int *dist = malloc(n * sizeof(int));

//     // conjunto de vértices com caminho mais curto ainda a descobrir
//     // FAZER FILA
//     int *s = malloc(n * sizeof(int));

//     // inicializa uma fila vazia
//     inicializaFila(&f);

//     // marcar todos os vértices ccomo não visitados, todas as distâncias como infinitas
//     for (i = 1; i < n; i++)
//     {
//         dist[i] = -1;
//         s[i] = i;

//         // insere vértice na fila
//         insereFila(f, i);
//     }

//     dist[r] = 0;

//     while (len(s) > 0)
//     {
//         /* code */
//     }
// }

// acha maior valor
int maiorPeso(int peso[n], int cor[n], int mtr[n][n], int index)
{
    int i;

    int pesoMax = -1;

    int vert;

    // percorre todos os vértices
    for (i = 0; i < n; i++)
    {
        if (cor[i] == 0 && mtr[index][i] > pesoMax)
        {
            pesoMax = mtr[index][i];
            vert = i;
        }
    }

    // printf("pesoMax vertice %d = %d\n", vert, pesoMax);

    return vert;
}

void agm(int mtr[n][n])
{
    int i, j, u;

    // peso da aresta mais pesada ligando x a componente de r
    int *peso = malloc(n * sizeof(int));

    // peso da aresta mais pesada ligando x a componente de r
    int *pred = malloc(n * sizeof(int));

    // vetor para indicar vértices a serem incluídos na árvore
    // 0 para não incluído - 1 para incluído
    int *cor = malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
    {
        peso[i] = -1;
        cor[i] = 0;
        pred[i] = -1;
    }

    peso[0] = 0;

    for (i = 0; i < (n / 2) + 1; i++)
    {
        // printf("vertice %d\n", i);

        // achar o vértice u adj de maior peso
        u = maiorPeso(peso, cor, mtr, i);

        // cor[u] = 1;

        if (mtr[i][u] != 0)
        {
            printf("%d %d\n", i, u);
        }

        for (j = u + 1; j < n; j++)
        {
            if (mtr[i][j] == mtr[i][u])
            {
                printf("%d %d\n", i, j);
            }
        }

        // cor[i] = 1;
    }
}

// para a implementação do algoritmo para Árvores Geradoras Mínimas, será utilizado o algoritmo de Prim
// void agm(int mtr[n][n])
// {
//     int i, v, u;

//     // peso da aresta mais pesada ligando x a componente de r
//     int *peso = malloc(n * sizeof(int));

//     // peso da aresta mais pesada ligando x a componente de r
//     int *pred = malloc(n * sizeof(int));

//     // vetor para indicar vértices a serem incluídos na árvore
//     // 0 para não incluído - 1 para incluído
//     int *cor = malloc(n * sizeof(int));

//     // marcar todos os vértices como não visitados
//     // inicializa dias como o original
//     for (i = 0; i < n; i++)
//     {
//         peso[i] = -1;
//         cor[i] = 0;
//     }

//     peso[0] = 0;

//     for (i = 0; i < n; i++)
//     {
//         printf("vertice %d\n", i);

//         // achar o vértice u adj de maior peso
//         u = maiorPeso(peso, cor, mtr, i);

//         printf("u %d\n", u);

//         // marca como vértice incluído
//         cor[u] = 1;

//         for (v = 0; v < n; v++)
//         {
//             // printf("mtr %d\ncor %d\n")
//             // verifica se o vértice é adjacente, se ainda não foi incluído, peso
//             if (mtr[i][v] != 0 && cor[v] == 0 && peso[v] < mtr[u][v])
//             {
//                 peso[v] = mtr[u][v];
//                 printf("%d %d\n", v, u);
//             }
//         }
//     }
// }

void printMatriz(int mtr[n][n])
{
    int i, j;
    // inicializa matriz com 0 para todos os vértices
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%d ", mtr[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int i, j, a, b, c;

    // receber n (num de vértices/cidades) e m (num de arestas/trechos)
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
        mtzAdj[b][a] = c;
    }

    // printMatriz(mtzAdj);

    agm(mtzAdj);

    return 0;
}