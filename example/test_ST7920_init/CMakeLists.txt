# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
set(PICO_SDK_PATH "${PICO_SDK_PATH}")

set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

if (PICO_SDK_VERSION_STRING VERSION_LESS "1.4.0")
  message(FATAL_ERROR "Raspberry Pi Pico SDK version 1.4.0 (or later) required. Your version is ${PICO_SDK_VERSION_STRING}")
endif()

project(test_ST7920_init C CXX ASM)

set(PICO_CXX_ENABLE_EXCEPTIONS 1)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

##include_directories(../../)

##add_subdirectory(../../ build)

# Add executable. Default name is the project name, version 0.1

add_executable(test_ST7920_init test_ST7920_init.cpp )

pico_set_program_name(test_ST7920_init "test_ST7920_init")
pico_set_program_version(test_ST7920_init "0.1")

pico_enable_stdio_uart(test_ST7920_init 1)
pico_enable_stdio_usb(test_ST7920_init 0)

# Add the standard library to the build
target_link_libraries(test_ST7920_init
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(test_ST7920_init PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
)

# Add any user requested libraries
target_link_libraries(test_ST7920_init 
        LCD_parallel_driver
        hardware_gpio
        hardware_timer
        hardware_clocks
        )

pico_add_extra_outputs(test_ST7920_init)

