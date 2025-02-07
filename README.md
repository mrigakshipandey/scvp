# SystemC and Virtual Prototyping
## Exercise 2
### Task 1 - NAND Gate
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
Format for a top level module to test the combinational block, same as a module composed of other SystemC modules
```
SC_MODULE(toplevel)
{
public:
    SC_CTOR(toplevel) : b("b"), var(0)
    {
        // bind all ports

        SC_METHOD(process);
        sensitive << ; // add all ports
    }

private:
    block b;
    unsigned int var;

    // declare IO signals and helper signals

    void process()
    {
        var++;

        // write to ports

        std::cout
        << " simulation time " << sc_time_stamp().to_default_time_units()
        << " ps Δ cycle " << sc_delta_count()
        << std::endl;
};

int sc_main(int, char**)
{
    toplevel top("toplevel");

    // Simulation starts here.
    sc_start();

    // Return zero after the end of the simulation.
    return 0;
}
```
### Task 2 - XOR Gate
SC_METHOD - Combinational logic, without wait

SC_THREAD - Sequential Logic, When we need to use wait statements

### Task 3 - Waveform Tracing
