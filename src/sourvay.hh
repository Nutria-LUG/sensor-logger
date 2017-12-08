/*!
 * \brief     This file contains the definition of the sourvay data
 *            structure use to represent a single sourvay to log.
 * \file      sourvay.hh
 * \author    NutriaLUG
 * \copyright GNU Public License
 */

#include <string>
#include "sensor.hh"
#include <ctime>

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

    
#endif
