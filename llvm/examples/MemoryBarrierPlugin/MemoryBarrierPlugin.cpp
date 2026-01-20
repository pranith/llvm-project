//===- MemoryBarrierPlugin.cpp - Inject memory-barrier pass ---------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
/// A pass plugin that adds the memory-barrier pass to LLVM pipelines.
///
/// Usage with clang:
///   clang -fpass-plugin=/path/to/libMemoryBarrierPlugin.so -O2 ...
/// The plugin hooks the optimizer pipeline and appends the pass near the end.
/// It also provides a pipeline name ("memory-barrier" or "add-memory-barrier")
/// so you can use -mllvm -passes='default<O2>,add-memory-barrier' if your
/// clang build supports textual pipelines.
//===----------------------------------------------------------------------===//

#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Transforms/Utils/MemoryBarrier.h"

using namespace llvm;

static void registerCallbacks(PassBuilder &PB) {
  PB.registerOptimizerLastEPCallback(
      [](FunctionPassManager &PM, OptimizationLevel) {
        PM.addPass(MemoryBarrierPass());
      });

  PB.registerPipelineParsingCallback(
      [](StringRef Name, FunctionPassManager &PM,
         ArrayRef<PassBuilder::PipelineElement>) {
        if (Name == "memory-barrier" || Name == "add-memory-barrier") {
          PM.addPass(MemoryBarrierPass());
          return true;
        }
        return false;
      });
}

extern "C" LLVM_ATTRIBUTE_WEAK PassPluginLibraryInfo llvmGetPassPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "MemoryBarrierPlugin", LLVM_VERSION_STRING,
          registerCallbacks};
}
