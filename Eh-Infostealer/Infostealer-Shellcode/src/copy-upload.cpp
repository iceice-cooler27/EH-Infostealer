#include "copy-upload.h"

namespace fs = std::filesystem;
namespace up {
    void fldir::add_files(fs::path addpath) {
        fVec.push_back(addpath);
    }
    void fldir::find_files() {
        fs::path dPath = dirPath;
        if (!fs::exists(dPath) || !fs::is_directory(dPath)) {
            std::cerr << "Invalid directory: " << dPath << "\n";
            return;
        }
        try {
            for (const auto& entry : std::filesystem::directory_iterator(dPath)) {
                std::cout << entry.path() << std::endl;
                find_file_path(entry.path());
            }
        } catch (const fs::filesystem_error& e) {
            std::cerr << "Filesystem error: " << e.what() << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "General error: " << e.what() << std::endl;
        }
    }
    void fldir::find_file_path(const fs::path& fPath) {
        std::ifstream file(fPath, std::ios::in | std::ios::binary);
        if (file.is_open()) {
            file.close();
            if (!rExt(fPath)){
                add_files(fPath);
            }
            std::cout << "File: " << fPath << "added" << std::endl;
        } else {
            std::cerr << "Could not open file: " << fPath << "\n";
        }
    }

    bool fldir::rExt(const fs::path& path) {
        auto ext = path.extension().string();
        for (const auto& validExt : EXT) {
            if (ext == validExt) {
                return true;
            }
        }
        return false;
    }
}