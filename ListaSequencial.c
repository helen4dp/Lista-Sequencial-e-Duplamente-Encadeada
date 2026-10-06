#define MAX 50
#include<stdlib.h>

typedef struct lista_cursor {
    int quantidade;
    int p_cursor;
    int dados[MAX];
} ListaCursor;

ListaCursor* criar_lista(void){
    ListaCursor *l = malloc(sizeof(ListaCursor));
    if(l == NULL) return NULL;

    l->quantidade = 0;
    l->p_cursor = 0;

    return l;
}

void destruir_lista(ListaCursor* l){
    if(l == NULL) return;

    free(l);
    l = NULL;

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

    if(l->quantidade >= MAX) return 0;
    int posicao_anterior = l->p_cursor;

    if(posicao_anterior < 0) posicao_anterior = 0;


    for(int i = l->quantidade; i > posicao_anterior; i--){
        l->dados[i] = l->dados[i - 1];
    }
    l->dados[posicao_anterior] = valor;
    l->p_cursor++;
    l->quantidade++;

    return 1;

 }

int inserir_depois(ListaCursor* l, int valor){
    if(l == NULL) return -1;

    if(l->quantidade >= MAX) return 0;
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
