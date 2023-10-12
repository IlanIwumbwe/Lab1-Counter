#include "Vcounter.h"   // once the counter.cv file gets compiled, a Vcounter.h header file is created, so this makes sence
#include "verilated.h"
#include "verilated_vcd_c.h"

int main(int argc, char **argv, char **env){ 
    int i;
    int clk;
    int stopping_cycles = 0;

    Verilated::commandArgs(argc, argv);
    // init DUT instance
    Vcounter* top = new Vcounter;

    // init trace dump
    Verilated::traceEverOn(true);  // turn on signal tracing
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("counter.vcd");  // dump waveform data into 'counter.vcd'

    // initialise simulation inputs
    top->clk = 1;
    top->rst = 1;
    top->en = 0;

    // run simulation for many clock cycles
    for(i = 0; i < 300; i++){
        top->rst = (i<2) | (i == 25);  // change rst and on signals during simulation
        top->en = (i>4);  // change the signal during simulation

        if(top->count == 0x9){
            top->en = stopping_cycles >= 3;
            stopping_cycles++;
        }

        /*
            This for-loop toggles the clock and outputs the trace for each 
            half of the clock cycle, forcing the model to evaluate at both sides 
            of the clock rising edge
        */
        for(clk=0; clk<2; clk++){
            tfp->dump(2*i+clk);
            top->clk = !top->clk;
            top->eval();
        }
    }

    tfp->close();
    exit(0);
}