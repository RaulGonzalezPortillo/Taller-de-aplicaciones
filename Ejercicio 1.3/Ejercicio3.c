#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct def_Nodo
{
  int Cantidad;
  char ID;
  struct def_Nodo **Aristas;
} TipoNodo;

void Enter ()
{
  printf ("Presiona Enter para continuar...\n\n");
  __fpurge (stdin);
  getchar ();
  __fpurge (stdin);
  printf ("\n");
}

void BuscarDireccionNodo (TipoNodo *Inicio, int Contador, int ConexionesMax, char IDBuscar, TipoNodo **NodoEncontrado)
{
  if (Inicio != NULL)
  {
    if (Inicio -> ID != IDBuscar)
    {
      while (Contador < ConexionesMax)
      {
        if (Inicio -> Aristas [Contador] != NULL)
        {
          BuscarDireccionNodo (Inicio -> Aristas [Contador], Contador, ConexionesMax, IDBuscar, NodoEncontrado);
        }
        Contador++;
      }
    }
    else
    {
      *NodoEncontrado = Inicio;
    }
  }
}

void AnadirNodo (char *ID, TipoNodo **Inicio, int ConexionesMax)
{
  int i, Error;
  char IDPrevio;
  TipoNodo *Nuevo, *Previo;
  Nuevo = (TipoNodo *) malloc (sizeof (TipoNodo));
  Nuevo -> Cantidad = 0;
  Nuevo -> ID = *ID;
  Nuevo -> Aristas = (TipoNodo **) malloc (sizeof (TipoNodo *) * ConexionesMax);
  for (i = 0; i < ConexionesMax; i++)
    Nuevo -> Aristas [i] = NULL;
  printf ("INFO: Agregando el nodo con el ID %c\n\n", Nuevo -> ID);
  if (*Inicio == NULL)
  {
    *Inicio = Nuevo;
    (*ID)++;
  }
  else
  {
    Error = 1;
    do
    {
      printf ("¿A donde quieres conectar este nodo?\n\n");
      __fpurge (stdin);
      scanf (" %c", &IDPrevio);
      printf ("\n");
      Previo = NULL;
      BuscarDireccionNodo (*Inicio, 0, ConexionesMax, IDPrevio, &Previo);
      if (Previo != NULL)
      {
        printf ("INFO: Añadiendo al nodo con el ID: %c\n\n", Previo -> ID);
        if (Previo -> Cantidad == ConexionesMax - 1)
          printf ("INFO: El nodo está lleno\n\n");
        else
        {
          Previo -> Aristas [Previo -> Cantidad] = Nuevo;
          (Previo -> Cantidad)++;
          printf ("INFO: Nodo añadido\n\n");
          Error = 0;
          (*ID)++;
        }
      }
      else
        printf ("INFO: No se encontró el nodo\n\n");
    }
    while (Error == 1);
  }
  Enter ();
}

void ImprimirGrafo (TipoNodo *Inicio, int Contador, int ConexionesMax)
{
  if (Inicio != NULL)
  {
    while (Contador < ConexionesMax)
    {
      if (Inicio -> Aristas [Contador] != NULL)
      {
        ImprimirGrafo (Inicio -> Aristas [Contador], Contador, ConexionesMax);
      }
      if (Contador == ConexionesMax - 1)
      {
        printf ("%c\n\n", Inicio -> ID);
      }
      Contador++;
    }
  }
}

void BorrarGrafo (TipoNodo *Inicio, int Contador, int ConexionesMax)
{
  if (Inicio != NULL)
  {
    while (Contador < ConexionesMax)
    {
      if (Inicio -> Aristas [Contador] != NULL)
      {
        BorrarGrafo (Inicio -> Aristas [Contador], Contador, ConexionesMax);
      }
      if (Contador == ConexionesMax - 1)
      {
        free (Inicio);
        Inicio = NULL;
      }
      Contador++;
    }
  }
}

void Buscar (TipoNodo *Inicio, int ConexionesMax)
{
  int i;
  char IDBuscador;
  TipoNodo *Buscador;
  printf ("Introduzca el ID del nodo a buscar\n\n");
  __fpurge (stdin);
  scanf (" %c", &IDBuscador);
  printf ("\n");
  Buscador = NULL;
  BuscarDireccionNodo (Inicio, 0, ConexionesMax, IDBuscador, &Buscador);
  if (Buscador != NULL)
  {
    printf ("Se encontró el Nodo con el ID: %c\n\n", Buscador -> ID);
    printf ("Este nodo tiene %d conexiones:\n", Buscador -> Cantidad);
    for (i = 0; Buscador -> Aristas [i] != NULL; i++)
      printf ("Arista %d: Conectada al nodo %c\n", i + 1, Buscador -> Aristas [i] -> ID);
    printf ("\n");
  }
  else
  {
    printf ("No se encontró el nodo...\n\n");
  }
  Enter ();
}

void AnadirArista (TipoNodo *Inicio, int ConexionesMax)
{
  char IDOrigen, IDDestino;
  TipoNodo *Origen, *Destino;
  printf ("Introduzca el ID del nodo origen\n\n");
  scanf (" %c", &IDOrigen);
  printf ("Introduzca el ID del nodo destino\n\n");
  scanf (" %c", &IDDestino);
  Origen = NULL;
  Destino = NULL;
  BuscarDireccionNodo (Inicio, 0, ConexionesMax, IDOrigen, &Origen);
  BuscarDireccionNodo (Inicio, 0, ConexionesMax, IDDestino, &Destino);
  if (Origen == NULL || Destino == NULL)
  {
    printf ("No se encontró alguno de los nodos\n\n");
  }
  else
  {
    if (Origen -> Cantidad == ConexionesMax - 1)
    {
      printf ("El nodo origen está lleno\n\n");
    }
    else
    {
      Origen -> Aristas [Origen -> Cantidad] = Destino;
      (Origen -> Cantidad)++;
    }
  }
}

int main (void)
{
  int ConexionesMax, Seleccion;
  char IDActual = 97;
  TipoNodo *Inicio = NULL;
  system ("clear");
  printf ("Ingrese el número de conexiones máximas por Nodo:\n\n");
  scanf ("%d", &ConexionesMax);
  printf ("\n");
  do
  {
    printf ("Elija una opción:\n\n");
    printf ("1.- Añadir nodo\n");
    printf ("2.- Añadir arista\n");
    printf ("3.- Desplegar gráfo\n");
    printf ("4.- Buscar dato\n");
    printf ("5.- Salir y liberar memoria\n\n");
    scanf ("%d", &Seleccion);
    printf ("\n");
    switch (Seleccion)
    {
      case 1:
      AnadirNodo (&IDActual, &Inicio, ConexionesMax);
      break;
      case 2:
      AnadirArista (Inicio, ConexionesMax);
      break;
      case 3:
      ImprimirGrafo (Inicio, 0, ConexionesMax);
      break;
      case 4:
      Buscar (Inicio, ConexionesMax);
      break;
      case 5:
      BorrarGrafo (Inicio, 0, ConexionesMax);
      break;
    }
  } while (Seleccion != 5);
}
