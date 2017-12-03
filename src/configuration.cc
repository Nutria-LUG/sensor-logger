#include "defs.hh"
#include "filesystem.hh"
#include "configuration.hh"
#include <sstream>
#include <fstream>

namespace __CONFIGURATION__INTERNAL__NS__ {
    const char* SOURVAYS_DB = "sourvays";
    const char* DB_EXTENSION = ".db";

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
    
    const std::string& create_if_not_exists(
        const std::string& config_file) {
        if(!filesystem::exists(config_file)) {
            filesystem::create_directories(config_file);
            std::string path = filesystem::get_path(config_file);
            std::ofstream of(config_file);
            of << SOURVAYS_DB << " = "
               << path << "/" << SOURVAYS_DB << DB_EXTENSION
               << std::endl;
            of.close();
        }
        return config_file;
    }
}

configuration::ConfigFile::ConfigFile()
    : _config() { }

configuration::ConfigFile::ConfigFile(const std::string& file)
    : configuration::ConfigFile::ConfigFile() {
    std::ifstream fs(file.c_str());
    std::pair<std::string, std::string> elem;
    std::string line;
    int posEqual;
    while (std::getline(fs,line)) {
        if (!line.length() ||
            line[0] == '#' ||
            line[0] == ';') {
            continue;
        }        
        posEqual = line.find('=');
        elem.first  = __CONFIGURATION__INTERNAL__NS__::trim(
            line.substr(0, posEqual));
        elem.second = __CONFIGURATION__INTERNAL__NS__::trim(
            line.substr(posEqual + 1));
        _config.insert(elem);
    }
}

configuration::ConfigFile::~ConfigFile() { }


const std::string&
configuration::ConfigFile::get(const std::string& key) {
    return _config[key];
}

std::string configuration::get_config_folder() {
    std::string path(getenv(SENSOR_READER_INFO::HOME_ENV));
    path += "/.config";
    if(!filesystem::exists(path)) {
        filesystem::create_directories(path);
    }
    path += "/";
    path += SENSOR_READER_INFO::NAME;;
    if(!filesystem::exists(path)) {
        filesystem::create_directories(path);
    }
    return path;
}
std::string configuration::get_config_file() {
    std::stringstream ss;
    ss << configuration::get_config_folder()
       << "/" << SENSOR_READER_INFO::CONFIG_FILE_NAME;
    return ss.str();
}

configuration::Configuration::Configuration()
    : configuration::Configuration(configuration::get_config_file()) {
}
configuration::Configuration::Configuration(const std::string&
                                            config_file)
    : _configuration_data() {
    __CONFIGURATION__INTERNAL__NS__::create_if_not_exists(config_file);
    configuration::ConfigFile file(config_file);
    _configuration_data.sourvays_db =
        file.get(__CONFIGURATION__INTERNAL__NS__::SOURVAYS_DB);
}

configuration::Configuration::~Configuration() { }

const configuration::ConfigurationData&
configuration::Configuration::get_data() const {
    return _configuration_data;
}
