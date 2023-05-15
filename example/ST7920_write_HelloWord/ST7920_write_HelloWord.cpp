#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <stdint.h>
#include "LCD_parallel_driver.hpp"

int main(){
    stdio_init_all();
    uint16_t display_text[] = {
        0xB0DA,
        0xB970,
        0xB751, 
        0xB351, 
        0xBDD5,
        0xB1D0,
        0xBE61, //靠
        0xA55F, //北
        0xA475, //工
        0xB57B, //程
        0xAE76, //師
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
        0xBDB2, 
        0xA5E0, 
        0xBE55
        };
    parallel_pin LCD_pin(0, 1, 12, parallel_4);
    parallel_interface LCD(2, LCD_pin, 5);
    sleep_ms(1000);
    LCD.write_instruction(0b100000, 100);
    sleep_ms(1000);
    LCD.write_instruction(0b100000, 100);
    LCD.write_instruction(0b1100, 100);
    LCD.write_instruction(0b0001, 1800);
    LCD.write_instruction(0b100, 100);
    LCD.write_instruction(0b0001, 1800);
    LCD.write_instruction(0b1100, 100);
    LCD.write_instruction(0b10100, 100);
    LCD.write_instruction(0x80, 100);
    for(int j=6; j<11; ++j){
        LCD.write_register((display_text[j]>>8) & 0xFF, 100);
        LCD.write_register(display_text[j] & 0xFF, 100);
    }
    int j = 21;
    /*
        LCD.write_register((display_text[j]>>8) & 0xFF, 100);
        LCD.write_register(display_text[j] & 0xFF, 100);
        j++;
        LCD.write_register((display_text[j]>>8) & 0xFF, 100);
        LCD.write_register(display_text[j] & 0xFF, 100);
        j++;
        LCD.write_register((display_text[j]>>8) & 0xFF, 100);
        LCD.write_register(display_text[j] & 0xFF, 100);
        j++;/*
        LCD.write_register((display_text[j]>>8) & 0xFF, 100);
        LCD.write_register(display_text[j] & 0xFF, 100);
        j++;
        LCD.write_register((display_text[j]>>8) & 0xFF, 100);
        LCD.write_register(display_text[j] & 0xFF, 100);
        j++;
        LCD.write_register((display_text[j]>>8) & 0xFF, 100);
        LCD.write_register(display_text[j] & 0xFF, 100);
        j++;*/
    while(true){
    }
    return(0);
}
