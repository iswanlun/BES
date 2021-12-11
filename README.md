
# Brain evolution simulator #

## About ##

This simulator mimicks the evolution of organisms, here termed 'brains', by controling their thought processes through gene encoded pathways. Brains are controlled through wiring different neurons together and applying a weight to these connections to either amplify, suppress or invert neural pathways. Brains contain sense neurons to explore their environments, cognition neurons to modulate pathways, and motor neurons to interact with their environment. The simulation has distinct generations at the end of which brains are either culled if they do not meet some predefined criteria, or are allowed to reproduce. Brain reproduction comes with the possibility of mutation which allows brains to evolve traits over generations.

## Gene Gtructure ##

Neural links are encoded via 32 bit genes which indicate how the pathways of a brain are formed. Each gene describes the source type, either a sensory neuron or cognition neuron, the specific neuron, an output type, either cognitive or motor, its specific destination, and the weight this connection will have.

| source type | source neuron | output type | output neuron |  weight |
|:-----------:|:-------------:|:-----------:|:-------------:|:-------:|
| 1 bit       | 7 bits        | 1 bit       | 7 bits        | 16 bits |

## Dependecies ##

This project uses the libGD library to generate a gif represenation of generations periodically. LibGD can be downloaded from https://libgd.github.io/ or installed via package manager.

To install LibGD on Debian:

> sudo apt install libgd-dev

## Building and running ##

> git clone https://github.com/iswanlun/evo_brains.git \
> cd evo_brains/src \
> make sim 

If you want to use a pre-defined log file and output destination 
> make setup \
> ./sim log gifs/ 

If not 
> ./sim <path/to/logfile> <path/to/gif/folder/> 

### Credit ###

Inspired by David Randall Miller's project:  

https://www.youtube.com/watch?v=N3tRFayqVtk \
https://github.com/davidrmiller/biosim4
