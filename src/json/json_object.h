#ifndef JSON_OBJECT_H
#define JSON_OBJECT_H

#include "../global.h"
#include "json_value.h"
#include <initializer_list>
#include <string>
#include <map>

TOOSKA_BEGIN_NAMESPACE(core)
class string_renderer;
TOOSKA_END_NAMESPACE

TOOSKA_BEGIN_NAMESPACE(json)
class json_object_data;
class json_object : public json_value
{
    json_object(json_object_data *data);

public:
    json_object();
    json_object(const json_object &other);
    json_object(json_object &&other);
    json_object(std::initializer_list<std::pair<std::string, json_value> > args);

    json_object &operator =(const json_object &other);

    virtual ~json_object();

    void insert(const std::string &name, const json_value &value);
    void insert(const std::string &name, json_value &&value);
    bool has_key(const std::string &key) const;

    json_value get(const std::string &name);
    json_value operator[](const std::string &name);

private:
    json_object_data *_object_data;
    void render(core::string_renderer &r) const;

    friend class json_value;
};

TOOSKA_END_NAMESPACE

#endif // JSON_OBJECT_H
