#include "tape.h"

std::string PATH = "../res/";

Tape::Tape(const std::string& file_name)
     : name_(file_name), delay_() {
    text_file_to_bin();

    binfile_.open(PATH + name_ + ".bin",
                    std::ios::binary | std::ios::out | std::ios::in);
    // исключение если не открылся
    if (!binfile_.is_open()) {
        std::cout << "fail openning file" << std::endl;
    }

    size_t temp;
    if (!(binfile_.read(reinterpret_cast<char*>(&temp), sizeof(temp)))) {
        //кинуть исключение
        std::cout << "Write a len of tape at the file's begging" << std::endl;
    }
    len = temp;
}

// for creating new tapes
Tape::Tape(const std::string& file_name, size_t len)
        : name_(file_name), len(len), delay_() {
    binfile_.open(PATH + name_ + ".bin", std::ios::trunc | std::ios::binary |
                                            std::ios::out | std::ios::in);
    // исключение если не открылся
    if (!binfile_.is_open()) {
        std::cout << "fail openning file" << std::endl;
    }

    if (!(binfile_.write(reinterpret_cast<char*>(&len), sizeof(len)))) {
        //кинуть исключение
        std::cout << "Error in writing len" << std::endl;
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
  sleep(delay_.write_read);
  ++cur_position;
  return temp;
  // тоже кинуть исключение если ввод неверный
}

void Tape::write_tape(int32_t value) {
  if (cur_position < len) {
    binfile_.clear();
    if (!binfile_.write(reinterpret_cast<char*>(&value), sizeof(value))) {
      std::cout << "Error in write to tape" << std::endl;
    }
    sleep(delay_.write_read);
    sleep(delay_.oneshift);
  } else {
    // исключение
  }
  ++cur_position;

  // тоже кинуть исключение если вывод неверный
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
        std::cout << "rewind beyond tape" << std::endl;
    }
    sleep(delay_.oneshift * delay_.rewind);
}

void Tape::copy(Tape& src) {
    if (len != src.get_len()) {
        // error
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
        std::cout << "fail openning file" << std::endl;
    }

    std::ofstream file_out;
    file_out.open(PATH + name_ + ".bin", std::ios::binary | std::ios::out);

    if (!file_out.is_open()) {
        std::cout << "fail openning file" << std::endl;
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
        std::cout << "fail openning file" << std::endl;
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
    // исключение если не открылся
    if (!file.is_open()) {
        std::cout << "fail openning file" << std::endl;
    }

    file >> write_read >> oneshift >> rewind;
}

Delay::Delay(double write_read, double oneshift, double rewind)
    : write_read(write_read), oneshift(oneshift), rewind(rewind){};
