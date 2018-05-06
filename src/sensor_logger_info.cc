#include "sensor_logger_info.hh"

Informations::Informations() { }
Informations::~Informations() { }

std::ostream& operator<<(std::ostream& os,
                         const Informations& informations) {
    os << informations.name << " " << informations.version << "\n"
       << "License " << informations.license
       << "GNU GPL version 3 or later "
       << "<http://gnu.org/license/gpl.html>\n"
       << "This is a free software: you are free to change and "
       << "redistribute it.\n"
       << "There is NO WARRANTY, to the extent permitted law.";
    return os;
}
