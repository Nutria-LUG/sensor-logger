/*!
 * \brief     This file contains the definition of the structure used
 *            to represent a sensor.
 * \file      sensor.hh
 * \author    NutriaLUG
 * \copyright GNU Public License
 */

#include <string>
#include <ostream>

#ifndef SENSOR_INCLUDE_GUARD_HH
#define SENSOR_INCLUDE_GUARD_HH 1

/*!
 * \brief This structure represent a sensor. It contains main
 *        informations of the sensor.
 *
 * This structure contains the informations neede to represent a
 * a sensor. It is used to save the sourvay passed by argumetns in the
 * database: name passed is searched from the collection of available
 * sensors and the id used to perform entry in the data base.
 * 
 * \def   A sensor is a VALID SENSOR  if its id and name are not empty
 *        string.
 */
struct Sensor {

    /*! Id of the sensor used to identify it in the whole program. */
    std::string id;

    /*!
     * Name of the sensor. It represent the sensor in the command
     * line interface.
     */
    std::string name;

    /*! \brief Default constructor. */
    Sensor();

    /*!
     * Constructor with two parameters.
     * \param sensor_id   Id of the sensor.
     * \param sensor_name Name of the sensor.
     */
    Sensor(const std::string& sensor_id,
           const std::string& sensor_name);

    /*!
     * \brief Copy constructor
     * \param sensor Sensor to copy.
     */
    Sensor(const Sensor& sensor);

    /*!
     * \brief Move constructor. Move each attribute from the sensor
     *        passed to this object.
     * \param sensor Sensor to move.
     */    
    Sensor(const Sensor&& sensor);
    
    /*! Destructor. */
    ~Sensor();
};

/*!
 * Oveloading of the == operator. Check if the sensor id is the same
 * passed as second parameter.
 * \param sensor    - Sensor to check.
 * \param sensor_id - Id to check,
 * \return True if the sensor has the same id passed as second
 *         parameter, false otherwise.
 */
bool operator==(const Sensor& sensor, const char* sensor_id);

/*!
 * Overloading of the operator<<, it put in the stream passed the name
 * of the sensor with a \n at the end.
 * \param os     - Output stream where ouput the sensor passed as
 *                 parameter.
 * \param sensor - Sensor to output.
 * \return A ostream reference to give the possibility to chain the
 *         output.
 */
std::ostream& operator<<(std::ostream& os, const Sensor& sensor);

/*!
 * \brief Builder function for the sensors.
 *
 * This function fill the list of availble sensors in the program. The
 * available collection of sensors is created in the code (not by
 * configuration)
 *
 * \tparam InserterIterator - Inserter iterator.
 * \param inserter_iterator - Inserter iterator used to put the sensors
 *                            in.
 */
template<class InserterIterator>
inline void create_sensors(InserterIterator inserter_iterator) {
    *inserter_iterator = Sensor("pm10", "pm10");
    *inserter_iterator = Sensor("temperature", "temperature");
    *inserter_iterator = Sensor("humidity", "humidity");
}
#endif
