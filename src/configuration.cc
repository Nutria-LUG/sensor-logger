#include "sensor_logger_info.hh"
#include "filesystem/filesystem.hh"
#include "configuration.hh"
#include <fstream>
#include <sstream>
#include <istream>

namespace __CONFIGURATION__INTERNAL__NS__ {

    std::string trim(std::string const& source,
                     char const* delims = " \t\r\n") {
        std::string result(source);
        std::string::size_type index = result.find_last_not_of(delims);
        if(index != std::string::npos) {
            result.erase(++index);
        }
        index = result.find_first_not_of(delims);
        if(index != std::string::npos) {
            result.erase(0, index);
        } else {
            result.erase();
        }
        return result;
    }

}


ConfigurationData::ConfigurationData()
    : database_path() { }

ConfigurationData::~ConfigurationData() { }

#include<iostream>
std::istream& operator>>(std::istream& is,
                         ConfigurationData& config) {
    std::string line;
    int posEqual;
    while (std::getline(is, line)) {
        if (!line.length() ||
            line[0] == '#' ||
            line[0] == ';') {
            continue;
        }
        posEqual = line.find('=');
        std::string key = __CONFIGURATION__INTERNAL__NS__::trim(
            line.substr(0, posEqual));
        if (key == DATABASE_PATH_KEY) {
            std::string value = line.substr(posEqual + 1);
            config.database_path =
                __CONFIGURATION__INTERNAL__NS__::trim(value);
        }
    }    
    return is;
}


std::string get_config_folder_path(Filesystem& filesystem) {
    std::string path(filesystem.get_home_path());
    path += "/.config";
    if(!filesystem.exists(path)) {
        filesystem.create_directories(path);
    }
    path += "/";
    path += SensorLoggerInfo::NAME;
    if(!filesystem.exists(path)) {
        filesystem.create_directories(path);
    }
    return path;
}

std::string get_config_file_path(Filesystem& filesystem) {
    std::stringstream ss;
    ss << get_config_folder_path(filesystem)
       << "/" << SensorLoggerInfo::CONFIG_FILE_NAME;
    std::string file_path = ss.str();
    if(!filesystem.exists(file_path)) {
        std::ofstream of(file_path);
        of << DATABASE_PATH_KEY
           << "="
           << get_config_folder_path(filesystem)
           << "/database.db";
        of.close();
    }
    return ss.str();
}
