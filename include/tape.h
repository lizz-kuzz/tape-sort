#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <chrono>
#include <thread>

const size_t DEFAULT_DELAY = 0;
const size_t DEFAULT_REWIND = 0;
    
struct Delay {
    size_t write_read;
    size_t oneshift;
    size_t rewind;

    Delay(const std::string& config_name);
    Delay(size_t write_read = DEFAULT_DELAY, size_t oneshift = DEFAULT_DELAY,
            size_t rewind = DEFAULT_REWIND);
    ~Delay() = default;
};

class Tape {
public:
    Tape(const std::string& file_name);
    Tape(const std::string& file_name, const std::string& config_name);
    Tape(const std::string& file_name, size_t len);
    ~Tape();
    size_t get_len() const;
    size_t get_cur_position() const;
    int32_t read_tape();
    void write_tape(int32_t value);
    void copy(Tape& src);
    void rewind(int pos, std::ios_base::seekdir dir);
    void bin_file_to_text();
    void text_file_to_bin();

private:
    std::fstream binfile_;
    std::string name_;
    size_t len;
    size_t cur_position = 0;
    Delay delay_;
};
