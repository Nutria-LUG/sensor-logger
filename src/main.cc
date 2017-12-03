#include <iostream>
#include <cstring>
#include "sensor_reader_info.hh"

int main(int argc, char** argv) {
    if(argc == 2 && strcmp(argv[1], "--version") == 0) {
        std::cout << SensorReaderInfo::NAME << " "
                  << SensorReaderInfo::VERSION_NUMBER << "\n"
                  << "License GPLv3+: GNU GPL version 3 or later "
                  << "<http://gnu.org/licenses/gpl.html>.\n"
                  <<  "This is free software: you are free to change"
                  << "and redistribute it.\n"
                  << "There is NO WARRANTY, to the extent permitted by"
                  << "law.\n"
                  << std::endl;
    } else {
        std::cout << "Hello World" << std::endl;
    }
    return 0;
}
