#include "sensor_logger_info.hh"

void out_informations(std::ostream& os) {
    os << NAME << " " << VERSION << "\n"
       << "License " << LICENSE
       << "GNU GPL version 3 or later "
       << "<http:://gnu.org/license/gpl.html>\n"
       << "This is a free software: you are free to change and "
       << "redistribute it.\n"
       << "There is NO WARRANTY, to the extent permitted law."
       << std:: endl;
}
