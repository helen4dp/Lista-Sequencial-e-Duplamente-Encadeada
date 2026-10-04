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

