#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef enum
{
  ERROR_OK = 0
} ERROR_CODE;

/*Estructura de una neurona
-TamanoMatriz = Tamaño de la matriz de pesos de la neurona
-*W = Matriz de pesos de la Neurona
-Bw = Bias de la neurona
*/
typedef struct Def_Neurona
{
  int TamanoMatriz;
  double *W;
  struct Def_Neurona *NextLayer;
  double Error;
  double Bw;
} Neurona;

/*Función que asigna el tamaño del arreglo de pesos, el arreglo de pesos y el bias
en una neurona especificada*/
void InstanciarNeurona (Neurona *NuevaNeurona, int TamanoMatriz, double W1, double W2, double Bw)
{
  NuevaNeurona -> TamanoMatriz = TamanoMatriz;
  NuevaNeurona -> W = (double *) malloc (sizeof (double) * TamanoMatriz);
  NuevaNeurona -> W[0] = W1;
  if (TamanoMatriz == 2)
    NuevaNeurona -> W[1] = W2;
  NuevaNeurona -> Bw = Bw;
}

/*Función que asigna el tamaño del arreglo de pesos, el arreglo de pesos y el bias
en una neurona especificada, además asigna valores aleatorios a todos los parametros*/
void InstanciarNeuronaHebb (Neurona *NuevaNeurona, int TamanoMatriz)
{
  NuevaNeurona -> TamanoMatriz = TamanoMatriz;
  NuevaNeurona -> W = (double *) malloc (sizeof (double) * TamanoMatriz);
  srand48(time(NULL));
  NuevaNeurona -> W[0] = drand48();
  if (TamanoMatriz == 2)
    NuevaNeurona -> W[1] = drand48();
  NuevaNeurona -> Bw = drand48();
}

/*Función que lee los valores del arreglo de las entradas dado el tamaño de la matriz
de pesos de la neurona con la que se va a trabajar */
void LeerX (int TamanoMatriz, int *X)
{
  for (int i = 0; i < TamanoMatriz; i++)
  {
    printf ("Ingrese la entrada #%d\n", i + 1);
    scanf ("%d", &X[i]);
  }
  printf ("\n");
}

/*Función que verifica que el valor que recibe está sobre o debajo del Threshold (0.5)*/
int VerificarThreshold (double ResultadoEcuacion)
{
  if (ResultadoEcuacion >= 0.5)
    return 1;
  else
    return 0;
}

/*Función que verifica que el valor que recibe está sobre o debajo del Threshold (0)*/
int VerificarThresholdHebb (double ResultadoEcuacion)
{
  if (ResultadoEcuacion >= 0)
    return 1;
  else
    return -1;
}

/*Función que resuelve la ecuación LTI dados una neurona con sus pesos establecidos,
el tamaño de la matriz de los pesos y una matriz con valores de entrada*/
double Ecuacion (Neurona NeuronaActual, int *X)
{
  double ResultadoEcuacion = 0;
  for (int i = 0; i < NeuronaActual.TamanoMatriz; i++)
    ResultadoEcuacion += X[i]*NeuronaActual.W[i];
  ResultadoEcuacion += NeuronaActual.Bw;
  return ResultadoEcuacion;
}

/*Función que resuelve la ecuación LTI dados una neurona con sus pesos establecidos,
el tamaño de la matriz de los pesos y una matriz con valores de entrada*/
double EcuacionHebb (Neurona NeuronaActual, int Tabla[4][3], int Iteracion)
{
  for(int ContadorEntradas = 0; ContadorEntradas < NeuronaActual.TamanoMatriz; ContadorEntradas++)
    printf ("Entrada: %d\n", Tabla[Iteracion][ContadorEntradas]);
  double ResultadoEcuacion = 0;
  for (int i = 0; i < NeuronaActual.TamanoMatriz; i++)
    ResultadoEcuacion += Tabla[Iteracion][i]*NeuronaActual.W[i];
  ResultadoEcuacion += NeuronaActual.Bw;
  printf ("EcuacionHebb resolvió para un valor de: %f\n", ResultadoEcuacion);
  return ResultadoEcuacion;
}

void EntrenarNeuronaHebb (Neurona *NeuronaActual, int Tabla[4][3], int Combinaciones)
{
  int Iteracion = 0;
  double ResultadoEcuacion = 0, VelocidadAprendizaje = 0.2;
  for (int ContadorPesos = 0; ContadorPesos < NeuronaActual -> TamanoMatriz; ContadorPesos++)
    printf ("Peso inicial %d: %f\n", ContadorPesos + 1, NeuronaActual -> W[ContadorPesos]);
  printf ("\n");
  printf ("Siguiente resultado esperado: %d\n", Tabla[0][1]);
  while (Iteracion < Combinaciones)
  {
    ResultadoEcuacion = EcuacionHebb (*NeuronaActual, Tabla, Iteracion);
    if (VerificarThresholdHebb(ResultadoEcuacion) == Tabla[Iteracion][NeuronaActual -> TamanoMatriz])
    {
      printf ("Correcto\n\n");
      Iteracion++;
      if(Iteracion != Combinaciones)
        printf ("Siguiente resultado esperado: %d\n", Tabla[Iteracion][NeuronaActual->TamanoMatriz]);
    }
    else
    {
      printf ("Incorrecto\n");
      for (int i = 0; i < NeuronaActual->TamanoMatriz; i++)
      {
        NeuronaActual->W[i] =  NeuronaActual->W[i] + (VelocidadAprendizaje * Tabla[Iteracion][NeuronaActual->TamanoMatriz] * Tabla[Iteracion][i]);
        printf ("Peso nuevo %d: %f\t", i + 1, NeuronaActual->W[i]);
      }
      printf ("\n");
    }
  }
  printf ("Fin del entrenamiento\n\n");
}

int main (void)
{
  system ("clear");
  int Repetir, *X;
  Neurona And, Or, Not, AndHebb, OrHebb, NotHebb;
  int TablaAnd[4][3] =
  {
    {-1, -1, -1}, {-1, 1, -1}, {1, -1, -1}, {1, 1, 1}
  };
  int TablaOr[4][3] =
  {
    {-1, -1, -1}, {-1, 1, 1}, {1, -1, 1}, {1, 1, 1}
  };
  int TablaNot[4][3] =
  {
    {-1, 1, 0}, {1, -1, 0}, {0, 0, 0}, {0, 0, 0}
  };
  X = (int *) malloc (sizeof (int) * 2);
  InstanciarNeurona (&And, 2, 1, 1, -1);
  InstanciarNeurona (&Or, 2, 1, 1, 0);
  InstanciarNeurona (&Not, 1, -1, 0, 0.75);
  InstanciarNeuronaHebb (&AndHebb, 2);
  InstanciarNeuronaHebb (&OrHebb, 2);
  InstanciarNeuronaHebb (&NotHebb, 1);
  printf ("Inicia entrenamiento para neurona And:\n\n");
  EntrenarNeuronaHebb (&AndHebb, TablaAnd, 4);
  printf ("Inicia entrenamiento para neurona Or:\n\n");
  EntrenarNeuronaHebb (&OrHebb, TablaOr, 4);
  printf ("Inicia entrenamiento para neurona Not:\n\n");
  EntrenarNeuronaHebb (&NotHebb, TablaAnd, 2);
  do
  {
    printf ("Seleccione la neurona con que trabajar:\n\n");
    printf ("1.- And\n");
    printf ("2.- Or\n");
    printf ("3.- Not\n\n");
    printf ("-Algoritmo de entrenamiento (Hebb)-\n\n");
    printf ("4.- And\n");
    printf ("5.- Or\n");
    printf ("6.- Not\n");
    printf ("7.- Xor\n");
    printf ("8.- Salir\n");
    printf ("\n");
    scanf ("%d", &Repetir);
    printf ("\n");
    switch (Repetir)
    {
      case 1:
      LeerX (2, X);
      printf ("El resultado es: %d\n\n", VerificarThreshold (Ecuacion (And, X)));
      break;
      case 2:
      LeerX (2, X);
      printf ("El resultado es: %d\n\n", VerificarThreshold (Ecuacion (Or, X)));
      break;
      case 3:
      LeerX (1, X);
      printf ("El resultado es: %d\n\n", VerificarThreshold (Ecuacion (Not, X)));
      break;
      case 4:
      LeerX (2, X);
      printf ("El resultado sin procesar es: %f\n", Ecuacion (AndHebb, X));
      printf ("El resultado es: %d\n\n", VerificarThresholdHebb (Ecuacion (AndHebb, X)));
      break;
      case 5:
      LeerX (2, X);
      printf ("El resultado sin procesar es: %f\n", Ecuacion (OrHebb, X));
      printf ("El resultado es: %d\n\n", VerificarThresholdHebb (Ecuacion (OrHebb, X)));
      break;
      case 6:
      LeerX (1, X);
      printf ("El resultado sin procesar es: %f\n", Ecuacion (NotHebb, X));
      printf ("El resultado es: %d\n\n", VerificarThresholdHebb (Ecuacion (NotHebb, X)));
      break;
    }
  }
  while (Repetir != 8);
  free (And.W);
  free (Or.W);
  free (Not.W);
}
