// ============================================================================
//     DESAFIO CÓDIGO DA ILHA - EDIÇÃO FREE FIRE
// ============================================================================
//
// Funcionalidades Completas:
// - Adicionar/Remover itens com prioridade
// - Busca sequencial e busca binária
// - Ordenação por nome, tipo ou prioridade
// - Análise de desempenho
//
// ============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ============================================================================
// ESTRUTURAS DE DADOS
// ============================================================================

/**
 * Struct Item:
 * Representa um componente com nome, tipo, quantidade e prioridade (1 a 5).
 * A prioridade indica a importância do item na montagem do plano de fuga.
 */
typedef struct {
    char nome[50];
    char tipo[30];
    int quantidade;
    int prioridade;  // Valores de 1 a 5
} Item;

/**
 * Enum CriterioOrdenacao:
 * Define os critérios possíveis para a ordenação dos itens (nome, tipo ou prioridade).
 */
typedef enum {
    ORDENAR_NOME = 1,
    ORDENAR_TIPO = 2,
    ORDENAR_PRIORIDADE = 3
} CriterioOrdenacao;

// ============================================================================
// CONSTANTES
// ============================================================================

#define MAX_ITENS 10

// ============================================================================
// PROTÓTIPOS DAS FUNÇÕES
// ============================================================================

// Funções principais
void adicionarItem(Item mochila[], int* total);
void removerItem(Item mochila[], int* total);
void listarItens(const Item mochila[], int total);
void buscarItem(const Item mochila[], int total);
void ordenarMochila(Item mochila[], int total, CriterioOrdenacao criterio, int* comparacoes);
void buscaBinaria(const Item mochila[], int total, bool ordenadoPorNome);

// Funções auxiliares
int compararItens(const Item* a, const Item* b, CriterioOrdenacao criterio);
void limparBuffer();
void pausar();
void limparTela();

// ============================================================================
// FUNÇÃO PRINCIPAL
// ============================================================================

int main() {
    // Código da Ilha – Edição Free Fire
    // Nível: Mestre
    // Este programa simula o gerenciamento avançado de uma mochila com componentes 
    // coletados durante a fuga de uma ilha.
    // Ele introduz ordenação com critérios e busca binária para otimizar a gestão dos recursos.
    
    // Vetor mochila: Armazena até 10 itens coletados
    Item mochila[MAX_ITENS];
    
    // Variáveis de controle:
    // - numItens (quantidade atual de itens)
    // - ordenadaPorNome (controle para busca binária)
    int numItens = 0;
    int opcao;
    bool ordenadaPorNome = false;
    
    printf("╔════════════════════════════════════════════════════════════╗\n");
    printf("║     DESAFIO CÓDIGO DA ILHA - EDIÇÃO FREE FIRE             ║\n");
    printf("║     Sistema de Mochila Virtual de Sobrevivência           ║\n");
    printf("╚════════════════════════════════════════════════════════════╝\n\n");
    
    do {
        // Menu principal com opções:
        // 1. Adicionar um item
        // 2. Remover um item
        // 3. Listar todos os itens
        // 4. Buscar item (busca sequencial)
        // 5. Ordenar os itens por critério (nome, tipo, prioridade)
        // 6. Realizar busca binária por nome
        // 0. Sair
        // A estrutura switch trata cada opção chamando a função correspondente.
        
        limparTela();
        
        printf("\n========== MENU PRINCIPAL ==========\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - 🔍 Buscar item (busca sequencial)\n");
        printf("5 - 📊 Ordenar mochila\n");
        printf("6 - ⚡ Busca binária por nome\n");
        printf("0 - Sair\n");
        printf("====================================\n");
        if (ordenadaPorNome) {
            printf("Status: ✅ Mochila ordenada por nome (busca binária disponível)\n");
        } else {
            printf("Status: ⚠️  Mochila não ordenada por nome\n");
        }
        printf("====================================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        // A estrutura switch trata cada opção chamando a função correspondente
        switch(opcao) {
            case 1:
                // inserirItem(): Adiciona um novo componente à mochila se houver espaço
                // Solicita nome, tipo, quantidade e prioridade
                // Após inserir, marca a mochila como "não ordenada por nome"
                adicionarItem(mochila, &numItens);
                ordenadaPorNome = false;
                break;
                
            case 2:
                // removerItem(): Permite remover um componente da mochila pelo nome
                // Se encontrado, reorganiza o vetor para preencher a lacuna
                removerItem(mochila, &numItens);
                ordenadaPorNome = false;
                break;
                
            case 3:
                // listarItens(): Exibe uma tabela formatada com todos os componentes
                listarItens(mochila, numItens);
                break;
                
            case 4:
                // Busca sequencial simples por nome
                buscarItem(mochila, numItens);
                break;
                
            case 5: {
                // menuDeOrdenacao(): Permite ao jogador escolher como deseja ordenar os itens
                // Utiliza a função insertionSort() com o critério selecionado
                // Exibe a quantidade de comparações feitas (análise de desempenho)
                if (numItens == 0) {
                    printf("\n❌ Mochila vazia! Adicione itens primeiro.\n");
                    break;
                }
                
                int criterio;
                int comparacoes = 0;  // Variável para análise de desempenho
                printf("\n--- ORDENAR MOCHILA ---\n");
                printf("1 - Ordenar por Nome\n");
                printf("2 - Ordenar por Tipo\n");
                printf("3 - Ordenar por Prioridade\n");
                printf("Escolha o critério: ");
                scanf("%d", &criterio);
                limparBuffer();
                
                if (criterio >= 1 && criterio <= 3) {
                    // insertionSort(): Implementação do algoritmo de ordenação por inserção
                    // Funciona com diferentes critérios de ordenação:
                    // - Por nome (ordem alfabética)
                    // - Por tipo (ordem alfabética)
                    // - Por prioridade (da mais alta para a mais baixa)
                    ordenarMochila(mochila, numItens, (CriterioOrdenacao)criterio, &comparacoes);
                    printf("\n✅ Mochila ordenada com sucesso!\n");
                    printf("📊 Comparações realizadas: %d\n", comparacoes);
                    
                    ordenadaPorNome = (criterio == ORDENAR_NOME);
                } else {
                    printf("\n❌ Critério inválido!\n");
                }
                break;
            }
            
            case 6:
                // buscaBinariaPorNome(): Realiza busca binária por nome, desde que 
                // a mochila esteja ordenada por nome
                // Se encontrar, exibe os dados do item buscado
                // Caso contrário, informa que não encontrou o item
                buscaBinaria(mochila, numItens, ordenadaPorNome);
                break;
                
            case 0:
                printf("\nSaindo do sistema... Boa sorte na ilha! 🏝️\n");
                break;
                
            default:
                printf("\n❌ Opção inválida! Tente novamente.\n");
        }
        
        if (opcao != 0) {
            pausar();
        }
        
    } while(opcao != 0);
    
    return 0;
}

// ============================================================================
// IMPLEMENTAÇÃO DAS FUNÇÕES
// ============================================================================

/**
 * Adiciona um novo item à mochila com prioridade
 */
void adicionarItem(Item mochila[], int* total) {
    if (*total >= MAX_ITENS) {
        printf("\n❌ Mochila cheia! Remova itens antes de adicionar novos.\n");
        return;
    }
    
    printf("\n--- ADICIONAR NOVO ITEM ---\n");
    
    printf("Nome do item: ");
    fgets(mochila[*total].nome, 50, stdin);
    mochila[*total].nome[strcspn(mochila[*total].nome, "\n")] = '\0';
    
    printf("Tipo do item: ");
    fgets(mochila[*total].tipo, 30, stdin);
    mochila[*total].tipo[strcspn(mochila[*total].tipo, "\n")] = '\0';
    
    printf("Quantidade: ");
    scanf("%d", &mochila[*total].quantidade);
    
    do {
        printf("Prioridade (1-5): ");
        scanf("%d", &mochila[*total].prioridade);
        if (mochila[*total].prioridade < 1 || mochila[*total].prioridade > 5) {
            printf("❌ Prioridade deve estar entre 1 e 5!\n");
        }
    } while (mochila[*total].prioridade < 1 || mochila[*total].prioridade > 5);
    
    limparBuffer();
    
    (*total)++;
    printf("\n✅ Item adicionado com sucesso!\n");
}

/**
 * Remove um item da mochila pelo nome
 */
void removerItem(Item mochila[], int* total) {
    if (*total == 0) {
        printf("\n❌ Mochila vazia! Não há itens para remover.\n");
        return;
    }
    
    char nomeBusca[50];
    printf("\n--- REMOVER ITEM ---\n");
    printf("Nome do item a remover: ");
    fgets(nomeBusca, 50, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    // Busca o item pelo nome
    int encontrado = -1;
    for (int i = 0; i < *total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            encontrado = i;
            break;
        }
    }
    
    if (encontrado == -1) {
        printf("\n❌ Item '%s' não encontrado na mochila.\n", nomeBusca);
        return;
    }
    
    // Remove o item deslocando os elementos
    for (int i = encontrado; i < *total - 1; i++) {
        mochila[i] = mochila[i + 1];
    }
    
    (*total)--;
    printf("\n✅ Item removido com sucesso!\n");
}

/**
 * Lista todos os itens da mochila em formato de tabela
 */
void listarItens(const Item mochila[], int total) {
    if (total == 0) {
        printf("\n📦 Mochila vazia!\n");
        return;
    }
    
    printf("\n╔════════════════════════════════════════════════════════════════════════╗\n");
    printf("║                        ITENS NA MOCHILA                                ║\n");
    printf("╚════════════════════════════════════════════════════════════════════════╝\n");
    printf("%-20s %-20s %-12s %-10s\n", "NOME", "TIPO", "QUANTIDADE", "PRIORIDADE");
    printf("------------------------------------------------------------------------\n");
    
    for (int i = 0; i < total; i++) {
        printf("%-20s %-20s %-12d %-10d\n", 
               mochila[i].nome, 
               mochila[i].tipo, 
               mochila[i].quantidade,
               mochila[i].prioridade);
    }
    
    printf("------------------------------------------------------------------------\n");
    printf("Total de itens: %d/%d\n", total, MAX_ITENS);
}

/**
 * Busca sequencial por nome e exibe detalhes do item
 */
void buscarItem(const Item mochila[], int total) {
    if (total == 0) {
        printf("\n❌ Mochila vazia! Não há itens para buscar.\n");
        return;
    }
    
    char nomeBusca[50];
    printf("\n--- BUSCAR ITEM (Busca Sequencial) ---\n");
    printf("Nome do item: ");
    fgets(nomeBusca, 50, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    // Busca sequencial
    bool encontrado = false;
    for (int i = 0; i < total; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\n✅ Item encontrado!\n");
            printf("╔════════════════════════════════════════╗\n");
            printf("║        DETALHES DO ITEM                ║\n");
            printf("╚════════════════════════════════════════╝\n");
            printf("Nome:       %s\n", mochila[i].nome);
            printf("Tipo:       %s\n", mochila[i].tipo);
            printf("Quantidade: %d\n", mochila[i].quantidade);
            printf("Prioridade: %d/5\n", mochila[i].prioridade);
            encontrado = true;
            break;
        }
    }
    
    if (!encontrado) {
        printf("\n❌ Item '%s' não encontrado na mochila.\n", nomeBusca);
    }
}

/**
 * Compara dois itens baseado no critério especificado
 */
int compararItens(const Item* a, const Item* b, CriterioOrdenacao criterio) {
    switch(criterio) {
        case ORDENAR_NOME:
            return strcmp(a->nome, b->nome);
        case ORDENAR_TIPO:
            return strcmp(a->tipo, b->tipo);
        case ORDENAR_PRIORIDADE:
            return b->prioridade - a->prioridade; // Decrescente (maior prioridade primeiro)
        default:
            return 0;
    }
}

/**
 * Ordena a mochila usando Insertion Sort
 * Conta o número de comparações realizadas para análise de desempenho
 */
void ordenarMochila(Item mochila[], int total, CriterioOrdenacao criterio, int* comparacoes) {
    *comparacoes = 0;
    
    for (int i = 1; i < total; i++) {
        Item chave = mochila[i];
        int j = i - 1;
        
        while (j >= 0 && compararItens(&mochila[j], &chave, criterio) > 0) {
            (*comparacoes)++;
            mochila[j + 1] = mochila[j];
            j--;
        }
        
        if (j >= 0) {
            (*comparacoes)++;
        }
        
        mochila[j + 1] = chave;
    }
}

/**
 * Busca binária por nome (requer mochila ordenada por nome)
 * Algoritmo mais eficiente que busca sequencial: O(log n) vs O(n)
 */
void buscaBinaria(const Item mochila[], int total, bool ordenadoPorNome) {
    if (total == 0) {
        printf("\n❌ Mochila vazia! Não há itens para buscar.\n");
        return;
    }
    
    if (!ordenadoPorNome) {
        printf("\n❌ ERRO: A mochila deve estar ordenada por NOME para usar busca binária!\n");
        printf("Dica: Use a opção 5 para ordenar por nome primeiro.\n");
        return;
    }
    
    char nomeBusca[50];
    printf("\n--- BUSCA BINÁRIA ---\n");
    printf("Nome do item: ");
    fgets(nomeBusca, 50, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
    
    // Busca binária
    int esquerda = 0;
    int direita = total - 1;
    int meio;
    bool encontrado = false;
    
    while (esquerda <= direita) {
        meio = (esquerda + direita) / 2;
        int comparacao = strcmp(mochila[meio].nome, nomeBusca);
        
        if (comparacao == 0) {
            // Item encontrado
            printf("\n✅ Item encontrado com busca binária!\n");
            printf("╔════════════════════════════════════════╗\n");
            printf("║        DETALHES DO ITEM                ║\n");
            printf("╚════════════════════════════════════════╝\n");
            printf("Nome:       %s\n", mochila[meio].nome);
            printf("Tipo:       %s\n", mochila[meio].tipo);
            printf("Quantidade: %d\n", mochila[meio].quantidade);
            printf("Prioridade: %d/5\n", mochila[meio].prioridade);
            encontrado = true;
            break;
        } else if (comparacao < 0) {
            esquerda = meio + 1;
        } else {
            direita = meio - 1;
        }
    }
    
    if (!encontrado) {
        printf("\n❌ Item '%s' não encontrado na mochila.\n", nomeBusca);
    }
}

// ============================================================================
// FUNÇÕES UTILITÁRIAS
// ============================================================================

/**
 * Limpa o buffer de entrada para evitar problemas com scanf/fgets
 */
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * Pausa a execução aguardando ENTER do usuário
 */
void pausar() {
    printf("\nPressione ENTER para continuar...");
    getchar();
}

/**
 * limparTela():
 * Simula a limpeza da tela imprimindo várias linhas em branco.
 */
void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
