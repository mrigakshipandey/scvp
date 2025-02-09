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

## Exercise 4
### Task 1 - Custom sc_interface
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
Then we can write a Module that implements those methods
```
SC_MODULE(<module_name>){

    sc_port<channel_name> <port_name>;

    SC_CTOR(<module_name>){}

    // '->' to access methods for standard ports as opposed to sc_in and sc_out;
    ...
};
```
We can bind the module ports to the channel in the top-level module 
