/*!
 * \brief     This file contains the definition of the components and
 *            operators to fill the configuration data structure.
 * \file      configuration.hh
 * \author    NutriaLUG
 * \copyright GNU Public License
 */


#include <string>
#include <istream>

#ifndef CONFIGURATION_INCLUDE_GUARD_HH
#define CONFIGURATION_INCLUDE_GUARD_HH 1

#define OPEN_AIR_CONFIGURATION_FILE_NAME ".openair"
#define OPEN_AIR_DATABASE_NAME           ".openair.db"
#define OPEN_AIR_HOME_ENV                "HOME"

std::string get_configuration_file_path();

/*!
 * This macro represent the key value of the data base path in the
 * configuration file.
 */
#define DATABASE_PATH_KEY "data_base_path"

/*!
 * Data struct that contains the configuration informations.
 */
struct ConfigurationData {
    /*! 
     * Sqlite3 data base path that contains the database where perform
     * the log operations.
     */
    std::string database_path;
    
    /*! Default constructor. */
    ConfigurationData();

    /*! Default destructor. */
    ~ConfigurationData();
};

/*!
 * \brief This is the operator>> overloading used to initialize the
 *        configuration.
 *
 * Configuration must be passed in the following format:
 *   key = value
 * Where:
 *  key:   Name of the field to configure
 *  value: Value of that field.
 * Each key value pair will be put in the config object passed as
 * parameter.
 * Characters: '#' and ';' are handled as comments.
 *
 * \param is     - Input stream used to initialize the configuration
 *                 object.
 * \param config - Configuration object to initialize.
 * \return istream object passed as parameter to allow chaining.
 */
std::istream& operator>>(std::istream& is, ConfigurationData& config);

#endif
