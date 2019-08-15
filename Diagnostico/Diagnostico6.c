#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Def_Complejo
{
	float Real;
	float Imaginario;
} TipoComplejo;

int main (void)
{
	int Tamano;
	printf ("Ingrese el tamaño del arreglo:\n");
	scanf ("%d", &Tamano);
	TipoComplejo *Arreglo1 = (TipoComplejo *) malloc (sizeof (TipoComplejo) * Tamano);
	printf ("Se logró...creo\n");
}