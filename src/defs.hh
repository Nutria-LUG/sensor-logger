/*!
 * \brief     This file contains the definition of the information
 *            structure to have meta information about the program
 *            at run time.
 * \file      defs.hh
 * \author    NutriaLUG
 * \copyright GNU Public License
 */

#ifndef DEFS_INCLUDE_GUARD_HH
#define DEFS_INCLUDE_GUARD_HH 1

/*!
 * \brief This is the sensor reader information structure that contains
 *        data static inforamtions about the program.
 */
struct SensorReaderInfo {
    /*! Name of the program */
    static const char* NAME;
    /*! Current version of the program */
    static const char* VERSION_NUMBER;
    /*!
     * Identifier of the HOME env used to know where home folder is
     * located. This is used in the configuration module.
     */
    static const char* HOME_ENV;
    /*! Name of the configuration file. */
    static const char* CONFIG_FILE_NAME;
};

#endif
