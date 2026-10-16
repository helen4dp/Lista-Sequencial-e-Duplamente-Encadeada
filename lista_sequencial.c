#include "ListaComCursor.h"
#include<stdlib.h>

struct lista_cursor {
    int quantidade;
    int p_cursor;
    int *dados;
    int cap;                                                        // Adicionando a variavel capacidade
};

static int garante_capacidade(ListaCursor *l){                     // Função para garantir que o vetor suporte quantas entradas forem necessárias
    if (!l) {return 0;}                                            // Verificando se a lista foi criada
    if(l->quantidade < l->cap){return 1;}                          // verificando se já existe espaço

    // Alocando espaco:

    // Caso 1) Os dados ainda não foram inicializados
    if(l->cap == 0){

        l->dados = malloc(8*sizeof(*l->dados));
		if (!l->dados) {return 0;}                               // erro

        l->cap = 8;
    }

    // Caso 2) Os dados já foram inicializados, dobrando a capacidade:
    else {
        int nova_cap = 2*l->cap;
        int *novo = realloc(l->dados, nova_cap * sizeof(*l->dados));

        if(!novo){return 0;}                                                    // Verificando se deu certo

        l->dados = novo;
        l->cap = nova_cap;
    }

    // tudo certo, há espaço para inserções:
    return 1;
}


ListaCursor* criar_lista(void){
    ListaCursor *l = malloc(sizeof(ListaCursor));
    if(l == NULL) return NULL;

    l->dados = NULL;                                                // inicializando dados
    l->cap = 0;                                                     // inicializando cap
    l->quantidade = 0;
    l->p_cursor = 0;

    return l;
}

void destruir_lista(ListaCursor* l){
    if(l == NULL) return;

    free(l->dados);                                                 // liberando dados
    free(l);

    return;
}

void mover_inicio(ListaCursor* l){
    if(l == NULL) return;

    l->p_cursor = 0;
    return;
}

void mover_fim(ListaCursor* l){
    if(l == NULL) return;

    if(l->quantidade == 0) return;

    l->p_cursor =  l->quantidade  - 1;


    return;
}

int avancar_cursor(ListaCursor* l){
    if(l == NULL) return -1;
    if(l->p_cursor + 1 >= l->quantidade) return 0;
    l->p_cursor++;
    return 1;
}

int retroceder_cursor(ListaCursor* l){
    if(l == NULL) return -1;
    if(l->p_cursor - 1 < 0) return 0;

    l->p_cursor--;

    return 1;
}

int mover_para_indice(ListaCursor* l, int indice){
    if(l == NULL) return -1;

    if(indice < 0 || indice >= l->quantidade) return 0;
    
    l->p_cursor = indice;

    return 1;
}

 int obter_atual(ListaCursor* l, int* valor_saida){

        if(l == NULL) return -1;

        if(valor_saida == NULL) return -1;

        if(l->quantidade == 0) return 0;
        if(l->p_cursor >= l->quantidade || l->p_cursor < 0) return 0;

        *valor_saida = l->dados[l->p_cursor];

        return 1;
 }

 int inserir_antes(ListaCursor* l, int valor){

    if(l == NULL) return -1;

    if (garante_capacidade(l) != 1){return 0;}                         // garantindo que o vetor term capacidade para nova alocação

    // Caso 1) Lista vazia
    if(l->quantidade == 0){
        l->dados[0] = valor;
        l->p_cursor = 0;                                            // o cursor fica no novo elemento, que é unico
        l->quantidade = 1;

        return 1;
    }

    for(int i = l->quantidade; i > l->p_cursor; i--) { l->dados[i] = l->dados[i - 1];}

    l->dados[l->p_cursor] = valor;
    l->p_cursor++;                                          // o elemento antigo do cursor foi empurrado para a direita
    l->quantidade++;

    return 1;
 }

int inserir_depois(ListaCursor* l, int valor){
    if(l == NULL) return -1;

    if (garante_capacidade(l) != 1){return 0;}                         // garantindo que o vetor term capacidade para nova alocação
    
    int posicao_posterior = l->p_cursor + 1;

    if(posicao_posterior > l->quantidade) posicao_posterior = l->quantidade;

    for(int i = l->quantidade; i > posicao_posterior; i--){
        l->dados[i] = l->dados[i - 1];
    }
    l->dados[posicao_posterior] = valor;
    l->quantidade++;
    return 1;
}

int remover_atual(ListaCursor* l){
    if(l == NULL) return -1;

    if(l->quantidade == 0) return 0;

    for(int i = l->p_cursor; i < l->quantidade - 1; i++){
        l->dados[i] = l->dados[i+1];
    }

    l->quantidade--;

    if(l->quantidade == 0)
        l->p_cursor = 0;
    else if(l->p_cursor == l->quantidade){
        l->p_cursor--;
    } 

    return 1;
}

int tamanho_lista(ListaCursor* l){
    if(l == NULL) return -1;
    return l->quantidade;
}
