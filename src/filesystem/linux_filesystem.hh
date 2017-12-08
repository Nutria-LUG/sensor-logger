/*!
 * \brief     This file contains the implementation of the filesystem
 *            abstract class used to handle linux filesystem.
 * \file      filesystem/linux_filesystem.hh
 * \author    NutriaLUG
 * \copyright GNU Public License
 */

#include <string>
#include "filesystem.hh"

#ifndef LINUX_FILESYSTEM_INCLUDE_GUARD_HH
#define LINUX_FILESYSTEM_INCLUDE_GUARD_HH 1

/*!
 * \brief This class is used to handle the linux filesystem.
 */
class LinuxFilesystem : public Filesystem {
public:

    /*! \brief Default constructor. */
    LinuxFilesystem();

    /*! \brief Default destructor. */
    ~LinuxFilesystem();

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
