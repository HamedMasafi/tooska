#ifndef JSON_VALUE_P_H
#define JSON_VALUE_P_H

#include "../global.h"
#include <string>
#include "json_value.h"
#include <map>
#include <vector>

TOOSKA_BEGIN_NAMESPACE(json)

class json_value_data {
public:
    union {
        int n;
        float f;
        bool b;
    } _data;

    std::string _s;

    explicit json_value_data()
    {}

    explicit json_value_data(const bool &b)
    {
        _data.b = b;
    }

    explicit json_value_data(const int &n)
    {
        _data.n = n;
    }

    explicit json_value_data(const float &f)
    {
        _data.f = f;
    }

    explicit json_value_data(const std::string &value) : _s(value)
    {}
};

class json_object_data : public json_value_data
{
public:
    std::map<std::string, json_value> values;
};

class json_array_data : public json_value_data
{
public:
    std::vector<json_value> values;
};

TOOSKA_END_NAMESPACE

#endif // JSON_VALUE_P_H
