#include <string>
#include <experimental/filesystem>
#include "./filesystem.hh"

namespace fs = std::experimental::filesystem;

Filesystem::Filesystem() { }
Filesystem::~Filesystem() { }


#define LINUX_HOME_ENV "HOME"

LinuxFilesystem::LinuxFilesystem() { };
LinuxFilesystem::~LinuxFilesystem() { };

bool LinuxFilesystem::exists(const std::string& path) const {
    return fs::exists(path);
}

void LinuxFilesystem::create_directories(const std::string& path) {
    fs::create_directories(path);
}

std::string LinuxFilesystem::get_home_path() const {
    return getenv(LINUX_HOME_ENV);
}
