//===-- MemoryBarrier.cpp - Insert barriers after memory ops --------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This pass inserts a sequentially consistent fence after every load and store
// instruction in the input function.
//
//===----------------------------------------------------------------------===//

#include "llvm/Transforms/Utils/MemoryBarrier.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instructions.h"

using namespace llvm;

PreservedAnalyses MemoryBarrierPass::run(Function &F,
                                         FunctionAnalysisManager &AM) {
  bool Changed = false;
  LLVMContext &Ctx = F.getContext();

  for (BasicBlock &BB : F) {
    for (auto It = BB.begin(); It != BB.end();) {
      Instruction &Inst = *It++;
      if (!isa<LoadInst>(Inst) && !isa<StoreInst>(Inst))
        continue;

      IRBuilder<> Builder(&BB, It);
      Builder.CreateFence(AtomicOrdering::SequentiallyConsistent,
                          SyncScope::System);
      Changed = true;
    }
  }

  return Changed ? PreservedAnalyses::none() : PreservedAnalyses::all();
}
