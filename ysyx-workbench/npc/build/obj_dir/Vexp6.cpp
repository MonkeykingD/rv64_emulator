// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vexp6.h"
#include "Vexp6__Syms.h"

//============================================================
// Constructors

Vexp6::Vexp6(VerilatedContext* _vcontextp__, const char* _vcname__)
    : vlSymsp{new Vexp6__Syms(_vcontextp__, _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , LEDL{vlSymsp->TOP.LEDL}
    , LEDH{vlSymsp->TOP.LEDH}
    , L{vlSymsp->TOP.L}
    , H{vlSymsp->TOP.H}
    , rootp{&(vlSymsp->TOP)}
{
}

Vexp6::Vexp6(const char* _vcname__)
    : Vexp6(nullptr, _vcname__)
{
}

//============================================================
// Destructor

Vexp6::~Vexp6() {
    delete vlSymsp;
}

//============================================================
// Evaluation loop

void Vexp6___024root___eval_initial(Vexp6___024root* vlSelf);
void Vexp6___024root___eval_settle(Vexp6___024root* vlSelf);
void Vexp6___024root___eval(Vexp6___024root* vlSelf);
QData Vexp6___024root___change_request(Vexp6___024root* vlSelf);
#ifdef VL_DEBUG
void Vexp6___024root___eval_debug_assertions(Vexp6___024root* vlSelf);
#endif  // VL_DEBUG
void Vexp6___024root___final(Vexp6___024root* vlSelf);

static void _eval_initial_loop(Vexp6__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    Vexp6___024root___eval_initial(&(vlSymsp->TOP));
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial loop\n"););
        Vexp6___024root___eval_settle(&(vlSymsp->TOP));
        Vexp6___024root___eval(&(vlSymsp->TOP));
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = Vexp6___024root___change_request(&(vlSymsp->TOP));
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("/home/mkdai/ysyx-workbench/npc/vsrc/exp6.v", 1, "",
                "Verilated model didn't DC converge\n"
                "- See https://verilator.org/warn/DIDNOTCONVERGE");
        } else {
            __Vchange = Vexp6___024root___change_request(&(vlSymsp->TOP));
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vexp6::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vexp6::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vexp6___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        Vexp6___024root___eval(&(vlSymsp->TOP));
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = Vexp6___024root___change_request(&(vlSymsp->TOP));
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("/home/mkdai/ysyx-workbench/npc/vsrc/exp6.v", 1, "",
                "Verilated model didn't converge\n"
                "- See https://verilator.org/warn/DIDNOTCONVERGE");
        } else {
            __Vchange = Vexp6___024root___change_request(&(vlSymsp->TOP));
        }
    } while (VL_UNLIKELY(__Vchange));
}

//============================================================
// Invoke final blocks

void Vexp6::final() {
    Vexp6___024root___final(&(vlSymsp->TOP));
}

//============================================================
// Utilities

VerilatedContext* Vexp6::contextp() const {
    return vlSymsp->_vm_contextp__;
}

const char* Vexp6::name() const {
    return vlSymsp->name();
}
