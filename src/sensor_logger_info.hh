/*!
 * \file      src/sensor_logger_info.hh
 * \brief     This file contains the informations about this program.
 * \copyright GNU Public License.
 * \author    Gabriele Labita
 *            <gabriele.labita@linux.it>
 *
 * This file contains the definition of components used to gets
 * informations about this program.
 */

#include <ostream>

#ifndef SENSOR_LOGGER_INFO_INCLUDE_GUARD
#define SENSOR_LOGGER_INFO_INCLUDE_GUARD 1

/*! Name of the program. */
#define NAME    "sensor-logger"
/*! Current version. */
#define VERSION "2.0.0"
/*! Author.. */
#define AUTHOR  "NutriaLUG"
/*! License of this software */
#define LICENSE "GPLv3+"

/*!
 * Put in the output stream passed as parameter the informations about
 * this program.
 * \param os - output stream where put the informations.
 */
void out_informations(std::ostream& os);

#endif

