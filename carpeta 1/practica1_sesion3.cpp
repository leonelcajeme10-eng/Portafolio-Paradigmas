#define MAX_USER 32
#define MAX_DOC 48

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int trabajos_completados = 0;
int paginas_impresas = 0;

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

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

/* ----------- NODO DINAMICO ----------- */

typedef struct Node_t
{
    PrintJob_t job;
    struct Node_t *next;
} Node_t;

/* ----------- COLA DINAMICA ----------- */

typedef struct
{
    Node_t *head;
    Node_t *tail;
    int size;
} QueueDynamic_t;

/* ----------- DECLARACIONES ----------- */

void qd_init(QueueDynamic_t *q);
int qd_is_empty(const QueueDynamic_t *q);
int qd_enqueue(QueueDynamic_t *q, PrintJob_t job);
int qd_peek(const QueueDynamic_t *q, PrintJob_t *out);
int qd_dequeue(QueueDynamic_t *q, PrintJob_t *out);
void qd_print(const QueueDynamic_t *q);
void qd_destroy(QueueDynamic_t *q);
void delay_ms(int ms);
void simular_impresion(QueueDynamic_t *q);
int qd_enqueue_urgente(QueueDynamic_t *q, PrintJob_t job);
void continuar();
void menu();

/* ----------- MAIN ----------- */

int main()
{
    menu();
    return 0;
}

/* ----------- MENU ----------- */

int mensajes()
{
    char opc[32];

    printf("\n1. Agregar trabajo (enqueue)");
    printf("\n2. Ver siguiente trabajo (peek)");
    printf("\n3. Listar cola");
    printf("\n4. Simular Impresion");
    printf("\n5. Salir");
    printf("\nIngrese una opcion: ");

    if (fgets(opc, sizeof(opc), stdin) == NULL)
        return -1;

    return (int)strtol(opc, NULL, 10);
}

void menu()
{
    QueueDynamic_t cola;
    qd_init(&cola);

    int opcion;
    int id_counter = 1;

    PrintJob_t job;
    PrintJob_t aux;
    char buf[32];

    do
    {
        opcion = mensajes();

        switch (opcion)
        {

        case 1:

            job.id = id_counter++;

            printf("Usuario: ");
            fgets(job.usuario, MAX_USER, stdin);
            job.usuario[strcspn(job.usuario, "\n")] = '\0';

            printf("Documento: ");
            fgets(job.documento, MAX_DOC, stdin);
            job.documento[strcspn(job.documento, "\n")] = '\0';

            printf("Paginas: ");
            fgets(buf, sizeof(buf), stdin);
            job.paginas_total = (int)strtol(buf, NULL, 10);

            if (job.usuario[0] == '\0' || job.documento[0] == '\0' || job.paginas_total <= 0)
            {
                printf("Error: datos invalidos\n");
                id_counter--;
                continuar();
                break;
            }

            printf("Prioridad (0=NORMAL, 1=URGENTE): ");
            fgets(buf, sizeof(buf), stdin);
            job.prioridad = (Prioridad_t)strtol(buf, NULL, 10);

            if (job.prioridad != URGENTE)
                job.prioridad = NORMAL;

            job.paginas_restantes = job.paginas_total;
            job.copias = 1;
            job.estado = EN_COLA;
            job.ms_por_pagina = 300;

            int ok;

            if (job.prioridad == URGENTE)
                ok = qd_enqueue_urgente(&cola, job);
            else
                ok = qd_enqueue(&cola, job);

            if (ok)
                printf("Trabajo agregado ID=%d\n", job.id);

            continuar();
            break;

        case 2:

            if (qd_peek(&cola, &aux))
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

            qd_print(&cola);

            continuar();

            break;

        case 4:

            simular_impresion(&cola);

            break;
        }

    } while (opcion != 5);

    qd_destroy(&cola);
}

/* ----------- FUNCIONES DE COLA ----------- */

void qd_init(QueueDynamic_t *q)
{
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
}

int qd_is_empty(const QueueDynamic_t *q)
{
    return q->head == NULL;
}

int qd_enqueue(QueueDynamic_t *q, PrintJob_t job)
{
    Node_t *newNode = (Node_t *)malloc(sizeof(Node_t));

    if (newNode == NULL)
    {
        printf("Error: no hay memoria disponible\n");
        return 0;
    }

    newNode->job = job;
    newNode->next = NULL;

    if (qd_is_empty(q))
    {
        q->head = newNode;
        q->tail = newNode;
    }
    else
    {
        q->tail->next = newNode;
        q->tail = newNode;
    }

    q->size++;

    return 1;
}

int qd_peek(const QueueDynamic_t *q, PrintJob_t *out)
{
    if (qd_is_empty(q))
        return 0;

    *out = q->head->job;
    return 1;
}

int qd_dequeue(QueueDynamic_t *q, PrintJob_t *out)
{
    if (qd_is_empty(q))
        return 0;

    Node_t *temp = q->head;

    *out = temp->job;

    q->head = q->head->next;

    if (q->head == NULL)
        q->tail = NULL;

    free(temp);

    q->size--;

    return 1;
}

void qd_print(const QueueDynamic_t *q)
{
    if (qd_is_empty(q))
    {
        printf("\nCola vacia\n");
        return;
    }

    Node_t *current = q->head;

    printf("\nCOLA DE IMPRESION\n");

    while (current != NULL)
    {
        printf("ID:%d  Usuario:%s  Doc:%s  Pag:%d\n",
               current->job.id,
               current->job.usuario,
               current->job.documento,
               current->job.paginas_total);

        current = current->next;
    }
}

void qd_destroy(QueueDynamic_t *q)
{
    Node_t *current = q->head;

    while (current != NULL)
    {
        Node_t *temp = current;
        current = current->next;
        free(temp);
    }

    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
}

void simular_impresion(QueueDynamic_t *q)
{
    PrintJob_t job;

    while (!qd_is_empty(q))
    {
        qd_dequeue(q, &job);

        job.estado = IMPRIMIENDO;

        printf("\nImprimiendo trabajo ID %d (%s)\n",
               job.id, job.documento);

        while (job.paginas_restantes > 0)
        {
            printf("Pagina %d de %d\n",
                   job.paginas_total - job.paginas_restantes + 1,
                   job.paginas_total);

            delay_ms(job.ms_por_pagina);

            job.paginas_restantes--;
        }

        job.estado = COMPLETADO;

        printf("Trabajo %d COMPLETADO\n", job.id);
        trabajos_completados++;
        paginas_impresas += job.paginas_total;
    }

    printf("\nTodos los trabajos fueron impresos\n");
    printf("\nESTADISTICAS\n");
    printf("Trabajos completados: %d\n", trabajos_completados);
    printf("Paginas impresas: %d\n", paginas_impresas);

    continuar();
}

int qd_enqueue_urgente(QueueDynamic_t *q, PrintJob_t job)
{
    Node_t *newNode = (Node_t *)malloc(sizeof(Node_t));

    if (newNode == NULL)
    {
        printf("Error: no hay memoria disponible\n");
        return 0;
    }

    newNode->job = job;
    newNode->next = q->head;

    q->head = newNode;

    if (q->tail == NULL)
        q->tail = newNode;

    q->size++;

    return 1;
}

void delay_ms(int ms)
{
#ifdef _WIN32
    Sleep(ms);
#else
    usleep(ms * 1000);
#endif
}

void continuar()
{
    char buf[4];
    printf("\nPresiona ENTER para continuar...");
    fgets(buf, sizeof(buf), stdin);
}
