#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (void)
{
	char Arreglo1[50], Arreglo2[50];
	printf ("Ingrese el contenido del arreglo 1 (Cadena)\n");
	gets (Arreglo1);
	printf ("Ahí le va el arreglo 1:\n");
	puts (Arreglo1);
	strcpy (Arreglo2, Arreglo1);
	printf ("Ahí le va el arreglo 2:\n");
	puts (Arreglo2);
}