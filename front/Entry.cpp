#include "Memory.h"
#include "remill/Arch/AArch64/Runtime/State.h"
#include "remill/Arch/Runtime/Intrinsics.h"
#include "remill/BC/Debug.h"

#include <cstdint>
#include <cstring>
#include <map>
#include <stdio.h>

State g_state = State();
RuntimeManager *g_run_mgr;

int main(int argc, char *argv[]) {

  std::vector<MappedMemory *> emulated_memorys;

  /* allocate Stack */
  emulated_memorys.push_back(MappedMemory::VMAStackEntryInit(argc, argv, &g_state));
  /* allocate Heap */
  emulated_memorys.push_back(MappedMemory::VMAHeapEntryInit());
  /* allocate every sections */
  for (int i = 0; i < __g_data_sec_num; i++) {
    emulated_memorys.push_back(new MappedMemory(
        MemoryAreaType::DATA, reinterpret_cast<const char *>(__g_data_sec_name_ptr_array[i]),
        __g_data_sec_vma_array[i], static_cast<size_t>(__g_data_sec_size_array[i]),
        __g_data_sec_bytes_ptr_array[i],
        __g_data_sec_bytes_ptr_array[i] + __g_data_sec_size_array[i], false));
  }
  /* set program counter */
  g_state.gpr.pc = {.qword = __g_entry_pc};
  /* set system register (FIXME) */
  g_state.sr.tpidr_el0 = {.qword = 0};
  g_state.sr.midr_el1 = {.qword = 0xf0510};
  g_state.sr.ctr_el0 = {.qword = 0x80038003};
  g_state.sr.dczid_el0 = {.qword = 0x4};
  /* set global RuntimeManager */
  g_run_mgr = new RuntimeManager(emulated_memorys);
  g_run_mgr->heaps_end_addr = HEAPS_START_VMA + HEAP_SIZE;
  /* set lifted function pointer table */
  for (int i = 0; __g_fn_vmas[i] && __g_fn_ptr_table[i]; i++) {
    g_run_mgr->addr_fn_map[__g_fn_vmas[i]] = __g_fn_ptr_table[i];
  }
#if defined(LIFT_CALLSTACK_DEBUG)
  /* set lifted function symbol table (for debug) */
  for (int i = 0; __g_fn_vmas_second[i] && __g_fn_symbol_table[i]; i++) {
    g_run_mgr->addr_fn_symbol_map[__g_fn_vmas_second[i]] = (const char *) __g_fn_symbol_table[i];
  }
#endif
  /* set global block address data array */
  for (int i = 0; i < __g_block_address_array_size; i++) {
    auto bb_num = __g_block_address_size_array[i];
    std::map<uint64_t, uint64_t *> vma_bb_map;
    auto t_block_address_ptrs = __g_block_address_ptrs_array[i];
    auto t_block_address_vmas = __g_block_address_vmas_array[i];
    for (int j = 0; j < bb_num; j++)
      vma_bb_map[t_block_address_vmas[j]] = t_block_address_ptrs[j];
    g_run_mgr->addr_block_addrs_map[__g_block_address_fn_vma_array[i]] = vma_bb_map;
  }
  /* go to the entry function (entry function is injected by lifted LLVM IR) */
  __g_entry_func(&g_state, __g_entry_pc, reinterpret_cast<Memory *>(g_run_mgr));

  delete (g_run_mgr);

  return 0;
}
