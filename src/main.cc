/*!
 * \brief     This file contains the definition of the main program
 *            used to perform the sourvays log.
 * \file      main.cc
 * \author    NutriaLUG
 * \copyright GNU Public License
 */

#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <cstring>

#include "logger/sourvay_logger.hh"
#include "logger/sqlite_logger.hh"
#include "filesystem/cpp_std_filesystem.hh"
#include "configuration.hh"
#include "sensor_logger_info.hh"
#include "sensor.hh"
#include "sourvay.hh"

int main(int argc, char** argv) {
    std::list<Sensor> available_sensors;
    std::list<Sourvay> sourvays;
    create_sensors(std::back_inserter(available_sensors));

    CppStdFilesystem fs;
    auto config_file = get_config_file_path(fs);
    std::ifstream is(config_file);
    ConfigurationData config;
    is >> config;

    if(is.is_open()) {
        is.close();
    }
    
    if(argc == 2) {
        if(strcmp(argv[1], "--version") == 0) {
            out_informations(std::cout);
        } else if(strcmp(argv[1], "--list") == 0) {
            std::ostream_iterator<Sensor> os_itr(std::cout);
            std::copy(available_sensors.begin(),
                      available_sensors.end(),
                      os_itr);
        } else if(strcmp(argv[1], "--log") == 0) {
            std::list<std::string> sensor_sourvays;
            std::string str;
            while(std::getline(std::cin, str)) {
                sensor_sourvays.push_back(str);
            };
            bool res = create_sourvays(sensor_sourvays.begin(),
                                       sensor_sourvays.end(),
                                       available_sensors.begin(),
                                       available_sensors.end(),
                                       std::back_inserter(sourvays));
            if(!res) {
                std::cerr << "Invalid arguments" << std::endl;
            } else {
                SqliteLogger logger(config.database_path);
                log_sourvays(sourvays.begin(), sourvays.end(), logger);
            }
        }
    }

    return 0;
}
