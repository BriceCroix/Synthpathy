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

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(Synthpathy
    pico_stdlib
    hardware_pwm
)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(Synthpathy)