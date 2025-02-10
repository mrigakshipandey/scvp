# SystemC and Virtual Prototyping
## Simple Combinational Blocks
Format for a combinational block
```
SC_MODULE(<name>)
{
    sc_in<type> i_port;
    sc_out<type> o_port;

    SC_CTOR(<name>): i_port("i_port"), o_port("o_port")
    {
        SC_METHOD(<do_thing>);
        sensitive << i_port;
    }

    void do_thing()
    {
    ...
    }
}
```
A Test Module - Atomic in nature, shows delta cycles for a single computation
```
SC_MODULE(toplevel)
{
private:
    block b;
    unsigned int var;

    // declare IO / helper signals corresponding to the ports

    void process()
    {
        var++;

        // write to ports

        std::cout
        << " simulation time " << sc_time_stamp().to_default_time_units()
        << " ps Δ cycle " << sc_delta_count()
        << std::endl;
    }

    public:
    SC_CTOR(toplevel) : b("b"), var(0) // Instantiate all modules and signals
    {
        // bind all ports to signals

        SC_METHOD(process);
        sensitive << ; // add all signals 
    }

};
```
For Testing in a Sequential Fashion, we can create Stimulus and Monitor Modules
```
SC_MODULE(stim)
{
public:
    sc_out<bool> A, B;
    sc_in<bool> clk; //task4

    SC_CTOR(stim)
    {
        SC_THREAD(StimGen);
        sensitive << clk.pos(); //task4
    }

private:
    void StimGen()
    {
        wait();//wait(SC_ZERO_TIME);
        A.write(false);
        B.write(false);
        wait();//wait(10, SC_NS);
        A.write(false);
        B.write(true);
        wait();//wait(15, SC_NS);
        A.write(true);
        B.write(false);
        wait();//wait(10, SC_NS);
        A.write(true);
        B.write(true);
        wait();//wait(10, SC_NS);
        A.write(false);
        B.write(false);
        wait();//wait(10, SC_NS);
        sc_stop();
    }
};

SC_MODULE(Monitor)
{
public:
    sc_in<bool> A, B, Z;
    sc_in<bool> clk; 

    SC_CTOR(Monitor)
    {
        std::cout << std::endl <<  "time\tA\tB\tZ" << std::endl;
        SC_METHOD(monitor);
        sensitive << clk.pos(); //task4
        //sensitive << A << B << Z;
        dont_initialize();
    }

private:
    void monitor()
    {
        std::cout << sc_time_stamp()  << "\t" << A << "\t" << B << "\t" << Z << std::endl;
    }
};
```
These can finally be connected in the main call
```

int sc_main(int, char**)
{
    sc_signal<bool> sigals...;
    sc_clock clock("<name>",<time>, <unit eg. SC_NS>); 

    // Declare modules
    // bind signals

    //setup waveform tracing 
    sc_trace_file *wf = sc_create_vcd_trace_file("traceFile_EXOR");
    sc_trace(wf, <signal name>,"<display name>");
    sc_start();  // run forever
    sc_close_vcd_trace_file(wf); 

    return 0;
}
}
```
SC_METHOD - Combinational logic, without wait

SC_THREAD - Sequential Logic, When we need to use wait statements

## Custom sc_interface
An Interface only describes the behaviour of the channel using pure virtual methods
```
class <interface_name>: public sc_interface
{
    public:
    virtual <return type> func(<type> arg) = 0;
};
```
A channel is a class that implements those methods
```
class <channel_name>: public <interface_name>
{
    private:
    // member variables
    ...

    public:
     <channel_name>{
    // set member variables
    ...
    }

    // implements methods
};
```
Then we can write a Module that calls those methods
```
SC_MODULE(<module_name>){

    sc_port<channel_name> <port_name>;

    SC_CTOR(<module_name>){}

    // '->' to access methods for standard ports as opposed to sc_in and sc_out;
    ...
};
```
We can bind the module ports to the channel in the top-level module , then start simulation in the main call
