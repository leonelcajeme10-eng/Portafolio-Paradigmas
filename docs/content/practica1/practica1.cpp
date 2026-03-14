#define MAX_USER 32
#define MAX_DOC 48
#define MAX_JOBS 10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    NORMAL = 0,
    URGENTE = 1
} Prioridad_t;

typedef enum
{
    EN_COLA = 0,
    IMPRIMIENDO = 1,
    COMPLETADO = 2,
    CANCELADO = 3,
} Estado_t;

typedef struct
{
    int id;
    char usuario[MAX_USER];
    char documento[MAX_DOC];
    int paginas_total;
    int paginas_restantes;
    int copias;
    Prioridad_t prioridad;
    Estado_t estado;
    int ms_por_pagina;
} PrintJob_t;

typedef struct
{
    PrintJob_t data[MAX_JOBS];
    int size;
} QueueStatic_t;

void limpiar_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void qs_init(QueueStatic_t *q)
{
    q->size = 0;
}

int qs_is_empty(const QueueStatic_t *q)
{
    return q->size == 0;
}

int qs_is_full(const QueueStatic_t *q)
{
    return q->size == MAX_JOBS;
}

int qs_enqueue(QueueStatic_t *q, PrintJob_t job)
{
    if (qs_is_full(q))
        return 0;

    q->data[q->size] = job;
    q->size++;

    return 1;
}

int qs_peek(const QueueStatic_t *q, PrintJob_t *out)
{
    if (qs_is_empty(q))
        return 0;

    *out = q->data[0];
    return 1;
}

int qs_dequeue(QueueStatic_t *q, PrintJob_t *out)
{
    if (qs_is_empty(q))
        return 0;

    *out = q->data[0];

    for (int i = 1; i < q->size; i++)
    {
        q->data[i - 1] = q->data[i];
    }

    q->size--;

    return 1;
}

void qs_print(const QueueStatic_t *q)
{
    if (qs_is_empty(q))
    {
        printf("\nCola vacia\n");
        return;
    }

    printf("\nCOLA DE IMPRESION\n");

    for (int i = 0; i < q->size; i++)
    {
        printf("ID:%d Usuario:%s Doc:%s Pag:%d\n",
               q->data[i].id,
               q->data[i].usuario,
               q->data[i].documento,
               q->data[i].paginas_total);
    }
}

int mensajes()
{
    int opc;

    printf("\e[1;1H\e[2J");
    printf("\n1. Agregar trabajo (enqueue)");
    printf("\n2. Ver siguiente trabajo (peek)");
    printf("\n3. Procesar trabajo (dequeue)");
    printf("\n4. Listar cola");
    printf("\n5. Salir");
    printf("\nIngrese una opcion: ");

    if (scanf("%d", &opc) != 1)
    {
        printf("Entrada invalida\n");
        limpiar_buffer();
        return 0;
    }

    limpiar_buffer();

    return opc;
}

void continuar()
{
    char buf[4];
    printf("\nPresiona ENTER para continuar...");
    fgets(buf, sizeof(buf), stdin);
}


void menu()
{
    QueueStatic_t cola;
    qs_init(&cola);

    int opcion;
    int id_counter = 1;

    PrintJob_t job;
    PrintJob_t aux;

    do
    {
        opcion = mensajes();

        switch (opcion)
        {

        case 1:

            if (qs_is_full(&cola))
            {
                printf("\nCola llena\n");
                continuar();
                break;
            }

            job.id = id_counter++;

            printf("Usuario: ");
            scanf("%31s", job.usuario);
            limpiar_buffer();

            printf("Documento: ");
            scanf("%47s", job.documento);
            limpiar_buffer();

            printf("Paginas: ");

            if (scanf("%d", &job.paginas_total) != 1 || job.paginas_total <= 0)
            {
                printf("Numero de paginas invalido\n");
                limpiar_buffer();
                id_counter--;
                break;
            }

            limpiar_buffer();

            job.paginas_restantes = job.paginas_total;
            job.copias = 1;
            job.prioridad = NORMAL;
            job.estado = EN_COLA;
            job.ms_por_pagina = 300;

            qs_enqueue(&cola, job);

            printf("Trabajo agregado ID=%d\n", job.id);
            continuar();
            break;

        case 2:

            if (qs_peek(&cola, &aux))
            {
                printf("\nSiguiente trabajo:\n");
                printf("ID:%d Usuario:%s Doc:%s Pag:%d\n",
                       aux.id, aux.usuario, aux.documento, aux.paginas_total);
            }
            else
            {
                printf("\nCola vacia\n");
            }
            continuar();
            break;

        case 3:

            if (qs_dequeue(&cola, &aux))
            {
                printf("\nProcesado:\n");
                printf("ID:%d Usuario:%s Doc:%s Pag:%d\n",
                       aux.id, aux.usuario, aux.documento, aux.paginas_total);
            }
            else
            {
                printf("\nCola vacia\n");
            }

            continuar();
            break;

        case 4:

            qs_print(&cola);
            continuar();
            break;
        }

    } while (opcion != 5);
}

int main()
{
    menu();
    return 0;
}