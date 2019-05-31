#ifndef JSON_VALUE_P_H
#define JSON_VALUE_P_H


#include <map>
#include <string>
#include <vector>
#include "../global.h"
#include "json_value.h"

TOOSKA_BEGIN_NAMESPACE(json)

class json_value_data {
public:
    json_value::type_t type;

    union {
        int n;

        int8_t i8;
        int16_t i16;
        int32_t i32;
        int64_t i64;

        uint8_t u8;
        uint16_t u16;
        uint32_t u32;
        uint64_t u64;

        double d;
        float f;
        bool b;
    } _data;

    std::string _s;

    explicit json_value_data();

    explicit json_value_data(json_value::type_t type);

    explicit json_value_data(const bool &b);

    explicit json_value_data(const int &n);

    explicit json_value_data(const float &f);

    explicit json_value_data(const std::string &value);

    virtual ~json_value_data() = default;

    virtual void render(core::string_renderer &r);

};

class json_object_data : public json_value_data
{
public:
    std::map<std::string, json_value> values;

    json_object_data();
    virtual ~json_object_data() = default;

    void render(core::string_renderer &r) override;
};

class json_array_data : public json_value_data
{
public:
    std::vector<json_value> values;

    json_array_data();

    virtual ~json_array_data() = default;

    void render(core::string_renderer &r) override;

};

TOOSKA_END_NAMESPACE

#endif // JSON_VALUE_P_H
