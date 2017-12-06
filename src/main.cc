/*!
 * \brief     This file contains the definition of the main program
 *            used to perform the sourvays log.
 * \file      main.cc
 * \author    NutriaLUG
 * \copyright GNU Public License
 */

#include <iostream>
#include <cstring>
#include <list>
#include <iterator>
#include <algorithm>
#include <fstream>

#include "filesystem.hh"
#include "configuration.hh"
#include "sensor_reader_info.hh"
#include "sensor.hh"

template<class BackInserterIterator>
void initialize_sensors(BackInserterIterator itr) {
    *itr = Sensor("01", "pm10");
}

int main(int argc, char** argv) {

    std::list<Sensor> available_sensors;
    initialize_sensors(std::back_inserter(available_sensors));

    LinuxFilesystem fs;
    auto config_file = get_config_file_path(fs);
    std::cout << config_file << std::endl;
    std::ifstream is(config_file);
    ConfigurationData config;
    is >> config;

    std::cout << config.database_path << std::endl;

    if(argc == 2) {
        if(strcmp(argv[1], "--version") == 0) {
            std::cout << SensorReaderInfo::NAME << " "
                      << SensorReaderInfo::VERSION_NUMBER << "\n"
                      << "License GPLv3+: GNU GPL version 3 or later "
                      << "<http://gnu.org/licenses/gpl.html>.\n"
                      << "This is free software: you are free to "
                      << "change and redistribute it.\n"
                      << "There is NO WARRANTY, to the extent "
                      << "permitted by law.\n"
                      << std::endl;
        } else if(strcmp(argv[1], "--list") == 0) {
            std::ostream_iterator<Sensor> os_itr(std::cout);
            std::copy(available_sensors.begin(),
                      available_sensors.end(),
                      os_itr);
        }
    }
    return 0;
}
