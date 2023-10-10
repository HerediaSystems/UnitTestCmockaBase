cmake_minimum_required( VERSION 3.0 )

set(CMAKE_BUILD_TYPE Release)

project(tests)

enable_testing()
set(CMAKE_C_FLAGS "-Wall -Werror -Wpedantic -std=c11")
add_compile_definitions(UTEST)

include_directories ("${PROJECT_SOURCE_DIR}")

# Crée des variables avec les fichiers à compiler
set(SRCS
    module_a_tester.c
    tests/tests_code.c
    )


add_executable (tests_code ${SRCS} )
target_link_libraries(tests_code cmocka)