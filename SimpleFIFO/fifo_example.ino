#include "SimpleFIFO.h"

#define MAX_COMMAND_FIFO_SIZE 10

/* Basic type for the FIFO */
typedef struct {
  int  smthg;
} s_elem;

SimpleFIFO<s_elem, MAX_COMMAND_FIFO_SIZE> fifo;

void setup()
{
  fifo.flush();
}

void loop()
{
  delay(50);

  s_elem e={42};

  fifo.enqueue(e);
  if (fifo.count() > 0) {

	e = fifo.dequeue();
  }
}
