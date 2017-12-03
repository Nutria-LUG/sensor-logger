#include "sensor.hh"
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
