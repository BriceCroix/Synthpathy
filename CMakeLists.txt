cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
include(pico_sdk_import.cmake)

project(Synthpathy
    LANGUAGES C CXX
    VERSION 1.0.0
)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# Specify the source and headers directories
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
)

# Search for all source and header files
file(GLOB all_SRCS
    "${PROJECT_SOURCE_DIR}/include/*.h"
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.c"
)

# Finally specify the executable
add_executable(Synthpathy
    ${all_SRCS}
)

# Print all warning and consider them as errors
add_compile_options(-Wall -Wextra -Wpedantic -Werror)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(Synthpathy
    pico_stdlib
    hardware_pwm
)

if(DEBUG)
    message(STATUS "Defined DEBUG macro")
    # Enable usb standard output if DEBUG is specified
    pico_enable_stdio_usb(Synthpathy 1)
    # #define DEBUG for compiler
    add_compile_definitions(DEBUG=${DEBUG})
endif()
if(DEBUG_AUDIO)
    message(STATUS "Defined DEBUG_AUDIO macro")
    # Enable usb standard output if DEBUG_AUDIO is specified
    pico_enable_stdio_usb(Synthpathy 1)
    # #define DEBUG_AUDIO for compiler
    add_compile_definitions(DEBUG_AUDIO=${DEBUG_AUDIO})
endif()
if(TESTS_ONLY)
    message(STATUS "Defined TESTS_ONLY macro")
    # Enable usb standard output if TESTS_ONLY is specified
    pico_enable_stdio_usb(Synthpathy 1)
    # #define TESTS_ONLY for compiler
    add_compile_definitions(TESTS_ONLY=${TESTS_ONLY})
endif()
if(NOT(DEBUG OR DEBUG_AUDIO OR TESTS_ONLY))
    message(STATUS "Disabled stdio usb")
    # Disable usb standard output if no debug is specified
    pico_enable_stdio_usb(Synthpathy 0)
endif()

# Always disable uart standard output 
pico_enable_stdio_uart(Synthpathy 0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(Synthpathy)