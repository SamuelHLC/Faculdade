#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMMAX 100
#define TAMFILA 100

struct Produto {
    char nome[50];
    float preco;
    int quantidade;
};

struct Categoria {
    char nome[50];
    struct Produto *produtos;
    int numProdutos;
    int capacidadeProdutos;
};

// ---------- Pilha ----------
typedef struct {
    char historicoOperacoes[TAMMAX][100];
    int topo;
} Pilha;

void init(Pilha *p) {
    p->topo = -1;
}

int empty(Pilha *p) {
    return p->topo == -1;
}

int full(Pilha *p) {
    return p->topo == TAMMAX - 1;
}

void push(Pilha *p, const char *op) {
    if (!full(p)) {
        p->topo++;
        strcpy(p->historicoOperacoes[p->topo], op);
    }
}

void mostrarHistorico(Pilha *p) {
    printf("\n--- Historico de Operacoes (Pilha) ---\n");
    for (int i = p->topo; i >= 0; i--) {
        printf("%s\n", p->historicoOperacoes[i]);
    }
    if (empty(p)) {
        printf("Nenhuma operacao registrada.\n");
    }
}

// ---------- Fila ----------
typedef struct {
    char operacoes[TAMFILA][100];
    int inicio, fim;
} Fila;

void inicializaFila(Fila *f) {
    f->inicio = 0;
    f->fim = -1;
}

int filaVazia(Fila *f) {
    return f->fim < f->inicio;
}

int filaCheia(Fila *f) {
    return f->fim == TAMFILA - 1;
}

void enfileirar(Fila *f, const char *op) {
    if (filaCheia(f)) {
        printf("Fila cheia, não é possível adicionar mais operações.\n");
        return;
    }
    f->fim++;
    strcpy(f->operacoes[f->fim], op);
}

void imprimirFila(Fila *f) {
    if (filaVazia(f)) {
        printf("Fila vazia.\n");
        return;
    }
    printf("\n--- Fila de Operacoes ---\n");
    for (int i = f->inicio; i <= f->fim; i++) {
        printf("%s\n", f->operacoes[i]);
    }
}

// ---------- Utilitário ----------
void limpaBuffer() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// ---------- Ordenação ----------
void ordenarProdutosPorNome(struct Produto *produtos, int numProdutos) {
    for (int i = 0; i < numProdutos - 1; i++) {
        for (int j = 0; j < numProdutos - i - 1; j++) {
            if (strcmp(produtos[j].nome, produtos[j + 1].nome) > 0) {
                struct Produto temp = produtos[j];
                produtos[j] = produtos[j + 1];
                produtos[j + 1] = temp;
            }
        }
    }
}

// ---------- Funções principais ----------
void salvarEstoque(struct Categoria *categorias, int numCategorias) {
    FILE *arquivo = fopen("estoque.dat", "wb");
    if (arquivo == NULL) {
        printf("Erro ao criar arquivo.\n");
        return;
    }

    fwrite(&numCategorias, sizeof(int), 1, arquivo);
    for (int i = 0; i < numCategorias; i++) {
        fwrite(categorias[i].nome, sizeof(char), 50, arquivo);
        fwrite(&categorias[i].numProdutos, sizeof(int), 1, arquivo);
        fwrite(&categorias[i].capacidadeProdutos, sizeof(int), 1, arquivo);
        if (categorias[i].numProdutos > 0) {
            fwrite(categorias[i].produtos, sizeof(struct Produto), categorias[i].numProdutos, arquivo);
        }
    }

    fclose(arquivo);
    printf("Estoque salvo com sucesso!\n");
}

void carregarEstoque(struct Categoria *categorias, int *numCategorias) {
    FILE *arquivo = fopen("estoque.dat", "rb");
    if (arquivo == NULL) {
        printf("Nenhum dado anterior encontrado.\n");
        return;
    }

    for (int i = 0; i < *numCategorias; i++) {
        free(categorias[i].produtos);
    }

    fread(numCategorias, sizeof(int), 1, arquivo);

    for (int i = 0; i < *numCategorias; i++) {
        fread(categorias[i].nome, sizeof(char), 50, arquivo);
        fread(&categorias[i].numProdutos, sizeof(int), 1, arquivo);
        fread(&categorias[i].capacidadeProdutos, sizeof(int), 1, arquivo);
        categorias[i].produtos = malloc(sizeof(struct Produto) * categorias[i].capacidadeProdutos);
        if (categorias[i].produtos == NULL) {
            fprintf(stderr, "Erro de alocacao de memoria!\n");
            exit(1);
        }
        if (categorias[i].numProdutos > 0) {
            fread(categorias[i].produtos, sizeof(struct Produto), categorias[i].numProdutos, arquivo);
        }
    }

    fclose(arquivo);
    printf("Dados carregados com sucesso.\n");
}

void criarCategoria(struct Categoria *categorias, int *numCategorias) {
    printf("Digite o nome da nova categoria: ");
    scanf("%s", categorias[*numCategorias].nome);

    categorias[*numCategorias].produtos = malloc(sizeof(struct Produto) * 1);
    if (categorias[*numCategorias].produtos == NULL) {
        printf("Erro de alocacao de memoria\n");
        exit(1);
    }

    categorias[*numCategorias].numProdutos = 0;
    categorias[*numCategorias].capacidadeProdutos = 1;

    printf("Categoria '%s' criada com sucesso\n", categorias[*numCategorias].nome);
    (*numCategorias)++;
}

void adicionarProduto(struct Categoria *categorias, int *numCategorias) {
    char nomeCategoria[50], nomeProduto[50];
    float precoProduto;
    int quantidadeAdicionar;
    int categoriaEncontrada = 0, produtoEncontrado = 0;

    printf("Digite o nome da categoria para adicionar/atualizar o produto: ");
    scanf("%s", nomeCategoria);

    for (int i = 0; i < *numCategorias; i++) {
        if (strcmp(categorias[i].nome, nomeCategoria) == 0) {
            categoriaEncontrada = 1;

            printf("Digite o nome do produto: ");
            scanf("%s", nomeProduto);

            printf("Digite a quantidade a adicionar: ");
            scanf("%d", &quantidadeAdicionar);

            for (int j = 0; j < categorias[i].numProdutos; j++) {
                if (strcmp(categorias[i].produtos[j].nome, nomeProduto) == 0) {
                    categorias[i].produtos[j].quantidade += quantidadeAdicionar;
                    produtoEncontrado = 1;
                    printf("Quantidade de '%s' atualizada para %d na categoria '%s'.\n",
                           nomeProduto, categorias[i].produtos[j].quantidade, nomeCategoria);
                    break;
                }
            }

            if (!produtoEncontrado) {
                if (categorias[i].numProdutos == categorias[i].capacidadeProdutos) {
                    categorias[i].capacidadeProdutos *= 2;
                    struct Produto *temp = realloc(categorias[i].produtos,
                                                   sizeof(struct Produto) * categorias[i].capacidadeProdutos);
                    if (temp == NULL) {
                        printf("Erro de realocacao de memoria!\n");
                        exit(1);
                    }
                    categorias[i].produtos = temp;
                }

                strcpy(categorias[i].produtos[categorias[i].numProdutos].nome, nomeProduto);
                printf("Digite o preco do novo produto '%s': ", nomeProduto);
                scanf("%f", &precoProduto);
                categorias[i].produtos[categorias[i].numProdutos].preco = precoProduto;
                categorias[i].produtos[categorias[i].numProdutos].quantidade = quantidadeAdicionar;

                categorias[i].numProdutos++;
                printf("Novo produto '%s' com %d unidades adicionado à categoria '%s'!\n",
                       nomeProduto, quantidadeAdicionar, nomeCategoria);
            }

            return;
        }
    }

    printf("Categoria '%s' nao encontrada!\n", nomeCategoria);
}

void retirarProduto(struct Categoria *categorias, int *numCategorias) {
    char nomeCategoria[50], nomeProduto[50];
    int quantidade;

    printf("Digite o nome da categoria para retirar o produto: ");
    scanf("%s", nomeCategoria);

    for (int i = 0; i < *numCategorias; i++) {
        if (strcmp(categorias[i].nome, nomeCategoria) == 0) {
            printf("Digite o nome do produto: ");
            scanf("%s", nomeProduto);

            for (int j = 0; j < categorias[i].numProdutos; j++) {
                if (strcmp(categorias[i].produtos[j].nome, nomeProduto) == 0) {
                    printf("Digite a quantidade a ser retirada: ");
                    scanf("%d", &quantidade);

                    if (categorias[i].produtos[j].quantidade >= quantidade) {
                        categorias[i].produtos[j].quantidade -= quantidade;
                        printf("Retirada de %d unidades de '%s' realizada com sucesso!\n",
                               quantidade, nomeProduto);
                    } else {
                        printf("Estoque insuficiente! Apenas %d unidades disponiveis.\n",
                               categorias[i].produtos[j].quantidade);
                    }
                    return;
                }
            }
            printf("Produto '%s' nao encontrado na categoria '%s'.\n", nomeProduto, nomeCategoria);
            return;
        }
    }
    printf("Categoria '%s' nao encontrada.\n", nomeCategoria);
}

void verificarProdutosRec(struct Produto *produtos, int j, int numProdutos) {
    if (j >= numProdutos) return;

    printf("  Produto: %s | Preco: R$%.2f | Quantidade: %d\n",
           produtos[j].nome, produtos[j].preco, produtos[j].quantidade);

    verificarProdutosRec(produtos, j + 1, numProdutos);
}

void verificarCategoriasRec(struct Categoria *categorias, int i, int numCategorias) {
    if (i >= numCategorias) return;

    printf("\nCategoria: %s\n", categorias[i].nome);

    if (categorias[i].numProdutos == 0) {
        printf("  Nenhum produto cadastrado.\n");
    } else {
        ordenarProdutosPorNome(categorias[i].produtos, categorias[i].numProdutos); // <-- Aqui a ordenação
        verificarProdutosRec(categorias[i].produtos, 0, categorias[i].numProdutos);
    }

    verificarCategoriasRec(categorias, i + 1, numCategorias);
}

void verificarEstoque(struct Categoria *categorias, int numCategorias) {
    if (numCategorias == 0) {
        printf("\nNenhuma categoria cadastrada.\n");
        return;
    }

    printf("\n--- Estoque Geral ---\n");
    verificarCategoriasRec(categorias, 0, numCategorias);
}

// ---------- Menu ----------
void menu() {
    printf("\nMenu Principal:\n");
    printf("1. Criar categoria\n");
    printf("2. Adicionar/Atualizar produto\n");
    printf("3. Retirar produto\n");
    printf("4. Ver estoque\n");
    printf("5. Salvar estoque\n");
    printf("6. Carregar estoque\n");
    printf("7. Ver historico de operacoes (Pilha + Fila)\n");
    printf("8. Sair\n");
    printf("Opcao: ");
}

// ---------- Main ----------
int main() {
    struct Categoria categorias[100];
    int numCategorias = 0;
    int opcao;
    Pilha historico;
    Fila filaOperacoes;

    init(&historico);
    inicializaFila(&filaOperacoes);

    do {
        menu();
        scanf("%d", &opcao);
        limpaBuffer();

        switch (opcao) {
            case 1:
                criarCategoria(categorias, &numCategorias);
                push(&historico, "Criou uma nova categoria");
                enfileirar(&filaOperacoes, "Criou uma nova categoria");
                break;
            case 2:
                adicionarProduto(categorias, &numCategorias);
                push(&historico, "Adicionou/Atualizou um produto");
                enfileirar(&filaOperacoes, "Adicionou/Atualizou um produto");
                break;
            case 3:
                retirarProduto(categorias, &numCategorias);
                push(&historico, "Retirou um produto");
                enfileirar(&filaOperacoes, "Retirou um produto");
                break;
            case 4:
                verificarEstoque(categorias, numCategorias);
                push(&historico, "Verificou o estoque");
                enfileirar(&filaOperacoes, "Verificou o estoque");
                break;
            case 5:
                salvarEstoque(categorias, numCategorias);
                push(&historico, "Salvou o estoque");
                enfileirar(&filaOperacoes, "Salvou o estoque");
                break;
            case 6:
                carregarEstoque(categorias, &numCategorias);
                push(&historico, "Carregou o estoque");
                enfileirar(&filaOperacoes, "Carregou o estoque");
                break;
            case 7:
                mostrarHistorico(&historico);
                imprimirFila(&filaOperacoes);
                break;
            case 8:
                printf("Saindo do sistema...\n");
                for (int i = 0; i < numCategorias; i++) {
                    free(categorias[i].produtos);
                }
                break;
            default:
                printf("Opcao invalida! Por favor, escolha uma opcao entre 1 e 8\n");
        }
    } while (opcao != 8);

    return 0;
}
