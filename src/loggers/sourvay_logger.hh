/*!
 * \brief     This file contains the definition of the abstract logger
 *            class used to represent a generic sourvay log method.
 * \file      logger.hh
 * \author    NutriaLUG
 * \copyright GNU Public License
 */

#include "../sourvay.hh"

#ifndef SOURVAY_LOGGER_INCLUDE_GAURD_HH
#define SOURVAY_LOGGER_INCLUDE_GAURD_HH 1

/*!
 * \brief Logger class used to log sourvays.
 * This is an abstraction on the log operation of the sourvays. This is
 * used for test purpose (avoiding using data base on the test suites).
 */
class SourvayLogger {
public:
    /*! \brief Default constructor. */
    SourvayLogger();

    /*! Default destrcutor. */
    virtual ~SourvayLogger();
    
    /*!
     * \brief Insert the sourvay passed as parameter in the log.
     *
     * Insert the sourvay passed as parameter in the log system
     * depends by the implementation.
     * \param sourvay - Sourvay to insert in the log system. It must
     *                  be valid.
     *
     * <h3> CONTRACT </h3>
     * \pre  Sourvay passed as parameter must be valid.
     * \post Count method return a number equals to previous count
     *       result + 1.
     */
    virtual void log(const Sourvay& souvary) noexcept = 0;

    /*!
     * Gets the number of entries inside the log system.
     * \return An unsigned int that represent the number of entries
     *         logged.
     *
     * <h3>CONTRACT</h3>
     * \pre  No preconditions.
     * \post No exceptions to have been thrown.
     */
    virtual unsigned int count() const noexcept = 0;
private:

    /*! Private not implemented. */
    SourvayLogger(const SourvayLogger&);

    /*! Private not implemented. */
    SourvayLogger(const SourvayLogger&&);

};

/*!
 * Log sourvays passed as range parameter through the logger spcified.
 * \tpar ForwardIteartor - Forward iterator used to specify the range
 *                         of the collection to log.
 * \param begin  - Iterator to the begin of the collection of the
 *                 sourvays to log.
 * \param end    - Iterator to the end of the collection of the
 *                 sourvays to log.
 * \param logger - Logger to use to log the sourvays specified by
 *                 iterator range.
 */
template<class ForwardIterator>
inline void log_sourvays(ForwardIterator begin,
                         ForwardIterator end,
                         SourvayLogger& logger) {
    while(begin != end) {
        logger.log(*begin);
        ++begin;
    }
}

#endif
