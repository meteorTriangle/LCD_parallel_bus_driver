#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "LCD_parallel_driver.hpp"

int main(){
    stdio_init_all();
    parallel_pin LCD_pin(0, 1, 8, parallel_8);
    parallel_interface LCD(2, LCD_pin, 5);
    sleep_ms(200);
    LCD.write_instruction(0b110000);
    LCD.write_instruction(0b110000);
    LCD.write_instruction(0b1100, 100);
    LCD.write_instruction(0b0001, 1800);
    LCD.write_instruction(0b100, 100);
    LCD.write_instruction(0b0001, 1800);
    LCD.write_instruction(0b1100, 100);
    LCD.write_instruction(0b110100, 100);
    LCD.write_instruction(0b110110, 100);
            LCD.write_instruction(0b10000010, 100);
            LCD.write_instruction(0b10000000, 100);
            LCD.write_register(0b01010101, 100);
            LCD.write_register(0b01010101, 100);

    while(true){
    }
    return(0);
}