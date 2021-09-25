#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

int n = 0;
int m = 0;

int buscaProfundidade(int mtr[n][n], int tempos[n], int dias[n], int u)
{
    int v, i, tmp;

    // vetor para indicar quais vértices já foram visitados
    // 0 para não visitado - 1 para visitado - 2 explorado
    int *cor = malloc(n * sizeof(int));

    // marcar todos os vértices como não visitados
    // inicializa dias como o original
    for (i = 0; i < n; i++)
    {
        cor[i] = 0;
    }

    // printf("dias\n");
    // imprimeVetor(dias);

    // inicialmente, o tempo máximo do projeto é o tempo informado
    int tempoMax = tempos[u];

    // marca vértice como visitado
    cor[u] = 1;

    // printf("vertice %d\n", u);
    // printf("tempo %d\n", tempos[u]);

    for (v = 0; v < n; v++)
    {
        // verifica se o vértice é adj. e se ainda não foi visitado
        if (mtr[u][v] != 0 && cor[v] == 0)
        {
            // printf("%d adj de %d\n", v, u);
            tmp = buscaProfundidade(mtr, tempos, dias, v);

            if (tempoMax < tempos[u] + tmp)
            {
                tempoMax = tempos[u] + tmp;
                // printf("tempo max %d + %d: %d\n", u, v, tempoMax);
            }
        }
    }

    // marca vértice como explorado
    cor[u] = 2;

    dias[u] = tempoMax;

    free(cor);

    return tempoMax;
}

// para a obtenção da ordenação topológica, será utilizado o algoritmo de busca em profundidade
int ordenacaoTopologica(int mtr[n][n], int tempos[n])
{
    int i, t;

    int max = 0;

    int *dias = malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
    {
        dias[i] = 0;
    }

    // percorre todos os vértices
    for (i = 0; i < n; i++)
    {
        // faz a busca nos vértices que ainda não foram visitados

        // FILTRAR SÓ FONTES
        // printf("-------------- novo\n");
        t = buscaProfundidade(mtr, tempos, dias, i);

        if (max < t)
        {
            max = t;
        }
    }

    free(dias);

    return max;
}

int main()
{
    int i, j, u, v;

    // receber n (num de vértices/cruzamentos) e m (num de arestas/trechos)
    scanf("%d %d", &n, &m);

    // criar matrz para n vértices
    int mtzAdj[n][n];
    // criar vetor para tempo estimados de cada projeto
    int tempos[n];

    // tempos estimados de conclusão
    for (i = 0; i < n; i++)
    {
        scanf("%d", &tempos[i]);
    }

    // inicializa matriz com 0 para todos os vértices
    // multiplica tempos por -1, para auxiliar na execução do algoritmo
    // (o algoritmo irá considerar então o maior tempo, visto que está multiplicado por -1)
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            mtzAdj[i][j] = 0;
        }
        // tempos[i] *= -1;
    }

    // adiciona arestas na matriz
    for (i = 0; i < m; i++)
    {
        scanf("%d %d", &u, &v);
        mtzAdj[u][v] = 1;
    }

    printf("%d\n", ordenacaoTopologica(mtzAdj, tempos));

    return 0;
}