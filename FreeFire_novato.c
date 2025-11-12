#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10

// ==================== ESTRUTURA DE DADOS ====================
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// ==================== CABEÇALHO DAS FUNÇÕES ====================
void inserirItem(Item mochila[], int *total);
void removerItem(Item mochila[], int *total);
void listarItens(Item mochila[], int total);
void buscarItem(Item mochila[], int total);

// ==================== FUNÇÃO PRINCIPAL ====================
int main() {
    Item mochila[MAX_ITENS];
    int total = 0;
    int opcao;

    do {
        printf("\n===== SISTEMA DE INVENTÁRIO =====\n");
        printf("1. Adicionar item\n");
        printf("2. Remover item\n");
        printf("3. Listar itens\n");
        printf("4. Buscar item\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // limpa o buffer de entrada

        switch (opcao) {
            case 1:
                inserirItem(mochila, &total);
                break;
            case 2:
                removerItem(mochila, &total);
                break;
            case 3:
                listarItens(mochila, total);
                break;
            case 4:
                buscarItem(mochila, total);
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }

    } while (opcao != 0);

    return 0;
}

// ==================== FUNÇÃO INSERIR ITEM ====================
void inserirItem(Item mochila[], int *total) {
    if (*total >= MAX_ITENS) {
        printf("\n⚠️ Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novo;
    printf("\n--- CADASTRO DE ITEM ---\n");
    printf("Nome do item: ");
    fgets(novo.nome, sizeof(novo.nome), stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0'; // remove o \n final

    printf("Tipo do item (arma, munição, cura, etc): ");
    fgets(novo.tipo, sizeof(novo.tipo), stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);
    getchar(); // limpa buffer

    mochila[*total] = novo;
    (*total)++;

    printf("\n✅ Item adicionado com sucesso!\n");
    listarItens(mochila, *total);
}

// ==================== FUNÇÃO REMOVER ITEM ====================
void removerItem(Item mochila[], int *total) {
    if (*total == 0) {
        printf("\n⚠️ Mochila vazia! Nenhum item para remover.\n");
        return;
    }

    char nomeRemover[30];
    printf("\nDigite o nome do item a ser removido: ");
    fgets(nomeRemover, sizeof(nomeRemover), stdin);
    nomeRemover[strcspn(nomeRemover, "\n")] = '\0';

    int encontrado = 0;
    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nomeRemover) == 0) {
            encontrado = 1;
            for (int j = i; j < *total - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*total)--;
            printf("\n🗑️  Item '%s' removido com sucesso!\n", nomeRemover);
            break;
        }
    }

    if (!encontrado) {
        printf("\n❌ Item não encontrado!\n");
    }

    listarItens(mochila, *total);
}

// ==================== FUNÇÃO LISTAR ITENS ====================
void listarItens(Item mochila[], int total) {
    printf("\n--- ITENS NA MOCHILA (%d/%d) ---\n", total, MAX_ITENS);
    printf("------------------------------------------------------\n");
    printf("NOME            | TIPO           | QUANTIDADE\n");
    printf("------------------------------------------------------\n");

    if (total == 0) {
        printf("Nenhum item cadastrado.\n");
    } else {
        for (int i = 0; i < total; i++) {
            printf("%-15s | %-15s | %d\n",
                   mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
        }
    }

    printf("------------------------------------------------------\n");
}

// ==================== FUNÇÃO BUSCAR ITEM ====================
void buscarItem(Item mochila[], int total) {
    if (total == 0) {
        printf("\n⚠️ Mochila vazia! Nenhum item para buscar.\n");
        return;
    }

    char nomeBusca[30];
    printf("\nDigite o nome do item para buscar: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n--- ITEM ENCONTRADO ---\n");
            printf("Nome: %s\n", mochila[i].nome);
            printf("Tipo: %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            printf("------------------------\n");
            return;
        }
    }

    printf("\n❌ Item '%s' não encontrado na mochila.\n", nomeBusca);
}
