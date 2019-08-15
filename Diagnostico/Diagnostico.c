#include <stdio.h>
#include <stdlib.h>

void ModificarDosVariables (double *variable1, double *variable2);

int main (void)
{
	double variable1, variable2;
	printf ("Ingrese la variable 1 (Número)\n");
	scanf ("%lf", &variable1);
	printf ("Ingrese la variable 2 (Número)\n");
	scanf ("%lf", &variable2);
	printf ("Variable 1: %f\n", variable1);
	printf ("Variable 2: %f\n", variable2);
	printf ("Intercambiando...\n");
	ModificarDosVariables (&variable1, &variable2);
	printf ("Variable 1: %f\n", variable1);
	printf ("Variable 2: %f\n", variable2);
}

void ModificarDosVariables (double *variable1, double *variable2)
{
	double variabletemp;
	variabletemp = *variable1;
	*variable1 = *variable2;
	*variable2 = variabletemp;
}