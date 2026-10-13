
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "ListaComCursor.h"

#define NUM_EXECUCOES 10
#define NUM_TAMANHOS 5
#define NUM_OPERACOES 100

// tamanhos de lista pedidos pelo prof
int tamanhos[NUM_TAMANHOS] = {1000, 50000, 100000, 500000, 1000000};

// calcula o tempo gasto em nanossegundos
double calcula_tempo(LARGE_INTEGER inicio, LARGE_INTEGER fim, LARGE_INTEGER freq)
{
    return (double)(fim.QuadPart - inicio.QuadPart) * 1000000000.0 / (double)freq.QuadPart;
}

static int rand_grande(void)
{
    return (rand() << 15) | rand();  //combinando os campos de bits 15 a 29 e 0 a 14
}


// Cria uma lista e preenche com os valores de 0 ate n - 1
// A criacao e o preenchimento ficam fora da medição
ListaCursor *prepara_lista(int n)
{
    ListaCursor *l = criar_lista();


    if (!l)
    {
        return NULL;
    }

    // Insere os elementos na lista
    for (int i = 0; i < n; i++)
    {
        int sucesso;

        if (i == 0)
        {
            sucesso = inserir_antes(l, i);
        }
        else
        {
            mover_fim(l);
            sucesso = inserir_depois(l, i);
        }

        // Se a insercao falhar, libera a lista
        if (sucesso != 1)
        {
            destruir_lista(l);
            return NULL;
        }
    }

    // Deixa o cursor no inicio da lista
    mover_inicio(l);

    return l;
}

// 1. Mede o tempo de 100 insercoes no inicio da lista
double testa_insercao_inicio(int n, LARGE_INTEGER freq)
{
    double soma_tempos = 0.0;

    // Repete o teste 10 vezes
    for (int exec = 0; exec < NUM_EXECUCOES; exec++)
    {
        // Cria uma lista nova para cada execucao
        ListaCursor *l = prepara_lista(n);

        if (!l)
        {
            return -1.0;//como é double,  devolver -1.0
        }

        LARGE_INTEGER inicio, fim;

        // Inicia a medicao
        QueryPerformanceCounter(&inicio);

        // Insere 100 elementos no inicio da lista
        for (int i = 0; i < NUM_OPERACOES; i++)
        {
            mover_inicio(l);

            if (inserir_antes(l, -i - 1) != 1)
            {
                destruir_lista(l);
                return -1.0;
            }
        }

        // Finaliza a medicao
        QueryPerformanceCounter(&fim);

        // Soma o tempo dessa execucao
        soma_tempos += calcula_tempo(inicio, fim, freq);

        // Libera a lista fora da medicao
        destruir_lista(l);
    }

    // Retorna o tempo medio das execucoes
    return soma_tempos / NUM_EXECUCOES;
}

// 2. Mede 100 acessos a indices aleatorios da lista
double testa_acesso_indice(int n, LARGE_INTEGER freq, const int indices[])
{
    double soma_tempos = 0.0;

    // Repete o teste 10 vezes
    for (int exec = 0; exec < NUM_EXECUCOES; exec++)
    {
        // Cria uma lista nova para cada execucao
        ListaCursor *l = prepara_lista(n);

        if (!l)
        {
            return -1.0;
        }

        LARGE_INTEGER inicio, fim;
        int valor;

        // Inicia a medicao
        QueryPerformanceCounter(&inicio);

        // Percorre os indices previamente gerados
        for (int i = 0; i < NUM_OPERACOES; i++)
        {
            // Move o cursor para o indice e consulta seu valor
            if (!mover_para_indice(l, indices[i]) || !obter_atual(l, &valor))
            {
                destruir_lista(l);
                return -1.0;
            }
        }

        // Finaliza a medicao
        QueryPerformanceCounter(&fim);

        // Soma o tempo da execucao
        soma_tempos += calcula_tempo(inicio, fim, freq);

        // Libera a lista
        destruir_lista(l);
    }

    // Retorna o tempo medio
    return soma_tempos / NUM_EXECUCOES;
}

// 3. Mede 100 remocoes consecutivas a partir do inicio
double testa_remocao_inicio(int n, LARGE_INTEGER freq)
{
    double soma_tempos = 0.0;

    // Repete o teste 10 vezes
    for (int exec = 0; exec < NUM_EXECUCOES; exec++)
    {
        // Cria uma lista nova para cada execucao
        ListaCursor *l = prepara_lista(n);

        if (!l)
        {
            return -1.0;
        }

        // Posiciona o cursor antes de iniciar a medicao
        mover_inicio(l);

        LARGE_INTEGER inicio, fim;

        // Inicia a medicao
        QueryPerformanceCounter(&inicio);

        // Remove 100 elementos sem reposicionar o cursor
        for (int i = 0; i < NUM_OPERACOES; i++)
        {
            if (remover_atual(l) != 1)
            {
                destruir_lista(l);
                return -1.0;
            }
        }

        // Finaliza a medicao
        QueryPerformanceCounter(&fim);

        // Soma o tempo 
        soma_tempos += calcula_tempo(inicio, fim, freq);

        // Libera a lista 
        destruir_lista(l);
    }

    // Retorna o tempo medio
    return soma_tempos / NUM_EXECUCOES;
}

// 4. Mede 100 remocoes consecutivas a partir do meio
double testa_remocao_meio(int n, LARGE_INTEGER freq)
{
    double soma_tempos = 0.0;

    // Repete o teste 10 vezes
    for (int exec = 0; exec < NUM_EXECUCOES; exec++)
    {
        // Cria uma lista nova para cada execucao
        ListaCursor *l = prepara_lista(n);

        if (!l)
        {
            return -1.0;
        }

        // Posiciona o cursor no indice central antes da medicao
        if (!mover_para_indice(l, n / 2))
        {
            destruir_lista(l);
            return -1.0;
        }

        LARGE_INTEGER inicio, fim;

        // Inicia a medicao
        QueryPerformanceCounter(&inicio);

        // Remove 100 elementos sem reposicionar o cursor
        for (int i = 0; i < NUM_OPERACOES; i++)
        {
            if (remover_atual(l) != 1)
            {
                destruir_lista(l);
                return -1.0;
            }
        }

        // Finaliza a medicao
        QueryPerformanceCounter(&fim);

        // Soma o tempo 
        soma_tempos += calcula_tempo(inicio, fim, freq);

        // Libera a lista fora da medicao
        destruir_lista(l);
    }

    // Retorna o tempo medio 
    return soma_tempos / NUM_EXECUCOES;
}

// 5. Mede o tempo para percorrer todos os elementos da lista
double testa_percurso(int n, LARGE_INTEGER freq)
{
    double soma_tempos = 0.0;

    // Repete o teste 10 vezes
    for (int exec = 0; exec < NUM_EXECUCOES; exec++)
    {
        // Cria uma lista nova para cada execucao
        ListaCursor *l = prepara_lista(n);

        if (!l)
        {
            return -1.0;
        }

        // Posiciona o cursor no inicio antes da medicao
        mover_inicio(l);

        LARGE_INTEGER inicio, fim;
        int valor;

        // Inicia a medicao
        QueryPerformanceCounter(&inicio);

        // Consulta o elemento atual e avanca ate o final
        do
        {
            if (!obter_atual(l, &valor))
            {
                destruir_lista(l);
                return -1.0;
            }
        } while (avancar_cursor(l));

        // Finaliza a medicao
        QueryPerformanceCounter(&fim);

        // Soma o tempo desta execucao
        soma_tempos += calcula_tempo(inicio, fim, freq);

        // Libera a lista fora da medicao
        destruir_lista(l);
    }

    // Retorna o tempo medio das execucoes
    return soma_tempos / NUM_EXECUCOES;
}

int main(void)
{
    LARGE_INTEGER freq;

    // Define uma seed p/ gerar numeros aleatorios
    srand(12345);

    // Obtém a frequencia do contador de alta precisao do Windows
    if (!QueryPerformanceFrequency(&freq))
    {
        printf("Erro ao obter a frequencia\n");
        return 1;
    }

    // Printa um menu dos resultados
    printf("n - ins_inicio - acesso_ind - rem_inicio - rem_meio - percurso\n");

    FILE *arq = fopen("resultados_testes.csv", "w");
        if(!arq){
            printf("Nao foi possível gerar o .csv\n");
            return -1;
        }

    //escrevendo menu no .csv
    fprintf(arq,"n,ins_inicio,acesso_ind,rem_inicio,rem_meio,percurso\n");

    // Executa os testes para cada tamanho de lista
    for (int i = 0; i < NUM_TAMANHOS; i++)
    {
        int n = tamanhos[i];
        int indices[NUM_OPERACOES];

        // Gera 100 indices aleatorios antes da medicao
        for (int j = 0; j < NUM_OPERACOES; j++)
        {
            indices[j] = rand_grande() % n;
        }

        // Executa cada teste e guarda seu tempo medio
        double t1 = testa_insercao_inicio(n, freq);
        double t2 = testa_acesso_indice(n, freq, indices);
        double t3 = testa_remocao_inicio(n, freq);
        double t4 = testa_remocao_meio(n, freq);
        double t5 = testa_percurso(n, freq);

        // Verifica se algum teste falhou
        if (t1 < 0 || t2 < 0 || t3 < 0 || t4 < 0 || t5 < 0)
        {
            printf("Erro ao executar os testes\n");
            return 1;
        }

        // Printa os tempos medios em nanossegundos
        printf("%d - %.2f - %.2f - %.2f - %.2f - %.2f\n", n, t1, t2, t3, t4, t5);
        
        //passando para o .csv
        fprintf(arq,"%d,%.2f,%.2f,%.2f,%.2f,%.2f\n", n, t1, t2, t3, t4, t5);
    }

    printf("FIM.");
    fclose(arq);
    return 0;
}