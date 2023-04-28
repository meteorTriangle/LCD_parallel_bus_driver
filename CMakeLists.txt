cmake_minimum_required(VERSION 3.13)

project(LCD_parallel_driver VERSION 0.2.1 DESCRIPTION "for LCD parallel driver")
add_library(LCD_parallel_driver src/LCD_parallel_driver.cpp)


set(PICO_SDK_PATH "${PICO_SDK_PATH}")
set(PICO_BOARD pico CACHE STRING "Board type")

include(pico_sdk_import.cmake)

pico_sdk_init()

target_include_directories(LCD_parallel_driver PRIVATE
    ${PICO_SDK_PATH}
)

target_include_directories(LCD_parallel_driver PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(LCD_parallel_driver PRIVATE
        pico_stdlib
        hardware_gpio)