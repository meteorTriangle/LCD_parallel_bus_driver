#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "LCD_parallel_driver.hpp"

int main(){
    const uint16_t display_text[] = {
        0xA2D6, //H 
        0xA2ED, //e
        0xA2F4, //l
        0xA2F4, //l
        0xA2F7, //o
        0xA140, //space
        0xA340, //w
        0xA2F7, //o
        0xA2FA, //r
        0xA2EC, //d
        };
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
    LCD.write_instruction(0b1111, 100);
    LCD.write_instruction(0b11100, 100);
    for(int i=0; i<2; i++){
        LCD.write_instruction(0x82 + i, 100);
        LCD.write_register((display_text[i]>>8) & 0xFF, 100);
        LCD.write_register(display_text[i] & 0xFF, 100);
        sleep_ms(1);
    }

    while(true){
    }
    return(0);
}