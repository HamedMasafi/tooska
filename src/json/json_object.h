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
class object : public value
{
    std::map<std::string, value*> _values;

public:
    object();
    object(std::initializer_list<std::pair<std::string, value> > args);

    virtual ~object();
    void insert(const std::string &name, value *value);
    bool has_key(const std::string &name);
    value *get(const std::string &name);

    value *operator[](const std::string &name);

private:
    void render(core::string_renderer &r);

    friend class json_document;
};

TOOSKA_END_NAMESPACE

#endif // JSON_OBJECT_H
