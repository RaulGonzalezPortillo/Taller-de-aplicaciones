//Este programa regenera una señal por el método de Fourier mediante los datos de su
//Amplitud, frecuencia, número de harmónicos y tiempo final los cuales ingresa el
//usuario dentro del programa

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct def_Senal //Estructura de la señal, n = número de harmónicos, A = Amplitud, f = frecuencia, tf = tiempo final, t = Arreglo de t, ft = Arreglo de f(t)
{
  int n;
  double A, f, tf;
  double *t, *ft;
  struct def_Senal *Sig;
} TipoSenal;

void PedirDatos (double *A, double *f, int *n, double *tf, int *sizeoft) //Esta función le pide al usuario los datos de la señal y los devuelve al main
{
  printf ("Introduzca los sigs. datos\n\n");
  printf ("Amplitud\n\n");
  scanf ("%lf", A);
  printf ("\n");
  printf ("Frecuencia\n\n");
  scanf ("%lf", f);
  printf ("\n");
  printf ("Número de harmónicos\n\n");
  scanf ("%d", n);
  printf ("\n");
  printf ("Tiempo final\n\n");
  scanf ("%lf", tf);
  printf ("\n");
  printf ("Tamaño de T\n\n");
  scanf ("%d", sizeoft);
  printf ("\n");
}

void Instanciar (double A, double f, int n, double tf, int sizeoft, TipoSenal *Senal) //Esta función instancia la estructura de la señal, asignando los valores del usuario y reservando la memoria necesaria
{
  Senal -> A = A;
  Senal -> f = f;
  Senal -> n = n;
  Senal -> tf = tf;
  Senal -> t = (double *) malloc (sizeof (double) * sizeoft);
  Senal -> ft = (double *) malloc (sizeof (double) * sizeoft);
}

void Resolver (double sizeoft, TipoSenal *Senal) //Esta función recibe el tamaño de los arreglos y la señal instanciada, procede a resolver por Fourier
{
  int i;
  double j;
  double Incremento = Senal -> tf / sizeoft;
  double Sumatoria;
  for (i = 0; i <= sizeoft; i++)
  {
    Senal -> t[i] = Incremento * (i);
    //printf (" %lf", Senal -> t[i]);
    Sumatoria = 0;
    for (j = 1; j <= Senal -> n; j++)
    {
      Sumatoria += (- ((Senal -> A / (M_PI * j)) * (cos (M_PI * j) - 1) * (sin (2 * M_PI * j * Senal -> f * Senal -> t[i]))));
      //printf (" %lf", Sumatoria);
    }
    Senal -> ft[i] = Sumatoria + (Senal -> A / 2);
  }
}

void ImprimirArch (double sizeoft, TipoSenal Senal) //Esta función recorre los arreglos de t y de f(t) y guarda los datos en un archivo
{
  int i;
  FILE *Archivo;
  printf ("\n");
  Archivo = fopen ("DatosFourier.txt", "wt");
  for (i = 0; i < sizeoft; i++)
  {
    fprintf (Archivo, "%lf %lf\n", Senal.t [i], Senal.ft [i]);
  }
  fclose (Archivo);
}

void Graficar() //Abre GNU plot, le envía los datos registrados y los grafica, añadiendole título a los ejes y a la gráfica
{
  int i;
  char *AbrirGnuPlot[] = {"set title \"Método de Fourier\"",
			  "set ylabel \"----f(t)--->\"",
			  "set xlabel \"----t--->\"",
			  "plot \"DatosFourier.txt\" with lines"
  };
  FILE *VentanaGnuPlot = popen ("gnuplot -persist", "w");
  for (i=0; i<4; i++)
    fprintf(VentanaGnuPlot, "%s \n", AbrirGnuPlot[i]);
}

int main (int argc, char *argv[])
{
  int n, sizeoft;
  double A, f, tf;
  TipoSenal Senal;
  PedirDatos (&A, &f, &n, &tf, &sizeoft);
  Instanciar (A, f, n, tf, sizeoft, &Senal);
  Resolver (sizeoft, &Senal);
  ImprimirArch (sizeoft, Senal);
  Graficar ();
}
