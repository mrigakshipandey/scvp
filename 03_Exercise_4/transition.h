#ifndef TRANSITION_H
#define TRANSITION_H

#include <systemc.h>

#include "place.h"

// Transition:
// TODO
template<unsigned int N = 1, unsigned int M = 1>
SC_MODULE(transition)
{
    public:
    sc_port<placeInterface, N, SC_ALL_BOUND> in;
    sc_port<placeInterface, M, SC_ALL_BOUND> out;

    SC_CTOR(transition){}

    void fire(){

        int can_fire = 1;

        for(int i = 0; i < N; i++) {
            if (in[i]->testTokens() < 1) {
                can_fire = 0;
                break;
            }
        }

        if(can_fire){
            std::cout << this->name() << ": Fired" << std::endl;

            // remove one token from each in port
            for(int i = 0; i < N; i++)
            in[i]->removeTokens();

            // add one token to each out port
            for(int i = 0; i < M; i++)
            out[i]->addTokens();
        } else {
            std::cout << this->name() << ": NOT Fired" << std::endl;
        }
    }
};

#endif // TRANSITION_H
