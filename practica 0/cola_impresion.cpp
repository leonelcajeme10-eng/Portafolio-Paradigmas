#include <stdio.h>


typedef struct trabajo
{
    int id; // numero autoincremental
    char usuario[32]; // quien mando imprimir
    char documento[42]; // titulo del documento
    int total_pgs; // numero total de paginas
    int restante_pgs; // paginas restantes por imprimir
    int copias; // copias por imprimir
    priority_t prioridad; // NORMAL, URGENTE
    state_t estado; // EN COLA, IMPRIMIENDO, COMPLETADO
}Trabajo;

typedef enum
{
    NORMAL,
    URGENTE
}priority_t;

typedef enum
{
    EN_COLA, 
    IMPRIMIENDO,
    COMPLETADO
}state_t;

void mensajes();
int  menu();

main ()
{

}

