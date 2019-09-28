#ifndef SERIALIZER_BASE_H
#define SERIALIZER_BASE_H

#include <string>
#include "../global.h"
#include "../json/json_object.h"
#include "../json/json_value.h"
#include "serializable.h"
#include "../core/converter.h"
#include "serializable.h"

namespace std {
inline string to_string(string __val)
{
    return __val;
}
}

#define FOR_EACH_TYPES(x) \
    x(char) \
    x(char16_t) \
    x(char32_t) \
    x(short) \
    x(int) \
    x(long) \
    x(long long) \
    x(unsigned int) \
    x(unsigned long) \
    x(unsigned long long) \
    x(std::string) \
    x(long double) \
    x(double)

TOOSKA_BEGIN_NAMESPACE(serialization)

class serializer_base
{
public:
    enum mode_t {
        Unset,
        Deserialize,
        Serialize
    } mode;

    serializer_base(mode_t mode) : mode(mode)
    {}

//#define x(type) virtual void set(const std::string &name, type &value) = 0;
//    FOR_EACH_TYPES(x)
//#undef x

    virtual serializable *create_object() const;
    virtual serializer_base *create_serializer() const;

    virtual bool has_key(const std::string &key) const = 0;
    virtual void set_value(const std::string &name, const std::string &value) = 0;
    virtual void get_value(const std::string &name, std::string &value) = 0;

    template<typename T>
    void set(const std::string &name, T &t)
    {
        if (mode == Deserialize) {
            if (has_key(name)) {
                std::string v;
                get_value(name, v);
                tooska::core::converter::read(t, v);
            }
        } else if (mode == Serialize) {
            set_value(name, std::to_string(t));
//            auto v = new json::value(t);
//            v->_s = std::to_string(t);
//            _obj->insert(name, v);
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

//        if (mode == Deserialize) {
//            if (object)
//                delete object;
//            object = new T;
//            auto s = dynamic_cast<tooska::serialization::serializable*>(object);
//            auto obj = _obj->get(name)->to_object();
//            serializer_base w(obj);
//            /*s->*/w.serialize(object);
//        } else if (mode == Serialize) {
//            auto s = dynamic_cast<tooska::serialization::serializable*>(object);
//            serializer_base w;
//            /*s->*/w.serialize(object);
//            _obj->insert(name, w._obj);
//        }
    }

    virtual std::string serialize(serializable *object) const {

    }



    //    virtual std::string serialize_array(const std::vector<T *> &object) const = 0;
    //    virtual T *deserialize(const std::string &data) const = 0;
    //    virtual std::vector<T *> deserialize_array(const std::string &data) const = 0;
};

class json_serializer : public serializer_base
{
    tooska::json::object *_object;
public:

    json_serializer() : serializer_base(Serialize), _object(new json::object) {

    }

    json_serializer(json::object *obj) : serializer_base(Deserialize), _object(obj) {

    }

    bool has_key(const std::string &key) const {
        return _object->has_key(key);
    }
    void set_value(const std::string &name, const std::string &value)
    {
        _object->insert(name, new json::value(value));
    }
    void get_value(const std::string &name, std::string &value)
    {
        value = _object->get(name)->to_string();
    }

    template<class S>
    void deserialize(tooska::json::object *json, S *obj) const
    {

    }
};

//template<class C, class N>
//class serializer : public serializer_base
//{
//public:
//    serializer() : serializer_base(Unset)
//    {}
//};

//template<class T>
//class abstract_serializer
//{
//public:
//    virtual std::string serialize(T *object) const = 0;
//    virtual std::string serialize_array(const std::vector<T *> &object) const = 0;
//    virtual T *deserialize(const std::string &data) const = 0;
//    virtual std::vector<T *> deserialize_array(const std::string &data) const = 0;
//};

//template<class T>
//class json_object_serializer : public abstract_serializer<T>
//{
//    json::object *object;

//public:
//    std::string serialize(T *object) const override
//    {
//        object->serialize(this);
//    }
//    std::string serialize_array(const std::vector<T*> &object) const override
//    {

//    }
//    T *deserialize(const std::string &data) const override
//    {
////        if (object)
//            //                delete object;
//            //            object = new T;
//            //            auto s = dynamic_cast<tooska::serialization::serializable*>(object);
//            //            auto obj = _obj->get(name)->to_object();
//            //            serializer<tooska::json::object> w(obj);
//            //            s->serialize(&w);
//            //        } else if (mode == Serialize) {
//            //            auto s = dynamic_cast<tooska::serialization::serializable*>(object);
//            //            serializer<tooska::json::object> w;
//            //            s->serialize(&w);
//            //            _obj->insert(name, w._obj);
//            //        }
////        auto t = new T;
////        t->serialize(this);
////        return t;
//    }
//    std::vector<T*> deserialize_array(const std::string &data) const override
//    {

//    }


//};

TOOSKA_END_NAMESPACE

#endif // SERIALIZER_BASE_H
