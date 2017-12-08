#include "sensor_reader_info.hh"
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

ConfigurationData::~ConfigurationData() {
}


std::istream& operator>>(std::istream& is,
                         ConfigurationData& config) {
    std::string line;
    int posEqual;
    while (std::getline(is,line)) {
        if (!line.length() ||
            line[0] == '#' ||
            line[0] == ';') {
            continue;
        }        
        posEqual = line.find('=');
        std::string key = __CONFIGURATION__INTERNAL__NS__::trim(
            line.substr(0, posEqual));
        if(key == DATABASE_PATH_KEY) {
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
    path += SensorReaderInfo::NAME;
    if(!filesystem.exists(path)) {
        filesystem.create_directories(path);
    }
    return path;
}

std::string get_config_file_path(Filesystem& filesystem) {
    std::stringstream ss;
    ss << get_config_folder_path(filesystem)
       << "/" << SensorReaderInfo::CONFIG_FILE_NAME;
    return ss.str();
}
