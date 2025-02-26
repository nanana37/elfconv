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

#pragma once

#include "remill/Arch/Runtime/Definitions.h"
#include "remill/Arch/X86/Runtime/Types.h"

template <typename T>
struct TPair {
  T r1;
  T r2;
} __attribute__((packed));

typedef struct {
  uint64_t r1;
  uint64_t r2;
} U64U64 __attribute__((packed));

typedef struct {
  uint32_t r1;
  uint64_t r2;
} U32U64 __attribute__((packed));

typedef struct {
  uint32_t r1;
  uint32_t r2;
} U32U32 __attribute__((packed));

typedef struct {
  float64_t r1;
  uint64_t r2;
} F64U64 __attribute__((packed));

typedef struct {
  float32_t r1;
  float32_t r2;
} F32F32 __attribute__((packed));

typedef struct {
  float64_t r1;
  float64_t r2;
} F64F64 __attribute__((packed));

#if defined(__x86_64__)
typedef _ecv_u128v2_t V128V128;
#else
typedef struct {
  _ecv_u128v1_t r1;
  _ecv_u128v1_t r2;
} V128V128 __attribute__((packed));
#endif

// Define a semantics implementing function for aarch64 target.
#define DEF_SEM_VOID(name, ...) ALWAYS_INLINE __attribute__((flatten)) static void name(__VA_ARGS__)

#define DEF_SEM_VOID_STATE(name, ...) \
  ALWAYS_INLINE __attribute__((flatten)) static void name(State &state, ##__VA_ARGS__)

#define DEF_SEM_VOID_RUN(name, ...) \
  ALWAYS_INLINE __attribute__((flatten)) static void name(RuntimeManager *runtime_manager, \
                                                          ##__VA_ARGS__)

#define DEF_SEM_VOID_STATE_RUN(name, ...) \
  ALWAYS_INLINE __attribute__((flatten)) static void name( \
      State &state, RuntimeManager *runtime_manager, ##__VA_ARGS__)

#define DEF_SEM_U64(name, ...) \
  ALWAYS_INLINE __attribute__((flatten)) static uint64_t name(__VA_ARGS__)

#define DEF_SEM_U64_STATE(name, ...) \
  ALWAYS_INLINE __attribute__((flatten)) static uint64_t name(State &state, ##__VA_ARGS__)

#define DEF_SEM_U64_RUN(name, ...) \
  ALWAYS_INLINE __attribute__((flatten)) static uint64_t name(RuntimeManager *runtime_manager, \
                                                              ##__VA_ARGS__)

#define DEF_SEM_U64_STATE_RUN(name, ...) \
  ALWAYS_INLINE __attribute__((flatten)) static uint64_t name( \
      State &state, RuntimeManager *runtime_manager, ##__VA_ARGS__)

#define DEF_SEM_T(name, ...) ALWAYS_INLINE __attribute__((flatten)) static auto name(__VA_ARGS__)

#define DEF_SEM_T_STATE(name, ...) \
  ALWAYS_INLINE __attribute__((flatten)) static auto name(State &state, ##__VA_ARGS__)

#define DEF_SEM_T_RUN(name, ...) \
  ALWAYS_INLINE __attribute__((flatten)) static auto name(RuntimeManager *runtime_manager, \
                                                          ##__VA_ARGS__)

#define DEF_SEM_T_STATE_RUN(name, ...) \
  ALWAYS_INLINE __attribute__((flatten)) static auto name( \
      State &state, RuntimeManager *runtime_manager, ##__VA_ARGS__)

#define DEF_SEM_U64U64_STATE(name, ...) \
  ALWAYS_INLINE __attribute__((flatten)) static U64U64 name(State &state, ##__VA_ARGS__)

#define DEF_SEM_U64U64_RUN(name, ...) \
  ALWAYS_INLINE __attribute__((flatten)) static U64U64 name(RuntimeManager *runtime_manager, \
                                                            ##__VA_ARGS__)

#define DEF_SEM_U64U64_STATE_RUN(name, ...) \
  ALWAYS_INLINE __attribute__((flatten)) static U64U64 name( \
      State &state, RuntimeManager *runtime_manager, ##__VA_ARGS__)

#define DEF_SEM_U32U32_STATE_RUN(name, ...) \
ALWAYS_INLINE __attribute__((flatten)) static U32U32 name( \
    State &state, RuntimeManager *runtime_manager, ##__VA_ARGS__)