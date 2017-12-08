/*!
 * \brief     This file contains the implementation of the filesystem
 *            abstract class using the new c++17 standard features.
 * \file      filesystem/cpp_std_filesystem.hh
 * \author    NutriaLUG
 * \copyright GNU Public License
 */

#include <string>
#include "filesystem.hh"

#ifndef CPP_STD_FILESYSTEM_INCLUDE_GUARD_HH
#define CPP_STD_FILESYSTEM_INCLUDE_GUARD_HH 1

/*!
 * \brief This class is used to handle the filesystem using the c++17
 *        standard features..
 */
class CppStdFilesystem : public Filesystem {
public:

    /*! \brief Default constructor. */
    CppStdFilesystem();

    /*! \brief Default destructor. */
    ~CppStdFilesystem();

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
