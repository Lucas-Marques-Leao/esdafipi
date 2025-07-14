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

char *dequeue(Fila *q) {
    if (q->begin == NULL) {
        printf("Fila vazia!\n");
        return NULL;
    }

    List *temp = q->begin;
    char *name = strdup(temp->name); 

    q->begin = temp->next;
    if (q->begin == NULL) {
        q->end = NULL;
    }

    free(temp);
    return name;
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
    initializeQueue(&q);

    int option;

    printf("\n🎓 BEM-VINDO À BIBLIOTECA DO IFAL 🎓\n");

    do {
        printf("\n--------- Menu ----------\n");
        printf("1 - Inserir estudante (Enfileirar)\n");
        printf("2 - Atender estudante (Desenfileirar)\n");
        printf("3 - Mostrar fila\n");
        printf("0 - Sair\n");
        printf("Escolha sua opção: ");
        scanf("%d", &option);
        getchar(); 

        switch (option) {
            case 1:
                cadastrarEstudante(&q);
                break;

            case 2: {
                char *served = dequeue(&q);
                if (served != NULL) {
                    printf("Estudante atendido: %s\n", served);
                    free(served);
                }
                break;
            }

            case 3:
                show(&q);
                break;

            case 0:
                printf("Encerrando o sistema...\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
        }

    } while (option != 0);

    return 0;
}
