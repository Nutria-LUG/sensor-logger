/*!
 * \brief     This file contains the sourvay logger (a logger
 *            implementaion based on sqlite engine) and each component
 *            component used to realize it.
 * \file      sqlite_logger.hh
 * \author    NutriaLUG
 * \copyright GNU Public License
 */

#ifndef SQLITE_LOGGER_INCLUDE_GUARD_HH
#define SQLITE_LOGGER_INCLUDE_GUARD_HH 1

#include <vector>
#include <list>
#include <string>
#include <sqlite3.h>
#include "sourvay_logger.hh"
#include "../sourvay.hh"

/*!
 * This represent an exception thrown when an error occours during
 * an operation on the data base.
 * If an exception is thronw, the operation is not performed.
 */
struct DataBaseException {
    /*! Code of the exception. */
    int         code;

    /*! Readable message error */
    std::string message;

    /*! Default constructor. */
    DataBaseException();

    /*! 
     * \brief Constructor with two parameters.
     * \param exception_code    - Code of the exception.
     * \param exception_message - Message of the exception.
     */
    DataBaseException(const int          exception_code,
                      const std::string& exception_message);

    /*! 
     * Copy constructor.
     * \param db_exception - Exception object to copy.
     */
    DataBaseException(const DataBaseException& db_exception);

    /*! Default destructor. */
    ~DataBaseException();
};


/*!
 * This is the data struct used to represent a query result. It uses
 * collection because sqlite connection retrieve data as const char*
 */
struct QueryResult {
    /*! Type definition used to represent a single row. */
    typedef std::vector<std::string> row;
    
    /*!
     * Vector that contains the collection of columns. This must be
     * used to know the position of single cells inside the row.
     */
    std::vector<std::string> columns;

    /*! List of rows retrieved by the query. */
    std::list<row>           rows;
    
    /*! Default constructor. */
    QueryResult();
    
    /*! Destructor. */
    ~QueryResult();
};

    
/*!
 * Convert the query result to a list of elements.
 * \tpar MapFunc - Map function map. It is used to assign a cell
 *                 value to a field of the result type element. It
 *                 must take:
 *                  - string: that represent the column name.
 *                  - string: that represent the value
 *                  - Result: Object to assign the value.
 * \tpar Result  - Result type object.
 * \return A list of Result elements.
 *         NOTE: The list is returned as move copy.
 */
template<typename MapFunc, typename Result> 
inline std::list<Result> query_result_converter(
    const QueryResult& query_result, const MapFunc& map_func) {
    std::list<Result> to_ret;
    for(auto i : query_result.rows) {
        Result target;
        for(auto j : query_result.columns) {
            map_func(j, i, target);
        }
        to_ret(target);
    }        
    return std::move(to_ret);        
}

/*!
 * This is the logger object based on sqlite database. It use the
 * relative driver to open a connection and write value on it.
 * See project documentation to have the description of the database
 * and each table.
 * \def Sqlite data base is valid if and only if the funcitons
 *      sqlite3_extended_errcode return STATUS_OK.
 */
class SqliteLogger : public SourvayLogger  {
public:

    /*! Name of the column used as id in each table. */
    const std::string ID_COLUMN_NAME = "id";

    /*! Name of the sourvays table. */
    const std::string SOURVAYS_TABLE_NAME = "sourvays";

    /*! Name of the timestamp sourvay's column. */
    const std::string SOURVAYS_TABLE_TIMESTAMP_COLUMN = "timestamp";

    /*!
     * This is the flag used to know if the sourvay to have been send
     * to the server or not.
     */
    const std::string SOURVAYS_TABLE_SEND_FLAG_COLUMN = "send_flag";

    /*! Name of the column used to store the value in sensor table. */
    const std::string SENSOR_TABLE_VALUE_COLUMN = "value";

    /*!
     * Name of the foreign key of the sensor table to have the sourvay
     * reference.
     */
    const std::string SENSOR_TABLE_SOURVAY_COLUMN = "sourvay";
    
    /*!
     * \brief Constructor with one parameter.
     * Initialize the sqlite3 data base with the file specified. If
     * file does not exists, this constructor create it.
     * IMPORTANT: If there is not the Sourvays table inside the
     *            data base, this method will create it.
     * This can throw DataBaseException.
     *
     * <h3> CONTRACT </h3>
     * \pre  File specified must be a valid path.
     * \post This data base is valid.
     */
    SqliteLogger(const std::string& db_file);

    /*!
     * Destroy the data base connection according to RRID pattern.
     */
    ~SqliteLogger();

    /*!
     * \inheritdoc
     * <h3> CONTRACT </h3>
     * \pre  As parent class and this data base must be valid.
     * \post As parent class and this data base is still valid.
     */
    void log(const Sourvay& sourvay) noexcept;

    /*!
     * \inheritdoc
     *
     * <h3>CONTRACT</h3>
     * \pre  As parent class and this data base must be valid.
     * \post As parent class and this data base still is valid.
     */
    unsigned int count() const noexcept;

private:
    /*!
     * \brief Assertion method. It check the status of the data
     *        base.
     * \return True if the _db pointer is not null and its status
     *         is SQLITE_OK: sqlite3_extended_errcode return
     *         SQLITE_OK.
     */
    bool OK() const;
        
    /*! Not implemented. */
    SqliteLogger();

    /*! Not implemented. */
    SqliteLogger(const SqliteLogger&);

    /*! Not implemented. */
    SqliteLogger(const SqliteLogger&&);

    /*! Pointer to the sqlite3 data base connector. */
    sqlite3 *_db;
};

#endif
