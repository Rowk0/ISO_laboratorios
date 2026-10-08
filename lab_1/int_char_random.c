#include <stdio.h>   
#include <stdlib.h> 
#include <time.h>

double delay(int min_miliseg, int max_miliseg);

//Tercer proceso Genera (Una letra acompañada de un numero entero)

int main(void)
{
    int caracterRand = 0, num_rand = 0;
    clock_t tiempo_init, tiempo_end;
    double seg = 0, dey = 0;
    FILE *archivo =  fopen("int_char_random.txt", "w");

    fprintf(archivo, "Iniciando proceso\n\n");

    srand(time(NULL));

    for (int i = 0; i < 100; i++)
    {
        printf("\n=====Ciclo %d=====\n", i);

        tiempo_init = clock();

        caracterRand = 65 + (rand() % (90 + 1 - 65));

        num_rand = rand() % 10;
        
        printf("\n%c%d", caracterRand, num_rand);

        tiempo_end = clock();

        seg = (double) (tiempo_end - tiempo_init)/CLOCKS_PER_SEC;
        printf("\nLa cpu tardó [%f] segs en generar una letra y un numero\n", seg);	

        //dey = delay(0, 3000);
        printf("DELAY: %.2f segs\n", dey);

        fprintf(archivo, "Generacion: %c%d\n Tiempo generacion: %f\n Delay: %.2f\n", caracterRand, num_rand, seg, dey);
    }

    fprintf(archivo, "\nProceso terminado\n");

    fclose(archivo);

	return 0;
}

double delay(int min_miliseg, int max_miliseg)
{
	double segs = 0, ticks = 0, milisegs;
	clock_t tiempo_inicio, tiempo_final;

	milisegs = (rand() % (max_miliseg - min_miliseg + 1)) + min_miliseg; //Genera de 0 a 3000 milisegundos 

	ticks = milisegs / 1000.0 * CLOCKS_PER_SEC; //Convierte milisegundos a ticks

	tiempo_inicio = clock(); //toma una fotografía de los ciclos actuales del cpu

	while (clock() < tiempo_inicio + ticks); //Bucle, saca fotos de los ticks actuales hasta llegar a los esperados

	tiempo_final = clock(); //toma una fotografía de los ciclos actuales del cpu

	tiempo_final -= tiempo_inicio; //La diferencia entre ambos dara el valor de tiempo de espera

	return (double) tiempo_final/CLOCKS_PER_SEC; //Devuelve segundos
}