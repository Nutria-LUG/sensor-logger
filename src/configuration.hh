/*!
 * \brief     This file contains the definition of the object used
 *            to handle the configuration of the application in a more
 *            confortable way: it use the ConfigFile class to read
 *            data and put theme in a strcut.
 * \file      configuration.hh
 * \author    NutriaLUG
 * \copyright GNU Public License
 */


#ifndef CONFIGURATION_INCLUDE_GUARD_HH
#define CONFIGURATION_INCLUDE_GUARD_HH 1

#include <string>
#include <map>

namespace configuration {

    /*!
     * This class represent a configuration file. It parse a file with
     * the following format:
     *
     *  # This is a comment.
     *  # This is the configuartion entry for 'configuration_key':
     *  configuration_key = configuration_value
     *
     * Each entry can be retrived by the get method.
     */
    class ConfigFile {
    public:
        /*\
         * \brief Default constructor.
         * Initialize an empty file with no entries.
         */
        ConfigFile();
        /*!
         * \brief Constructor with one parameter.
         * Initialize the object parsing the file specified as
         * parameter. If file does not exists or cannot be open, an
         * exception will be thrown.
         *
         * \param file - Configuration file to parse.
         */
        ConfigFile(const std::string& file);
        /*! Destructor. */
        ~ConfigFile();
        /*!
         * \brief Gets the value of the entry passed as parameter.
         * Gets the value keyed by the parameter passed. That value is
         * taken by the configuration file passed. If the entry does
         * not exists this method return an empty string.
         *
         * \param key - Key of the configuration value to get.
         * \return The relative value assigned in the configuration
         *         file at the key passed. For example, given the
         *         following configuration file:
         *            fake_key = fake_value
         *         when get method is called passing "fake_key" as
         *         parameter, the string "fake_value" to be returned.
         */
        const std::string& get(const std::string& key);
        
    private:
        /*!
         * Map used to store the keys and values taken by the
         * configuration file.
         */
        std::map<std::string, std::string> _config;
    };
    
    /*!
     * \brief Get the configuraiton folder
     * Gets the configuration folder of the system. It is located in
     * HOME_ENV/.config/APPLICATION_NAME where:
     *  - HOME_ENV: Is the value of the HOME environment variable.
     *  - APPLICATION_NAME: Name of the application.
     * See defs.hh for the preprocessor directive that define both.
     * \return A string that contains the path of the configuration
     *         folder.
     */
    std::string get_config_folder();

    /*!
     * \brief Get the configuration file.
     * Gets the configuration file. It is located in 
     * HOME_ENV/.config/APPLICATION_NAME/configuration where:
     *  - HOME_ENV: Is the value of the HOME environment variable.
     *  - APPLICATION_NAME: Name of the application.
     * See defs.hh for the preprocessor directive that define both.
     * \return A string that contains the path of the configuration
     *         file.
     */
    std::string get_config_file();

    /*!
     * Data struct that contains the configuration informations.
     */
    struct ConfigurationData {
        /*! 
         * Sqlite data base path that contains the sourvays registered
         * from the sensors.
         */
        std::string  sourvays_db;
    };


    /*!
     * Configuration object that allow to handle the configuration
     * file in a more confortable way.
     */
    class Configuration {
    public:
        /*!
         * \brief Default constructor: initialize the data by the
         *        configuration file.
         * Default constructor. Build the configuration through the
         * file retrieved by get_config_file function. Each not
         * existent folder in the path will be created and if the file
         * does not exists, this constructor create it with the default
         * values.
         */
        Configuration();
        /*! Destructor. */
        ~Configuration();
        /*!
         * \brief Gets the configuration data.
         * This method return the data parsed from the configuration
         * file. This is used to handle configuration in a more
         * confortable way, through a struct instead of a list of
         * strings.
         * \return Data struct that contains each configuration entry.
         */
        const ConfigurationData& get_data() const;

    private:
        /*!
         * \brief Constructor with one parameter.
         * Initialize the configuration from the file passed. It is
         * used by the default constructor.
         */
        Configuration(const std::string& config_file);
        /*! Configuration data retrieved by the configuration file. */
        ConfigurationData _configuration_data;
    };    
}

#endif
