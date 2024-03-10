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

#include <stdio.h>

extern "C" void debug_state_machine();

namespace {

DEF_SEM(DoNOP) {
  return memory;
}

}  // namespace

DEF_ISEL(NOP) = DoNOP;
DEF_ISEL(HINT_1) = DoNOP;
DEF_ISEL(HINT_2) = DoNOP;
DEF_ISEL(HINT_3) = DoNOP;
DEF_ISEL(NOP_HI_SYSTEM) = DoNOP;

/* FIXME?? */
DEF_ISEL(PRFM_P_LDST_POS) = DoNOP;

namespace {

DEF_SEM(UNDEF_CNT_ASIMDMISC_R) {
  UNDEF_INSN_PRINT(CNT_ASIMDMISC_R);
  return memory;
}

DEF_SEM(UNDEF_CMGE_ASISDMISC_Z) {
  UNDEF_INSN_PRINT(CMGE_ASISDMISC_Z);
  return memory;
}

DEF_SEM(UNDEF_CNTB_X64_BITCOUNT) {
  UNDEF_INSN_PRINT(CNTB_X64_BITCOUNT);
  return memory;
}

DEF_SEM(UNDEF_CNTD_X64_BITCOUNT) {
  UNDEF_INSN_PRINT(CNTD_X64_BITCOUNT);
  return memory;
}

DEF_SEM(UNDEF_CNTH_X64_BITCOUNT) {
  UNDEF_INSN_PRINT(CNTH_X64_BITCOUNT);
  return memory;
}

DEF_SEM(UNDEF_CNTW_X64_BITCOUNT) {
  UNDEF_INSN_PRINT(CNTW_X64_BITCOUNT);
  return memory;
}

DEF_SEM(UNDEF_WHILELO_PREDICATE) {
  UNDEF_INSN_PRINT(WHILELO_PREDICATE);
  return memory;
}

}  // namespace

/* FIXME */
DEF_ISEL(CNT_ASIMDMISC_R) = UNDEF_CNT_ASIMDMISC_R; /* CNT  <Vd>.<T>, <Vn>.<T> */
DEF_ISEL(CMGE_ASISDMISC_Z) = UNDEF_CMGE_ASISDMISC_Z; /* CMGE  <V><d>, <V><n>, #0 */
DEF_ISEL(CNTB_X64_BITCOUNT) = UNDEF_CNTB_X64_BITCOUNT; /* CNTB <Xd>{, <pattern>{, MUL #<imm>}} */
DEF_ISEL(CNTD_X64_BITCOUNT) = UNDEF_CNTD_X64_BITCOUNT; /* CNTD <Xd>{, <pattern>{, MUL #<imm>}} */
DEF_ISEL(CNTH_X64_BITCOUNT) = UNDEF_CNTH_X64_BITCOUNT; /* CNTH <Xd>{, <pattern>{, MUL #<imm>}} */
DEF_ISEL(CNTW_X64_BITCOUNT) = UNDEF_CNTW_X64_BITCOUNT; /* CNTW <Xd>{, <pattern>{, MUL #<imm>}} */
DEF_ISEL(WHILELO_PREDICATE) = UNDEF_WHILELO_PREDICATE; /* WHILELO <Pd>.<T>, <R><n>, <R><m> */
