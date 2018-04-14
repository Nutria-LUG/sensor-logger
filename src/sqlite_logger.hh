
#ifndef SQLITE_LOGGER_INCLUDE_GUARD
#define SQLITE_LOGGER_INCLUDE_GUARD 1

#include <sqlite3.h>
#include <string>
#include <istream>

class SqliteLogger {
public:
    SqliteLogger(const std::string& db_path);
    ~SqliteLogger();

    std::istream& log(std::istream& is);    
private:
    SqliteLogger();
    SqliteLogger(const SqliteLogger&);
    SqliteLogger(const SqliteLogger&&);

    void _execute(const std::string& stmt);
    
    /*! Pointer to the sqlite3 data base connector. */
    sqlite3           *_db;
    const std::string _table_name = "sourvays";
    const std::string _id_column_name = "id";
    const std::string _sensor_column_name = "sensor";
    const std::string _value_column_name = "value";
    const std::string _timestamp_column_name = "timestamp";
    const std::string _sent_flag_column_name = "sentflag";
};

#endif
