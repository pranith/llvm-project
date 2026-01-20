//===-- MemoryBarrier.h - Insert barriers after memory ops -----*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
/// \file
/// A simple function pass that inserts a sequentially consistent fence
/// instruction after every load and store.
//===----------------------------------------------------------------------===//

#ifndef LLVM_TRANSFORMS_UTILS_MEMORYBARRIER_H
#define LLVM_TRANSFORMS_UTILS_MEMORYBARRIER_H

#include "llvm/IR/PassManager.h"

namespace llvm {

class MemoryBarrierPass : public PassInfoMixin<MemoryBarrierPass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
};

} // namespace llvm

#endif // LLVM_TRANSFORMS_UTILS_MEMORYBARRIER_H
