#include <stdio.h>
#include <stdlib.h>
#include "ListaComCursor.h"

struct lista_cursor
{
    int qtd;
    Node *head;
    Node *butt;                                             // AHAHHAHAHA
    Node *cursor;

};

typedef struct node
{
    struct lista_cursor *next;
    struct lista_cursor *previous;
    int data;

} Node;




// ListaCursor* criar_lista(void);
ListaCursor *criar_lista(void){
    ListaCursor *l = malloc(sizeof(ListaCursor));                           // Alocar espaço na lista

    if(!l){return NULL}                                                     // Verificar se o espaço foi alocado 

    l->head = NULL;
    l->qtd = 0;                                                             // Lista criada porém vazia

    // Sucesso
    return l;

}

// void destruir_lista(ListaCursor* l);
ListaCursor *destruir_lista(ListaCursor *l){
    Node *temp;                                                              // poteiro temporario

    temp = l->head;

    while(temp != NULL)                       // loop para que rem sempre aponte para o node anterior do node que temp aponta
    {                                         // com isso, podemos remover da lista o node que rem aponta, sem perder a "ponta"
       Node *rem = temp;                    
       temp = temp->next;
       free(rem);
    }

    l = NULL;
}


// void mover_inicio(ListaCursor* l);
ListaCursor *mover_inicio(ListaCursor *l){
    l->cursor = l->head;
}

// void mover_fim(ListaCursor* l);
ListaCursor *mover_fim(ListaCursor *l){
    l->cursor = l->butt;
}


// int avancar_cursor(ListaCursor* l);
ListaCursor *avancar_cursor(ListaCursor *l){
    if(l->head == NULL){return 0;}                              // checando se a lista está vazia

    Node *temp = l->cursor;
    if(temp->next == NULL){return 0;}                          // checando se o cursor não está no fim da lista

    l->cursor = temp->next;                                     // se não, avança o cursor um nó pra frente
    return 1;
}


// int retroceder_cursor(ListaCursor* l);
ListaCursor *retroceder_cursor(ListaCursor *l){
    if (l->cursor == l->head){return 0;}                        // checando se está no inicio da lista
    if(l->head == NULL){return 0;}                              // checando se a lista está vazia

    Node *temp = l->cursor;
    l->cursor = temp->previous;                                 // retrocede o cursor
    return 1;
}


// int mover_para_indice(ListaCursor* l, int indice);
ListaCursor *mover_para_indice(ListaCursor *l, int indice){
    if(l->head == NULL){return 0;}                                  // checando se a lista está vazia
    if(indice < 0 || indice >= l->qtd){return 0;}                   // checando se o indice é válido

    Node *temp = l->head;
    for (int i = 0; i < indice; i++){
        temp = temp->next;
    }
    l->cursor = temp;
    return 1;
}

// Consulta
// Retorna 1 se obteve o valor; 0 se a lista esta vazia.
// Em caso de retorno 0, *valor_saida permanece inalterado.
int obter_atual(ListaCursor* l, int* valor_saida){
    if(l == NULL) return -1;
    Node *atual;
    atual = l->cursor;
    *valor_saida = atual->data;

    return 1;
}

 // Insere antes do cursor
int inserir_antes(ListaCursor* l, int valor){
    if(l == NULL) return -1;
    
    Node *novo = malloc(sizeof(Node));
    if(novo == NULL) return -1;
    novo->data = valor;

    // Caso lista vazia
    if(l->cursor == NULL){
        l->head = novo;
        l->cursor = novo;
        l->butt = novo;
        l->qtd = 1;
        novo->next = NULL;
        novo->previous = NULL;
        return 1;
    }


    Node *atual;
    atual = l->cursor;

    Node *anterior;
    anterior = atual->previous;

    novo->previous = anterior;
    novo->next = atual;
    atual->previous = novo;
    l->qtd++;

    // Caso o cursor aponte para o primeiro elemento
    if(anterior == NULL){
        l->head = novo;
    } else{
            anterior->next = novo;
    }

    return 1;
} 

// Insere depois do cursor
int inserir_depois(ListaCursor* l, int valor){
    if(l == NULL) return -1;

    Node *novo = malloc(sizeof(Node));
    if(novo == NULL) return -1;
    novo->data = valor;


    // Caso a lista esteja vazia
    if(l->cursor == NULL){
        l->head = novo;
        l->cursor = novo;
        l->butt = novo;
        l->qtd = 1;
        novo->next = NULL;
        novo->previous = NULL;
        return 1;
    }

    // Caso geral
    Node *atual = l->cursor;
    Node *proximo = atual->next;
    
    atual->next = novo;
    novo->previous = atual;
    novo->next = proximo;

    l->qtd++;

    // Caso inserção no final
    if(proximo == NULL){
        l->butt = novo;
    } else{
        proximo->previous = novo;

    }

    return 1;
     
}

// Retorna tamanho da lista;
int tamanho_lista(ListaCursor* l){
    if(l == NULL) return -1;
    return l->qtd;
}

// Remove o elemento atual
int remover_atual(ListaCursor* l){
    if(l == NULL) return -1;

    Node *atual = l->cursor;
    Node *proximo = atual->next;
    Node *anterior = atual->previous;


    // Caso cursor aponte para o primeiro elemento
    if(atual->previous == NULL){
        l->head = proximo;
    } else {
            anterior->next = proximo;
    }

    // Caso cursor aponte para o último
    if(proximo == NULL){
        l->butt = anterior;
    } else {
            proximo->previous = anterior;
    }


    if(proximo == NULL){
        l->cursor = anterior;
    } else {
        l->cursor = proximo;
    }

    free(atual);
    atual = NULL;
    l->qtd--;

    return 1;

}  


