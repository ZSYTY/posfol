add_library(codegen
        CodeGen.cpp
        FunctionContext.cpp TypeUtil.cpp)

find_package(
        LLVM REQUIRED CONFIG,
        Clang REQUIRED
)

target_include_directories(codegen
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${LLVM_INCLUDE_DIRS}
        )

target_compile_definitions(codegen
        PUBLIC ${LLVM_DEFINITIONS}
        )

llvm_map_components_to_libnames(LLVM_LIBS support core irreader)

target_link_libraries(codegen
        PUBLIC parser semantic ${LLVM_LIBS}
        )

set_property(TARGET codegen PROPERTY CXX_STANDARD 17)
