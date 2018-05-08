#include <string>
#include <sstream>
#include "sqlite_logger.hh"

namespace __SQLITE__INTERNAL__ {  
    sqlite3* create_connection(const std::string& db_file) {
        sqlite3 *db;
        sqlite3_open(db_file.c_str(), &db);
        return db;
    }
    
    void create_surveys_table_cmd(std::ostream& os) {
        os << "CREATE TABLE IF NOT EXISTS "
           << SURVEYS_TABLE_NAME << " ("
           << ID_COLUMN_NAME << " INTEGER PRIMARY KEY,"
           << SENSOR_COLUMN_NAME << " TEXT NOT NULL,"
           << VALUE_COLUMN_NAME << " REAL NOT NULL,"
           << TIMESTAMP_COLUMN_NAME
           << " INTEGER NOT NULL);";
    }

    void create_errors_table_cmd(std::ostream& os) {
        os << "CREATE TABLE IF NOT EXISTS "
           << ERRORS_TABLE_NAME << " ("
           << ID_COLUMN_NAME << " INTEGER PRIMARY KEY,"
           << VALUE_COLUMN_NAME << " TEXT NOT NULL,"
           << TIMESTAMP_COLUMN_NAME
           << " INTEGER NOT NULL);";
    }
}

SqliteLogger::SqliteLogger(const std::string& db_path)
    : _db(__SQLITE__INTERNAL__::create_connection(db_path)){
    
    std::stringstream ss;
    __SQLITE__INTERNAL__::create_surveys_table_cmd(ss);
    _execute(ss.str());
        
    ss.clear();
    __SQLITE__INTERNAL__::create_errors_table_cmd(ss);
    _execute(ss.str());
}

SqliteLogger::~SqliteLogger() {
    sqlite3_close(_db);
}

void SqliteLogger::_execute(const std::string& stmt) {
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
