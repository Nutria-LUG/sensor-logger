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
#include <string.h>
#include <iterator>

#include "configuration.hh"
#include "sqlite_logger.hh"
#include "sensor_logger_info.hh"

int main(int argc, char* argv[]) {
    SqliteLogger logger("");
    if (argc >= 2) {
        if(strcmp(argv[1], "--version") == 0) {
            out_informations(std::cout);
        } else {
            logger.log(argv + 1, argv + argc - 1);
        }
    } else {
        std::istream_iterator<std::string> begin(std::cin);
        std::istream_iterator<std::string> end;
        logger.log(begin, end);
    }
    return 0;
}
