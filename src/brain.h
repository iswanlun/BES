#ifndef BRAIN_H
#define BRAIN_H

#include <stdint.h>
#include "env.h"

#define IN(x)       ( ( x >> 24 ) & 0x7F )      /* Input neuron index and buffer */
#define OUT(x)      ( ( x >> 16 ) & 0x7F )      /* Output neuron index and buffe */
#define IN_SRC(x)   ( ( x >> 31 ) & 0x1  )      /* Input source */
#define OUT_SRC(x)  ( ( x >> 23 ) & 0x1  )      /* Output source */

void brain_react( brain* br, environment* env );

#endif