#include <string>
#include <sstream>
#include "sqlite_logger.hh"

namespace __SQLITE__INTERNAL__ {  
    sqlite3* create_connection(const std::string& db_file) {
        sqlite3 *db;
        sqlite3_open(db_file.c_str(), &db);
        return db;
    }
}

SqliteLogger::SqliteLogger(const std::string& db_path)
    : _db(__SQLITE__INTERNAL__::create_connection(db_path)){
    
    std::stringstream ss;
    ss << "CREATE TABLE IF NOT EXISTS "
       << _table_name << " ("
       << _id_column_name << " INTEGER PRIMARY KEY,"
       << _sensor_column_name << " TEXT NOT NULL,"
       << _value_column_name << " REAL NOT NULL,"
       << _timestamp_column_name << " INTEGER NOT NULL,"
       << _sent_flag_column_name << " INTEGER NOT NULL);";
    _execute(ss.str());
}

SqliteLogger::~SqliteLogger() {
    sqlite3_close(_db);
}

void SqliteLogger::_execute(const std::string& stmt) {
    std::cout << "Executing: \n"
              << stmt
              << "\n" << std::endl;
    char *zErrMsg = 0;
    auto result = sqlite3_exec(_db,
                               stmt.c_str(),
                               NULL,
                               NULL,
                               &zErrMsg);
    if(result != SQLITE_OK) {            
        throw sqlite3_errmsg(_db);
    }
}
