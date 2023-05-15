cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)
set(PICO_SDK_PATH "${PICO_SDK_PATH}")
set(PICO_BOARD pico CACHE STRING "Board type")

project(LCD_parallel_driver C CXX ASM)
add_library(LCD_parallel_driver STATIC src/LCD_parallel_driver.cpp)



target_include_directories(LCD_parallel_driver PRIVATE
    ${PICO_SDK_PATH}
)

pico_sdk_init()

target_include_directories(LCD_parallel_driver PUBLIC
    ./include
)

target_link_libraries(LCD_parallel_driver
        pico_stdlib
        hardware_gpio
        hardware_timer
        hardware_clocks)

add_subdirectory(example)