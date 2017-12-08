/*!
 * \brief     This file contains the abstract definition of the
 *            filesystem used to handle it in a confortable and
 *            portable way.
 * \file      filesystem/filesystem.hh
 * \author    NutriaLUG
 * \copyright GNU Public License
 */

#include <string>

#ifndef FILESYSTEM_INCLUDE_GUARD_HH
#define FILESYSTEM_INCLUDE_GUARD_HH 1

/*!
 * \brief This class is an abstraction of the current os's filesystem.
 *
 * This represent a filesystem and it is used to perform opertaion on
 * it in a more confortable (and portable) way.
 * c++ does not support filesystem opertion nativaly (filesystem module
 * of the c++17 std is in experimental status), so an abstraction is
 * usefull. There are different approach that you can use to make an
 * implementation such as boost library, c system library or
 * experimental c++17 features. With this abstraction you don't care
 * about it and program can be use the filesystem in a independent way.
 */
class Filesystem {
public:
    /*! \brief Default constructor. */
    Filesystem();

    /*! \brief Default destructor */
    ~Filesystem();

    /*!
     * \brief Gets the full path to the home folder.
     *
     * This method is used to retrieve the full path to the home
     * folder.
     * \return A string that represent the full path to the home
     *         folder.
     *
     * <h3>CONTRACT</h3>
     * \pre  No preconditions.
     * \post Returned path exists (use exists method).
     */
    virtual std::string get_home_path() const noexcept = 0;

    /*!
     * \brief Check if the path passed as parameter exists.
     *
     * \param path - Path to check. It must be a valid path (see
     *               is_valid_path method).
     * \return True if the path exists, false otherwise.
     *
     * <h3>CONTRACT</h3>
     * \pre  Path passed must be valid: see is_valid_path method.
     * \post No exception to have been thrown.
     */
    virtual bool exists(const std::string& path) const noexcept = 0;

    /*!
     * \brief Check if the path passed is valid.
     *
     * Path format supported are the same of the c++17 standards:
     * http://en.cppreference.com/w/cpp/experimental/fs/path.
     * This choice is taken to have compatibility with the standard of
     * the language and having the c++17 std implemetation.
     *
     * \param path - Path to check
     * \return True if the path passed as parameter is valid, false
     *         otherwise.
     *
     * <h3>CONTRACT</h3>
     * \pre  No preconditions.
     * \post No exception to have been thrown.
     */
    virtual bool
    is_valid_path(const std::string& path) const noexcept = 0;

    /*!
     * \brief Check if current user has the write permission on the
     *        path passed as parameter.
     * This method is used to check if the user has the write
     * permission on the path passed as parameter.
     * \param path - Path to check. This must be a valid path.
     * \return True if the user has the write permission on the path
     *         passed, false otherwise.
     *
     * <h3>CONTRACT</h3>
     * \pre  Path passed must be valid (see is_valid_path method)
     * \post No postconditions.
     */
    virtual bool
    has_write_permission(const std::string& path) const noexcept = 0;

    /*!
     * \brief Check if current user has the read permission on the path
     *        passed as parameter.
     * This method is used to check if the user has the read permission
     * on the path passed as parameter.
     * \param path - Path to check. This must be a valid path.
     * \return True if the user has the read permission on the path
     *         passed, false otherwise.
     *
     * <h3>CONTRACT</h3>
     * \pre  Path passed must be valid (see is_valid_path method).
     * \post No postconditions.
     */    
    virtual bool
    has_read_permission(const std::string& path) const noexcept = 0;
    
    /*!
     * \brief Create the directories giving a path.
     * This method create each directory of the path passed as
     * parameter. Existent directories are ignored.
     * User must have the write permission on each directory of
     * the path, otherwise undefined behavior.
     * \param path - Directories path to create.
     *
     * <h3>CONTRACT</h3>
     * \pre  Path passed must be valid and user must have the write
     *       permission on each directory of the path.
     * \post Path passed as parameter exists.
     */
    virtual void create_directories(const std::string& path) = 0;
};


#endif
