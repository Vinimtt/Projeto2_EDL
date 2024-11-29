#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CAPACIDADE 1000
#define TAM 50

typedef struct no {
    char chave[TAM];
    int quantidade;
    int ocupado; // estado da posicao
} No;

No hash[CAPACIDADE];

void inicializarHash() {
    for (int i = 0; i < CAPACIDADE; i++) {
        hash[i].ocupado = 0; 
    }
}

int funcaohash(char nome[TAM]) {
    int soma = 0, tam = strlen(nome);

    for (int i = 0; i < tam; i++) {
        soma += nome[i];
    }

    return abs(soma) % CAPACIDADE;
}

int sondagemLinear(int posicaoInicial) {
    int i = posicaoInicial;

    while (hash[i].ocupado == 1) {
        i = (i + 1) % CAPACIDADE;
        if (i == posicaoInicial) {
            return -1; //cheio
        }
    }

    return i;
}

void inserir_hash(char nome[TAM], int quantidade) {
    char nomeMaiusculo[TAM];
    for (int i = 0; i < TAM / 2 && nome[i] != '\0'; ++i) {
        nomeMaiusculo[i] = toupper(nome[i]);
    }
    nomeMaiusculo[strlen(nome)] = '\0';

    int posicao = funcaohash(nomeMaiusculo);
    int novaPosicao = sondagemLinear(posicao);

    if (novaPosicao == -1) {
        printf("Erro: tabela de hash cheia.\n");
        return;
    }

    strcpy(hash[novaPosicao].chave, nomeMaiusculo);
    hash[novaPosicao].quantidade = quantidade;
    hash[novaPosicao].ocupado = 1;
}

int buscar_item(char *nome) {
    char nomeMaiusculo[TAM];
    for (int i = 0; i < TAM / 2 && nome[i] != '\0'; ++i) {
        nomeMaiusculo[i] = toupper(nome[i]);
    }
    nomeMaiusculo[strlen(nome)] = '\0';

    int posicao = funcaohash(nomeMaiusculo);
    int i = posicao;

    while (hash[i].ocupado != 0) {
        if (hash[i].ocupado == 1 && strcmp(hash[i].chave, nomeMaiusculo) == 0) {
            printf("Item %s encontrado na posição %d\n", nomeMaiusculo, i);
            return i;
        }
        i = (i + 1) % CAPACIDADE;
        if (i == posicao) {
            break; // volta ao inicio
        }
    }

    printf("Item %s não encontrado\n", nomeMaiusculo);
    return -1;
}

void remover_item(char *nome) {
    int posicao = buscar_item(nome);

    if (posicao != -1) {
        hash[posicao].ocupado = -1; //remove
        printf("Item %s removido\n", nome);
    }
}

void printar_hash() {
    for (int i = 0; i < CAPACIDADE; ++i) {
        if (hash[i].ocupado == 1) {
            printf("Posição %d: [%s, %d]\n", i, hash[i].chave, hash[i].quantidade);
        }
    }
}

void print_menu() {
    printf("\n1-Inserir item simples (até 64)\n2-Inserir item especial\n3-Exibir hash\n4-Remover item\n5-Buscar item\n0-Sair\n");
}

int main() {
    char nome[TAM];
    int opcao, quantidade;

    inicializarHash();

    do {
        print_menu();
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("Informe o nome do item\n");
                fgets(nome, TAM, stdin);
                nome[strlen(nome) - 1] = '\0';
                printf("Informe a quantidade de que você deseja adicionar\n");
                scanf("%d", &quantidade);
                while (quantidade <= 0 || quantidade > 64) {
                    printf("Valor inválido! Informe um valor entre 1 e 64\n");
                    scanf("%d", &quantidade);
                }
                inserir_hash(nome, quantidade);
                break;

            case 2:
                quantidade = 1;
                printf("Informe o nome do item\n");
                fgets(nome, TAM, stdin);
                nome[strlen(nome) - 1] = '\0';
                inserir_hash(nome, quantidade);
                break;

            case 3:
                printar_hash();
                break;

            case 4:
                printf("Informe o nome do item que você deseja remover\n");
                fgets(nome, TAM, stdin);
                nome[strlen(nome) - 1] = '\0';
                remover_item(nome);
                break;

            case 5:
                printf("Informe o nome do item que você deseja procurar\n");
                fgets(nome, TAM, stdin);
                nome[strlen(nome) - 1] = '\0';
                buscar_item(nome);
                break;
        }

    } while (opcao != 0);

    return 0;
}
