#include "LCD_parallel_driver.hpp"

/// @brief initial the parallel interface
/// @param RS RS(register select) pin 
/// @param RW RW(read/write) pin
/// @param data_pin1 the first pin of parallel
/// @param mode_bit set the parallel bit mode use parallel_4 to set 4-bit mode and parallel_8 set 8-bit mode
parallel_pin::parallel_pin(uint RS, uint RW, uint data_pin1, bit_mode mode_bit){
    this->RS = RS;
    this->RW = RW;
    this->data_pin1 = data_pin1;
    this->parallel_bit = parallel_bit;
    gpio_init(RS);
    gpio_init(RW);
    gpio_put(RS, false);
    gpio_put(RW, false);
    gpio_set_dir(RS, true);
    gpio_set_dir(RW, true);
    int data_pin_q = (parallel_bit == 1) ? 8 : 4;
    for(int i=0; i<data_pin_q; i++){
        gpio_init(data_pin1 + i);
        gpio_pull_down(data_pin1 + i);
    }
}

void parallel_pin::set_write(){
    gpio_put(RW, false);
    int data_pin_q = (parallel_bit == 1) ? 8 : 4;
    for(int i=0; i<data_pin_q; i++){
        gpio_set_dir(data_pin1 + i, true);
    }
}

void parallel_pin::set_read(){
    gpio_put(RW, true);
    int data_pin_q = (parallel_bit == 1) ? 8 : 4;
    for(int i=0; i<data_pin_q; i++){
        gpio_set_dir(data_pin1 + i, false);
    }
}

void parallel_pin::out_data_set8(uint8_t data){
    for(int i=0; i<8; i++){
        bool sta = ((data>>i) & 0x01) == 0x01;
        gpio_put(data_pin1+i, sta);
    }

}

void parallel_pin::out_data_set4(uint8_t data){
    for(int i=0; i<4; i++){
        bool sta = ((data>>i) & 0x01) == 0x01;
        gpio_put(data_pin1+i, sta);
    }

}

void parallel_pin::RS_instruction(){
    gpio_put(RS, false);
}

void parallel_pin::RS_data_reg(){
    gpio_put(RS, true);
}

bit_mode parallel_pin::bit_mode_get(){
    return(parallel_bit);
}

parallel_interface::parallel_interface(int ena, parallel_pin parallel_obj){
    this->ena_pin = ena;
    this->parallel_obj = &parallel_obj;
    gpio_init(ena_pin);
    gpio_put(ena_pin, false);
    gpio_set_dir(ena_pin, true);
}


parallel_interface::parallel_interface(int ena, parallel_pin parallel_obj, int ena_keep_ns){
    this->ena_pin = ena;
    this->parallel_obj = &parallel_obj;
    this->ena_keep_ns = ena_keep_ns;
    gpio_init(ena_pin);
    gpio_put(ena_pin, false);
    gpio_set_dir(ena_pin, true);
}

void parallel_interface::set_ena_keep_ns(int ena_keep_ns){
    this->ena_keep_ns = ena_keep_ns;
}

void parallel_interface::enable(){
    gpio_put(ena_pin, true);
    sleep_us(1);
    gpio_put(ena_pin, false);
}

void parallel_interface::write(uint8_t data){
     if(parallel_obj->bit_mode_get() == parallel_4){
        sleep_us(10);
     }
     if(parallel_obj->bit_mode_get() == parallel_8){
        parallel_obj->set_write();
        parallel_obj->out_data_set8(data);
        sleep_us(10);
        enable();
     }
}