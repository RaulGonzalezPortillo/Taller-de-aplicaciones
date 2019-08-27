#include <stdio.h>
#include <time.h>

int main (void)
{
	double Tiempo = 0.0;
	int RepeticionesInf, RepeticionesSup, IteracionActual;
	long long int Num1, Num2, Resultado;
	FILE *Archivo;
	Archivo = fopen ("DatosIterativo.txt", "wt");
	printf ("Ingrese el límite inferior de iteraciones:\n");
	scanf ("%d", &RepeticionesInf);
	printf ("Ingrese el límite superior de iteraciones:\n");
	scanf ("%d", &RepeticionesSup);
	Num1 = 0;
	Num2 = 1;
	clock_t Inicio = clock ();
	for (IteracionActual = 2; IteracionActual <= RepeticionesSup; IteracionActual++)
	{
		Resultado = Num1 + Num2;
		Num1 = Num2;
		Num2 = Resultado;
		if (IteracionActual >= RepeticionesInf)
		{
			clock_t Fin = clock ();
			Tiempo = (double)(Fin - Inicio) / CLOCKS_PER_SEC;
			fprintf (Archivo, "%d ", IteracionActual);
			printf ("Iteración %d = %lld - ", IteracionActual, Resultado);
			fprintf (Archivo, "%f\n", Tiempo);
			printf ("%fs\n", Tiempo);	
		}
	}
	printf ("El resultado es: %lld\n", Resultado);
}