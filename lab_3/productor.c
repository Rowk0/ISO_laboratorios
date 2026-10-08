#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#define MAX_CHAR 100
#define CLAVE 246

//gcc productor.c -o ./productor.out && ./productor.out

struct 
{
    long tipo;
    char cadena[MAX_CHAR];
} mensaje;


int main()
{
    int msqid;
    int longitud = sizeof(mensaje) - sizeof(mensaje.tipo);

    //Creando la cola de mensajes
    //Cuando está entre parentesis una asignacion, tiene mayor prioridad que una comparacion (==)

    if ((msqid = msgget(CLAVE, IPC_CREAT | 0600)) == -1)
    {
        printf("Error al crear la cola de mensajes \n");
        exit(-1);
    }

    //Preparacion de mensaje
    
    mensaje.tipo = 1;
    strcpy(mensaje.cadena, "Hola, soy Rodriguez");

    printf("Mensaje enviado desde productor: %s\n", mensaje.cadena);

    // Envio de mensaje a la cola clave 246

    if (msgsnd(msqid, &mensaje, longitud, 0) == -1)
    {
        printf("Error al enviar el mensaje a la cola de mensajes");
        exit(-1);
    }
    

    return 0;
}