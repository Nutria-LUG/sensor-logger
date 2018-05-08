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

#include <sqlite3.h>
#include <string>
#include <istream>

#ifndef SQLITE_LOGGER_INCLUDE_GUARD
#define SQLITE_LOGGER_INCLUDE_GUARD 1

/*!
 * This is the code used to identify a log operation, this means that
 * log to have been performed in SURVEYS_TABLE_NAME table.
 */
#define LOG_CODE "log:"

/*!
 * This macro is uused to identify an error log operation, this means
 * that log to have been performed in ERRORS_TABLE_NAME.
 */
#define ERROR_CODE "error:"

/*! Name of the survays table. */
#define SURVEYS_TABLE_NAME "surveys"

/*! Name of the errors table. */
#define ERRORS_TABLE_NAME "errors"

/*! Name of the id column. */
#define ID_COLUMN_NAME "id"

/*! Name of the id column. */
#define SENSOR_COLUMN_NAME "sensor"

/*! Name of the id column. */
#define VALUE_COLUMN_NAME "value"

/*! Name of the id column. */
#define TIMESTAMP_COLUMN_NAME "timestamp"

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
    sqlite3 *_db;
};

#include <ctime>
#include <sstream>

inline bool is_log_code(const std::string& str) {
    return str == LOG_CODE || str == ERROR_CODE;
}
    
template<class ForwardIterator>
void add_survey_values_to_cmd(ForwardIterator& itr,
                              std::ostream& sql_cmd,
                              const std::time_t& timestamp) {
    sql_cmd << "(NULL,\""
            << *itr << "\",";
    ++itr;
    sql_cmd << *itr << "," << timestamp << ")";
    ++itr;
}

template<class ForwardIterator>
void add_error_values_to_cmd(ForwardIterator& itr,
                             ForwardIterator end,
                             std::ostream& sql_cmd,
                             const std::time_t& timestamp) {
    sql_cmd << "(NULL,\"";
    while(itr != end && !is_log_code(*itr)) {
        sql_cmd << *itr << " ";
        ++itr;
    }
    sql_cmd << "\"," << timestamp << ")";
}

template<class ForwardIterator>
void SqliteLogger::log(ForwardIterator begin, ForwardIterator end) {
    std::time_t t;
    std::time(&t);
    bool has_survays = false;
    bool has_errors = false;
    std::string str;
    std::stringstream survays;
    std::stringstream errors;
    survays << "INSERT INTO "
            << SURVEYS_TABLE_NAME << "("
            << ID_COLUMN_NAME << ","
            << SENSOR_COLUMN_NAME << ","
            << VALUE_COLUMN_NAME << ","
            << TIMESTAMP_COLUMN_NAME << ")VALUES";

    errors << "INSERT INTO "
           << ERRORS_TABLE_NAME << "("
           << ID_COLUMN_NAME << ","
           << VALUE_COLUMN_NAME << ","
           << TIMESTAMP_COLUMN_NAME << ")VALUES";
    
    while(begin != end) {
        if (*begin == LOG_CODE) {
            if(has_survays) {
                survays << ",";
            }
            has_survays = true;
            ++begin;
            add_survey_values_to_cmd(
                begin,
                survays,
                t);
        } else if (*begin == ERROR_CODE) {
            if(has_errors) {
                errors << ",";
            }
            has_errors = true;
            ++begin;
            add_error_values_to_cmd(
                begin,
                end,
                errors,
                t);
        } else {
            throw "invalid stream";
        }        
    }
    survays << ";";
    errors << ";";
    if(has_survays) {
        _execute(survays.str());
    }
    if(has_errors) {
        _execute(errors.str());
    }
}
#endif
