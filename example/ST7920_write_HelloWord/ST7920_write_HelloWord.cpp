#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/clocks.h"
#include "LCD_parallel_driver.hpp"

int main(){
    stdio_init_all();
    set_sys_clock_khz(48*1000, true);
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
    sleep_ms(1800);
    LCD.write_instruction(0b100000);
    sleep_ms(1800);
    LCD.write_instruction(0b100000);
    LCD.write_instruction(0b1100);
    LCD.write_instruction(0b0001, 1800);
    LCD.write_instruction(0b100);
    LCD.write_instruction(0b0001, 1800);
    LCD.write_instruction(0b1100);
    LCD.write_instruction(0b10100);
    LCD.write_instruction(0b10);
    LCD.write_instruction(0x80);
    for(int j=6; j<11; ++j){
        LCD.write_register((display_text[j]>>8) & 0xFF, 100);
        LCD.write_register(display_text[j] & 0xFF, 100);
    }
    int j = 21;


    uint8_t receieve_data[100];
    bool last_receieve_status = false;
    bool receieve_status = false;
    bool flag = false;
    while(true){
        int receieve_ = getchar_timeout_us(1);
        receieve_status = receieve_ != -1;
        if(receieve_status && (!last_receieve_status)){
            receieve_data[0] = 0;
        }
        if(receieve_status){
            receieve_data[0]++;
            receieve_data[receieve_data[0]] = receieve_;
        }
        if(!receieve_status && last_receieve_status){
            flag = true;
        }
        last_receieve_status = receieve_status;

        if(flag){
            if(receieve_data[1] == 0x02){
                LCD.write_instruction(0b0001, 1800);
            }

            if(receieve_data[1] == 0x03){    
                LCD.write_instruction(0x80, 100);
                printf("%d", receieve_data[0]/2);
                for(int i = 0; i < receieve_data[0]/2; i++){
                    LCD.write_register(receieve_data[(i*2)+2], 100);
                    LCD.write_register(receieve_data[(i*2)+3], 100);
                }
            }
            flag = false;
        }
    }
    return(0);
}
