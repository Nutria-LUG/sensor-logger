/*!
 * \brief     This file contains the definition of the sourvay data
 *            structure use to represent a single sourvay to log.
 * \file      sourvay.hh
 * \author    NutriaLUG
 * \copyright GNU Public License
 */

#include <string>
#include <ctime>
#include "sensor.hh"

#ifndef SOURVAY_INCLUDE_GUARD_HH
#define SOURVAY_INCLUDE_GUARD_HH 1

/*!
 * \brief This is the data structure used to represent a single sourvay
 *        to register on the data base.
 *
 * \def   A sourvay is VALID SOURVAY if the sensor pointer is not null
 *        and points to a valid sensor (see sensor.hh to have the
 *        defintion of valid sensor).
 */
struct Sourvay {

    /*! Pointer to the sensor that performed the souvay. */
    Sensor* sensor;

    /*! Value of the sourvay to save on the data base. */
    float value;

    /*! Timestamp of the sourvay. */
    std::time_t timestamp;

    /*!
     * \brief Default constructor.
     *
     * Initialize the value to its default value and pointer to the
     * sensor to null.
     */
    Sourvay();

    /*!
     * \brief Copy constructor.
     *
     * \param sourvay Sourvay to copy.
     */
    Sourvay(const Sourvay& sourvay);

    /*!
     * \brief Move constructor.
     *
     * \param sourvay - Sourvay to move.
     */
    Sourvay(Sourvay&& sourvay);

    /*! Default destructor. */
    ~Sourvay();
};



#include <ctime>
#include <algorithm>
#include <sstream>

/*!
 * Create the sourvays adding it in the inserter iterator passed as
 * parameter.
 * Parse the arguments passed as range parameters and use the sensor
 * range to take the right sensor to put inside each sourvays.
 * Timestamp of each sourvay is set to current time.
 *
 * \tpar SourvayIterator  - Forward iterator of the sourvays to parse.
 * \tpar SensorIterator   - Forward iterator of the sensors.
 * \tpar InserterIterator - Inserter iterator to assign the sourvays.
 *
 * \param sourvay_begin  - Iterator to the begin of the sourvays
 *                         collection in the format:
 *                           name_of_sensor valu_of_sensor
 *                         In pratice name and value separated by a
 *                         space.
 * \param sourvay_end    - Iterator to the end of the sourvays
 *                         collection in the format:
 *                           name_of_sensor valu_of_sensor
 *                         In pratice name and value separated by a
 *                         space
 * \param s_begin        - Iterator to the begin of the sensors
 *                         collection.
 * \param s_end          - Iteartor to the end of the sensors
 *                         collection.
 * \param inserter       - Inserter iterator used to put the sourvays
 *                         inside a collection.
 */
template<class SourvayIterator,
         class SensorIterator,
         class InserterIterator>
bool create_sourvays(SourvayIterator sourvay_begin,
                     SourvayIterator sourvay_end,
                     SensorIterator s_begin,
                     SensorIterator s_end,
                     InserterIterator inserter) {
    std::time_t t;
    std::time(&t);

    while(sourvay_begin != sourvay_end) {
        std::string sensor_id;
        std::string value;
        std::istringstream ss(*sourvay_begin);

        std::getline(ss, sensor_id, ' ');
        std::getline(ss, value, ' ');
        
        auto s_itr = std::find(s_begin, s_end, sensor_id);
        if(s_itr == s_end) {
            return false;
        }
        Sourvay sourvay;
        sourvay.timestamp = t;
        sourvay.sensor = &(*s_itr);
        
        try {
            sourvay.value = std::stof(value);
        } catch(...) {
            return false;
        }
        *inserter = sourvay;
        ++sourvay_begin;
    }
    return true;
}

#endif
