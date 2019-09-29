#ifndef SERIALIZER_BASE_H
#define SERIALIZER_BASE_H

#include "../global.h"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "../core/variant.h"
#include "serializable.h"

TOOSKA_BEGIN_NAMESPACE(serialization)

class serializable;
class serializer_base
{
public:
    enum mode_t {
        Unset,
        Deserialize,
        Serialize
    } mode;

    void serialize(serializable *obj) {
        before_serialize(obj);
        obj->__tokenize(this);
    }

    template<class T>
    T *deserialize() {
        auto t = new T;
        t->__tokenize(this);
        return t;
    }

    serializer_base(mode_t m);
    template<typename T>
    void set(const std::string &name, T &t)
    {
        if (mode == Deserialize) {
            if (has_key(name)) {
                tooska::core::variant var;
                deserialize_value(name, var);
                t = var.value<T>();
            }
        } else if (mode == Serialize) {
            tooska::core::variant var(t);
            serialize_value(name, var);
        }
    }
    template<typename T>
    void set(const std::string &name, std::vector<T> &vec)
    {
        if (mode == Deserialize) {
            if (!has_key(name))
                return;

            tooska::core::variant_vector v;
            deserialize_vector(name, v);

            vec.reserve(v.size());
            std::for_each(v.begin(), v.end(), [&vec](tooska::core::variant t) {
                vec.push_back(t.value<T>());
            });
        } else if (mode == Serialize) {
            auto v = tooska::core::variant_vector::from_vector(vec);
            serialize_vector(name, v);
        }
    }
    template<typename T>
    void set(const std::string &name, T* &object)
    {
        if (!std::is_base_of<serializable, T>::value) {
            std::cerr << "The child for key " << name
                      << " is not derived from tooska::serialization::serializable"
                      << std::endl;
            return;
        }

        if (mode == Serialize) {
            if (!object) {
                serialize_value(name, tooska::core::variant());
                return;
            }
            serialize_object(name, object);
        } else {
            if (!object)
                object = new T;
            deserialize_object(name, object);
        }
    }

    virtual void before_serialize(serializable *object)
    {}
    virtual serializer_base *create_serializer(serializable *child) const = 0;
    virtual bool has_key(const std::string &key) const = 0;
    virtual void serialize_value(const std::string &name, const tooska::core::variant &value) = 0;
    virtual void deserialize_value(const std::string &name, tooska::core::variant &value) = 0;

    virtual void serialize_vector(const std::string &name, const tooska::core::variant_vector &vec) = 0;
    virtual void deserialize_vector(const std::string &name, tooska::core::variant_vector &vec) = 0;

    virtual void serialize_object(const std::string &name, serializable *object) = 0;
    virtual void deserialize_object(const std::string &name, serializable *object) = 0;
};

TOOSKA_END_NAMESPACE

#endif // SERIALIZER_BASE_H
