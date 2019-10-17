#include <stdio.h>
#include <stdlib.h>

typedef struct neuron
{
  double *w;
  double threshold;
  struct neuron *next_layer[];
  double error;
  double y;
} LTU_neuron;

typedef enum
{
  ERROR_OK = 0;
} ERROR_CODE;



int main (void)
{

}
