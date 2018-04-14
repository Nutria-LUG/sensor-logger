/*!
 * \brief     This file contains the definition of the main program
 *            used to perform the sourvays log.
 * \file      main.cc
 * \author    NutriaLUG
 * \copyright GNU Public License
 */

#include <iostream>
#include <cstring>
#include <fstream>
#include "configuration.hh"
#include "sqlite_logger.hh"

int main(int argc, char* argv[]) {
    if(argc == 2 && strcmp(argv[1], "--log") == 0) {
        std::ifstream is(get_configuration_file_path());
        ConfigurationData config;
        is >> config;
        SqliteLogger logger(config.database_path);
        logger.log(std::cin);
        
    }
    return 0;
}
