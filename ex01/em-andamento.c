#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

int n = 0;
int m = 0;

typedef struct no
{
    int vertice;
    struct No *proximo;
} No;

typedef struct grafo
{
    int qtdVertices;
    struct No **lista;
} Grafo;

int **criarMatrizAdj()
{
    // n verts
    // m arestas
    int i, j;
    int u, v;

    // printf("digite n m\n");
    scanf("%d %d", &n, &m);

    int mtzAdj[n][n];

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            mtzAdj[i][j] = 0;
        }
    }

    for (i = 0; i < m; i++)
    {
        scanf("%d %d", &u, &v);
        mtzAdj[u][v] = 1;
        mtzAdj[v][u] = 1;
    }

    // printf("\n\n");

    // for (i = 0; i < n; i++)
    // {
    //     for (j = 0; j < n; j++)
    //     {
    //         printf("%d\t", mtzAdj[i][j]); // mudança
    //     }
    //     printf("\n");
    // }
}

void criarListaAdj()
{
    // n verts
    // m arestas
    int i, n, m, u, v;
    printf("digite n m\n");
    scanf("%d %d", &n, &m);

    // criar o grafo
    Grafo *grf = (Grafo *)malloc(sizeof(Grafo));
    grf->qtdVertices = n;
    grf->lista = malloc(n * sizeof(No));

    // printf("\nvalores:\nn = %d\nm = %d\n", n, m);

    // inicializar o grafo
    for (i = 0; i < n; i++)
    {
        grf->lista[i] = NULL;
    }

    for (i = 0; i < m; i++)
    {
        scanf("%d %d", &u, &v);

        // adicionar arestas
        // No *novo = (No *)malloc(sizeof(No));
        // novo->vertice = u;
        // novo->proximo = grf->lista[v];
        // grf->lista[v] = novo;

        // novo->vertice = v;
        // novo->proximo = grf->lista[u];
        // grf->lista[u] = novo;
    }

    // int r;
    // for (r = 0; r < grf->qtdVertices; r++)
    // {
    //     No *temp = grf->lista[r];
    //     printf("\n Vertex %d\n: ", r);
    //     while (temp)
    //     {
    //         printf("%d -> ", temp->vertice);
    //         temp = temp->proximo;
    //     }
    //     printf("\n");
    // }
}

bool verificaGrau(int mtr[n][n])
{
    bool grauPar = true;
    int i, j;
    int cont;

    for (i = 0; i < n; i++)
    {
        cont = 0;

        for (j = 0; j < n; j++)
        {
            cont += mtr[i][j];
        }

        if (cont % 2 != 0)
        {
            grauPar = false;
            break;
        }
    }

    return grauPar;
}

bool averificaConexo(int mtr[n][n])
{
    bool grafoConexo = false;
    int i;

    // vetor para indicar quais vértices já foram visitados
    // 0 para não visitado - 1 para visitado
    int visitados[n];

    // vetor de fila, para indicar a ordem de visitação
    int fila[n];
    int fila_inicio = 0, fila_fim = 1;

    // marcar todos os vértices ccomo não visitados
    for (i = 0; i < n; i++)
    {
        visitados[i] = 0;
    }

    // inicia a busca pela raiz
    fila[fila_fim] = mtr[0][0];
    visitados[0] = 1;

    while (fila_inicio != fila_fim)
    {
        /* code */
    }

    return grafoConexo;
}

int *buscaLargura(int mtr[n][n], int cor[n], int u)
{
    int v;

    // marca vértice como visitado
    cor[u] = 1;

    for (v = 0; v < n; v++)
    {
        // verifica se o vértice é adj. e se ainda não foi visitado
        if (mtr[u][v] != 0 && cor[v] == 0)
        {
            buscaLargura(mtr, cor, v);
        }
    }

    cor[u] = 2;

    return cor;
}

bool verificaConexo(int mtr[n][n])
{
    bool grafoConexo = true;
    int i, u;

    // vetor para indicar quais vértices já foram visitados
    // 0 para não visitado - 1 para visitado - 2 explorado
    int *cor = malloc(n);

    // marcar todos os vértices ccomo não visitados
    for (i = 0; i < n; i++)
    {
        cor[i] = 0;
    }

    cor = buscaLargura(mtr, cor, 0);

    for (i = 0; i < n; i++)
    {
        if (cor[i] != 2)
        {
            grafoConexo = false;
            break;
        }
    }

    return grafoConexo;
}

void main()
{
    // int **matriz = criarMatrizAdj();

    int i, j;
    int u, v;

    // receber n (num de vértices) e m (num de arestas)
    scanf("%d %d", &n, &m);

    // criar matrz para n vértices
    int mtzAdj[n][n];

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            mtzAdj[i][j] = 0;
        }
    }

    for (i = 0; i < m; i++)
    {
        scanf("%d %d", &u, &v);
        mtzAdj[u][v] = 1;
        mtzAdj[v][u] = 1;
    }

    bool par = verificaGrau(mtzAdj);
    bool conexo = verificaConexo(mtzAdj);

    if (par && conexo)
    {
        printf("O grafo eh Euleriano.");
    }
    else
    {
        printf("O grafo nao eh Euleriano.");
    }
}