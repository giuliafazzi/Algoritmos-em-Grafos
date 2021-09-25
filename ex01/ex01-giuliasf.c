#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

int n = 0;
int m = 0;

bool verificaGrau(int mtr[n][n])
{
    bool grauPar = true;
    int i, j;
    int cont;

    // percorre matriz de adj.
    for (i = 0; i < n; i++)
    {
        cont = 0;

        // conta quantas arestas são incidentes no vértice
        for (j = 0; j < n; j++)
        {
            cont += mtr[i][j];
        }

        // verifica se o grau do vértice não é par
        if (cont % 2 != 0)
        {
            grauPar = false;
            break;
        }
    }

    return grauPar;
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

    // marca vértice como explorado
    cor[u] = 2;

    return cor;
}

bool verificaConexo(int mtr[n][n])
{
    bool grafoConexo = true;
    int i;

    // vetor para indicar quais vértices já foram visitados
    // 0 para não visitado - 1 para visitado - 2 explorado
    int *cor = malloc(n * sizeof(int));

    // marcar todos os vértices ccomo não visitados
    for (i = 0; i < n; i++)
    {
        cor[i] = 0;
    }

    cor = buscaLargura(mtr, cor, 0);

    // verifica se algum vértice não foi visitado
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

int main()
{
    int i, j;
    int u, v;

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
        scanf("%d %d", &u, &v);
        mtzAdj[u][v]++;
        mtzAdj[v][u]++;
    }

    bool par = verificaGrau(mtzAdj);
    bool conexo = verificaConexo(mtzAdj);

    if (par && conexo)
    {
        printf("O grafo eh Euleriano.\n");
    }
    else
    {
        printf("O grafo nao eh Euleriano.\n");
    }

    return 0;
}