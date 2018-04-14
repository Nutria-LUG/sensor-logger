#include <string>
#include <ctime>
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
}

SqliteLogger::~SqliteLogger() {
    sqlite3_close(_db);
}

std::istream& SqliteLogger::log(std::istream& is) {
    std::time_t t;
    std::time(&t);
    bool first = true;
    std::string str;
    std::stringstream ss("INSERT INTO ");
    ss << _table_name << "("
       << _id_column_name << ","
       << _sensor_column_name << ","
       << _value_column_name << ","
       << _timestamp_column_name << ")";
    while(is >> str) {
        if(!first) {
            ss << ",";
        } else {
            first = false;
        }
        ss << " VALUES(NULL, "
           << str << ",";
        is >> str;
        ss << str << "," << t << ")";
    }
    ss << ";";
    if(!first) {
        _execute(ss.str());
    }
    return is;
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
