// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vexp6.h for the primary calling header

#ifndef VERILATED_VEXP6___024ROOT_H_
#define VERILATED_VEXP6___024ROOT_H_  // guard

#include "verilated_heavy.h"

//==========

class Vexp6__Syms;

//----------

VL_MODULE(Vexp6___024root) {
  public:

    // PORTS
    VL_IN8(clk,0,0);
    VL_OUT8(LEDL,3,0);
    VL_OUT8(LEDH,3,0);
    VL_OUT8(L,6,0);
    VL_OUT8(H,6,0);

    // LOCAL SIGNALS
    CData/*0:0*/ exp6__DOT__bit1__DOT__tmp;
    CData/*7:0*/ exp6__DOT__bit1__DOT__t;

    // LOCAL VARIABLES
    CData/*7:0*/ exp6__DOT____Vcellout__bit1____pinNumber3;
    CData/*0:0*/ __Vclklast__TOP__clk;

    // INTERNAL VARIABLES
    Vexp6__Syms* vlSymsp;  // Symbol table

    // CONSTRUCTORS
  private:
    VL_UNCOPYABLE(Vexp6___024root);  ///< Copying not allowed
  public:
    Vexp6___024root(const char* name);
    ~Vexp6___024root();

    // INTERNAL METHODS
    void __Vconfigure(Vexp6__Syms* symsp, bool first);
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

//----------


#endif  // guard
