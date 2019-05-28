#ifndef TOKEN_SERIALIZER_H
#define TOKEN_SERIALIZER_H

#include "../global.h"
#include "converter.h"
#include "serializable.h"
#include "../json/json_object.h"
#include "../json/json_value.h"
#include "../json/json_document.h"

namespace std {
    inline string to_string(string __val)
    {
        return __val;
    }
}

template<typename>
struct __is_serializable_object_helper
        : public std::false_type { };

template<>
struct __is_serializable_object_helper<tooska::serialization::serializable*>
        : public std::true_type { };

template<typename _Tp>
struct is_serializable_object
        : public __is_serializable_object_helper<typename std::remove_cv<_Tp>::type>::type
{ };

TOOSKA_BEGIN_NAMESPACE(serialization)

class token_serializer
{
    protected:
public:
    enum {
        deserialize,
        serialize
    } mode;
    json::json_object *_obj;
    token_serializer();
    token_serializer(json::json_object *obj);

    template<typename T>
    void set(const std::string &name, T &t)
    {
        if (mode == deserialize) {
            if (_obj->has_key(name))
                read(t, _obj->get(name)->to_string());
        } else {
            json::json_value *v = new json::json_value(t);
            v->_s = std::to_string(t);
            _obj->insert(name, v);
        }
    }

    template<typename T>
    void set(const std::string &name, T* &t)
    {
        if (!std::is_base_of<serializable, T>::value) {
            std::cerr << "The child for key " << name
                      << " is not derived from tooska::serialization::serializable"
                      << std::endl;
            return;
        }

        if (mode == deserialize) {
            if (t)
                delete t;
            t = new T;
            serializable *s = dynamic_cast<serializable*>(t);
            auto obj = _obj->get(name)->to_object();
            token_serializer w(obj);
            s->serialize(&w);
        } else {
            serializable *s = dynamic_cast<serializable*>(t);
            token_serializer w;
            s->serialize(&w);
            _obj->insert(name, w._obj);
        }
    }
};

class token_serializer_reader : public token_serializer
{
public:
    token_serializer_reader(json::json_object *obj);

    template<typename T>
    void set(const std::string &name, T &t)
    {
        read(t, _obj->get(name)->to_string());
    }
    template<typename T>
    void set(const std::string &name, T* &t)
    {
        if (!std::is_base_of<serializable, T>::value) {
            std::cerr << "The child for key " << name
                      << " is not derived from tooska::serialization::serializable"
                      << std::endl;
            return;
        }

        if (t)
            delete t;
        t = new T;
        serializable *s = dynamic_cast<serializable*>(t);
        auto obj = _obj->get(name)->to_object();
        token_serializer w(obj);
        s->serialize(&w);
    }
};

class token_serializer_writer : public token_serializer
{
public:
    token_serializer_writer();

    template<typename T>
    void set(const std::string &name, T &t)
    {
        json::json_value *v = new json::json_value(t);
        v->_s = std::to_string(t);
        _obj->insert(name, v);
    }

    template<typename T>
    void set(const std::string &name, T* &t)
    {
        if (!std::is_base_of<serializable, T>::value) {
            std::cerr << "The child for key " << name
                      << " is not derived from tooska::serialization::serializable"
                      << std::endl;
            return;
        }

        serializable *s = dynamic_cast<serializable*>(t);
        token_serializer w;
        s->serialize(&w);
        _obj->insert(name, w._obj);
    }
};

TOOSKA_END_NAMESPACE

#endif // TOKEN_SERIALIZER_H
