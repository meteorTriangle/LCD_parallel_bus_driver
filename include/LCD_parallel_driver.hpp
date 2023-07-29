#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include <stdint.h>

#ifndef LCD_PARALLEL_DRIVER_H
#define LCD_PARALLEL_DRIVER_H


enum bit_mode {parallel_4 , parallel_8};

class parallel_pin {
    public:
        parallel_pin(uint RS, uint RW, uint data_pin1, bit_mode mode_bit);
        void set_write();
        void set_read();
        void out_data_set8(uint8_t data);
        void out_data_set4(uint8_t data);
        //uint8_t in_data_read8();
        //uint8_t in_data_read4();
        void RS_instruction();
        void RS_data_reg();
        bit_mode bit_mode_get();
    private:
        int RS, RW, data_pin1;
        bit_mode parallel_bit;

};

class parallel_interface {
    public:
        parallel_interface(int ena, parallel_pin parallel_obj);
        parallel_interface(int ena, parallel_pin parallel_obj, int ena_keep_ns);
        void set_ena_keep_ns(int ena_keep_ns);
        void write_instruction(uint8_t data);
        void write_instruction_4(uint8_t data, int delay_us);
        void write_instruction(uint8_t data, int delay_us);
        void write_register(uint8_t data);
        void write_register(uint8_t data, int delay_us);
        bit_mode getBusBitWidth();
        //uint8_t read();
    private:
        void enable();
        parallel_pin *parallel_obj;
        int ena_pin;
        int ena_keep_ns;
};
#endif