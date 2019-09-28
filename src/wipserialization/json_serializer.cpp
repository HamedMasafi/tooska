#include "json_serializer.h"
#include <iostream>

TOOSKA_BEGIN_NAMESPACE(serialization)

json_serializer::json_serializer()
{

}

bool json_serializer::has_key(const std::string &key) const
{
    return true;
}

void json_serializer::set_value(const std::string &name, const std::string &value)
{
    std::cout <<"set_value " << name << " = " << value << std::endl;
}

void json_serializer::get_value(const std::string &name, std::string &value)
{
    std::cout << "get_value " << name << " = " << value << std::endl;
}

serializer_base *json_serializer::create_serializer() const
{
    auto t = new json_serializer;
    t->mode = mode;
    return t;
}

TOOSKA_END_NAMESPACE
