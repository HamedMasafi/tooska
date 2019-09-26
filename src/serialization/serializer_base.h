#ifndef SERIALIZER_BASE_H
#define SERIALIZER_BASE_H

#include <string>
#include "../global.h"
#include "../json/json_object.h"
#include "../json/json_value.h"
#include "serializable.h"
#include "../core/converter.h"
#include "serializable.h"

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

#define x(type) virtual void set(const std::string &name, type &value) = 0;
    FOR_EACH_TYPES(x)
#undef x

    virtual void set(const std::string &name, serializable *object) {
        auto t = create_object();
        t->serialize(this);
    }

    virtual serializable *create_object() const
    {
        return nullptr;
    }
};

template<class C, class N>
class serializer : public serializer_base
{
public:
    serializer() : serializer_base(Unset)
    {}
};

template<class T>
class abstract_serializer
{
public:
    virtual std::string serialize(T *object) const = 0;
    virtual std::string serialize_array(const std::vector<T*> &object) const = 0;
    virtual T *deserialize(const std::string &data) const = 0;
    virtual std::vector<T*> deserialize_array(const std::string &data) const = 0;
};

template<class T>
class json_object_serializer : public abstract_serializer<T>
{
    json::object *object;

public:
    std::string serialize(T *object) const override
    {
        object->serialize(this);
    }
    std::string serialize_array(const std::vector<T*> &object) const override
    {

    }
    T *deserialize(const std::string &data) const override
    {
        auto t = new T;
        t->serialize(this);
        return t;
    }
    std::vector<T*> deserialize_array(const std::string &data) const override
    {

    }
};

TOOSKA_END_NAMESPACE

#endif // SERIALIZER_BASE_H
