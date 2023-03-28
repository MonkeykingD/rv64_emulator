// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vexp6.h for the primary calling header

#include "Vexp6___024root.h"
#include "Vexp6__Syms.h"

//==========


void Vexp6___024root___ctor_var_reset(Vexp6___024root* vlSelf);

Vexp6___024root::Vexp6___024root(const char* _vcname__)
    : VerilatedModule(_vcname__)
 {
    // Reset structure values
    Vexp6___024root___ctor_var_reset(this);
}

void Vexp6___024root::__Vconfigure(Vexp6__Syms* _vlSymsp, bool first) {
    if (false && first) {}  // Prevent unused
    this->vlSymsp = _vlSymsp;
}

Vexp6___024root::~Vexp6___024root() {
}

void Vexp6___024root___initial__TOP__2(Vexp6___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vexp6__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vexp6___024root___initial__TOP__2\n"); );
    // Body
    vlSelf->exp6__DOT__bit1__DOT__t = 1U;
}

void Vexp6___024root___settle__TOP__3(Vexp6___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vexp6__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vexp6___024root___settle__TOP__3\n"); );
    // Body
    vlSelf->LEDH = (0xfU & ((IData)(vlSelf->exp6__DOT____Vcellout__bit1____pinNumber3) 
                            >> 4U));
    vlSelf->LEDL = (0xfU & (IData)(vlSelf->exp6__DOT____Vcellout__bit1____pinNumber3));
    vlSelf->H = ((0U == (IData)(vlSelf->LEDH)) ? 1U
                  : ((1U == (IData)(vlSelf->LEDH)) ? 0x4fU
                      : ((2U == (IData)(vlSelf->LEDH))
                          ? 0x12U : ((3U == (IData)(vlSelf->LEDH))
                                      ? 6U : ((4U == (IData)(vlSelf->LEDH))
                                               ? 0x4cU
                                               : ((5U 
                                                   == (IData)(vlSelf->LEDH))
                                                   ? 0x24U
                                                   : 
                                                  ((6U 
                                                    == (IData)(vlSelf->LEDH))
                                                    ? 0x20U
                                                    : 
                                                   ((7U 
                                                     == (IData)(vlSelf->LEDH))
                                                     ? 0xfU
                                                     : 
                                                    ((8U 
                                                      == (IData)(vlSelf->LEDH))
                                                      ? 0U
                                                      : 
                                                     ((9U 
                                                       == (IData)(vlSelf->LEDH))
                                                       ? 0xcU
                                                       : 
                                                      ((0xaU 
                                                        == (IData)(vlSelf->LEDH))
                                                        ? 8U
                                                        : 
                                                       ((0xbU 
                                                         == (IData)(vlSelf->LEDH))
                                                         ? 0x60U
                                                         : 
                                                        ((0xcU 
                                                          == (IData)(vlSelf->LEDH))
                                                          ? 0x31U
                                                          : 
                                                         ((0xdU 
                                                           == (IData)(vlSelf->LEDH))
                                                           ? 0x42U
                                                           : 
                                                          ((0xeU 
                                                            == (IData)(vlSelf->LEDH))
                                                            ? 0x30U
                                                            : 0x38U)))))))))))))));
    vlSelf->L = ((0U == (IData)(vlSelf->LEDL)) ? 1U
                  : ((1U == (IData)(vlSelf->LEDL)) ? 0x4fU
                      : ((2U == (IData)(vlSelf->LEDL))
                          ? 0x12U : ((3U == (IData)(vlSelf->LEDL))
                                      ? 6U : ((4U == (IData)(vlSelf->LEDL))
                                               ? 0x4cU
                                               : ((5U 
                                                   == (IData)(vlSelf->LEDL))
                                                   ? 0x24U
                                                   : 
                                                  ((6U 
                                                    == (IData)(vlSelf->LEDL))
                                                    ? 0x20U
                                                    : 
                                                   ((7U 
                                                     == (IData)(vlSelf->LEDL))
                                                     ? 0xfU
                                                     : 
                                                    ((8U 
                                                      == (IData)(vlSelf->LEDL))
                                                      ? 0U
                                                      : 
                                                     ((9U 
                                                       == (IData)(vlSelf->LEDL))
                                                       ? 0xcU
                                                       : 
                                                      ((0xaU 
                                                        == (IData)(vlSelf->LEDL))
                                                        ? 8U
                                                        : 
                                                       ((0xbU 
                                                         == (IData)(vlSelf->LEDL))
                                                         ? 0x60U
                                                         : 
                                                        ((0xcU 
                                                          == (IData)(vlSelf->LEDL))
                                                          ? 0x31U
                                                          : 
                                                         ((0xdU 
                                                           == (IData)(vlSelf->LEDL))
                                                           ? 0x42U
                                                           : 
                                                          ((0xeU 
                                                            == (IData)(vlSelf->LEDL))
                                                            ? 0x30U
                                                            : 0x38U)))))))))))))));
}

void Vexp6___024root___eval_initial(Vexp6___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vexp6__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vexp6___024root___eval_initial\n"); );
    // Body
    vlSelf->__Vclklast__TOP__clk = vlSelf->clk;
    Vexp6___024root___initial__TOP__2(vlSelf);
}

void Vexp6___024root___eval_settle(Vexp6___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vexp6__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vexp6___024root___eval_settle\n"); );
    // Body
    Vexp6___024root___settle__TOP__3(vlSelf);
}

void Vexp6___024root___final(Vexp6___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vexp6__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vexp6___024root___final\n"); );
}

void Vexp6___024root___ctor_var_reset(Vexp6___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vexp6__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vexp6___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clk = 0;
    vlSelf->LEDL = 0;
    vlSelf->LEDH = 0;
    vlSelf->L = 0;
    vlSelf->H = 0;
    vlSelf->exp6__DOT____Vcellout__bit1____pinNumber3 = 0;
    vlSelf->exp6__DOT__bit1__DOT__tmp = 0;
    vlSelf->exp6__DOT__bit1__DOT__t = 0;
}
