#include "tape.h"


std::string PATH = "../res/";


Tape::Tape(const std::string& file_name) : name_(file_name), delay_() {
    text_file_to_bin(name_); 
    cur_position = 0;

    binfile_.open(PATH + name_ + ".bin", std::ios::binary | std::ios::out | std::ios::in);
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

Tape::Tape(const std::string& file_name, const std::string& config_name) : Tape(file_name) {
    Delay temp(config_name);
    delay_ = temp;
};

Tape::~Tape() {
    binfile_.close();
}


int32_t Tape::read_tape() {
    // std::cout << delay_.write_read << " " << delay_.oneshift << " " << delay_.rewind << std::endl;
    int32_t temp;
    binfile_.read(reinterpret_cast<char*>(&temp), sizeof(temp));
    sleep(delay_.write_read);
    ++cur_position;
    return temp;
    // delay!!
    // тоже кинуть исключение если ввод неверный 
}

void Tape::write_tape(int32_t value) {
    if (cur_position < len) {
        binfile_.write(reinterpret_cast<char*>(&value), sizeof(value));
        sleep(delay_.write_read);
        sleep(delay_.oneshift);
    } else {
        // исключение
    }
    ++cur_position;
    // std::cout << std::endl << value << std::endl;

    // delay!!
    // тоже кинуть исключение если вывод неверный   

}
size_t Tape::get_len() const {
    return len;
}

void Tape::rewind(int pos, std::ios_base::seekdir dir) {
    if (pos + cur_position <= len) {
        binfile_.seekg(pos * sizeof(int32_t), dir);
        sleep(delay_.oneshift * delay_.rewind);
        cur_position += pos;
    } else {
        // исключение  
        std::cout << "rewind beyond tape" << std::endl;
    }


}   

void text_file_to_bin(const std::string& name) {
    std::ifstream file_in;
    file_in.open(PATH + name);

    if (!file_in.is_open()) {
        std::cout << "fail openning file" << std::endl;
    }

    std::ofstream file_out;
    file_out.open(PATH + name + ".bin", std::ios::binary | std::ios::out);
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
    std::ofstream file_in; 
    file_in.open(PATH + name_);
    // std::cout << name_;
    if (!file_in.is_open()) {
        std::cout << "fail openning file" << std::endl;
    }
    binfile_.seekg(0, std::ios_base::beg);
    size_t temp_len;
    binfile_.read(reinterpret_cast<char*>(&temp_len), sizeof(temp_len));
    file_in << temp_len << std::endl;

    int32_t val;
    while (binfile_.read(reinterpret_cast<char*>(&val), sizeof(val))) {
        // std::cout << val << std::endl;
        file_in << val << std::endl;
    }
    file_in.close();
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

Delay::Delay(double write_read, double oneshift, double rewind) : 
            write_read(write_read), oneshift(oneshift), rewind(rewind) {};
