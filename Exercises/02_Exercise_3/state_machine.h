#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <systemc.h>

enum base {Start, G, GA, GAA, GAAG};

// TODO
SC_MODULE(stateMachine){
    sc_in<char> input;
    sc_in<bool> clk;

    base state;
    int cnt, cnt_often;

    SC_CTOR(stateMachine): input("input"), clk("clk"){
        state = Start;
        cnt = 0;
        cnt_often = 0;
        SC_METHOD(process);
        sensitive << clk.pos();
        dont_initialize();
    }

    void process(){
        char c = input.read();
        cnt++;
        switch(state){
            case Start:
                if ( c == 'G') {
                    state = G;
                }
                else if (( c == 'A') || ( c == 'C') || ( c =='T')) {
                    state = Start;
                }
                break;
            case G:
                if ( c == 'A') {
                    state = GA;
                }
                else if ( c == 'G') {
                    state = G;
                }
                else if (( c == 'C') || ( c =='T')) {
                    state = Start;
                }
                break;
            case GA:
            if ( c == 'A') {
                    state = GAA;
                }
                else if ( c == 'G') {
                    state = G;
                }
                else if (( c == 'C') || ( c =='T')) {
                    state = Start;
                }
                break;
            case GAA:
            if ( c == 'G') {
                    state = GAAG;
                    cnt_often++;
                }
                else if (( c == 'A') || ( c == 'C') || ( c =='T')) {
                    state = Start;
                }
                break;
            case GAAG:
                std::cout<< "Sequence ["<< cnt_often <<"] at position "<< cnt - 3 <<std::endl;
                if ( c == 'G') {
                    state = G;
                }
                else if (( c == 'A') || ( c == 'C') || ( c =='T')) {
                    state = Start;
                }
                break;
            default:
                state = Start;
        }
    }
};

#endif // STATE_MACHINE_H


