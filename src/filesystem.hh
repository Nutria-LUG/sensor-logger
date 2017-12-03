#include <string>

#ifndef FILESYSTEM_INCLUDE_GUARD_HH
#define FILESYSTEM_INCLUDE_GUARD_HH 1

namespace filesystem {
    bool exists(const std::string& path) noexcept;

    void create_directories(const std::string& file_path) noexcept;

    std::string get_path(const std::string& file_path) noexcept;
}

#endif
