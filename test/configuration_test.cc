#include "../src/sensor_logger_info.hh"
#include "../src/configuration.hh"

#include "utils/filesystem.hh"
#include <sstream>
#include <CppUTest/TestHarness.h>
#include <CppUTestExt/MockSupport.h>


TEST_GROUP(ConfigurationTest) {
    void setup() { }
    void teardown() {
        mock().clear();
    }
};

/**
 * HAVE A TestFilesystem object
 * WHEN get_config_folder_path
 * THEN expect path returned to be: ~/.config/name_of_app
 *      where ~ is the home directory and name_of_app is the name of
 *      this application: SensorLogger::NAME
 */
TEST(ConfigurationTest, ConfigurationTest_01) {
    std::string home_dir("my_home_dir"); 
    TestFilesystem fs(home_dir);
    std::string expected_dir(home_dir);
    expected_dir += "/.config/";
    expected_dir += SensorLoggerInfo::NAME;    
    CHECK_EQUAL(get_config_folder_path(fs), expected_dir);
}

/**
 * HAVE A TestFilesystem object
 * WHEN get_config_filer_path
 * THEN expect path returned to be: ~/.config/name_of_app/config
 *      where ~ is the home directory and name_of_app is the name of
 *      this application: SensorLogger::NAME
 */
TEST(ConfigurationTest, ConfigurationTest_02) {
    std::string home_dir("my_home_dir"); 
    TestFilesystem fs(home_dir);
    std::string path(home_dir);
    path += "/.config/";
    path += SensorLoggerInfo::NAME;
    path += "/config";
    CHECK_EQUAL(get_config_file_path(fs), path);
}

/**
 * HAVE A new instance of ConfigurationData object
 * WHEN input the empty string
 * THEN database_path to be an empty string
 */
TEST(ConfigurationTest, ConfigurationTest_03) {
    std::string empty;
    ConfigurationData config;
    std::stringstream ss(empty);    
    ss >> config;
    CHECK_EQUAL(config.database_path, empty);
}

/**
 * HAVE A new instance of ConfigurationData object
 * WHEN input a string with not valid value
 * THEN datapase_path to be an empty string.
 */
TEST(ConfigurationTest, ConfigurationTest_04) {
    std::string empty;
    std::string invalid_value("This is an invalid value");
    ConfigurationData config;
    std::stringstream ss(invalid_value);    
    ss >> config;
    CHECK_EQUAL(config.database_path, empty);
}

/**
 * HAVE A new instance of ConfigurationData object
 * WHEN input a string as follow: "data_base_path = path_to_value"
 * THEN datapase_path of the configuration object to be path_to_value
 */
TEST(ConfigurationTest, ConfigurationTest_05) {
    std::string value("path_to_value");
    std::string config_string("data_base_path = path_to_value");
    ConfigurationData config;
    std::stringstream ss(config_string);
    ss >> config;
    CHECK_EQUAL(config.database_path, value);
}

/**
 * HAVE A new instance of ConfigurationData object
 * WHEN input a string as follow: "data_base_path=path_to_value"
 * THEN datapase_path of the configuration object to be path_to_value
 */
TEST(ConfigurationTest, ConfigurationTest_06) {
    std::string value("path_to_value");
    std::string config_string("data_base_path=path_to_value");
    ConfigurationData config;
    std::stringstream ss(config_string);
    ss >> config;
    CHECK_EQUAL(config.database_path, value);
}


/**
 * HAVE A new instance of ConfigurationData object
 * WHEN input a string as follow: "#data_base_path=path_to_value"
 * THEN datapase_path of the configuration object to be an empty string
 *      (# character is a comment).
 */
TEST(ConfigurationTest, ConfigurationTest_07) {
    std::string empty;
    std::string config_string("#data_base_path=path_to_value");
    ConfigurationData config;
    std::stringstream ss(config_string);
    ss >> config;
    CHECK_EQUAL(config.database_path, empty);
}

/**
 * HAVE A filesystem object with a not existed configuration path
 * WHEN call get_config_folder_pat
 * THEN the configuration path to have been created through the
 *      fileystem object.
 */
TEST(ConfigurationTest, ConfigurationTest_08) {
     std::string home_path("my_home_dir");
     TestFilesystem fs(home_path);
     std::stringstream ss;
     ss << home_path << "/.config/" << SensorLoggerInfo::NAME;
     fs.set_existance(ss.str(), false);
     get_config_folder_path(fs);
     CHECK(fs.exists(ss.str()));
}
