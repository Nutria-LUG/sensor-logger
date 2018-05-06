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
#include <string>

#ifndef SENSOR_LOGGER_INFO_INCLUDE_GUARD
#define SENSOR_LOGGER_INFO_INCLUDE_GUARD 1

/*!
 * This struct contains the informations about this program.
 * It is used to print that informations when required.
 */
struct Informations {
    /*! Name of the program. */
    const std::string name    = "sensor-logger";
    /*! Current version. */
    const std::string version = "2.1.0";
    /*! Author. */
    const std::string author  = "NutriaLUG";
    /*! License of this software. */
    const std::string license = "GPLv3+";

    /*! Default constructor. */
    Informations();
    /*! Default destructor. */
    ~Informations();
};

/*!
 * operator<< overloading used to print the inforamtions stored inside
 * the struct passed.
 *
 * \param os           - output stream used to print out the
 *                       informations stred in the struct passed as
 *                       parameter.
 * \param informations - Informations structure to print.
 * \return The ostream reference passed as parameter to perform
 *         operator chaining.
 */
std::ostream& operator<<(std::ostream& os,
                         const Informations& informations);

#endif

