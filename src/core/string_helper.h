#ifndef STRING_HELPER_H
#define STRING_HELPER_H

#include "../global.h"

#include <string>
#include <vector>

TOOSKA_BEGIN_NAMESPACE(core)

class string_helper
{
public:
    string_helper();
    static bool is_integer(const std::string &s);
    static bool is_float(const std::string &s);

    static std::string trim_copy(std::string s);
    static std::string rtrim_copy(std::string s);
    static std::string ltrim_copy(std::string s);
    static void trim(std::string &s);
    static void rtrim(std::string &s);
    static void ltrim(std::string &s);

    static void tolower(std::string &str);
    static void toupper(std::string &str);
    static bool replace(std::string &str, const std::string &from, const std::string &to);
    static std::vector<std::string> split(std::string str, const char &sep);

    static bool starts_width(std::string &str, std::string &substr);
};

TOOSKA_END_NAMESPACE

#endif // STRING_HELPER_H
