/*!
 * \brief     This file contains the definition of the components and
 *            operators to fill the configuration data structure.
 * \file      configuration.hh
 * \author    NutriaLUG
 * \copyright GNU Public License
 */


#include <string>
#include <istream>
#include "filesystem/filesystem.hh"

#ifndef CONFIGURATION_INCLUDE_GUARD_HH
#define CONFIGURATION_INCLUDE_GUARD_HH 1


/*!
 * \brief Get the configuraiton folder
 * Gets the configuration folder of the system. It is located in
 * HOME_ENV/.config/APPLICATION_NAME where:
 *  - HOME_ENV:         Is the home folder returned by the filesystem
 *                      implementation.
 *  - APPLICATION_NAME: Name of the application.
 * \param filesystem - Filesystem implementation used to perform the
 *                     dependents operations (such as get of the home
 *                     env).
 * If the folder does not exists, it will be created.
 * \return A string that contains the path of the configuration
 *         folder.
 */
std::string get_config_folder_path(Filesystem& filesystem);

/*!
 * \brief Get the configuration file.
 * Gets the configuration file. It is located in 
 * HOME_ENV/.config/APPLICATION_NAME/configuration where:
 *  - HOME_ENV:         Is the home folder returned by the filesystem
 *                      implementation.
 *  - APPLICATION_NAME: Name of the application.
 * If the path to the file is not found, it will be created (this
 * function calls get_config_folder_path function).
 * \return A string that contains the path of the configuration
 *         file.
 */
std::string get_config_file_path(Filesystem& filesystem);

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
 * This macro represent the key value of the data base path in the
 * configuration file.
 */
#define DATABASE_PATH_KEY "data_base_path"

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
