/* Log sensor values.
 * Copyright (C) 2018 NutriaLUG
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*!
 * \file      src/sensor_logger_info.hh
 * \brief     This file contains the informations about this program.
 * \copyright GNU Public License.
 * \author    NutriaLUG
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

