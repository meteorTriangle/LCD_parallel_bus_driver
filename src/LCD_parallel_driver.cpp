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
    this->parallel_bit = mode_bit;
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

/// @brief set GPIO write
void parallel_pin::set_write(){
    gpio_put(RW, false);
    int data_pin_q = (parallel_bit == 1) ? 8 : 4;
    for(int i=0; i<data_pin_q; i++){
        gpio_set_dir(data_pin1 + i, true);
    }
}
/// @brief set GPIO read
void parallel_pin::set_read(){
    int data_pin_q = (parallel_bit == 1) ? 8 : 4;
    for(int i=0; i<data_pin_q; i++){
        gpio_set_dir(data_pin1 + i, false);
    }
    gpio_put(RW, true);
}
/// @brief set GPIO output data 8-bit
/// @param data which you want gpio set(8-bit data)
void parallel_pin::out_data_set8(uint8_t data){
    for(int i=0; i<8; i++){
        bool sta = ((data>>i) & 0x01) == 0x01;
        gpio_put(data_pin1+i, sta);
    }

}

/// @brief set GPIO output data 4-bit
/// @param data which you want gpio set(4-bit data)
void parallel_pin::out_data_set4(uint8_t data){
    for(int i=0; i<4; i++){
        bool sta = ((data>>i) & 0x01) == 0x01;
        gpio_put(data_pin1+i, sta);
    }

}

/// @brief set to write instruction
void parallel_pin::RS_instruction(){
    gpio_put(RS, false);
}

/// @brief set to write or read data reg
void parallel_pin::RS_data_reg(){
    gpio_put(RS, true);
}

/// @brief get parallel bit
/// @return parallel_4 is 4-bit, parallel_8 is 8-bit
bit_mode parallel_pin::bit_mode_get(){
    return(parallel_bit);
}

/// @brief initial parallel_interface
/// @param ena ena pin
/// @param parallel_obj parallel_pin object
parallel_interface::parallel_interface(int ena, parallel_pin parallel_obj){
    this->ena_pin = ena;
    this->parallel_obj = &parallel_obj;
    gpio_init(ena_pin);
    gpio_put(ena_pin, false);
    gpio_set_dir(ena_pin, true);
}

/// @brief initial parallel_interface
/// @param ena ena pin
/// @param parallel_obj parallel_pin object
/// @param ena_keep_ns enable pin pulse width(unit: ms)
parallel_interface::parallel_interface(int ena, parallel_pin parallel_obj, int ena_keep_ns){
    this->ena_pin = ena;
    this->parallel_obj = &parallel_obj;
    this->ena_keep_ns = ena_keep_ns;
    gpio_init(ena_pin);
    gpio_put(ena_pin, false);
    gpio_set_dir(ena_pin, true);
}

/// @brief set enable pin pulse width(unit: ms)
/// @param ena_keep_ns enable pin pulse width(unit: ms)
void parallel_interface::set_ena_keep_ns(int ena_keep_ns){
    this->ena_keep_ns = ena_keep_ns;
}

/// @brief generate a enable pulse
[[gnu::noinline]]
void parallel_interface::enable(){
    gpio_put(ena_pin, true);
    uint32_t x = 5;
    asm volatile(
        " dmb\n"
        " 1:\n"
        " sub %[x], %[x], #1\n"
        " cmp %[x], #0\n"
        " bne 1b"
        : [x] "+r" (x) :: "cc"
    );
    gpio_put(ena_pin, false);
}

/// @brief write a 8 bit data to instruction
/// @param data which you want to write 
void parallel_interface::write_instruction(uint8_t data){
    parallel_obj->RS_instruction();
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

/// @brief write a 8 bit data to instruction
/// @param data which you want to write 
/// @param delay_us delay after write data(unit: us)
void parallel_interface::write_instruction(uint8_t data, int delay_us){
    parallel_obj->RS_instruction();
    parallel_obj->set_write();
    if(parallel_obj->bit_mode_get() == parallel_4){
        parallel_obj->out_data_set4(data>>4);
        this->enable();
        sleep_us(2);
        parallel_obj->out_data_set4(data);
        this->enable();
        sleep_us(delay_us);
     }
     if(parallel_obj->bit_mode_get() == parallel_8){
        parallel_obj->out_data_set8(data);
        this->enable();
        sleep_us(delay_us);
     }
}

/// @brief write a 8 bit data to register
/// @param data which you want to write 
void parallel_interface::write_register(uint8_t data){
    parallel_obj->RS_data_reg();
     if(parallel_obj->bit_mode_get() == parallel_4){
        sleep_us(10);
     }
     if(parallel_obj->bit_mode_get() == parallel_8){
        parallel_obj->set_write();
        parallel_obj->out_data_set8(data);
        sleep_us(10);
        this->enable();
        sleep_us(10);
     }
}

/// @brief write a 8 bit data to register
/// @param data which you want to write 
/// @param delay_us delay after write data(unit: us)
void parallel_interface::write_register(uint8_t data, int delay_us){
    parallel_obj->RS_data_reg();
    parallel_obj->set_write();
    if(parallel_obj->bit_mode_get() == parallel_4){
        parallel_obj->out_data_set4(data>>4);
        this->enable();
        parallel_obj->out_data_set4(data & 0b1111);
        this->enable();
        sleep_us(delay_us);
     }
     if(parallel_obj->bit_mode_get() == parallel_8){
        parallel_obj->out_data_set8(data);
        this->enable();
        sleep_us(delay_us);
     }
}

