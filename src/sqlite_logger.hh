/* Log sensor values.
 * Copyright (C) 2018 NutriaLUG
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*!
 * \file      src/sqlite_logger.hh
 * \brief     Object used to log the surveys.
 * \copyright GNU Public License.
 * \author    NutriaLUG
 *
 * This file contains the definition of the sensor logger, the object
 * used to perform surveys log in a sqlite3 data base.
 */


#ifndef SQLITE_LOGGER_INCLUDE_GUARD
#define SQLITE_LOGGER_INCLUDE_GUARD 1

#include <sqlite3.h>
#include <string>
#include <istream>

/*! This is the class used to perform the log of sensor sourveys. */
class SqliteLogger {
public:
    /*!
     * Constructor with one parameter. Initialize the logger with the
     * path of the sqlite3 database.
     * This open the connection and try to create surveys table if it
     * does not exists.
     * \param db_path - Path to the sqlite3 data base.
     */
    SqliteLogger(const std::string& db_path);
    /*! Destructor. Close the connectio to the data base. */
    ~SqliteLogger();

    /*!
     * \brief Log the survays.
     *
     * Perform the log operation, writing in to the data base the
     * survays represented by the range passed as iterators.
     * Range passed must contains the name of the sensor followed
     * by its value. For example: ["pm10", "1", "pm2.5", "2"].
     * If a wrong sequence is provided, this method throw a const char*
     * exception: "invalid stream".
     * \tparm ForwardIterator - Forward iterator representing used to
     *                          move in the stream sequence.
     *
     * \param begin - Start of the stream sequence to log.
     * \param end   - End of the stream sequence to log.
     */
    template <class ForwardIterator>
    void log(ForwardIterator begin, ForwardIterator end);    
private:
    /*! Private not implemented. */
    SqliteLogger();
    /*! Private not implemented. */
    SqliteLogger(const SqliteLogger&);
    /*! Private not implemented. */
    SqliteLogger(const SqliteLogger&&);

    /*!
     * \brief Execute a SQL statement.
     * Execute the SQL stmt passed as string on the sqlite3 database.
     * \param stmt - Statement to execute. It must be a valid SQL
     *               statement for Sqlite3 engine, otherwise undefined
     *               behavior.
     */
    void _execute(const std::string& stmt);
    
    /*! Pointer to the sqlite3 data base connector. */
    sqlite3           *_db;
    /*! Name of the survays table. */
    const std::string _table_name = "surveys";
    /*! Name of the id column. */
    const std::string _id_column_name = "id";
    /*! Name of the id column. */
    const std::string _sensor_column_name = "sensor";
    /*! Name of the id column. */
    const std::string _value_column_name = "value";
    /*! Name of the id column. */
    const std::string _timestamp_column_name = "timestamp";
    /*! Name of the id column. */
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
       << _sent_flag_column_name << ")VALUES";

    while(begin != end) {
        if(!first) {
            ss << ",";
        } else {
            first = false;
        }
        ss << "(NULL,\""
           << *begin << "\",";
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
