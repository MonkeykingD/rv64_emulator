// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vexp6.h for the primary calling header

#include "Vexp6___024root.h"
#include "Vexp6__Syms.h"

//==========

VL_INLINE_OPT void Vexp6___024root___sequent__TOP__1(Vexp6___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vexp6__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vexp6___024root___sequent__TOP__1\n"); );
    // Variables
    CData/*0:0*/ __Vdly__exp6__DOT__bit1__DOT__tmp;
    // Body
    __Vdly__exp6__DOT__bit1__DOT__tmp = vlSelf->exp6__DOT__bit1__DOT__tmp;
    __Vdly__exp6__DOT__bit1__DOT__tmp = (1U & VL_REDXOR_32(
                                                           (0x1dU 
                                                            & (IData)(vlSelf->exp6__DOT__bit1__DOT__t))));
    vlSelf->exp6__DOT__bit1__DOT__t = (((IData)(vlSelf->exp6__DOT__bit1__DOT__tmp) 
                                        << 7U) | (0x7fU 
                                                  & ((IData)(vlSelf->exp6__DOT__bit1__DOT__t) 
                                                     >> 1U)));
    vlSelf->exp6__DOT____Vcellout__bit1____pinNumber3 
        = vlSelf->exp6__DOT__bit1__DOT__t;
    vlSelf->exp6__DOT__bit1__DOT__tmp = __Vdly__exp6__DOT__bit1__DOT__tmp;
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

void Vexp6___024root___eval(Vexp6___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vexp6__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vexp6___024root___eval\n"); );
    // Body
    if (((IData)(vlSelf->clk) & (~ (IData)(vlSelf->__Vclklast__TOP__clk)))) {
        Vexp6___024root___sequent__TOP__1(vlSelf);
    }
    // Final
    vlSelf->__Vclklast__TOP__clk = vlSelf->clk;
}

QData Vexp6___024root___change_request_1(Vexp6___024root* vlSelf);

VL_INLINE_OPT QData Vexp6___024root___change_request(Vexp6___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vexp6__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vexp6___024root___change_request\n"); );
    // Body
    return (Vexp6___024root___change_request_1(vlSelf));
}

VL_INLINE_OPT QData Vexp6___024root___change_request_1(Vexp6___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vexp6__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vexp6___024root___change_request_1\n"); );
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vexp6___024root___eval_debug_assertions(Vexp6___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vexp6__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vexp6___024root___eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((vlSelf->clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
}
#endif  // VL_DEBUG
