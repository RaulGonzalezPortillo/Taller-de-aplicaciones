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
	TipoComplejo Numero;
	printf ("Buenas noches\n");
	printf ("Ingrese la parte real de su número:\n");
	scanf ("%f", &Numero.Real);
	printf ("Ingrese la parte imaginaria de su número:\n");
	scanf ("%f", &Numero.Imaginario);
	printf ("Ahí le va su número si o no raza\n");
	printf ("%f%+fi\n", Numero.Real, Numero.Imaginario);
}