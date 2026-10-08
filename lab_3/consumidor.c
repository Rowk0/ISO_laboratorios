#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#define MAX_CHAR 100
#define CLAVE 246

//gcc consumidor.c -o ./consumidor.out && ./consumidor.out

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

    if ((msqid = msgget(CLAVE, IPC_CREAT | 0600)) == -1)
    {
        printf("Error al crear la cola de mensajes \n");
        exit(-1);
    }

    //Recepcion del mensaje
    
    if (msgrcv(msqid, &mensaje, longitud, 1, 0) == -1)
    {
        printf("Error al leer un mensaje en la cola de mensajes\n");
        exit(-1);
    }

    printf("El mensaje leido en consumidor es: %s\n", mensaje.cadena);
    
    //borrado de cola de mensajes

    if(msgctl(msqid, IPC_RMID, 0) == -1)
    {
        printf("Error al eliminar la cola de mensajes\n");
        exit(-1);
    }

    return 0;
}