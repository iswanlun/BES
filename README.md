
# Brain evolution simulator #

Inspired by David Randall Miller's project:  

https://www.youtube.com/watch?v=N3tRFayqVtk \
https://github.com/davidrmiller/biosim4


## About ##

This simulator mimicks the evolution of organisms, here termed 'brains', by controling their thought processes through gene encoded pathways. Brains are controlled through wiring different neurons together and applying a weight to these connections to either amplify, suppress or invert neural pathways. Brains contain sense neurons to explore their environments, cognition neurons to modulate pathways and motor neurons to interact with their environment. The simulation has distinct generations at the end of which brains are either culled if they do not meet some predefined criteria, or are allowed to reproduce. Brain reproduction comes with the possibility of mutation which allows brains to evolve traits over generations.

### 32 bit gene structure ###

| source type | source neuron | output type | output neuron |  weight |
|:-----------:|:-------------:|:-----------:|:-------------:|:-------:|
| 1 bit       | 7 bits        | 1 bit       | 7 bits        | 16 bits |
