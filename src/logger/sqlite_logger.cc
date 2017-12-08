#include <sqlite3.h>
#include <sstream>
#include <list>
#include <vector>
#include <assert.h>

#include "sqlite_logger.hh"

namespace __SQLITE__INTERNAL__ {
  
    sqlite3* sqlite_create_connection(const std::string& db_file) {
        sqlite3 *db;
        sqlite3_open(db_file.c_str(), &db);
        return db;
    }

    static int __callback__(void *query_result,
                            int argc,
                            char **argv,
                            char **azColName) {
        auto *res = (QueryResult*)query_result;
        QueryResult::row row;
        for(int i = 0; i < argc; ++i) {
            if((res -> columns).size() < (unsigned int)(i + 1)) {
                (res -> columns).push_back(azColName[i]);
            }
            row.push_back(argv[i]);
        }
        (res -> rows).push_back(row);
        return 0;
    }

    void sqlite_execute_stmt(sqlite3 *db,
                             const std::string& stmt,
                             QueryResult* out){
        char *zErrMsg = 0;
        auto result = sqlite3_exec(db,
                                   stmt.c_str(),
                                   __callback__,
                                   out,
                                   &zErrMsg);
        if(result != SQLITE_OK) {
            throw DataBaseException(result, sqlite3_errmsg(db));
        }
    }
    
    void sqlite_execute_stmt(sqlite3 *db, const std::string& stmt) {
        char *zErrMsg = 0;
        auto result = sqlite3_exec(db,
                                   stmt.c_str(),
                                   NULL,
                                   NULL,
                                   &zErrMsg);
        if(result != SQLITE_OK) {
            throw DataBaseException(result, sqlite3_errmsg(db));
        }
    }    
}



QueryResult::QueryResult() {}
QueryResult::~QueryResult(){}


DataBaseException::DataBaseException()
  : code(), message() { }

DataBaseException::DataBaseException(
    int exception_code,
    const std::string&
    exception_message)
    : code(exception_code), message(exception_message) { }

DataBaseException::DataBaseException(
    const DataBaseException& db_exception)
    : DataBaseException(db_exception.code, db_exception.message) { }

DataBaseException::~DataBaseException() { }


SqliteLogger::SqliteLogger(const std::string& db_file)
    : _db(__SQLITE__INTERNAL__::sqlite_create_connection(db_file)) {
    assert(OK());
    
    std::stringstream stmt;
    stmt <<  "CREATE TABLE IF NOT EXISTS "
         << SOURVAYS_TABLE_NAME << "("
         << ID_COLUMN_NAME << " INTEGER PRIMARY KEY,"
         << SOURVAYS_TABLE_TIMESTAMP_COLUMN << " INTEGER,"
         << SOURVAYS_TABLE_SEND_FLAG_COLUMN << " INTEGER)"; 
    __SQLITE__INTERNAL__::sqlite_execute_stmt(_db, stmt.str());
    
    assert(OK());
}

SqliteLogger::~SqliteLogger() {
    sqlite3_close(_db);
}

void SqliteLogger::log(const Sourvay& sourvay) noexcept {
    assert(OK() &&
           sourvay.sensor != NULL &&
           sourvay.sensor -> id != "" &&
           sourvay.sensor -> name != "");
    
    std::stringstream add_table_stmt;
    
    add_table_stmt << "CREATE TABLE IF NOT EXISTS "
                   << sourvay.sensor -> name << "("
                   << ID_COLUMN_NAME << " INTEGER PRIMARY KEY,"
                   << SENSOR_TABLE_VALUE_COLUMN << " REAL NOT NULL,"
                   << SENSOR_TABLE_SOURVAY_COLUMN
                   << " INTEGER NOT NULL,"
                   << "FOREIGN KEY("
                   << SENSOR_TABLE_SOURVAY_COLUMN << ") "
                   << "REFERENCES " <<  SOURVAYS_TABLE_NAME
                   << "(" << ID_COLUMN_NAME << "))";
    __SQLITE__INTERNAL__::sqlite_execute_stmt(_db,
                                              add_table_stmt.str());

    std::stringstream insert_sourvay_stmt;
    insert_sourvay_stmt << "INSERT INTO " << SOURVAYS_TABLE_NAME
                        << "(" << ID_COLUMN_NAME << ","
                        << SOURVAYS_TABLE_TIMESTAMP_COLUMN << ","
                        << SOURVAYS_TABLE_SEND_FLAG_COLUMN << ") "
                        << "VALUES(NULL,"
                        << sourvay.timestamp << ","
                        << "0" << ");";
    __SQLITE__INTERNAL__::sqlite_execute_stmt(
        _db, insert_sourvay_stmt.str());

    int last_id = sqlite3_last_insert_rowid(_db);
    std::stringstream insert_sensor_value_stmt;
    insert_sensor_value_stmt << "INSERT INTO "
                             << sourvay.sensor -> name
                             << "(" << ID_COLUMN_NAME << ","
                             << SENSOR_TABLE_VALUE_COLUMN << ","
                             << SENSOR_TABLE_SOURVAY_COLUMN << ") "
                             << "VALUES(NULL, "
                             << sourvay.value << ","
                             << last_id << ");";
    __SQLITE__INTERNAL__::sqlite_execute_stmt(
        _db, insert_sensor_value_stmt.str());
    
    
    assert(OK());
}

unsigned int SqliteLogger::count() const noexcept {
    assert(OK());
    
    std::stringstream stmt;  
    QueryResult result;
    stmt << "SELECT count(" << SOURVAYS_TABLE_NAME << ")"
         << "FROM " << SOURVAYS_TABLE_NAME << ";";
    __SQLITE__INTERNAL__::sqlite_execute_stmt(_db,
                                              stmt.str(),
                                              &result);

    assert(OK());
    return std::stoi(*(result.rows.begin() -> begin()));
}

bool SqliteLogger::OK() const {
    return _db != NULL &&
        sqlite3_extended_errcode(_db) == SQLITE_OK;
}
