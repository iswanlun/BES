
# Brain Evolution Simulator #

## About ##

This simulator mimicks the evolution of organisms, here termed 'brains', by controling their thought processes through gene encoded pathways. Brains are controlled through wiring different neurons together and applying a weight to these connections to either amplify, suppress or invert neural pathways. Brains contain sense neurons to explore their environments, cognition neurons to modulate pathways, and motor neurons to interact with their environment. The simulation has distinct generations at the end of which brains are either culled if they do not meet some predefined criteria, or are allowed to reproduce. Brain reproduction comes with the possibility of mutation which allows brains to evolve traits over generations.

## Gene Structure ##

Neural links are encoded via 32 bit genes which indicate how the pathways of a brain are formed. Each gene describes the source type, either a sensory neuron or cognition neuron, the specific neuron, an output type, either cognitive or motor, its specific destination, and the weight this connection will have.

| source type | source neuron | output type | output neuron |  weight |
|:-----------:|:-------------:|:-----------:|:-------------:|:-------:|
| 1 bit       | 7 bits        | 1 bit       | 7 bits        | 16 bits |

## Dependecies ##

This project uses the libGD library to generate a gif represenation of generations periodically. LibGD can be downloaded from https://libgd.github.io/ or installed via package manager.

To install LibGD on Debian:

    sudo apt install libgd-dev

## Building and running ##

    git clone https://github.com/iswanlun/BES.git
    cd BES
    make

If you want to use a pre-defined log file, settings file, and output destination

    make setup

If not, in settings.conf under the paths section change:

    graphics=<path/to/gif/directory/>
    log=<path/to/log/file>

Run with

    ./sim settings.conf 

## Notes on running simulations ##

A great many outcomes are possible with this simulator including many unsatisfactory or uninteresting outcomes. For each type of selection mechanism there is a sweet spot for making the simulator generate interesting results. To little evolutionary pressure, say by making survival zones to large or by allowing too many iterations will generate lethargic and unintesting brains. Too much pressure and generations get wiped out frequently and brains never reach maturity. The brains are remarkably resilliant despite their limits, but hostile or poorly configured environments can waste computational resources.

## Credit ##

Inspired by David Randall Miller's project:  

https://www.youtube.com/watch?v=N3tRFayqVtk \
https://github.com/davidrmiller/biosim4
