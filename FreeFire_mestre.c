#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 10

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade;
} Componente;

// ===============================
// Funções auxiliares
// ===============================
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void mostrarInventario(Componente v[], int n) {
    if (n == 0) {
        printf("\n--- Mochila vazia. Nenhum componente coletado. ---\n");
        return;
    }

    printf("\n--- INVENTARIO ATUAL (%d/%d) ---\n", n, MAX);
    printf("--------------------------------------------------------------\n");
    printf("%-15s | %-12s | %-10s | %-10s\n", "NOME", "TIPO", "QUANTIDADE", "PRIORIDADE");
    printf("--------------------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("%-15s | %-12s | %-10d | %-10d\n",
               v[i].nome, v[i].tipo, v[i].quantidade, v[i].prioridade);
    }

    printf("--------------------------------------------------------------\n");
}

// ===============================
// Algoritmos de ordenação
// ===============================
int bubbleSortNome(Componente v[], int n) {
    int comp = 0;
    Componente temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comp++;
            if (strcmp(v[j].nome, v[j + 1].nome) > 0) {
                temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
    return comp;
}

int insertionSortTipo(Componente v[], int n) {
    int comp = 0;
    Componente chave;
    int j;
    for (int i = 1; i < n; i++) {
        chave = v[i];
        j = i - 1;
        while (j >= 0 && strcmp(v[j].tipo, chave.tipo) > 0) {
            v[j + 1] = v[j];
            j--;
            comp++;
        }
        v[j + 1] = chave;
    }
    return comp;
}

int selectionSortPrioridade(Componente v[], int n) {
    int comp = 0;
    int min;
    Componente temp;
    for (int i = 0; i < n - 1; i++) {
        min = i;
        for (int j = i + 1; j < n; j++) {
            comp++;
            if (v[j].prioridade < v[min].prioridade) {
                min = j;
            }
        }
        if (min != i) {
            temp = v[i];
            v[i] = v[min];
            v[min] = temp;
        }
    }
    return comp;
}

// ===============================
// Busca Binária
// ===============================
int buscaBinariaPorNome(Componente v[], int n, char chave[]) {
    int ini = 0, fim = n - 1, meio;
    while (ini <= fim) {
        meio = (ini + fim) / 2;
        int cmp = strcmp(v[meio].nome, chave);
        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            ini = meio + 1;
        else
            fim = meio - 1;
    }
    return -1;
}

// ===============================
// Função principal
// ===============================
int main() {
    Componente mochila[MAX];
    int qtd = 0;
    int opcao;
    int ordenadoPorNome = 0;

    clock_t inicio, fim;
    double tempo;
    int comparacoes;

    do {
        printf("\n====================================================\n");
        printf("   PLANO DE FUGA - CODIGO DA ILHA (NIVEL MESTRE)\n");
        printf("====================================================\n");
        printf("Itens na Mochila: %d/%d\n", qtd, MAX);
        printf("Status da Ordenacao por Nome: %s\n", ordenadoPorNome ? "ORDENADO" : "NAO ORDENADO");
        printf("----------------------------------------------------\n");
        printf("1. Adicionar Componente\n");
        printf("2. Descartar Componente\n");
        printf("3. Listar Inventario\n");
        printf("4. Organizar Mochila (Ordenar Componentes)\n");
        printf("5. Busca Binaria por Componente-Chave (por nome)\n");
        printf("6. ATIVAR TORRE DE FUGA (Sair)\n");
        printf("----------------------------------------------------\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                if (qtd >= MAX) {
                    printf("\n--- Mochila cheia! Descarte algo antes. ---\n");
                    break;
                }
                printf("\n--- Coletando Novo Componente ---\n");
                printf("Nome: ");
                fgets(mochila[qtd].nome, 30, stdin);
                mochila[qtd].nome[strcspn(mochila[qtd].nome, "\n")] = 0;

                printf("Tipo: ");
                fgets(mochila[qtd].tipo, 20, stdin);
                mochila[qtd].tipo[strcspn(mochila[qtd].tipo, "\n")] = 0;

                printf("Quantidade: ");
                scanf("%d", &mochila[qtd].quantidade);
                limparBuffer();

                printf("Prioridade (1-10): ");
                scanf("%d", &mochila[qtd].prioridade);
                limparBuffer();

                qtd++;
                ordenadoPorNome = 0;
                printf("--- Componente adicionado! Agora há %d/%d componentes. ---\n", qtd, MAX);
                break;

            case 2:
                if (qtd == 0) {
                    printf("\n--- Mochila vazia, nada para descartar. ---\n");
                    break;
                }
                mostrarInventario(mochila, qtd);
                printf("Informe o numero do componente para descartar (1-%d): ", qtd);
                int pos;
                scanf("%d", &pos);
                limparBuffer();
                if (pos < 1 || pos > qtd) {
                    printf("--- Posicao invalida! ---\n");
                    break;
                }
                for (int i = pos - 1; i < qtd - 1; i++)
                    mochila[i] = mochila[i + 1];
                qtd--;
                printf("--- Componente descartado com sucesso. ---\n");
                break;

            case 3:
                mostrarInventario(mochila, qtd);
                break;

            case 4:
                if (qtd == 0) {
                    printf("\n--- Nenhum componente para ordenar. ---\n");
                    break;
                }
                printf("\n=== Escolha o Metodo de Ordenacao ===\n");
                printf("1. Bubble Sort (por nome)\n");
                printf("2. Insertion Sort (por tipo)\n");
                printf("3. Selection Sort (por prioridade)\n");
                printf("Opcao: ");
                int metodo;
                scanf("%d", &metodo);
                limparBuffer();

                inicio = clock();
                switch (metodo) {
                    case 1:
                        comparacoes = bubbleSortNome(mochila, qtd);
                        ordenadoPorNome = 1;
                        break;
                    case 2:
                        comparacoes = insertionSortTipo(mochila, qtd);
                        ordenadoPorNome = 0;
                        break;
                    case 3:
                        comparacoes = selectionSortPrioridade(mochila, qtd);
                        ordenadoPorNome = 0;
                        break;
                    default:
                        printf("--- Metodo invalido! ---\n");
                        continue;
                }
                fim = clock();
                tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

                printf("\n--- Mochila Organizada! ---\n");
                mostrarInventario(mochila, qtd);
                printf("Comparacoes: %d | Tempo: %.6f s\n", comparacoes, tempo);
                break;

            case 5:
                if (!ordenadoPorNome) {
                    printf("\n--- A mochila precisa estar ordenada por nome! ---\n");
                    break;
                }
                printf("Digite o nome do componente-chave: ");
                char chave[30];
                fgets(chave, 30, stdin);
                chave[strcspn(chave, "\n")] = 0;

                int idx = buscaBinariaPorNome(mochila, qtd, chave);
                if (idx != -1)
                    printf("\n>>> Componente encontrado: %s | Tipo: %s | Quantidade: %d | Prioridade: %d <<<\n",
                           mochila[idx].nome, mochila[idx].tipo, mochila[idx].quantidade, mochila[idx].prioridade);
                else
                    printf("\n--- Componente nao encontrado! ---\n");
                break;

            case 6:
                printf("\n>>> TORRE DE FUGA ATIVADA! <<<\n");
                printf("O plano de fuga foi concluido com sucesso.\n");
                break;

            default:
                printf("\n--- Opcao invalida! ---\n");
        }

    } while (opcao != 6);

    printf("\n=== Missao Encerrada. Fim de Jogo. ===\n");
    return 0;
}
