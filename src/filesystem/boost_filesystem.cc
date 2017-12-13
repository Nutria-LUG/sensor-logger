#include <string>
#include <boost/filesystem.hpp>
#include "boost_filesystem.hh"

namespace fs = boost::filesystem;

#define HOME_ENV "HOME"

BoostFilesystem::BoostFilesystem() { };
BoostFilesystem::~BoostFilesystem() { };


std::string BoostFilesystem::get_home_path() const noexcept{
    return getenv(HOME_ENV);
}

bool BoostFilesystem::exists(const std::string& path) const noexcept {
    return fs::exists(path);
}

bool BoostFilesystem::is_valid_path(
    const std::string& path) const noexcept {
    fs::path p(path);
    return p.is_relative() || p.is_absolute();
}

bool BoostFilesystem::has_write_permission(
    const std::string& path) const noexcept {
    fs::file_status status = fs::status(path);
    fs::perms p = status.permissions();
    return (p & fs::perms::owner_write) != fs::perms::no_perms ||
        (p & fs::perms::group_write) != fs::perms::no_perms ||
        (p & fs::perms::others_write) != fs::perms::no_perms;
}

bool BoostFilesystem::has_read_permission(
    const std::string& path) const noexcept {
    fs::file_status status = fs::status(path);
    fs::perms p = status.permissions();
    return (p & fs::perms::owner_read) != fs::perms::no_perms ||
        (p & fs::perms::group_read) != fs::perms::no_perms ||
        (p & fs::perms::others_read) != fs::perms::no_perms;
}


void BoostFilesystem::create_directories(const std::string& path) {
    fs::create_directories(path);
}
