#ifndef JSON_TOKEN_SERIALIZER_H
#define JSON_TOKEN_SERIALIZER_H

#include "../json/json_object.h"
#include "../json/json_value.h"
#include "serializer_base.h"

namespace std
{
inline string to_string(string __val)
{
    return __val;
}
} // namespace std

TOOSKA_BEGIN_NAMESPACE(serialization)

template <class C> class serializer<C, tooska::json::object> : public serializer_base
{
    tooska::json::object *_obj;

public:
    serializer() : serializer_base(serializer_base::Serialize), _obj(nullptr)
    {
    }
    serializer(json::object *obj)
        : serializer_base(serializer_base::Deserialize), _obj(obj)
    {
    }
#define x(type)                                                     \
    void set(const std::string &name, type &value) override   \
    {                                                               \
        if (mode == Deserialize) {                                  \
            if (_obj->has_key(name))                                \
                value = tooska::core::converter::from_string<type>( \
                    _obj->get(name)->to_string());                  \
        } else if (mode == Serialize) {                             \
            auto v = json::create<type>(value);                     \
            v->_s  = std::to_string(value);                         \
            _obj->insert(name, v);                                  \
        }                                                           \
    }

    FOR_EACH_TYPES(x)
#undef x

    /*
    template<typename T>
    void set(const std::string &name, T &t)
    {
        if (mode == Deserialize) {
            if (_obj->has_key(name))
                tooska::core::converter::read(t, _obj->get(name)->to_string());
        } else if (mode == Serialize) {
            auto v = new json::value(t);
            v->_s = std::to_string(t);
            _obj->insert(name, v);
        }
    }
*/
    void set(const std::string &name, serializable *object) override
//    template<typename T>
//    void set(const std::string &name, T* &t)
    {
//        if (!std::is_base_of<serializable, T>::value) {
//            std::cerr << "The child for key " << name
//                      << " is not derived from
//    tooska::serialization::serializable"
//                      << std::endl;
//            return;
//        }

//        if (mode == Deserialize) {
//            if (object)
//                delete object;
//            object = new T;
//            auto s = dynamic_cast<tooska::serialization::serializable*>(object);
//            auto obj = _obj->get(name)->to_object();
//            serializer<tooska::json::object> w(obj);
//            s->serialize(&w);
//        } else if (mode == Serialize) {
//            auto s = dynamic_cast<tooska::serialization::serializable*>(object);
//            serializer<tooska::json::object> w;
//            s->serialize(&w);
//            _obj->insert(name, w._obj);
//        }
    }

    tooska::json::object *obj() const
    {
        return _obj;
    }
};

template<class T>
using json_token_serializer = serializer<T, tooska::json::object>;

TOOSKA_END_NAMESPACE

#endif // JSON_TOKEN_SERIALIZER_H
