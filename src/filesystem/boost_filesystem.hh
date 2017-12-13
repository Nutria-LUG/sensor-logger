/*!
 * \brief     This file contains the implementation of the filesystem
 *            abstract class using the new boost library.
 * \file      filesystem/boost_filesystem.hh
 * \author    NutriaLUG
 * \copyright GNU Public License
 */

#include <string>
#include "filesystem.hh"

#ifndef BOOST_FILESYSTEM_INCLUDE_GUARD_HH
#define BOSST_FILESYSTEM_INCLUDE_GUARD_HH 1

/*!
 * \brief This class is used to handle the filesystem using the c++17
 *        standard features..
 */
class BoostFilesystem : public Filesystem {
public:

    /*! \brief Default constructor. */
    BoostFilesystem();

    /*! \brief Default destructor. */
    ~BoostFilesystem();

    /*! \inheritdoc */
    std::string get_home_path() const noexcept;

    /*! \inheritdoc */
    bool exists(const std::string& path) const noexcept;

    /*! \inheritdoc */
    bool is_valid_path(const std::string& path) const noexcept;

    /*! \inheritdoc */
    bool has_write_permission(const std::string& path) const noexcept;

    /*! \inheritdoc */
    bool has_read_permission(const std::string& path) const noexcept;

    /*! \inheritdoc */
    void create_directories(const std::string& path);

};
#endif
