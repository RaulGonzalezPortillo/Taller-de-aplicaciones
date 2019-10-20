#include <stdio.h>
#include <stdlib.h>

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
  NuevaNeurona -> W[0] = W1;
  if (TamanoMatriz == 2)
  {
    NuevaNeurona -> W[1] = W2;
  }
  NuevaNeurona -> Bw = Bw;
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

/*Función que resuelve la ecuación LTI dados una neurona con sus pesos establecidos,
el tamaño de la matriz de los pesos y una matriz con valores de entrada*/
double Ecuacion (Neurona NeuronaOperadora, int TamanoMatriz, int *X)
{
  double ResultadoEcuacion = 0;
  for (int i = 0; i < TamanoMatriz; i++)
  {
    ResultadoEcuacion += X[i]*NeuronaOperadora.W[i];
  }
  ResultadoEcuacion += NeuronaOperadora.Bw;
  return ResultadoEcuacion;
}

/*Función que verifica que el valor que recibe está sobre o debajo del Threshold (0.5)*/
int VerificarThreshold (double ResultadoEcuacion)
{
  if (ResultadoEcuacion >= 0.5)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

int main (void)
{
  int Repetir, *X;
  Neurona And, Or, Not;
  X = (int *) malloc (sizeof (int) * 2);
  And.W = (double *) malloc (sizeof (double) * 2);
  Or.W = (double *) malloc (sizeof (double) * 2);
  Not.W = (double *) malloc (sizeof (double));
  InstanciarNeurona (&And, 2, 1, 1, -1);
  InstanciarNeurona (&Or, 2, 1, 1, 0);
  InstanciarNeurona (&Not, 1, -1, 0, 0.75);
  do
  {
    printf ("Seleccione la neurona con que trabajar:\n\n");
    printf ("1.- And\n");
    printf ("2.- Or\n");
    printf ("3.- Not\n");
    printf ("4.- Xor\n");
    printf ("5.- Salir\n");
    printf ("\n");
    scanf ("%d", &Repetir);
    printf ("\n");
    switch (Repetir)
    {
      case 1:
      LeerX (2, X);
      printf ("El resultado es: %d\n\n", VerificarThreshold (Ecuacion (And, 2, X)));
      break;
      case 2:
      LeerX (2, X);
      printf ("El resultado es: %d\n\n", VerificarThreshold (Ecuacion (Or, 2, X)));
      break;
      case 3:
      LeerX (1, X);
      printf ("El resultado es: %d\n\n", VerificarThreshold (Ecuacion (Not, 1, X)));
      break;
      case 4:
      break;
    }
  }
  while (Repetir != 5);
  free (And.W);
  free (Or.W);
  free (Not.W);
}
