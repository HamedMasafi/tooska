#ifndef JSON_TOKEN_SERIALIZER_H
#define JSON_TOKEN_SERIALIZER_H

#include "serializer_base.h"
#include "../json/json_object.h"
#include "../json/json_value.h"

TOOSKA_BEGIN_NAMESPACE(serialization)

template<>
class serializer<tooska::json::json_object> : public serializer_base
{
    tooska::json::json_object *_obj;

public:
    serializer() : serializer_base(serializer_base::Serialize), _obj(nullptr){

    }
    serializer(json::json_object *obj)  : serializer_base(serializer_base::Serialize), _obj(obj) {

    }
    template<typename T>
    void set(const std::string &name, T &t)
    {
        if (mode == Deserialize) {
            if (_obj->has_key(name))
                tooska::core::converter::read(t, _obj->get(name)->to_string());
        } else if (mode == Serialize) {
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

        if (mode == Deserialize) {
            if (t)
                delete t;
            t = new T;
            auto s = dynamic_cast<tooska::serialization::serializable*>(t);
            auto obj = _obj->get(name)->to_object();
            serializer<tooska::json::json_object> w(obj);
            s->serialize(&w);
        } else if (mode == Serialize) {
            auto s = dynamic_cast<tooska::serialization::serializable*>(t);
            serializer<tooska::json::json_object> w;
            s->serialize(&w);
            _obj->insert(name, w._obj);
        }
    }
    tooska::json::json_object *obj() const
    {
        return _obj;
    }
};

typedef serializer<tooska::json::json_object> json_token_serializer;

TOOSKA_END_NAMESPACE

#endif // JSON_TOKEN_SERIALIZER_H
