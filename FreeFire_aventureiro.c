#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==================== DEFINIÇÃO DAS STRUCTS ====================

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Nó para lista encadeada
typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// ==================== VARIÁVEIS GLOBAIS ====================
#define MAX_ITENS 10

Item mochilaVetor[MAX_ITENS];
int totalVetor = 0;

No* cabecaLista = NULL;

// Contadores de comparações
int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

// ==================== FUNÇÕES VETOR ====================

void inserirItemVetor() {
    if (totalVetor >= MAX_ITENS) {
        printf("Mochila cheia!\n");
        return;
    }
    Item novo;
    printf("Nome do item: ");
    scanf("%s", novo.nome);
    printf("Tipo (arma/municao/cura): ");
    scanf("%s", novo.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochilaVetor[totalVetor++] = novo;
    printf("Item inserido no vetor!\n");
}

void removerItemVetor() {
    if (totalVetor == 0) {
        printf("Mochila vazia!\n");
        return;
    }
    char nome[30];
    printf("Nome do item a remover: ");
    scanf("%s", nome);

    int i, encontrado = 0;
    for (i = 0; i < totalVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            encontrado = 1;
            break;
        }
    }
    if (encontrado) {
        for (int j = i; j < totalVetor - 1; j++) {
            mochilaVetor[j] = mochilaVetor[j + 1];
        }
        totalVetor--;
        printf("Item removido!\n");
    } else {
        printf("Item não encontrado.\n");
    }
}

void listarItensVetor() {
    printf("\n--- ITENS NA MOCHILA (%d/%d) ---\n", totalVetor, MAX_ITENS);
    printf("-------------------------------------------------------------\n");
    printf("NOME           | TIPO       | QUANTIDADE\n");
    printf("-------------------------------------------------------------\n");
    for (int i = 0; i < totalVetor; i++) {
        printf("%-14s | %-10s | %9d\n",
               mochilaVetor[i].nome,
               mochilaVetor[i].tipo,
               mochilaVetor[i].quantidade);
    }
    printf("-------------------------------------------------------------\n");
}

// Ordenação por nome (Bubble Sort)
void ordenarVetor() {
    for (int i = 0; i < totalVetor - 1; i++) {
        for (int j = i + 1; j < totalVetor; j++) {
            if (strcmp(mochilaVetor[i].nome, mochilaVetor[j].nome) > 0) {
                Item temp = mochilaVetor[i];
                mochilaVetor[i] = mochilaVetor[j];
                mochilaVetor[j] = temp;
            }
        }
    }
}

// Busca sequencial
int buscarSequencialVetor(char nome[]) {
    comparacoesSequencial = 0;
    for (int i = 0; i < totalVetor; i++) {
        comparacoesSequencial++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1;
}

// Busca binária (vetor deve estar ordenado)
int buscarBinariaVetor(char nome[]) {
    comparacoesBinaria = 0;
    int inicio = 0, fim = totalVetor - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        comparacoesBinaria++;
        int cmp = strcmp(mochilaVetor[meio].nome, nome);
        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

// ==================== FUNÇÕES LISTA ENCADEADA ====================

void inserirItemLista() {
    Item novo;
    printf("Nome do item: ");
    scanf("%s", novo.nome);
    printf("Tipo (arma/municao/cura): ");
    scanf("%s", novo.tipo);
    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->dados = novo;
    novoNo->proximo = cabecaLista;
    cabecaLista = novoNo;

    printf("Item inserido na lista!\n");
}

void removerItemLista() {
    if (!cabecaLista) {
        printf("Mochila vazia!\n");
        return;
    }
    char nome[30];
    printf("Nome do item a remover: ");
    scanf("%s", nome);

    No* atual = cabecaLista;
    No* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL) { // Remover cabeça
                cabecaLista = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            printf("Item removido da lista!\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Item não encontrado na lista.\n");
}

void listarItensLista() {
    int count = 0;
    No* atual = cabecaLista;
    while (atual != NULL) {
        count++;
        atual = atual->proximo;
    }

    printf("\n--- ITENS NA MOCHILA (%d/10) ---\n", count);
    printf("-------------------------------------------------------------\n");
    printf("NOME           | TIPO       | QUANTIDADE\n");
    printf("-------------------------------------------------------------\n");

    atual = cabecaLista;
    while (atual != NULL) {
        printf("%-14s | %-10s | %9d\n",
               atual->dados.nome,
               atual->dados.tipo,
               atual->dados.quantidade);
        atual = atual->proximo;
    }
    printf("-------------------------------------------------------------\n");
}

// Busca sequencial em lista encadeada
No* buscarSequencialLista(char nome[]) {
    comparacoesSequencial = 0;
    No* atual = cabecaLista;
    while (atual != NULL) {
        comparacoesSequencial++;
        if (strcmp(atual->dados.nome, nome) == 0)
            return atual;
        atual = atual->proximo;
    }
    return NULL;
}

// ==================== MENU PRINCIPAL ====================

int main() {
    int opcao, estrutura;
    char nomeBusca[30];

    do {
        printf("\nEscolha a estrutura de dados:\n1. Vetor\n2. Lista Encadeada\n0. Sair\nOpcao: ");
        scanf("%d", &estrutura);

        if (estrutura == 0) break;

        do {
            printf("\n--- Menu ---\n");
            printf("1. Inserir item\n");
            printf("2. Remover item\n");
            printf("3. Listar itens\n");
            printf("4. Buscar item\n");
            printf("0. Voltar\n");
            printf("Opcao: ");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    if (estrutura == 1) inserirItemVetor();
                    else inserirItemLista();
                    break;
                case 2:
                    if (estrutura == 1) removerItemVetor();
                    else removerItemLista();
                    break;
                case 3:
                    if (estrutura == 1) listarItensVetor();
                    else listarItensLista();
                    break;
                case 4:
                    printf("Nome do item a buscar: ");
                    scanf("%s", nomeBusca);
                    if (estrutura == 1) {
                        ordenarVetor(); // ordenar para busca binaria
                        int posSeq = buscarSequencialVetor(nomeBusca);
                        int posBin = buscarBinariaVetor(nomeBusca);

                        if (posSeq != -1) {
                            printf("[Sequencial] Item encontrado: %s (%s, %d) Comparacoes: %d\n",
                                   mochilaVetor[posSeq].nome, mochilaVetor[posSeq].tipo,
                                   mochilaVetor[posSeq].quantidade, comparacoesSequencial);
                        } else printf("[Sequencial] Item nao encontrado.\n");

                        if (posBin != -1) {
                            printf("[Binaria] Item encontrado: %s (%s, %d) Comparacoes: %d\n",
                                   mochilaVetor[posBin].nome, mochilaVetor[posBin].tipo,
                                   mochilaVetor[posBin].quantidade, comparacoesBinaria);
                        } else printf("[Binaria] Item nao encontrado.\n");
                    } else {
                        No* achado = buscarSequencialLista(nomeBusca);
                        if (achado)
                            printf("[Sequencial] Item encontrado: %s (%s, %d) Comparacoes: %d\n",
                                   achado->dados.nome, achado->dados.tipo,
                                   achado->dados.quantidade, comparacoesSequencial);
                        else printf("[Sequencial] Item nao encontrado.\n");
                    }
                    break;
                case 0:
                    break;
                    
                default:
                    printf("Opcao invalida!\n");
            }
        } while (opcao != 0);

    } while (estrutura != 0);

    printf("Programa encerrado.\n");
    return 0;
}