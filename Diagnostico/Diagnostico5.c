#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (void)
{
	int Tamano, i;
	printf ("¿De que tamaño el arreglo joven?\n");
	scanf ("%d", &Tamano);
	int *Arreglo1 = (int *) malloc (sizeof (int) * Tamano);
	for (i = 0; i < Tamano; i++)
	{
		printf ("Ingrese el número %d:\n", i + 1);
		scanf ("%d", &Arreglo1 [i]);
	}
	printf ("Ahí le va el arreglo, oh si\n");
	for (i = 0; i < Tamano; i++)
	{
		printf ("%d\n", Arreglo1 [i]);
	}
}