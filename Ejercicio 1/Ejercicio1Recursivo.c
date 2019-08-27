#include <stdio.h>
#include <time.h>

void Fibonacci (int RepeticionesInf, int RepeticionesSup, int IteracionActual, clock_t Inicio, long long int Penultimo, long long int Ultimo)
{
	double Tiempo = 0.0;
	clock_t Fin = clock ();
	Tiempo += (double)(Fin - Inicio) / CLOCKS_PER_SEC;
	FILE *Archivo;
	Archivo = fopen ("DatosRecursivo.txt", "at");
	if (IteracionActual >= RepeticionesInf)
	{
		fprintf (Archivo, "%d ", IteracionActual);
		printf ("Iteración %d = %lld - ", IteracionActual, Ultimo);
		fprintf (Archivo, "%f\n", Tiempo);
		printf ("%fs\n", Tiempo);
	}
	if (IteracionActual < RepeticionesSup)
	{
		Fibonacci (RepeticionesInf, RepeticionesSup, IteracionActual + 1, Inicio, Ultimo, Penultimo + Ultimo);
	}
}

int main (void)
{
	FILE *Archivo;
	int RepeticionesInf, RepeticionesSup;
	printf ("Ingrese límite inferior de iteraciones:\n");
	scanf ("%d", &RepeticionesInf);
	printf ("Ingrese límite superior de iteraciones:\n");
	scanf ("%d", &RepeticionesSup);
	Archivo = fopen ("DatosRecursivo.txt", "wt");
	fclose (Archivo);
	clock_t Inicio = clock ();
	Fibonacci (RepeticionesInf, RepeticionesSup, 1, Inicio, 0, 1);
}