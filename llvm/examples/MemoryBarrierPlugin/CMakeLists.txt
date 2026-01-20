if (NOT WIN32 AND NOT CYGWIN)
  add_llvm_pass_plugin(MemoryBarrierPlugin
    MemoryBarrierPlugin.cpp
    DEPENDS
    intrinsics_gen
    BUILDTREE_ONLY
    )

  install(TARGETS ${name} RUNTIME DESTINATION "${LLVM_EXAMPLES_INSTALL_DIR}")
  set_target_properties(${name} PROPERTIES FOLDER "Examples")
endif()
