# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NEVER EDIT THE NEXT LINES for Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.0.0)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================

set(PICO_BOARD pico2 CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(ST7920_write_Image C CXX ASM)


# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

##include_directories(../../)

##add_subdirectory(../../ build)

# Add executable. Default name is the project name, version 0.1

add_executable(ST7920_write_Image ST7920_write_Image.cpp)

pico_set_program_name(ST7920_write_Image "ST7920_write_Image")
pico_set_program_version(ST7920_write_Image "0.1")

pico_enable_stdio_uart(ST7920_write_Image 0)
pico_enable_stdio_usb(ST7920_write_Image 1)

# Add the standard library to the build
target_link_libraries(ST7920_write_Image
        pico_stdlib)

# Add the standard include files to the build
target_include_directories(ST7920_write_Image PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
)

# Add any user requested libraries
target_link_libraries(ST7920_write_Image
        LCD_parallel_driver
        hardware_gpio
        hardware_timer
        hardware_clocks
        )

pico_add_extra_outputs(ST7920_write_Image)

