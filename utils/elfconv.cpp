#include "elfconv.h"

#include <iomanip>
#include <iostream>
#include <remill/Arch/AArch64/Runtime/State.h>
#include <remill/BC/HelperMacro.h>
#include <vector>

#define PRINT_GPR(index) \
  std::cout << std::hex << "x" << #index << ": 0x" << g_state.gpr.x##index.qword << std::endl;

extern State g_state;

/* debug func */
extern "C" void debug_state_machine() {
  std::cout << "[Debug] State Machine. Program Counter: 0x" << std::hex << std::setw(16)
            << std::setfill('0') << g_state.gpr.pc.qword << std::endl;
  std::cout << "State.GPR:" << std::endl;
  PRINT_GPR(0);
  PRINT_GPR(1);
  PRINT_GPR(2);
  PRINT_GPR(3);
  PRINT_GPR(4);
  PRINT_GPR(5);
  PRINT_GPR(6);
  PRINT_GPR(7);
  PRINT_GPR(8);
  PRINT_GPR(9);
  PRINT_GPR(10);
  PRINT_GPR(11);
  PRINT_GPR(12);
  PRINT_GPR(13);
  PRINT_GPR(14);
  PRINT_GPR(15);
  PRINT_GPR(16);
  PRINT_GPR(17);
  PRINT_GPR(18);
  PRINT_GPR(19);
  PRINT_GPR(20);
  PRINT_GPR(21);
  PRINT_GPR(22);
  PRINT_GPR(23);
  PRINT_GPR(24);
  PRINT_GPR(25);
  PRINT_GPR(26);
  PRINT_GPR(27);
  PRINT_GPR(28);
  PRINT_GPR(29);
  PRINT_GPR(30);
  std::cout << std::hex << "sp: 0x" << g_state.gpr.sp.qword << ", pc: 0x" << g_state.gpr.pc.qword
            << std::endl;
  auto sr = g_state.sr;
  std::cout << "State.SR" << std::dec << std::endl;
  std::cout << std::hex << "tpidr_el0: 0x" << sr.tpidr_el0.qword << ", tpidrro_el0: 0x"
            << sr.tpidrro_el0.qword << ", ctr_el0: 0x" << sr.ctr_el0.qword << ", dczid_el0: 0x"
            << sr.dczid_el0.qword << ", midr_el1: 0x" << sr.midr_el1.qword << std::dec
            << ", n: " << (uint64_t) sr.n << ", z: " << (uint64_t) sr.z
            << ", c: " << (uint64_t) sr.c << ", v: " << (uint64_t) sr.v << ", ixc: " << sr.ixc
            << ", ofc: " << sr.ofc << ", ufc: " << sr.ufc << ", idc: " << sr.idc
            << ", ioc: " << sr.ioc << std::endl;
  // abort();
}

extern "C" void debug_state_machine_vectors() {
  std::cout << "[Debug] State Machine Vector Registers. Program Counter: 0x" << std::hex
            << std::setw(16) << std::setfill('0') << g_state.gpr.pc.qword << std::endl;
  std::cout << "State.SIMD:" << std::endl;
  std::cout << std::hex;
  for (int i = 0; i < kNumVecRegisters /* = 32 */; i++) {
    std::cout << "v." << std::to_string(i) << " = { [64:127]: 0x"
              << g_state.simd.v[i].qwords.elems[1] << ", [0:63]: 0x"
              << g_state.simd.v[i].qwords.elems[0] << " }" << std::endl;
  }
}

extern "C" void debug_llvmir_u64value(uint64_t val) {
  std::cout << std::hex << "LLVM IR value: 0x" << val << std::endl;
}

extern "C" void debug_llvmir_f64value(double val) {
  std::cout << "LLVM IR value: " << val << std::endl;
}

extern "C" void debug_insn() {
  auto gpr = g_state.gpr;
  std::cout << "PC: 0x" << std::hex << g_state.gpr.pc.qword << " x0: 0x" << gpr.x0.qword
            << " x1: 0x" << gpr.x1.qword << " x2: 0x" << gpr.x2.qword << " x3: 0x" << gpr.x3.qword
            << " x4: 0x" << gpr.x4.qword << " x5: 0x" << gpr.x5.qword << " x6: 0x" << gpr.x6.qword
            << " x7: 0x" << gpr.x7.qword << " x8: 0x" << gpr.x8.qword << " x9: 0x" << gpr.x9.qword
            << " x10: 0x" << gpr.x10.qword << " x11: 0x" << gpr.x11.qword << " x12: 0x"
            << gpr.x12.qword << " x13: 0x" << gpr.x13.qword << " x14: 0x" << gpr.x14.qword
            << " x15: 0x" << gpr.x15.qword << " x16: 0x" << gpr.x16.qword << " x17: 0x"
            << gpr.x17.qword << " x18: 0x" << gpr.x18.qword << " x19: 0x" << gpr.x19.qword
            << " x20: 0x" << gpr.x20.qword << " x21: 0x"
            << " x21: 0x" << gpr.x21.qword << " x22: 0x" << gpr.x22.qword << " x23: 0x"
            << gpr.x23.qword << " x24: 0x" << gpr.x24.qword << " x25: 0x" << gpr.x25.qword
            << " x26: 0x" << gpr.x26.qword << " x27: 0x" << gpr.x27.qword << " x28: 0x"
            << gpr.x28.qword << " x29: 0x" << gpr.x29.qword << " x30: 0x" << gpr.x30.qword
            << " SP: 0x" << gpr.sp.qword << std::endl;
}

#if defined(LIFT_DEBUG) && defined(__linux__)
extern "C" void segv_debug_state_machine(int sig, siginfo_t *info, void *ctx) {
  std::cout << "[ERROR] Segmantation Fault." << std::endl;
  std::cout << "signo: " << info->si_signo << " code: " << info->si_code << std::endl;
  debug_state_machine();
  exit(0);
}
#endif