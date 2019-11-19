#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*Estructura de una neurona
-TamanoMatriz = Tamaño de la matriz de pesos de la neurona
-*W = Matriz de pesos de la Neurona
-Bw = Bias de la neurona
*/
typedef struct Def_Neurona
{
  int TamanoMatriz;
  double *W;
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

/*Función que resuelve la ecuación LTI dados una neurona con sus pesos establecidos,
el tamaño de la matriz de los pesos y un arreglo con valores de entrada*/
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
  double ResultadoEcuacion = 0;
  for (int i = 0; i < NeuronaActual.TamanoMatriz; i++)
    ResultadoEcuacion += Tabla[Iteracion][i]*NeuronaActual.W[i];
  ResultadoEcuacion += NeuronaActual.Bw;
  printf ("Resultado = %f\t", ResultadoEcuacion);
  return ResultadoEcuacion;
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

/*Función que imprime los valores que se encuentren en la matriz de pesos de una
neurona dada*/
void ImprimirPesosIniciales (Neurona NeuronaActual)
{
  for (int i = 0; i < NeuronaActual.TamanoMatriz; i++)
    printf ("Peso inicial %d: %f\t", i + 1, NeuronaActual.W[i]);
  printf ("\n\n");
}

/*Función que dada una neurona, una Tabla con Entradas y Salidas esperadas y el número
de iteración actual, imprime la salida esperada siguiente y las entradas que se utilizaran
para calcularla*/
void ImprimirDatosSiguienteIteracion (Neurona NeuronaActual, int Tabla[4][3], int Iteracion)
{
  printf ("Siguiente resultado: %d\n", Tabla[Iteracion][NeuronaActual.TamanoMatriz]);
  for (int i = 0; i < NeuronaActual.TamanoMatriz; i++)
    printf ("Entrada %d = %d\t", i + 1, Tabla[Iteracion][i]);
  printf ("\n\n");
}

/*Función que dada una Tabla con Entradas y Salidas esperadas y una Neurona, entrena
a la Neurona (ajusta su matriz de pesos) para producir las Salidas de la Tabla
en base a las Entradas*/
void EntrenarNeuronaHebb (Neurona *NeuronaActual, int Tabla[4][3])
{
  int Iteracion = 0;
  double ResultadoEcuacion = 0, VelocidadAprendizaje = 0.2;
  ImprimirPesosIniciales (*NeuronaActual);
  ImprimirDatosSiguienteIteracion (*NeuronaActual, Tabla, Iteracion);
  while (Iteracion < NeuronaActual -> TamanoMatriz * 2)
  {
    ResultadoEcuacion = EcuacionHebb (*NeuronaActual, Tabla, Iteracion);
    if (VerificarThresholdHebb(ResultadoEcuacion) == Tabla[Iteracion][NeuronaActual -> TamanoMatriz])
    {
      printf ("- Correcto\n\n");
      Iteracion++;
      if(Iteracion != NeuronaActual -> TamanoMatriz * 2)
        ImprimirDatosSiguienteIteracion (*NeuronaActual, Tabla, Iteracion);
    }
    else
    {
      printf ("- Incorrecto\n");
      for (int i = 0; i < NeuronaActual->TamanoMatriz; i++)
      {
        NeuronaActual->W[i] =  NeuronaActual->W[i] + (VelocidadAprendizaje * Tabla[Iteracion][NeuronaActual->TamanoMatriz] * Tabla[Iteracion][i]);
        printf ("Peso nuevo %d: %f\t", i + 1, NeuronaActual->W[i]);
      }
      printf ("\n");
    }
  }
  printf ("INFO: Fin del entrenamiento\n\n");
}

/*Función principal, declara a las Neuronas y a las Tablas de Verdad y llama a Tablas
funciones necesarias para instanciar, entrenar y operar a las neuronas mencionadas*/
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
  printf ("INFO: Inicia entrenamiento para neurona AND:\n____________________________________________\n\n");
  EntrenarNeuronaHebb (&AndHebb, TablaAnd);
  printf ("INFO: Inicia entrenamiento para neurona OR:\n___________________________________________\n\n");
  EntrenarNeuronaHebb (&OrHebb, TablaOr);
  printf ("INFO: Inicia entrenamiento para neurona NOT:\n____________________________________________\n\n");
  EntrenarNeuronaHebb (&NotHebb, TablaNot);
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
    printf ("7.- Salir\n");
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
  while (Repetir != 7);
  free (And.W);
  free (Or.W);
  free (Not.W);
  free (AndHebb.W);
  free (OrHebb.W);
  free (NotHebb.W);
}
