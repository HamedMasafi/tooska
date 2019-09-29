#ifndef VARIANT_H
#define VARIANT_H

#include <type_traits>
#include <string>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <functional>

#define FOR_EACH_TYPES(x) \
    x(bool, bool) \
    x(int, int) \
    x(unsigned int, unsigned_int) \
    x(unsigned long, unsigned_long) \
    x(long long, long_long) \
    x(unsigned long long, unsigned_long_long) \
    x(long double, long_double) \
    x(double, double) \
    x(float, float) \
    x(long, long)

//    x(char, char_t) \
//    x(char16_t, char16_t_t) \
//    x(char32_t, char32_t_t)
#define FOR_EACH_CTYPES(x) \
    x(std::string, string) \

#include "../global.h"
#include <string>

TOOSKA_BEGIN_NAMESPACE(core)

class variant
{
    union data_t {
#define x(type, name) type name##_t;
        FOR_EACH_TYPES(x)
#undef x
    } _data;
    std::string s;
public:
    /*
     * int
     * unsigned
     * unsigned long
     * long long
     * unsigned long long
     * float
     * double
     * long double
     */
    enum type_t {
        invalid,
#define x(type, name) name##_t,
        FOR_EACH_TYPES(x)
        FOR_EACH_CTYPES(x)
#undef x
    } _type;

    variant();
#define x(type, name) variant(const type &value);
    FOR_EACH_TYPES(x)
#undef x

    variant(const char *data);
    variant(const std::string &value);
//    variant(const variant &other);
//    variant(variant &&other);

//    variant operator =(const variant &other) {
//        return variant(other);
//    }

    inline type_t type() const {
        return _type;
    }

    inline std::string type_str() const {
        switch (_type) {
#define x(type, name) \
        case name##_t: \
            return #name;
            FOR_EACH_CTYPES(x)
            FOR_EACH_TYPES(x)
#undef x
        }
    }

    template <class T,
             std::enable_if_t<std::is_integral<T>::value || std::is_floating_point<T>::value, int> = 0
             >
    T value() const
    {
        switch (_type) {
        case invalid:
            return T();
        case bool_t:
            return _data.bool_t;
        case int_t:
            return static_cast<T>(_data.int_t);
        case unsigned_int_t:
            return static_cast<T>(_data.unsigned_int_t);
        case unsigned_long_t:
            return static_cast<T>(_data.unsigned_long_t);
        case long_long_t:
            return static_cast<T>(_data.long_long_t);
        case unsigned_long_long_t:
            return static_cast<T>(_data.unsigned_long_long_t);
        case long_double_t:
            return static_cast<T>(_data.long_double_t);
        case double_t:
            return static_cast<T>(_data.double_t);
        case float_t:
            return static_cast<T>(_data.float_t);
        case string_t: {
            if (std::is_same<T, int>())
                return std::stoi(s);
            if (std::is_same<T, unsigned>())
                return std::stoul(s);
            if (std::is_same<T, unsigned long>())
                return std::stoul(s);
            if (std::is_same<T, long long>())
                return std::stoll(s);
            if (std::is_same<T, unsigned long long>())
                return std::stoull(s);
            if (std::is_same<T, long double>())
                return std::stold(s);
            if (std::is_same<T, double>())
                return std::stod(s);
            if (std::is_same<T, long>())
                return std::stol(s);
            if (std::is_same<T, float>())
                return std::stof(s);
        }
        default:
            //unreachable
            return T();
        }
    }

    template <class T, typename std::enable_if<std::is_base_of<std::string, T>::value>::type* = nullptr>
    T value() const
    {
        switch (_type) {
        case invalid:
            return std::string();
        case string_t:
            return s;
        case bool_t:
            return _data.bool_t ? "true" : "false";
        case int_t:
            return std::to_string(_data.int_t);
        case unsigned_int_t:
            return std::to_string(_data.unsigned_int_t);
        case unsigned_long_t:
            return std::to_string(_data.unsigned_long_t);
        case long_long_t:
            return std::to_string(_data.long_long_t);
        case unsigned_long_long_t:
            return std::to_string(_data.unsigned_long_long_t);
        case long_double_t:
            return std::to_string(_data.long_double_t);
        case double_t:
            return std::to_string(_data.double_t);
        case float_t:
            return std::to_string(_data.float_t);
        default:
            //unreachable
            return T();
        }
    }

    bool is_integral() const {
        switch (_type) {
        case int_t:
        case unsigned_int_t:
        case unsigned_long_t:
        case long_long_t:
        case unsigned_long_long_t:
            return true;
        default:
            return false;
        }
    }
    bool is_floating_point() const {
        switch (_type) {
        case float_t:
        case double_t:
        case long_double_t:
            return true;
        default:
            return false;
        }
    }
    bool is_numeric() const {
        return is_integral() || is_floating_point();
    }

#define x(type, name) type to_##name() const{ return value<type>(); }
    FOR_EACH_TYPES(x)
    FOR_EACH_CTYPES(x)
#undef x
};

class variant_vector : public std::vector<variant>
{
public:
    variant_vector() {

    }

    template<typename T>
    std::vector<T> to_vector() {
        std::vector<T> v;
        v.reserve(this->size());
        std::for_each(this->begin(), this->end(), [&v](variant &var){
            v.push_back(var.value<T>());
        });
        return v;
    }
    template<typename T>
    static variant_vector from_vector(std::vector<T> vec) {
        variant_vector v;
        v.reserve(vec.size());
        std::for_each(vec.begin(), vec.end(), [&v](T t){
            v.push_back(t);
        });
        return v;
    }

    void for_each(std::function<void(variant)> &callback) {
        std::for_each(this->begin(), this->end(), callback);
    }
};

TOOSKA_END_NAMESPACE

#endif // VARIANT_H
