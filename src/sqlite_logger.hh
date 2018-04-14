
#ifndef SQLITE_LOGGER_INCLUDE_GUARD
#define SQLITE_LOGGER_INCLUDE_GUARD 1

#include <sqlite3.h>
#include <string>
#include <istream>

class SqliteLogger {
public:
    SqliteLogger(const std::string& db_path);
    ~SqliteLogger();

    template <class ForwardIterator>
    void log(ForwardIterator begin, ForwardIterator end);    
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

#include <ctime>
#include <sstream>
template<class ForwardIterator>
void SqliteLogger::log(ForwardIterator begin, ForwardIterator end) {
    std::time_t t;
    std::time(&t);
    bool first = true;
    std::string str;
    std::stringstream ss;
    ss << "INSERT INTO "
       << _table_name << "("
       << _id_column_name << ","
       << _sensor_column_name << ","
       << _value_column_name << ","
       << _timestamp_column_name << ","
       << _sent_flag_column_name << ")";

    while(begin != end) {
        if(!first) {
            ss << ",";
        } else {
            first = false;
        }
        ss << " VALUES(NULL, "
           << *begin << ",";
        if(begin == end) {
            throw "invalid stream";
        }
        ++begin;
        ss << *begin << "," << t << ",0)";

        // This is need for pointer usage.
        if(begin != end) {
            ++begin;
        }
        
    }
    ss << ";";
    if(!first) {
        _execute(ss.str());
    }
}

#endif
