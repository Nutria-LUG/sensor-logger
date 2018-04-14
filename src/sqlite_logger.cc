#include <string>

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

#include<iostream>
void SqliteLogger::_execute(const std::string& stmt) {
    std::cout << stmt << std::endl;
    // char *zErrMsg = 0;
    // auto result = sqlite3_exec(_db,
    //                            stmt.c_str(),
    //                            NULL,
    //                            NULL,
    //                            &zErrMsg);
    // if(result != SQLITE_OK) {            
    //     throw sqlite3_errmsg(_db);
    // }
}
