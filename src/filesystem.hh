#include <string>

#ifndef FILESYSTEM_INCLUDE_GUARD_HH
#define FILESYSTEM_INCLUDE_GUARD_HH 1


class Filesystem {
public:
    Filesystem();
    ~Filesystem();
    virtual std::string get_home_path() const = 0;
    virtual bool exists(const std::string& path) const = 0;
    virtual void create_directories(const std::string& path) = 0;
};


class LinuxFilesystem : public Filesystem {
public:
    LinuxFilesystem();
    ~LinuxFilesystem();
    
    std::string get_home_path() const;
    bool exists(const std::string& path) const;
    void create_directories(const std::string& path);     
};
#endif
