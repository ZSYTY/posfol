add_library(semantic
        check.cpp
        sem_util.cpp
        symbol.cpp
        )


target_include_directories(semantic
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
        )

target_link_libraries(semantic
        PUBLIC
        )

set_property(TARGET semantic PROPERTY CXX_STANDARD 17)