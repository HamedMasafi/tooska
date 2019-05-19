#ifndef TOKEN_SERIALIZER_H
#define TOKEN_SERIALIZER_H

#include "../global.h"
#include "converter.h"
#include "serializable.h"
#include "../json/json_object.h"
#include "../json/json_value.h"

namespace std {
    inline string to_string(string __val)
    {
        return __val;
    }
}
TOOSKA_BEGIN_NAMESPACE(serialization)

class token_serializer
{
public:
    enum class mode_t {
        read,
        write
    } mode;
    json::json_object *_obj;
    token_serializer();
    token_serializer(json::json_object *obj);

    template<typename T>
    void set(const std::string &name, T& t);

};

template<typename T>
void operator &(token_serializer *t, serialize_rule<T> r)
{
    if (t->mode == token_serializer::mode_t::read)
        read(r.data, t->_obj->get(r.name)->to_string());
    else
        t->_obj->insert(r.name, new json::json_value(std::to_string(r.data)));
}

//class token_serializer_writer : public token_serializer
//{
//public:
//    token_serializer_writer()
//    {}

//    template<typename T>
//    void field(const std::string &name, T& t)
//    { }
//};

//template<typename T>
//void operator &(token_serializer_writer *t, serialize_rule<T> r)
//{
//    std::cout << "write<T> " << r.name << std::endl;
//}

//class token_serializer_reader : public token_serializer
//{
//public:
//    json::json_object *_obj;
//    token_serializer_reader(json::json_object *obj) : _obj(obj)
//    {}

//    template<typename T>
//    void field(const std::string &name, T& t)
//    { }
//};

//template<typename T>
//void operator &(token_serializer_reader *t, serialize_rule<T> r)
//{
//    read(r.data, t->_obj->get(r.name));
//    std::cout << "read<T> " << r.name <<"="<<t->_obj->get(r.name)<< std::endl;
//}

TOOSKA_END_NAMESPACE

#endif // TOKEN_SERIALIZER_H
