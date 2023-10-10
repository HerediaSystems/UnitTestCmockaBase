cmake_minimum_required( VERSION 3.0 )

set(CMAKE_BUILD_TYPE Release)

project(tests)

enable_testing()
set(CMAKE_C_FLAGS "-Wall -Werror -Wpedantic -std=c11")
add_compile_definitions(UTEST)

include_directories ("${PROJECT_SOURCE_DIR}")
include_directories ("${PROJECT_SOURCE_DIR}/deps_headers")

# Crée des variables avec les fichiers à compiler
set(SRCS
    DRV_LED.c
    tests/tests_code.c
    )


add_executable (tests_code ${SRCS} )
target_link_libraries(tests_code cmocka)
set_target_properties(tests_code
        PROPERTIES
        LINK_FLAGS  "-Wl,--wrap=SYS_TIMESTAMP_get,--wrap=HAL_GPIO_set,--wrap=HAL_GPIO_toggle"
)