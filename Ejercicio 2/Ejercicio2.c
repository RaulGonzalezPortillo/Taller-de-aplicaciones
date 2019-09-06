#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Enter ()
{
	printf ("Presione Enter para continuar...\n\n");
	__fpurge (stdin);
	getchar ();
}

void Compresor (char *argv[], int Cantidad, int *Numero)
{
	int Lector, Desplazador = 12;
	for (int i = 1; i <= Cantidad; i ++)
	{
		sscanf (argv[i], " %d", &Lector);
		if ((strcmp (argv[i], "0") == 0) || (Lector >= 1 && Lector <= 15))
		{
			Lector <<= Desplazador;
			*(Numero) |= Lector;
			Desplazador -= 4;
		}
		else
		{
			system ("clear");
			printf ("Se recibió un caracter alfanumérico inválido\n");
			exit (0);
		}
	}
}

void Extractor (int Cantidad, int Numero, int *Numeros)
{
	int Desplazador = 12;
	Numeros [0] = Numero >> Desplazador;
	for (int i = 1; i < Cantidad; i ++)
	{
		Numero ^= (Numeros [i - 1] << Desplazador);
		Desplazador -= 4;
		Numeros [i] = Numero >> Desplazador;
	}
}

void Imprimir (int Cantidad, int *Numeros)
{
	for (int i = 0; i < Cantidad; i ++)
	{
		printf ("Número %d = %d\n", i + 1, Numeros [i]);
	}
	printf ("\n");
}

void Operacion (int Cantidad, int *Numeros, char Seleccion)
{
	int Numero1, Numero2;
	system ("clear");
	printf ("Eliga el primer número:\n\n");
	scanf ("%d", &Numero1);
	printf ("\n");
	printf ("Eliga el segundo número:\n\n");
	scanf ("%d", &Numero2);
	printf ("\n");
	if (Numero1 <= Cantidad && Numero1 > 0 && Numero2 <= Cantidad && Numero2 > 0)
	{
		switch (Seleccion)
		{
			case '+':
			printf ("%d %c %d = %d\n\n", Numeros [Numero1 - 1], Seleccion, Numeros [Numero2 - 1], Numeros [Numero1 - 1] + Numeros [Numero2 - 1]);
			Enter ();
			break;
			case '-':
			printf ("%d %c %d = %d\n\n", Numeros [Numero1 - 1], Seleccion, Numeros [Numero2 - 1], Numeros [Numero1 - 1] - Numeros [Numero2 - 1]);
			Enter ();
			break;
			case 'x':
			printf ("%d %c %d = %d\n\n", Numeros [Numero1 - 1], Seleccion, Numeros [Numero2 - 1], Numeros [Numero1 - 1] * Numeros [Numero2 - 1]);
			Enter ();
			break;
			case '/':
			printf ("%d %c %d = %d\n\n", Numeros [Numero1 - 1], Seleccion, Numeros [Numero2 - 1], Numeros [Numero1 - 1] / Numeros [Numero2 - 1]);
			Enter ();
			break;
		}
	}
	else
	{
		printf ("Alguno de los números especificados no existe...\n\n");
		Enter ();
	}
}

int main (int argc, char *argv[])
{
	int Numero, Cantidad = argc - 1, Numeros[4];
	char Seleccion;
	if (Cantidad > 4 || Cantidad < 1)
	{
		system ("clear");
		printf ("La cantidad de parámetros introducida es inválida\n\n");
		exit (0);
	}
	else 
	{
		Compresor (argv, Cantidad, &Numero);
		system ("clear");
		printf ("Se recibieron y comprimieron los datos...\n\n");
		Extractor (Cantidad, Numero, Numeros);
		printf ("Se descomprimieron los datos...\n\n");
		Enter ();
		if (Cantidad > 1)
		{
			do
			{
				system ("clear");
				printf ("Eliga una opción...\n\n");
				printf ("(+) Suma\n");
				printf ("(-) Resta\n");
				printf ("(x) Multiplicación\n");
				printf ("(/) División\n");
				printf ("(i) Imprimir\n");
				printf ("(s) Salir\n\n");
				scanf ("%c", &Seleccion);
				switch (Seleccion)
				{
					case '+': 
					Operacion (Cantidad, Numeros, Seleccion);
					break;
					case '-':
					Operacion (Cantidad, Numeros, Seleccion);
					break;
					case 'x':
					Operacion (Cantidad, Numeros, Seleccion);
					break;
					case '/':
					Operacion (Cantidad, Numeros, Seleccion);
					break;
					case 'i':
					system ("clear");
					Imprimir (Cantidad, Numeros);
					Enter ();
					break;
					case 's':
					break;
					default:
					break;
				}
			}
			while (Seleccion != 's');
		}
		else
		{
			system ("clear");
			printf ("Sólo se introdujo 1 dato, no hay operaciones que hacer. Imprimiendo...\n\n");
			Imprimir (Cantidad, Numeros);
		}
	}
}