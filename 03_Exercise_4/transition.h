#ifndef TRANSITION_H
#define TRANSITION_H

#include <systemc.h>

#include "place.h"

// Transition:
// TODO
SC_MODULE(transition){

    sc_port<placeInterface> in;
    sc_port<placeInterface> out;

    SC_CTOR(transition){}

    void fire(){
        // -> to access methods for standard ports
        if(in->testTokens() != 0){
            std::cout << this->name() << ": Fired" << std::endl;

            // remove one token from the in port
            in->removeTokens(1);

            // add one token to the out port
            out->addTokens(1);
        } else {
            std::cout << this->name() << ": NOT Fired" << std::endl;
        }
    }
};

#endif // TRANSITION_H
