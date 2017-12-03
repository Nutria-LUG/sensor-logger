#include <iostream>
#include <cstring>
#include <list>
#include <iterator>
#include "sensor_reader_info.hh"
#include "sensor.hh"

template<class BackInserterIterator>
void initialize_sensors(BackInserterIterator itr) {
    *itr = Sensor("01", "pm10");
}

int main(int argc, char** argv) {
    std::list<Sensor> available_sensors;
    initialize_sensors(std::back_inserter(available_sensors));
    
    
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
        for(auto itr = available_sensors.begin();
            itr != available_sensors.end();
            ++itr) {
            std::cout << itr -> id << " - " << itr -> name << "\n";
        }
        std::cout << std::endl;
        
    }
    return 0;
}
