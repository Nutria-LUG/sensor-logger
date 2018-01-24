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



#include <sstream>
#include <map>
#include <iostream>

/*!
 * This function perform the read of sourvays through the input stream
 * specified by parameter.
 * It put the result sourvays in the collection passed as inserter
 * iterator.
 * NOTE: Sourvays are read in the following format: id of the sensor,
 *       value of the sourvay seprated by a ' ' or '\n' character.
 *       Different sourvays must be seperated by ' ' or '\n' character.
 *
 * \tpar InserterIterator - Iterator to use to put the sourvays inside
 *                          the collection.
 * \param sensors  - Map of sensors used to get the sensors by id
 *                   without perform any search.
 * \param inserter - Inserter iterator used to put sourvays inside the
 *                   collection.
 * \param is       - Input stream used to get the sourvays.
 * \return A boolean value used to know if the sourvays passed are in
 *         the right format. Return true if sourvays are ok, false
 *         otherwise.
 */
template<class InserterIterator>
inline bool read_sourvays(const std::map<std::string, Sensor*>& sensors,
                          InserterIterator inserter,
                          std::istream& is) {
    std::time_t t;
    std::time(&t);

    std::string str;
    while(is >> str) {
        Sourvay sourvay;
        sourvay.timestamp = t;
        sourvay.sensor = sensors.at(str);
        if(sourvay.sensor == NULL) { return false; }
        is >> str;
        try {
            sourvay.value = std::stof(str);
        } catch(...) {
            return false;
        }
        *inserter = sourvay;
    }
    return true;
}
#endif
