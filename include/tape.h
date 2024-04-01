#pragma once 

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unistd.h>

const double DEFAULT_DELAY = 0.1;
const double DEFAULT_REWIND = 3;
struct Delay {
    double write_read;
    double oneshift;
    double rewind;
    
    Delay(const std::string& config_name);
    Delay(double write_read = DEFAULT_DELAY, double oneshift = DEFAULT_DELAY, double rewind = DEFAULT_REWIND);
    ~Delay() = default;
};

class Tape {
public:
    Tape(const std::string& file_name);
    Tape(const std::string& file_name, const std::string& config_name);
    ~Tape();
    size_t get_len() const;
    int32_t read_tape();
    void write_tape(int32_t value);
    void rewind(int pos, std::ios_base::seekdir dir); //подавать назад вперед и число насколько или просто число на сколько перемотать(отриц или полож) 
    void bin_file_to_text();

private:
    std::fstream binfile_;
    std::string name_;
    size_t len;
    size_t cur_position;
    Delay delay_;
};

void text_file_to_bin(const std::string& name);