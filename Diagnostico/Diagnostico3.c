#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Def_Dato
{
	int Dato;
	struct Def_Dato *Sig;
} TipoDato;

void InsertaFin (int Numero, TipoDato **Inicio);
void ImprimirLista (TipoDato *Inicio);
void BorrarLista (TipoDato *Inicio);

int main (void)
{
	int Numero, Repetidor;
	TipoDato *Inicio = NULL;
	do
	{
		printf ("Ingrese un número:\n");
		scanf ("%d", &Numero);
		printf ("¿Quiere ingresar otro? (1 = Sí)\n");
		scanf ("%d", &Repetidor);
	}
	while (Repetidor == 1);
	printf ("Ahí te va la lista:\n");
	InsertaFin (Numero, &Inicio);
	ImprimirLista (Inicio);
	BorrarLista (Inicio);
}

void InsertaFin (int Numero, TipoDato **Inicio)
{
	TipoDato *Nuevo, *Temp;
	Nuevo = (TipoDato *) malloc (sizeof (TipoDato));
	Nuevo -> Dato = Numero;
	Nuevo -> Sig = NULL;
	if (*Inicio != NULL)
	{
		Temp = *Inicio;
		while (Temp -> Sig != NULL)
			Temp = Temp -> Sig;
		Temp -> Sig = Nuevo;
	}
	else
		*Inicio = Nuevo;
}

void ImprimirLista (TipoDato *Inicio)
{
	TipoDato *Temp;
	Temp = Inicio;
	while (Temp != NULL)
	{
		printf ("%d\n", Temp -> Dato);
		Temp = Temp -> Sig;
	}
}

void BorrarLista (TipoDato *Inicio)
{
	TipoDato *Temp;
	while (Inicio != NULL)
	{
		Temp = Inicio;
		Inicio = Inicio -> Sig;
		free (Temp);
	}
}