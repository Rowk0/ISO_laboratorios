#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double delay(int min_miliseg, int max_miliseg);
//Primer proceso Genera (Números enteros aleatorios entre 0 y 100000000)

//CLOCKS_PER_SEC equivale a 1,000,000.
//CPU genera 1,000,000 de ciclos por cada 1 segundo:

int main()
{
	int alt, n = 0;
	clock_t tiempo_init, tiempo_end;
	double seg, dey = 0;
	FILE *archivo = fopen("int_random.txt", "w");

	fprintf(archivo, "Iniciando proceso\n\n");

	srand(time(NULL));
	
	printf("\n");

	while(n <= 100)
	{
		printf("\n=====Ciclo %d=====\n", n);

        tiempo_init = clock();
         
        alt = rand() % 100000001;
        printf("\nNúmero aleatorio: [%d]", alt);

        tiempo_end = clock();

        seg = (double) (tiempo_end - tiempo_init)/CLOCKS_PER_SEC;
        printf("\nLa cpu tardó [%f] segs en generar el numero", seg);	

        n++;

        dey = delay(0, 3000);
        printf("\nDELAY: %.2f segs\n", dey);

		fprintf(archivo, "Numero: %d\n Tiempo generacion: %f\n Delay: %.2f\n", alt, seg, dey);
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