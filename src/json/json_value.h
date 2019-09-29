#ifndef JSON_VALUE_H
#define JSON_VALUE_H

#include "../global.h"
#include "../core/variant.h"
#include <type_traits>

#include <string>

TOOSKA_BEGIN_NAMESPACE(core)
class string_renderer;
TOOSKA_END_NAMESPACE

TOOSKA_BEGIN_NAMESPACE(serialization)
class token_serializer;
class token_serializer_writer;
TOOSKA_END_NAMESPACE

TOOSKA_BEGIN_NAMESPACE(json)
class array;
class object;

class value
{
    tooska::core::variant _data;

public:
//    std::string _s;
    enum class type_t {
        invalid,
        bool_t,
        int_t,
        float_t,
        string_t,
        object_t,
        array_t
    };
    value();
    value(const tooska::core::variant &value);
    virtual ~value();

    type_t type() const;

    tooska::core::variant data() const;
    int to_int() const;
    float to_float() const;
    bool to_bool() const;
    std::string to_string() const;
    object *to_object();
    array *to_array();

protected:
    type_t _type;

private:
    virtual void render(core::string_renderer &r);

    friend class object;
    friend class array;
    friend class document;
    friend class tooska::serialization::token_serializer;
    friend class tooska::serialization::token_serializer_writer;
};

template <class T,
         std::enable_if_t<std::is_integral<T>::value, int> = 0
         >
value *create(const T &t)
{
    return new value(static_cast<int>(t));
}

template <class T,
          std::enable_if_t<std::is_floating_point<T>::value, int> = 0
          >
value *create(const T &t)
{
    return new value(static_cast<float>(t));
}

template <class T, typename std::enable_if<std::is_base_of<std::string, T>::value>::type* = nullptr>
value *create(const T &t)
{
    return new value(static_cast<std::string>(t));
}

TOOSKA_END_NAMESPACE

#endif // JSON_VALUE_H
