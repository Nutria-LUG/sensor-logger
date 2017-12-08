#include <string>
#include <experimental/filesystem>
#include "cpp_std_filesystem.hh"

namespace fs = std::experimental::filesystem;

#define HOME_ENV "HOME"

CppStdFilesystem::CppStdFilesystem() { };
CppStdFilesystem::~CppStdFilesystem() { };


std::string CppStdFilesystem::get_home_path() const noexcept{
    return getenv(HOME_ENV);
}

bool CppStdFilesystem::exists(const std::string& path) const noexcept {
    return fs::exists(path);
}

bool CppStdFilesystem::is_valid_path(
    const std::string& path) const noexcept {
    fs::path p(path);
    return p.is_relative() || p.is_absolute();
}

bool CppStdFilesystem::has_write_permission(
    const std::string& path) const noexcept {
    fs::file_status status = fs::status(path);
    fs::perms p = status.permissions();
    return (p & fs::perms::owner_write) != fs::perms::none ||
        (p & fs::perms::group_write) != fs::perms::none ||
        (p & fs::perms::others_write) != fs::perms::none;
}

bool CppStdFilesystem::has_read_permission(
    const std::string& path) const noexcept {
    fs::file_status status = fs::status(path);
    fs::perms p = status.permissions();
    return (p & fs::perms::owner_read) != fs::perms::none ||
        (p & fs::perms::group_read) != fs::perms::none ||
        (p & fs::perms::others_read) != fs::perms::none;
}


void CppStdFilesystem::create_directories(const std::string& path) {
    fs::create_directories(path);
}
