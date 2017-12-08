/*!
 * \brief     This file contains the informations data struct that
 *            contains static elements used to have program's
 *            informations at run time.
 * \file      sensor_logger_info.hh
 * \author    NutriaLUG
 * \copyright GNU Public License
 */

#include <ostream>

#ifndef SENSOR_LOGGER_INFO_INCLUDE_GUARD_HH
#define SENSOR_LOGGER_INFO_INCLUDE_GUARD_HH 1

/*!
 * This data struct contains static informations about the current
 * program.
 */
struct SensorLoggerInfo {
    /*! Name of the program. */
    static const char* NAME;
    /*! Current version. */
    static const char* VERSION_NUMBER;
    /*! Name of the configuration file. */
    static const char* CONFIG_FILE_NAME;
    /*! Kind of license of the program. */
    static const char* LICENSE;
};

/*!
 * Put the informations about the program on the ostream object passed
 * as parameter.
 * \param os - Ostream object where put the informations about this
 *             program.
 * \return ostream object passed as parameter to allow chaining.
 */
std::ostream& out_informations(std::ostream& os);
#endif
