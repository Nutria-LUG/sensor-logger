#include <ostream>
#include "sensor_logger_info.hh"

const char* SensorLoggerInfo::NAME  = "sensor-logger";
const char* SensorLoggerInfo::VERSION_NUMBER  = "1.0.0";
const char* SensorLoggerInfo::CONFIG_FILE_NAME  = "config";
const char* SensorLoggerInfo::LICENSE = "GPLv3";

std::ostream& out_informations(std::ostream& os) {
    os << SensorLoggerInfo::NAME << " "
       << SensorLoggerInfo::VERSION_NUMBER << "\n"
       << "License GPLv3+: GNU GPL version 3 or later "
       << "<http://gnu.org/licenses/gpl.html>.\n"
       << "This is free software: you are free to "
       << "change and redistribute it.\n"
       << "There is NO WARRANTY, to the extent "
       << "permitted by law.\n"
       << std::endl;
    return os;
}
