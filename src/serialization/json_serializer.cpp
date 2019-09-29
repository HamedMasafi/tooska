#include "json_serializer.h"
#include "../json/json_array.h"
#include <iostream>

TOOSKA_BEGIN_NAMESPACE(serialization)

json_serializer::json_serializer() : serializer_base(Serialize)
      , _object(new tooska::json::object)
{

}

json_serializer::json_serializer(tooska::json::object *obj) : serializer_base(Deserialize)
      , _object(obj)
{

}

bool json_serializer::has_key(const std::string &key) const
{
    return _object->has_key(key);
}

void json_serializer::serialize_value(const std::string &name, const tooska::core::variant &value)
{
    _object->insert(name, new tooska::json::value(value));
}

void json_serializer::deserialize_value(const std::string &name, tooska::core::variant &value)
{
    value = _object->get(name)->data();
}

serializer_base *json_serializer::create_serializer(serializable *child) const
{
    auto t = new json_serializer;
    t->mode = mode;
    return t;
}

tooska::json::object *json_serializer::object() const
{
    return _object;
}

void json_serializer::serialize_object(const std::string &name, serializable *object)
{
    json_serializer t;
    object->__tokenize(&t);
    _object->insert(name, t.object());
}

void json_serializer::deserialize_object(const std::string &name, serializable *object)
{
    if (!has_key(name)) {
        std::cout << name << " is not present in json!" << std::endl;
        return;
    }

    auto o = _object->get(name)->to_object();
    if (!o) {
        std::cout << name << " is not valid json object!" << std::endl;
        return;
    }
    json_serializer s(o);
    object->__tokenize(&s);
}

void json_serializer::serialize_vector(const std::string &name, const tooska::core::variant_vector &vec)
{
    auto arr = new tooska::json::array;
    std::for_each(vec.begin(), vec.end(), [&vec, arr](tooska::core::variant v){
        arr->add(new tooska::json::value(v));
    });
    _object->insert(name, arr);
}

void json_serializer::deserialize_vector(const std::string &name, tooska::core::variant_vector &vec)
{
    if (!has_key(name)) {
        std::cout << name << " is not present in json!" << std::endl;
        return;
    }

    auto a = _object->get(name)->to_array();
    if (!a) {
        std::cout << name << " is not valid json array!" << std::endl;
        return;
    }

    a->for_each([&vec](tooska::json::value *val){
        vec.push_back(val->data());
    });
}

TOOSKA_END_NAMESPACE

