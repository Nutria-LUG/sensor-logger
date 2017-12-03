#include <string>
#include <experimental/filesystem>
#include "./filesystem.hh"

namespace fs = std::experimental::filesystem;

bool filesystem::exists(const std::string& path) noexcept {
    return fs::exists(path);
}

void filesystem::create_directories(const std::string& path) noexcept {
    fs::create_directories(path);
}

std::string filesystem::get_path(const std::string& path) noexcept {
    auto path_obj = fs::path(path);
    return path_obj.parent_path();
}
