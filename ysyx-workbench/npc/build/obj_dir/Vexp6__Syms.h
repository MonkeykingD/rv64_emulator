// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VEXP6__SYMS_H_
#define VERILATED_VEXP6__SYMS_H_  // guard

#include "verilated_heavy.h"

// INCLUDE MODEL CLASS

#include "Vexp6.h"

// INCLUDE MODULE CLASSES
#include "Vexp6___024root.h"

// SYMS CLASS (contains all model state)
class Vexp6__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vexp6* const __Vm_modelp;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vexp6___024root                TOP;

    // CONSTRUCTORS
    Vexp6__Syms(VerilatedContext* contextp, const char* namep, Vexp6* modelp);
    ~Vexp6__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

#endif  // guard
