/*!
 * \brief     This file contains the definition of the main program
 *            used to perform the sourvays log.
 * \file      main.cc
 * \author    NutriaLUG
 * \copyright GNU Public License
 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <string.h>
#include <iterator>
#include <libopenair/configuration.hh>
#include "sqlite_logger.hh"
#include "sensor_logger_info.hh"

int main(int argc, char* argv[]) {
    try {
        openair::ConfigurationData config;
        std::fstream config_file(
            openair::get_configuration_file_path());
        config_file >> config;                         
        
        SqliteLogger logger(config.database_path);
        if (argc >= 2) {
            if(strcmp(argv[1], "--version") == 0) {
                Informations infos;
                std::cout << infos << std::endl;
            } else {
                logger.log(argv + 1, argv + argc - 1);            
            }
        } else {
            std::istream_iterator<std::string> begin(std::cin);
            std::istream_iterator<std::string> end;
            logger.log(begin, end);
        }
    }

    catch(const char* err) {
        std::cout << err << std::endl;
    }
    return 0;
}
