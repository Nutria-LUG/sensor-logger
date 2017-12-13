#include <string>
#include <map>
#include <iostream>

#include "../../src/filesystem/filesystem.hh"

#ifndef TEST_FILESYSTEM_INCLUDE_GUARD_HH
#define TEST_FILESYSTEM_INCLUDE_GUARD_HH 1

class TestFilesystem : public Filesystem {
public:
    TestFilesystem(const std::string& home_dir):
        Filesystem(),
        _path_existance(),
        _path_validity(),
        _write_permissions(),
        _read_permissions(),
        _home_dir(home_dir) {
    }
    TestFilesystem() : TestFilesystem("/") { }
    ~TestFilesystem() { }

    virtual std::string get_home_path() const noexcept {
        return _home_dir;
    }

    virtual bool
    exists(const std::string& path) const noexcept {
        auto elem = _path_existance.find(path);
        return elem == _path_existance.cend() || elem -> second;
    };

    virtual bool
    is_valid_path(const std::string& path) const noexcept {
        auto elem = _path_validity.find(path);
        return elem== _path_validity.cend() || elem -> second;
    }

    virtual bool
    has_write_permission(const std::string& path) const noexcept {
        auto elem = _write_permissions.find(path);
        return elem == _write_permissions.cend() || elem -> second;
    }

    virtual bool
    has_read_permission(const std::string& path) const noexcept {
        auto elem = _write_permissions.find(path);
        return elem == _read_permissions.cend() || elem -> second;
    };

    virtual void
    create_directories(const std::string& path) {
        auto elem = _path_existance.find(path);
        if(elem != _path_existance.cend()) {
            elem -> second = true;
        }
    };

    void set_existance(const std::string& path, bool value) {
        _set_value(_path_existance, path, value);
    }
    
    void set_validity(const std::string& path, bool value) {
        _set_value(_path_validity, path, value);
    }
    
    void set_write_permissions(const std::string& path, bool value) {
        _set_value(_write_permissions, path, value);
    }

    void set_read_permissions(const std::string& path, bool value) {
        _set_value(_read_permissions, path, value);
    }
    
private:
    void _set_value(std::map<std::string, bool>& map,
                    const std::string& path,
                    bool value) {
        map[path] = value;
    }
    
    std::map<std::string, bool> _path_existance;
    std::map<std::string, bool> _path_validity;
    std::map<std::string, bool> _write_permissions;
    std::map<std::string, bool> _read_permissions;
        
    std::string _home_dir;
};

class MockedFilesystem : public Filesystem  {
public:
    MockedFilesystem(Filesystem *fs) : Filesystem { };
    virtual std::string get_home_path() const noexcept {
        return _fs -> get_home_path();
    }

    virtual bool
    exists(const std::string& path) const noexcept {
        auto elem = _path_existance.find(path);
        return elem == _path_existance.cend() || elem -> second;
    };

    virtual bool
    is_valid_path(const std::string& path) const noexcept {
        auto elem = _path_validity.find(path);
        return elem== _path_validity.cend() || elem -> second;
    }

    virtual bool
    has_write_permission(const std::string& path) const noexcept {
        auto elem = _write_permissions.find(path);
        return elem == _write_permissions.cend() || elem -> second;
    }

    virtual bool
    has_read_permission(const std::string& path) const noexcept {
        auto elem = _write_permissions.find(path);
        return elem == _read_permissions.cend() || elem -> second;
    };

    virtual void
    create_directories(const std::string& path) {
        auto elem = _path_existance.find(path);
        if(elem != _path_existance.cend()) {
            elem -> second = true;
        }
    };
    
private:
    Filesystem *_fs;
};

#endif
