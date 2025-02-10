#include <iostream>
#include <systemc.h>

SC_MODULE(adder){

    sc_in<int> a,b;
    sc_out<int> z;

    SC_CTOR(adder){
        SC_METHOD(add);
        sensitive << a << b;

    }

    void add() {
        z.write(a.read()+b.read());
    }
};

SC_MODULE(stim)
{
public:
    sc_out<int> A, B;

    SC_CTOR(stim)
    {
        SC_THREAD(StimGen);
    }

private:
    void StimGen()
    {
        wait(SC_ZERO_TIME);
        A.write(10);
        B.write(15);
        wait(10, SC_NS);
        A.write(-7);
        B.write(22);
        wait(15, SC_NS);
        A.write(-16);
        B.write(-5);
        wait(10, SC_NS);
        A.write(41);
        B.write(1);
        wait(10, SC_NS);
        A.write(6);
        B.write(0);
        wait(10, SC_NS);
        sc_stop();
    }
};

SC_MODULE(Monitor)
{
public:
    sc_in<int> A, B, Z;

    SC_CTOR(Monitor)
    {
        std::cout << std::endl <<  "time\tA\tB\tZ" << std::endl;
        SC_METHOD(monitor);
        sensitive << Z;
        dont_initialize();
    }

private:
    void monitor()
    {
        std::cout << sc_time_stamp()  << "\t" << A << "\t" << B << "\t" << Z << std::endl;
    }
};

int sc_main(int, char**)
{
    sc_signal<int> SigA, SigB, SigZ;

    // Declare modules
    adder A("A");
    stim S("S");
    Monitor M("M");

    // bind signals

    S.A.bind(SigA);
    S.B.bind(SigB);

    A.a.bind(SigA);
    A.b.bind(SigB);
    A.z.bind(SigZ);

    M.A.bind(SigA);
    M.B.bind(SigB);
    M.Z.bind(SigZ); 

    sc_start();

    return 0;
}

