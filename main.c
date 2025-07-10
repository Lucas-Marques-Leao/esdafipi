#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lista
{
  char name[100];
  struct lista *next;
};
typedef struct lista List;

struct fila
{
  List *begin;
  List *end;
};
typedef struct fila Fila;

void initializeQueue(Fila *q)
{
  q->begin = NULL;
  q->end = NULL;
}

void enqueue(Fila *q, char *student_name)
{
  List *new = (List *)malloc(sizeof(List));
  strcpy(new->name, student_name);
  new->next = NULL;

  if (q->begin == NULL)
  {
    q->begin = q->end = new;
  }
  else
  {
    q->end->next = new;
    q->end = new;
  }
}

char *dequeue(Fila *q)
{
  if (q->begin == NULL)
  {
    printf("Fila vazia!\n");
    return NULL;
  }

  List *temp = q->begin;
  char *name = strdup(temp->name);
  q->begin = temp->next;

  if (q->begin == NULL)
  {
    q->end = NULL;
  }

  free(temp);
  return name;
}

void show(Fila *q)
{
  List *current = q->begin;
  while (current != NULL)
  {
    printf("[\n%s]", current->name);
    current = current->next;
  }
  printf("NULL\n");
}

int main()
{
  Fila q;
  initializeQueue(&q);

  int option;
  char name[100]; // Nome do estudante

  printf("\nBEM-VINDO À BIBLIOTECA DO IFAL!!\n");

  do
  {
    // Exibe o menu
    printf("\n--------- Menu ----------\n");
    printf("1 - Inserir estudante (Enfileirar)\n");
    printf("2 - Atender estudante (Desenfileirar)\n");
    printf("3 - Mostrar fila\n");
    printf("0 - Sair\n");
    printf("Escolha sua opção: ");
    scanf("%d", &option);
    getchar(); // Limpa '\n' do buffer do teclado

    switch (option)
    {
    case 1:
      printf("Digite o nome do estudante: ");
      fgets(name, sizeof(name), stdin);
      name[strcspn(name, "\n")] = 0;
      enqueue(&q, name);
      break;

    case 2:
    {
      char *served = dequeue(&q);
      if (served != NULL)
      {
        printf("Estudante atendido: %s\n", served);
        free(served);
      }
      break;
    }

    case 3:
      printf("Fila atual: ");
      show(&q);
      break;

    case 0:
      printf("Finalizando...\n");
      break;

    default:
      printf("Opção inválida!\n");
    }
  } while (option != 0);

  return 0;
}