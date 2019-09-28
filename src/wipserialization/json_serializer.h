#ifndef JSON_SERIALIZER_H
#define JSON_SERIALIZER_H

#include "../global.h"
#include "serializer_base.h"

TOOSKA_BEGIN_NAMESPACE(serialization)

class json_serializer : public serializer_base
{
public:
    json_serializer();

public:
    bool has_key(const std::string &key) const;
    void set_value(const std::string &name, const std::string &value);
    void get_value(const std::string &name, std::string &value);
    serializer_base *create_serializer() const;
};

TOOSKA_END_NAMESPACE

#endif // JSON_SERIALIZER_H
