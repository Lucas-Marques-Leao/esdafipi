#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lista {
    char name[100];
    char cpf[20];
    char matricula[20];
    struct lista *next;
};
typedef struct lista List;

struct fila {
    List *begin;
    List *end;
};
typedef struct fila Fila;

struct pilha {
    List *top;
};
typedef struct pilha Pilha;

void initializeQueue(Fila *q) {
    q->begin = NULL;
    q->end = NULL;
}

void enqueue(Fila *q, char *name, char *cpf, char *matricula) {
    List *new = (List *)malloc(sizeof(List));
    if (new == NULL) {
        printf("Erro ao alocar memória!\n");
        return;
    }

    strcpy(new->name, name);
    strcpy(new->cpf, cpf);
    strcpy(new->matricula, matricula);
    new->next = NULL;

    if (q->begin == NULL) {
        q->begin = q->end = new;
    } else {
        q->end->next = new;
        q->end = new;
    }
}

List *dequeue(Fila *q) {
    if (q->begin == NULL) {
        printf("Fila vazia!\n");
        return NULL;
    }

    List *temp = q->begin;
    q->begin = temp->next;
    if (q->begin == NULL) {
        q->end = NULL;
    }

    temp->next = NULL; 
    return temp;
}

void show(Fila *q) {
    if (q->begin == NULL) {
        printf("A fila está vazia.\n");
        return;
    }

    List *current = q->begin;
    printf("\n---- Fila de Estudantes ----\n");

    int pos = 1;
    while (current != NULL) {
        printf("%dº Estudante:\n", pos);
        printf("   Nome     : %s\n", current->name);
        printf("   CPF      : %s\n", current->cpf);
        printf("   Matrícula: %s\n\n", current->matricula);
        current = current->next;
        pos++;
    }

    printf("----------------------------\n");
}

void initializeStack(Pilha *p) {
    p->top = NULL;
}

void push(Pilha *p, List *student) {
    student->next = p->top;
    p->top = student;
}

List *pop(Pilha *p) {
    if (p->top == NULL) {
        printf("Histórico vazio!\n");
        return NULL;
    }

    List *temp = p->top;
    p->top = temp->next;
    temp->next = NULL;
    return temp;
}

void showHistory(Pilha *p) {
    if (p->top == NULL) {
        printf("Nenhum estudante foi atendido ainda.\n");
        return;
    }

    List *current = p->top;
    int pos = 1;

    printf("\n---- Histórico de Atendimentos ----\n");
    while (current != NULL) {
        printf("%dº Atendido:\n", pos);
        printf("   Nome     : %s\n", current->name);
        printf("   CPF      : %s\n", current->cpf);
        printf("   Matrícula: %s\n\n", current->matricula);
        current = current->next;
        pos++;
    }
    printf("-----------------------------------\n");
}

void cadastrarEstudante(Fila *q) {
    char nome[100];
    char cpf[20];
    char matricula[20];

    printf("Digite seu nome: ");
    scanf(" %[^\n]", nome);
    getchar();

    printf("Digite seu CPF [formato 000.000.000-00]: ");
    scanf(" %s", cpf);

    printf("Digite sua matrícula [4 primeiros números do CPF]: ");
    scanf(" %s", matricula);

    enqueue(q, nome, cpf, matricula);
    printf("✅ Estudante '%s' cadastrado com sucesso!\n", nome);
}

int main() {
    Fila q;
    Pilha historico;
    initializeQueue(&q);
    initializeStack(&historico);

    int option;

    printf("\n🎓 BEM-VINDO À BIBLIOTECA DO IFAL 🎓\n");

    do {
        printf("\n--------- Menu ----------\n");
        printf("1 - Inserir estudante (Enfileirar)\n");
        printf("2 - Atender estudante (Desenfileirar e guardar no histórico)\n");
        printf("3 - Mostrar fila\n");
        printf("4 - Mostrar histórico de atendimentos (Pilha)\n");
        printf("5 - Desfazer último atendimento (Desempilhar)\n");
        printf("0 - Sair\n");
        printf("Escolha sua opção: ");
        scanf("%d", &option);
        getchar();

        switch (option) {
            case 1:
                cadastrarEstudante(&q);
                break;

            case 2: {
                List *served = dequeue(&q);
                if (served != NULL) {
                    printf("🧾 Estudante atendido: %s\n", served->name);
                    push(&historico, served);
                }
                break;
            }

            case 3:
                show(&q);
                break;

            case 4:
                showHistory(&historico);
                break;

            case 5: {
                List *undone = pop(&historico);
                if (undone != NULL) {
                    printf("⚠️ Último atendimento desfeito: %s\n", undone->name);
                    enqueue(&q, undone->name, undone->cpf, undone->matricula);
                    free(undone); 
                }
                break;
            }

            case 0:
                printf("Encerrando o sistema...\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
        }

    } while (option != 0);

    return 0;
}
