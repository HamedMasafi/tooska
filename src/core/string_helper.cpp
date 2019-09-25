#include "../core/string_helper.h"

#include <sstream>
#include <iostream>
#include <algorithm>
#include <wctype.h>

TOOSKA_BEGIN_NAMESPACE(core)

using namespace std;

string_helper::string_helper()
{

}

bool string_helper::is_integer(const string &s)
{
    return all_of(s.begin(), s.end(), [](int n){
        return isdigit(n);
    });
}

bool string_helper::is_float(const string &s)
{
    int fc = 0;
    return all_of(s.begin(), s.end(), [&fc](int n){
        if (n == '.' && !fc) {
            fc = 1;
            return 1;
        }
        return isdigit(n);
    });
}

void string_helper::ltrim(string &s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](int ch) {
        return !isspace(ch);
    }));
}

void string_helper::toupper(string &str)
{
    transform(
      str.begin(), str.end(),
      str.begin(),
      towupper);
}
void string_helper::tolower(string &str)
{
    transform(
      str.begin(), str.end(),
      str.begin(),
      towlower);
}

// trim from end (in place)
void string_helper::rtrim(string &s) {
    s.erase(find_if(s.rbegin(), s.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
void string_helper::trim(string &s) {
    ltrim(s);
    rtrim(s);
}

// trim from start (copying)
string string_helper::ltrim_copy(string s) {
    ltrim(s);
    return s;
}

// trim from end (copying)
string string_helper::rtrim_copy(string s) {
    rtrim(s);
    return s;
}

// trim from both ends (copying)
string string_helper::trim_copy(string s) {
    trim(s);
    return s;
}


bool string_helper::replace(string& str, const string& from, const string& to) {
//    size_t start_pos = str.find(from);
//    if(start_pos == string::npos)
//        return false;
//    str.replace(start_pos, from.length(), to);
//    return true;
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return true;
}

vector<string> string_helper::split(string str, const char &sep)
{
    string temp;
    vector<string> parts;
    stringstream wss(str);
    while(getline(wss, temp, sep))
        parts.push_back(temp);
    return parts;
}

bool string_helper::starts_width(string &str, string &substr)
{
    return str.rfind(substr) == 0;
}

TOOSKA_END_NAMESPACE
