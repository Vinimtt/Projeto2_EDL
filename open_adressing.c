#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CAPACIDADE 1000
#define TAM 50

typedef struct no{
    char chave[TAM];
    char variavel[TAM];
    int quantidade;
    struct no * prox;
}No;

typedef struct lista{
    No * inicio;
    No * fim;
}Lista;

No * hash[CAPACIDADE];

void inicializarHash(){
    for(int i = 0; i < CAPACIDADE; i++){
        hash[i] = NULL;
    }
}

void printar_lista(No* inicio) {
    No* atual = inicio;
    printf("Elementos da lista: ");
    
    while (atual != NULL) {
        printf("[%s, %d] -> ", atual->variavel, atual->quantidade);
        atual = atual->prox;
    }
    
    printf("NULL\n");
}

void printar_hash() {
    for (int i = 0; i < CAPACIDADE; ++i) {
        if (hash[i] != NULL) {
            printf("Indice %d: ", i);
            printar_lista(hash[i]);
        }
    }
}

int funcaohash(char nome[TAM]) {
    int i, soma = 0, tam = strlen(nome);

    for (i = 0; i < tam; i++) {
        soma += nome[i];
    }

    return abs(soma) % CAPACIDADE;
}

void inserir_hash(Lista* lista, char nome[TAM], int quantidade) {
    //acho que ta colocando um espaco a mais no final, se estiver, vai fuder a busca
    char nomeMaiusculo[TAM];
    for (int i = 0; i < TAM / 2; ++i) {
        nomeMaiusculo[i] = toupper(nome[i]);
        
    }
    nomeMaiusculo[strlen(nomeMaiusculo)] = '\0';

    int a = funcaohash(nomeMaiusculo);

    No* novoNo = (No*)malloc(sizeof(No));
    strcpy(novoNo->chave, nome);
    strcpy(novoNo->variavel, nomeMaiusculo);
    novoNo->quantidade = quantidade;
    novoNo->prox = NULL;

    if (hash[a] == NULL) {

        hash[a] = novoNo;
        lista->inicio = novoNo;
        lista->fim = novoNo;
    } else {

        lista->fim->prox = novoNo;
        lista->fim = novoNo;
    }
}

void remover_item(char * nome){

    char nomeMaiusculo[TAM];
    for (int i = 0; i < TAM / 2; ++i) {
        nomeMaiusculo[i] = toupper(nome[i]);
        
    }
    nomeMaiusculo[strlen(nomeMaiusculo)] = '\0';

    int a = funcaohash(nomeMaiusculo);
    No * atual = hash[a];
    No * ant = NULL;

    while (atual != NULL) {
        if (strcmp(atual->variavel, nomeMaiusculo) == 0) {
            if (ant == NULL) {

                hash[a] = atual->prox;
            } else {
                ant->prox = atual->prox;
            }
            free(atual);
            printf("Item %s removido\n", nome);
            return;
        }
        ant = atual;
        atual = atual->prox;
    }
    printf("Item %s não encontrado\n", nome);
}

void buscar_item(char * nome){

    char nomeMaiusculo[TAM];
    for (int i = 0; i < TAM / 2; ++i) {
        nomeMaiusculo[i] = toupper(nome[i]);
        
    }
    nomeMaiusculo[strlen(nomeMaiusculo)] = '\0';

    int a = funcaohash(nomeMaiusculo);
    No * atual = hash[a];
    No * ant = NULL;

    while (atual != NULL) {
        if (strcmp(atual->variavel, nomeMaiusculo) == 0) {
            if (ant == NULL) {
                printf("Item %s encontrado no indice: %d\n", nomeMaiusculo, a);
                return;
            } else {
                ant->prox = atual->prox;
            }
        }
        ant = atual;
        atual = atual->prox;
    }
    printf("Item %s nao encontrado\n", nome);
}


void print_menu(){
    printf("\n1-Inserir item simples (ate 64)\n2-Inserir item especial\n3-Exibir bau\n4-Remover item\n5-Buscar item\n0-Sair\n");
}


int main() {
    Lista lista = {NULL, NULL};
    char nome[TAM];
    int opcao, quantidade;

    inicializarHash();
    
    do{
        print_menu();
        scanf("%d",&opcao);
        getchar();

        switch(opcao){

            case 1:
            printf("Informe o nome do item\n");
            fgets(nome,TAM,stdin);
            nome[strlen(nome) - 1] = '\0';
            printf("Informe a quantidade de que voce deseja adicionar\n");
            scanf("%d", &quantidade);
            while(quantidade <= 0 || quantidade > 64){
                printf("Valor invalido! Informe um valor entre 1 e 64\n");
                scanf("%d",&quantidade);
            }
            inserir_hash(&lista,nome,quantidade);
            break;

            case 2:

            quantidade = 1;

            printf("Informe o nome do item\n");
            fgets(nome,TAM,stdin);
            nome[strlen(nome) - 1] = '\0';

            inserir_hash(&lista,nome,quantidade);
            break;

            case 3:

            printar_hash(lista);

            break;

            case 4:

            printf("Informe o nome do item que voce deseja remover\n");
            fgets(nome,TAM,stdin);
            nome[strlen(nome) - 1] = '\0';
            remover_item(nome);

            break;

            case 5:

            printf("Informe o nome do item que voce deseja procurar\n");
            fgets(nome,TAM,stdin);
            nome[strlen(nome) - 1] = '\0';
            buscar_item(nome);
            break;
        }

    }while(opcao != 0);
        
    return 0;    
}
