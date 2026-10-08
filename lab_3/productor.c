#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <time.h>
#include <unistd.h>
#define MAX_CHAR 100
#define CLAVE 246
#define MAX_DATOS 105

//gcc productor.c -o ./productor.out && ./productor.out

typedef struct 
{
    long tipo;
    char cadena[MAX_CHAR];
} mensaje_;

int main()
{
    mensaje_ mensaje;
    int msqid;
    int longitud = sizeof(mensaje) - sizeof(mensaje.tipo);

    srand(time(NULL));

    //Creando la cola de mensajes
    //Cuando está entre parentesis una asignacion, tiene mayor prioridad que una comparacion (==)

    if ((msqid = msgget(CLAVE, IPC_CREAT | 0600)) == -1)
    {
        printf("Error al crear la cola de mensajes \n");
        exit(-1);
    }

    printf("Productor iniciado, enviando %d datos\n", MAX_DATOS);

    for (int i = 0; i < MAX_DATOS; i++)
    {
        //Retardo aleatorio entre 0.1 y 0.5 segs

        int retardo = 100000 + rand() % 400000;  
        usleep(retardo);

        //Preparacion de mensaje

        mensaje.tipo = 1;
        snprintf(mensaje.cadena, sizeof(mensaje.cadena), "Dato N°:%d", i);
        printf("[PRODUCTOR] %s [Retardo] %d\n", mensaje.cadena, retardo / 1000);

        // Envio de mensaje a la cola clave 246

        if (msgsnd(msqid, &mensaje, longitud, 0) == -1)
        {
            printf("Error al enviar el mensaje a la cola de mensajes");
            exit(-1);
        }

    }

    return 0;
}