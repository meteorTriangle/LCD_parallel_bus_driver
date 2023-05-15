#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "LCD_parallel_driver.hpp"

int main(){
    stdio_init_all();
    parallel_pin LCD_pin(0, 1, 12, parallel_4);
    parallel_interface LCD(2, LCD_pin, 5);
    LCD.write_instruction(0b100000);
    LCD.write_instruction(0b100000);
    LCD.write_instruction(0b1111);
    LCD.write_instruction(0b0001, 1800);
    LCD.write_instruction(0b100);
    LCD.write_instruction(0b0001, 1800);
    LCD.write_instruction(0b10);
    while(true){
    }
    return(0);
}