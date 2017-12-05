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
 * The list of available sensor is read from the data base.
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
 * Overloading of the operator<<, it put in the stream passed the name
 * of the sensor with a \n at the end.
 * \param os     - Output stream where ouput the sensor passed as
 *                 parameter.
 * \param sensor - Sensor to output.
 * \return A ostream reference to give the possibility to chain the
 *         output.
 */
std::ostream& operator<<(std::ostream& os, const Sensor& sensor);

#endif
