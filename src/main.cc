/*!
 * \brief     This file contains the definition of the main program
 *            used to perform the sourvays log.
 * \file      main.cc
 * \author    NutriaLUG
 * \copyright GNU Public License
 */

#include <iostream>
#include <string>
#include <list>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <map>

#include "loggers/sourvay_logger.hh"
#include "loggers/sqlite_logger.hh"
#include "configuration.hh"
#include "sensor_logger_info.hh"
#include "sensor.hh"
#include "sourvay.hh"

int main(int argc, char** argv) {
    std::list<Sensor> available_sensors;
    std::list<Sourvay> sourvays;
    create_sensors(std::back_inserter(available_sensors));

    std::ifstream is(get_configuration_file_path());
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
            std::map<std::string, Sensor*> map;
            for(auto itr = available_sensors.begin();
                itr != available_sensors.end();
                ++itr) {
                map[itr -> id] = &(*itr);
            }
            bool res = read_sourvays(map,
                                     std::back_inserter(sourvays),
                                     std::cin);
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
