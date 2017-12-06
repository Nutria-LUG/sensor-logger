/*!
 * \brief     This file contains the definition of the abstract logger
 *            class used to represent a generic sourvay log method.
 * \file      logger.hh
 * \author    NutriaLUG
 * \copyright GNU Public License
 */

#include "sourvay.hh"

#ifndef SOURVAY_LOGGER_INCLUDE_GAURD_HH
#define SOURVAY_LOGGER_INCLUDE_GAURD_HH 1

class SourvayLogger {
public:
    SourvayLogger();
    virtual ~SourvayLogger();

    virtual void log(const Sourvay& souvary) = 0;
    
private:
    /*! Private not implemented. */
    SourvayLogger(const SourvayLogger&);
    /*! Private not implemented. */
    SourvayLogger(const SourvayLogger&&);
};

#endif
