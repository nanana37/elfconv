/*
 * Copyright (c) 2017 Trail of Bits, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "remill/Arch/X86/Runtime/State.h"

#include <cstddef>
#include <cstdio>

// This is used by `print_x86_save_state_asm.sh` script. This is mostly for
// writing the code for saving native register state to somewhere that we can
// read it from. The code generated by this is `#include`d into `Test.S`. This
// code, as well as the `State` structure is pretty stable and so no one should
// really need to execute it. However, just in case things change, it's useful
// to keep around!
//
// Note: We compile this using the 64-bit, AVX512-enabled version of the
//       `State` structure. This doesn't actually matter because the `State`
//       structure has the same size/shape across all configurations.
int main(void) {

  printf("/* Auto-generated file! Don't modify! */\n\n");

  // Save the native FPU state.
  printf("#if 64 == ADDRESS_SIZE_BITS\n");
  printf("fxsave64 [RIP + STATE_PTR + %lu]\n", offsetof(State, x87));
  printf("#else\n");
  printf("fxsave [RIP + STATE_PTR + %lu]\n", offsetof(State, x87));
  printf("#endif\n");

  // Save whatever is on the stack that would get clobbered by the `PUSHFQ`.
  printf("lea RSP, [RSP - 8]\n");
  printf("pop QWORD PTR [RIP + SYMBOL(gStackSaveSlot)]\n");

  // Record the flags, both in native form (`Flags` struct), and in expanded
  // form (`ArithFlags` struct).
  printf("pushfq\n");
  printf("pop QWORD PTR [RIP + STATE_PTR + %lu]\n", offsetof(State, rflag));

  printf("bt QWORD PTR [RIP + STATE_PTR + %lu], 0\n", offsetof(State, rflag));
  printf("adc BYTE PTR [RIP + STATE_PTR + %lu], 0\n", offsetof(State, aflag.cf));

  printf("bt QWORD PTR [RIP + STATE_PTR + %lu], 2\n", offsetof(State, rflag));
  printf("adc BYTE PTR [RIP + STATE_PTR + %lu], 0\n", offsetof(State, aflag.pf));

  printf("bt QWORD PTR [RIP + STATE_PTR + %lu], 4\n", offsetof(State, rflag));
  printf("adc BYTE PTR [RIP + STATE_PTR + %lu], 0\n", offsetof(State, aflag.af));

  printf("bt QWORD PTR [RIP + STATE_PTR + %lu], 6\n", offsetof(State, rflag));
  printf("adc BYTE PTR [RIP + STATE_PTR + %lu], 0\n", offsetof(State, aflag.zf));

  printf("bt QWORD PTR [RIP + STATE_PTR + %lu], 7\n", offsetof(State, rflag));
  printf("adc BYTE PTR [RIP + STATE_PTR + %lu], 0\n", offsetof(State, aflag.sf));

  printf("bt QWORD PTR [RIP + STATE_PTR + %lu], 10\n", offsetof(State, rflag));
  printf("adc BYTE PTR [RIP + STATE_PTR + %lu], 0\n", offsetof(State, aflag.df));

  printf("bt QWORD PTR [RIP + STATE_PTR + %lu], 11\n", offsetof(State, rflag));
  printf("adc BYTE PTR [RIP + STATE_PTR + %lu], 0\n", offsetof(State, aflag.of));

  // Marshal the FPU status word flags.
  printf("bt QWORD PTR [RIP + STATE_PTR + %lu], 8\n", offsetof(State, x87.fxsave.swd));
  printf("adc BYTE PTR [RIP + STATE_PTR + %lu], 0\n", offsetof(State, sw.c0));

  printf("bt QWORD PTR [RIP + STATE_PTR + %lu], 9\n", offsetof(State, x87.fxsave.swd));
  printf("adc BYTE PTR [RIP + STATE_PTR + %lu], 0\n", offsetof(State, sw.c1));

  printf("bt QWORD PTR [RIP + STATE_PTR + %lu], 10\n", offsetof(State, x87.fxsave.swd));
  printf("adc BYTE PTR [RIP + STATE_PTR + %lu], 0\n", offsetof(State, sw.c2));

  printf("bt QWORD PTR [RIP + STATE_PTR + %lu], 14\n", offsetof(State, x87.fxsave.swd));
  printf("adc BYTE PTR [RIP + STATE_PTR + %lu], 0\n", offsetof(State, sw.c3));

  printf("bt QWORD PTR [RIP + STATE_PTR + %lu], 0\n", offsetof(State, x87.fxsave.swd));
  printf("adc BYTE PTR [RIP + STATE_PTR + %lu], 0\n", offsetof(State, sw.ie));

  printf("bt QWORD PTR [RIP + STATE_PTR + %lu], 1\n", offsetof(State, x87.fxsave.swd));
  printf("adc BYTE PTR [RIP + STATE_PTR + %lu], 0\n", offsetof(State, sw.de));

  printf("bt QWORD PTR [RIP + STATE_PTR + %lu], 2\n", offsetof(State, x87.fxsave.swd));
  printf("adc BYTE PTR [RIP + STATE_PTR + %lu], 0\n", offsetof(State, sw.ze));

  printf("bt QWORD PTR [RIP + STATE_PTR + %lu], 3\n", offsetof(State, x87.fxsave.swd));
  printf("adc BYTE PTR [RIP + STATE_PTR + %lu], 0\n", offsetof(State, sw.oe));

  printf("bt QWORD PTR [RIP + STATE_PTR + %lu], 4\n", offsetof(State, x87.fxsave.swd));
  printf("adc BYTE PTR [RIP + STATE_PTR + %lu], 0\n", offsetof(State, sw.ue));

  printf("bt QWORD PTR [RIP + STATE_PTR + %lu], 5\n", offsetof(State, x87.fxsave.swd));
  printf("adc BYTE PTR [RIP + STATE_PTR + %lu], 0\n", offsetof(State, sw.pe));

  // Restore the flags.
  printf("push QWORD PTR [RIP + STATE_PTR + %lu]\n", offsetof(State, rflag));
  printf("popfq\n");

  // Restore whatever was previously on the stack.
  printf("push QWORD PTR [RIP + SYMBOL(gStackSaveSlot)]\n");
  printf("lea RSP, [RSP + 8]\n");

  // Save segment registers.
  printf("mov WORD PTR [RIP + STATE_PTR + %lu], CS\n", offsetof(State, seg.cs));
  printf("mov WORD PTR [RIP + STATE_PTR + %lu], SS\n", offsetof(State, seg.ss));
  printf("mov WORD PTR [RIP + STATE_PTR + %lu], DS\n", offsetof(State, seg.ds));
  printf("mov WORD PTR [RIP + STATE_PTR + %lu], ES\n", offsetof(State, seg.es));
  printf("mov WORD PTR [RIP + STATE_PTR + %lu], FS\n", offsetof(State, seg.fs));
  printf("mov WORD PTR [RIP + STATE_PTR + %lu], GS\n", offsetof(State, seg.gs));

  printf("mov [RIP + STATE_PTR + %lu], AH\n", offsetof(State, gpr.rax.byte.high));
  printf("mov [RIP + STATE_PTR + %lu], BH\n", offsetof(State, gpr.rbx.byte.high));
  printf("mov [RIP + STATE_PTR + %lu], CH\n", offsetof(State, gpr.rcx.byte.high));
  printf("mov [RIP + STATE_PTR + %lu], DH\n", offsetof(State, gpr.rdx.byte.high));
  printf("mov [RIP + STATE_PTR + %lu], AL\n", offsetof(State, gpr.rax.byte.low));
  printf("mov [RIP + STATE_PTR + %lu], BL\n", offsetof(State, gpr.rbx.byte.low));
  printf("mov [RIP + STATE_PTR + %lu], CL\n", offsetof(State, gpr.rcx.byte.low));
  printf("mov [RIP + STATE_PTR + %lu], DL\n", offsetof(State, gpr.rdx.byte.low));
  printf("#if 64 == ADDRESS_SIZE_BITS\n");
  printf("mov [RIP + STATE_PTR + %lu], SIL\n", offsetof(State, gpr.rsi.byte.low));
  printf("mov [RIP + STATE_PTR + %lu], DIL\n", offsetof(State, gpr.rdi.byte.low));
  printf("mov [RIP + STATE_PTR + %lu], SPL\n", offsetof(State, gpr.rsp.byte.low));
  printf("mov [RIP + STATE_PTR + %lu], BPL\n", offsetof(State, gpr.rbp.byte.low));
  printf("mov [RIP + STATE_PTR + %lu], R8B\n", offsetof(State, gpr.r8.byte.low));
  printf("mov [RIP + STATE_PTR + %lu], R9B\n", offsetof(State, gpr.r9.byte.low));
  printf("mov [RIP + STATE_PTR + %lu], R10B\n", offsetof(State, gpr.r10.byte.low));
  printf("mov [RIP + STATE_PTR + %lu], R11B\n", offsetof(State, gpr.r11.byte.low));
  printf("mov [RIP + STATE_PTR + %lu], R12B\n", offsetof(State, gpr.r12.byte.low));
  printf("mov [RIP + STATE_PTR + %lu], R13B\n", offsetof(State, gpr.r13.byte.low));
  printf("mov [RIP + STATE_PTR + %lu], R14B\n", offsetof(State, gpr.r14.byte.low));
  printf("mov [RIP + STATE_PTR + %lu], R15B\n", offsetof(State, gpr.r15.byte.low));
  printf("#endif  /* 64 == ADDRESS_SIZE_BITS */\n");
  printf("mov [RIP + STATE_PTR + %lu], AX\n", offsetof(State, gpr.rax.word));
  printf("mov [RIP + STATE_PTR + %lu], BX\n", offsetof(State, gpr.rbx.word));
  printf("mov [RIP + STATE_PTR + %lu], CX\n", offsetof(State, gpr.rcx.word));
  printf("mov [RIP + STATE_PTR + %lu], DX\n", offsetof(State, gpr.rdx.word));
  printf("mov [RIP + STATE_PTR + %lu], SI\n", offsetof(State, gpr.rsi.word));
  printf("mov [RIP + STATE_PTR + %lu], DI\n", offsetof(State, gpr.rdi.word));
  printf("mov [RIP + STATE_PTR + %lu], SP\n", offsetof(State, gpr.rsp.word));
  printf("mov [RIP + STATE_PTR + %lu], BP\n", offsetof(State, gpr.rbp.word));
  printf("#if 64 == ADDRESS_SIZE_BITS\n");
  printf("mov [RIP + STATE_PTR + %lu], R8W\n", offsetof(State, gpr.r8.word));
  printf("mov [RIP + STATE_PTR + %lu], R9W\n", offsetof(State, gpr.r9.word));
  printf("mov [RIP + STATE_PTR + %lu], R10W\n", offsetof(State, gpr.r10.word));
  printf("mov [RIP + STATE_PTR + %lu], R11W\n", offsetof(State, gpr.r11.word));
  printf("mov [RIP + STATE_PTR + %lu], R12W\n", offsetof(State, gpr.r12.word));
  printf("mov [RIP + STATE_PTR + %lu], R13W\n", offsetof(State, gpr.r13.word));
  printf("mov [RIP + STATE_PTR + %lu], R14W\n", offsetof(State, gpr.r14.word));
  printf("mov [RIP + STATE_PTR + %lu], R15W\n", offsetof(State, gpr.r15.word));
  printf("#endif  /* 64 == ADDRESS_SIZE_BITS */\n");
  printf("mov [RIP + STATE_PTR + %lu], EAX\n", offsetof(State, gpr.rax.dword));
  printf("mov [RIP + STATE_PTR + %lu], EBX\n", offsetof(State, gpr.rbx.dword));
  printf("mov [RIP + STATE_PTR + %lu], ECX\n", offsetof(State, gpr.rcx.dword));
  printf("mov [RIP + STATE_PTR + %lu], EDX\n", offsetof(State, gpr.rdx.dword));
  printf("mov [RIP + STATE_PTR + %lu], ESI\n", offsetof(State, gpr.rsi.dword));
  printf("mov [RIP + STATE_PTR + %lu], EDI\n", offsetof(State, gpr.rdi.dword));
  printf("mov [RIP + STATE_PTR + %lu], ESP\n", offsetof(State, gpr.rsp.dword));
  printf("mov [RIP + STATE_PTR + %lu], EBP\n", offsetof(State, gpr.rbp.dword));

  printf("#if 64 == ADDRESS_SIZE_BITS\n");
  printf("mov [RIP + STATE_PTR + %lu], R8D\n", offsetof(State, gpr.r8.dword));
  printf("mov [RIP + STATE_PTR + %lu], R9D\n", offsetof(State, gpr.r9.dword));
  printf("mov [RIP + STATE_PTR + %lu], R10D\n", offsetof(State, gpr.r10.dword));
  printf("mov [RIP + STATE_PTR + %lu], R11D\n", offsetof(State, gpr.r11.dword));
  printf("mov [RIP + STATE_PTR + %lu], R12D\n", offsetof(State, gpr.r12.dword));
  printf("mov [RIP + STATE_PTR + %lu], R13D\n", offsetof(State, gpr.r13.dword));
  printf("mov [RIP + STATE_PTR + %lu], R14D\n", offsetof(State, gpr.r14.dword));
  printf("mov [RIP + STATE_PTR + %lu], R15D\n", offsetof(State, gpr.r15.dword));

  printf("mov [RIP + STATE_PTR + %lu], RAX\n", offsetof(State, gpr.rax.qword));
  printf("mov [RIP + STATE_PTR + %lu], RBX\n", offsetof(State, gpr.rbx.qword));
  printf("mov [RIP + STATE_PTR + %lu], RCX\n", offsetof(State, gpr.rcx.qword));
  printf("mov [RIP + STATE_PTR + %lu], RDX\n", offsetof(State, gpr.rdx.qword));
  printf("mov [RIP + STATE_PTR + %lu], RSI\n", offsetof(State, gpr.rsi.qword));
  printf("mov [RIP + STATE_PTR + %lu], RDI\n", offsetof(State, gpr.rdi.qword));
  printf("mov [RIP + STATE_PTR + %lu], RSP\n", offsetof(State, gpr.rsp.qword));
  printf("mov [RIP + STATE_PTR + %lu], RBP\n", offsetof(State, gpr.rbp.qword));
  printf("mov [RIP + STATE_PTR + %lu], R8\n", offsetof(State, gpr.r8.qword));
  printf("mov [RIP + STATE_PTR + %lu], R9\n", offsetof(State, gpr.r9.qword));
  printf("mov [RIP + STATE_PTR + %lu], R10\n", offsetof(State, gpr.r10.qword));
  printf("mov [RIP + STATE_PTR + %lu], R11\n", offsetof(State, gpr.r11.qword));
  printf("mov [RIP + STATE_PTR + %lu], R12\n", offsetof(State, gpr.r12.qword));
  printf("mov [RIP + STATE_PTR + %lu], R13\n", offsetof(State, gpr.r13.qword));
  printf("mov [RIP + STATE_PTR + %lu], R14\n", offsetof(State, gpr.r14.qword));
  printf("mov [RIP + STATE_PTR + %lu], R15\n", offsetof(State, gpr.r15.qword));
  printf("#endif  /* 64 == ADDRESS_SIZE_BITS */\n");

  printf("#if HAS_FEATURE_AVX\n");
  printf("#if HAS_FEATURE_AVX512\n");
  printf("vmovdqu [RIP + STATE_PTR + %lu], ZMM0\n", offsetof(State, vec[0].zmm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], ZMM1\n", offsetof(State, vec[1].zmm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], ZMM2\n", offsetof(State, vec[2].zmm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], ZMM3\n", offsetof(State, vec[3].zmm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], ZMM4\n", offsetof(State, vec[4].zmm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], ZMM5\n", offsetof(State, vec[5].zmm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], ZMM6\n", offsetof(State, vec[6].zmm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], ZMM7\n", offsetof(State, vec[7].zmm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], ZMM8\n", offsetof(State, vec[8].zmm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], ZMM9\n", offsetof(State, vec[9].zmm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], ZMM10\n", offsetof(State, vec[10].zmm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], ZMM11\n", offsetof(State, vec[11].zmm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], ZMM12\n", offsetof(State, vec[12].zmm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], ZMM13\n", offsetof(State, vec[13].zmm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], ZMM14\n", offsetof(State, vec[14].zmm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], ZMM15\n", offsetof(State, vec[15].zmm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], ZMM16\n", offsetof(State, vec[16].zmm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], ZMM17\n", offsetof(State, vec[17].zmm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], ZMM18\n", offsetof(State, vec[18].zmm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], ZMM19\n", offsetof(State, vec[19].zmm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], ZMM20\n", offsetof(State, vec[20].zmm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], ZMM21\n", offsetof(State, vec[21].zmm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], ZMM22\n", offsetof(State, vec[22].zmm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], ZMM23\n", offsetof(State, vec[23].zmm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], ZMM24\n", offsetof(State, vec[24].zmm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], ZMM25\n", offsetof(State, vec[25].zmm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], ZMM26\n", offsetof(State, vec[26].zmm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], ZMM27\n", offsetof(State, vec[27].zmm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], ZMM28\n", offsetof(State, vec[28].zmm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], ZMM29\n", offsetof(State, vec[29].zmm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], ZMM30\n", offsetof(State, vec[30].zmm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], ZMM31\n", offsetof(State, vec[31].zmm));
  printf("#endif  /* HAS_FEATURE_AVX512 */\n");

  printf("vmovdqu [RIP + STATE_PTR + %lu], YMM0\n", offsetof(State, vec[0].ymm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], YMM1\n", offsetof(State, vec[1].ymm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], YMM2\n", offsetof(State, vec[2].ymm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], YMM3\n", offsetof(State, vec[3].ymm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], YMM4\n", offsetof(State, vec[4].ymm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], YMM5\n", offsetof(State, vec[5].ymm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], YMM6\n", offsetof(State, vec[6].ymm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], YMM7\n", offsetof(State, vec[7].ymm));
  printf("#if HAS_FEATURE_AVX || 64 == ADDRESS_SIZE_BITS\n");
  printf("vmovdqu [RIP + STATE_PTR + %lu], YMM8\n", offsetof(State, vec[8].ymm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], YMM9\n", offsetof(State, vec[9].ymm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], YMM10\n", offsetof(State, vec[10].ymm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], YMM11\n", offsetof(State, vec[11].ymm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], YMM12\n", offsetof(State, vec[12].ymm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], YMM13\n", offsetof(State, vec[13].ymm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], YMM14\n", offsetof(State, vec[14].ymm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], YMM15\n", offsetof(State, vec[15].ymm));
  printf("#endif  /* HAS_FEATURE_AVX || 64 == ADDRESS_SIZE_BITS */\n");

  printf("#if HAS_FEATURE_AVX512\n");
  printf("vmovdqu [RIP + STATE_PTR + %lu], YMM16\n", offsetof(State, vec[16].ymm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], YMM17\n", offsetof(State, vec[17].ymm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], YMM18\n", offsetof(State, vec[18].ymm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], YMM19\n", offsetof(State, vec[19].ymm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], YMM20\n", offsetof(State, vec[20].ymm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], YMM21\n", offsetof(State, vec[21].ymm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], YMM22\n", offsetof(State, vec[22].ymm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], YMM23\n", offsetof(State, vec[23].ymm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], YMM24\n", offsetof(State, vec[24].ymm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], YMM25\n", offsetof(State, vec[25].ymm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], YMM26\n", offsetof(State, vec[26].ymm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], YMM27\n", offsetof(State, vec[27].ymm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], YMM28\n", offsetof(State, vec[28].ymm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], YMM29\n", offsetof(State, vec[29].ymm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], YMM30\n", offsetof(State, vec[30].ymm));
  printf("vmovdqu [RIP + STATE_PTR + %lu], YMM31\n", offsetof(State, vec[31].ymm));
  printf("#endif  /* HAS_FEATURE_AVX512 */\n");
  printf("#endif  /* HAS_FEATURE_AVX */\n");

  printf("movdqu [RIP + STATE_PTR + %lu], XMM0\n", offsetof(State, vec[0].xmm));
  printf("movdqu [RIP + STATE_PTR + %lu], XMM1\n", offsetof(State, vec[1].xmm));
  printf("movdqu [RIP + STATE_PTR + %lu], XMM2\n", offsetof(State, vec[2].xmm));
  printf("movdqu [RIP + STATE_PTR + %lu], XMM3\n", offsetof(State, vec[3].xmm));
  printf("movdqu [RIP + STATE_PTR + %lu], XMM4\n", offsetof(State, vec[4].xmm));
  printf("movdqu [RIP + STATE_PTR + %lu], XMM5\n", offsetof(State, vec[5].xmm));
  printf("movdqu [RIP + STATE_PTR + %lu], XMM6\n", offsetof(State, vec[6].xmm));
  printf("movdqu [RIP + STATE_PTR + %lu], XMM7\n", offsetof(State, vec[7].xmm));
  printf("#if HAS_FEATURE_AVX || 64 == ADDRESS_SIZE_BITS\n");
  printf("movdqu [RIP + STATE_PTR + %lu], XMM8\n", offsetof(State, vec[8].xmm));
  printf("movdqu [RIP + STATE_PTR + %lu], XMM9\n", offsetof(State, vec[9].xmm));
  printf("movdqu [RIP + STATE_PTR + %lu], XMM10\n", offsetof(State, vec[10].xmm));
  printf("movdqu [RIP + STATE_PTR + %lu], XMM11\n", offsetof(State, vec[11].xmm));
  printf("movdqu [RIP + STATE_PTR + %lu], XMM12\n", offsetof(State, vec[12].xmm));
  printf("movdqu [RIP + STATE_PTR + %lu], XMM13\n", offsetof(State, vec[13].xmm));
  printf("movdqu [RIP + STATE_PTR + %lu], XMM14\n", offsetof(State, vec[14].xmm));
  printf("movdqu [RIP + STATE_PTR + %lu], XMM15\n", offsetof(State, vec[15].xmm));
  printf("#endif  /* HAS_FEATURE_AVX || 64 == ADDRESS_SIZE_BITS */\n");

  printf("#if HAS_FEATURE_AVX512\n");
  printf("movdqu [RIP + STATE_PTR + %lu], XMM16\n", offsetof(State, vec[16].xmm));
  printf("movdqu [RIP + STATE_PTR + %lu], XMM17\n", offsetof(State, vec[17].xmm));
  printf("movdqu [RIP + STATE_PTR + %lu], XMM18\n", offsetof(State, vec[18].xmm));
  printf("movdqu [RIP + STATE_PTR + %lu], XMM19\n", offsetof(State, vec[19].xmm));
  printf("movdqu [RIP + STATE_PTR + %lu], XMM20\n", offsetof(State, vec[20].xmm));
  printf("movdqu [RIP + STATE_PTR + %lu], XMM21\n", offsetof(State, vec[21].xmm));
  printf("movdqu [RIP + STATE_PTR + %lu], XMM22\n", offsetof(State, vec[22].xmm));
  printf("movdqu [RIP + STATE_PTR + %lu], XMM23\n", offsetof(State, vec[23].xmm));
  printf("movdqu [RIP + STATE_PTR + %lu], XMM24\n", offsetof(State, vec[24].xmm));
  printf("movdqu [RIP + STATE_PTR + %lu], XMM25\n", offsetof(State, vec[25].xmm));
  printf("movdqu [RIP + STATE_PTR + %lu], XMM26\n", offsetof(State, vec[26].xmm));
  printf("movdqu [RIP + STATE_PTR + %lu], XMM27\n", offsetof(State, vec[27].xmm));
  printf("movdqu [RIP + STATE_PTR + %lu], XMM28\n", offsetof(State, vec[28].xmm));
  printf("movdqu [RIP + STATE_PTR + %lu], XMM29\n", offsetof(State, vec[29].xmm));
  printf("movdqu [RIP + STATE_PTR + %lu], XMM30\n", offsetof(State, vec[30].xmm));
  printf("movdqu [RIP + STATE_PTR + %lu], XMM31\n", offsetof(State, vec[31].xmm));
  printf("#endif  // HAS_FEATURE_AVX512\n");

  return 0;
}
