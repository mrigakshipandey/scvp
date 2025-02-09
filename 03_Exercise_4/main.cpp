#include <systemc.h>

#include "place.h"
#include "transition.h"
#include "subnet.h"

// Toplevel:
// TODO
SC_MODULE(toplevel){
    transition<1,1> ACT, RD, PRE, WR;
    place<1,1> IDLE, ACTIVE;

       
    SC_CTOR(toplevel): ACT("ACT"), RD("RD"), PRE("PRE"), WR("WR"), IDLE(1), ACTIVE(0) //  Petri Net (PN) as described in Fig. 3
    {
        SC_THREAD(process);

        // Petri Net (PN) as described in Fig. 3
        PRE.out.bind(IDLE);
        ACT.in.bind(IDLE);

        ACT.out.bind(ACTIVE);
        RD.out.bind(ACTIVE);
        WR.out.bind(ACTIVE);
        PRE.in.bind(ACTIVE);
        RD.in.bind(ACTIVE);
        WR.in.bind(ACTIVE);
    }

    void process(){
        while(true) {
            wait(10, SC_NS);
            ACT.fire();
            wait(10, SC_NS);
            ACT.fire();
            wait(10, SC_NS);
            RD.fire();
            wait(10, SC_NS);
            WR.fire();
            wait(10, SC_NS);
            PRE.fire();
            wait(10, SC_NS);
            ACT.fire();
            sc_stop();
        }
    }
};

int sc_main(int, char**)
{
    // TODO
    toplevel t("t");

    sc_start();
    return 0;
}
