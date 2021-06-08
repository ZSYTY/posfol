cmake_minimum_required(VERSION 3.5)

project(posfol)

add_subdirectory(parser)
add_subdirectory(codegen)
add_subdirectory(semantic)

add_executable(${PROJECT_NAME}
    main.cpp
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC parser codegen
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)