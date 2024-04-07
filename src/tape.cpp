#include "tape.h"

std::string PATH = "../res/";

Tape::Tape(const std::string& file_name) : name_(file_name), delay_() {
  text_file_to_bin();

  binfile_.open(PATH + name_ + ".bin",
                std::ios::binary | std::ios::out | std::ios::in);

  if (!binfile_.is_open()) {
    throw std::runtime_error("Fail openning file in Tape constructor");
  }

  size_t temp;
  if (!(binfile_.read(reinterpret_cast<char*>(&temp), sizeof(temp)))) {
    throw std::runtime_error("Write a len of tape at the file's begging");
  }

  len = temp;
}

// for creating new tapes
Tape::Tape(const std::string& file_name, size_t len)
        : name_(file_name), len(len), delay_() {
    binfile_.open(PATH + name_ + ".bin", std::ios::trunc | std::ios::binary |
                                            std::ios::out | std::ios::in);
    if (!binfile_.is_open()) {
        throw std::runtime_error("Fail openning file in Tape constructor");
    }

    if (!(binfile_.write(reinterpret_cast<char*>(&len), sizeof(len)))) {
        throw std::runtime_error("Error in writing len in Tape constructor");
    }
}

Tape::Tape(const std::string& file_name, const std::string& config_name)
        : Tape(file_name) {
    Delay temp(config_name);
    delay_ = temp;
};

Tape::~Tape() { binfile_.close(); }

int32_t Tape::read_tape() {
    int32_t temp;
    binfile_.read(reinterpret_cast<char*>(&temp), sizeof(temp));
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_.write_read));
    ++cur_position;
    return temp;
}

void Tape::write_tape(int32_t value) {
    if (cur_position <= len) {
        binfile_.clear();
        if (!binfile_.write(reinterpret_cast<char*>(&value), sizeof(value))) {
            throw std::runtime_error("Error in write to tape");
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_.write_read));
        std::this_thread::sleep_for(std::chrono::milliseconds(delay_.oneshift));
    } else {
        throw std::runtime_error("Try to write outside the tape");
    }
    ++cur_position;
}
size_t Tape::get_len() const { return len; }

size_t Tape::get_cur_position() const { return cur_position; }

void Tape::rewind(int pos, std::ios_base::seekdir dir) {
    binfile_.clear();
    if (pos + cur_position <= len && dir == std::ios_base::cur) {
        binfile_.seekg(pos * sizeof(int32_t), dir);
        cur_position += pos;
    } else if (pos <= len && pos >= 0 && dir == std::ios_base::beg) {
        binfile_.seekg(pos * sizeof(int32_t) + sizeof(size_t), dir);
        cur_position = pos;
    } else if (pos <= 0 && dir == std::ios_base::end) {
        cur_position = len + pos;
        binfile_.seekg(pos * sizeof(int32_t), dir);
    } else {
        throw std::runtime_error("Try to rewind beyond tape");
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_.oneshift * delay_.rewind));
}

void Tape::copy(Tape& src) {
    if (len != src.get_len()) {
        throw std::runtime_error("Try to copy tapes with different lens");
    } else {
        src.rewind(0, std::ios_base::beg);
        for (size_t i = 0; i < len; ++i) {
        write_tape(src.read_tape());
        }
    }
}

void Tape::text_file_to_bin() {
    std::ifstream file_in;
    file_in.open(PATH + name_);

    if (!file_in.is_open()) {
        throw std::runtime_error("Fail openning file_in in text_file_to_bin()");
    }

    std::ofstream file_out;
    file_out.open(PATH + name_ + ".bin", std::ios::binary | std::ios::out);

    if (!file_out.is_open()) {
        throw std::runtime_error("Fail openning file_out in text_file_to_bin()");
    }

    size_t temp_len;
    file_in >> temp_len;
    file_out.write(reinterpret_cast<char*>(&temp_len), sizeof(temp_len));

    int32_t val;
    while (file_in >> val) {
        file_out.write(reinterpret_cast<char*>(&val), sizeof(val));
    }

    file_in.close();
    file_out.close();
}

void Tape::bin_file_to_text() {
    std::ofstream file_out;
    file_out.open(PATH + name_);

    if (!file_out.is_open()) {
        throw std::runtime_error("Fail openning file_out in bin_file_to_text()");
    }
    binfile_.clear();
    binfile_.seekg(0, std::ios_base::beg);
    size_t temp_len;
    binfile_.read(reinterpret_cast<char*>(&temp_len), sizeof(temp_len));
    file_out << temp_len << std::endl;

    int32_t val;
    while (binfile_.read(reinterpret_cast<char*>(&val), sizeof(val))) {
        file_out << val << std::endl;
    }
}

Delay::Delay(const std::string& config_name) {
    std::fstream file;
    file.open(PATH + config_name);
    if (!file.is_open()) {
        throw std::runtime_error("Fail openning config file in Delay constructor");
    }

    file >> write_read >> oneshift >> rewind;
}

Delay::Delay(size_t write_read, size_t oneshift, size_t rewind)
     : write_read(write_read), oneshift(oneshift), rewind(rewind){};
