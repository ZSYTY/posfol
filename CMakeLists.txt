cmake_minimum_required(VERSION 3.5)

project(posfol)

find_package(
    LLVM REQUIRED CONFIG,
    Clang REQUIRED
)

add_subdirectory(parse)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${LLVM_INCLUDE_DIRS}
)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC ${LLVM_DEFINITIONS}
)

llvm_map_components_to_libnames(LLVM_LIBS support core irreader)

target_link_libraries(${PROJECT_NAME}
    PUBLIC ${LLVM_LIBS} parse
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)