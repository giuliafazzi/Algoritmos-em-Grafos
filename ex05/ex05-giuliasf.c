#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

int n = 0;
int m = 0;

// encontrar maior valor
int maxVal(int peso[n], int cor[n])
{
    int i;

    int max = -1;
    int index = -1;

    for (i = 0; i < n; i++)
    {
        // verifica se o vértice ainda não foi incluído
        // e se o peso dele é maior que o máximo encontrado até então
        if (cor[i] == 0 && peso[i] > max)
        {
            // se satisfeitas as condições, atualiza os valores
            max = peso[i];
            index = i;
        }
    }

    return index;
}

// para encontrar a árvore geradora mínima, será utilizado o algoritmo de Prim,
// com uma modificação para encontrar o caminho máximo
void prim(int mtr[n][n])
{
    int i, j, u;

    // marcar numero de arestas inseridas
    // a árvore deve conter n - 1 arestas
    int cont = 0;

    // vetor para indicar vértices a serem incluídos na árvore
    // 0 para não incluído - 1 para incluído
    int *cor = malloc(n * sizeof(int));

    // peso da aresta mais pesada ligando x a outro vértice
    int *peso = malloc(n * sizeof(int));

    // predecessor de cada vértice
    int *pred = malloc(n * sizeof(int));

    // inicializa os vetores cor, peso e pred
    for (i = 0; i < n; i++)
    {
        peso[i] = -1;
        cor[i] = 0;
        pred[0] = -1;
    }

    // inicializa raiz (0)
    peso[0] = 0;
    pred[0] = -1;

    // executa até a árvore estar formada (n - 1 arestas)
    while (cont < n - 1)
    {
        // achar o vértice u de maior peso
        u = maxVal(peso, cor);

        // marca vértice como incluído
        cor[u] = 1;

        if (pred[u] != -1)
        {
            // atualiza a matriz com -1 para as arestas a serem incluídas na árvore
            // para essa implementação, foi considerada a ordem lexicográfica
            if (pred[u] < u)
            {
                mtr[pred[u]][u] = -1;
            }
            else
            {
                mtr[u][pred[u]] = -1;
            }

            // incrementa contador do número de arestas
            cont++;
        }

        for (j = 0; j < n; j++)
        {
            // verifica:
            // - se o vértice é adjacente
            // - se não está incluído na árvore
            // - se o peso é maior do que o peso atual salvo
            if (mtr[u][j] != 0 && cor[j] == 0 && peso[j] < mtr[u][j])
            {
                // se satisfeitas as condições, os vetores peso e pred são então atualizados
                peso[j] = mtr[u][j];
                pred[j] = u;
            }
        }
    }
}

void printMatriz(int mtr[n][n])
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            // printa somente as arestas que foram inseridas na AGM
            if (mtr[i][j] == -1)
            {
                printf("%d %d\n", i, j);
            }
        }
    }
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
        mtzAdj[b][a] = c;
    }

    // executa o algoritmo de prim para encontrar a AGM
    prim(mtzAdj);

    printMatriz(mtzAdj);

    return 0;
}