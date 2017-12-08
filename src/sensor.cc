#include "sensor.hh"
#include <cstring>
#include <algorithm>

Sensor::Sensor() {}

Sensor::Sensor(const std::string& sensor_id,
               const std::string& sensor_name)
    : id(sensor_id), name(sensor_name) { }

Sensor::Sensor(const Sensor& sensor)
    : Sensor(sensor.id, sensor.name) { }

Sensor::Sensor(const Sensor&& sensor)
    : id(std::move(sensor.id)), name(std::move(sensor.name)) { }

Sensor::~Sensor() {}

bool operator==(const Sensor& sensor, const char* sensor_id) {
    return strcmp(sensor.id.c_str(), sensor_id) == 0;
}

std::ostream& operator<<(std::ostream& os, const Sensor& sensor) {
    os << sensor.name << "\n";
    return os;
}
