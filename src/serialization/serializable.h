#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include "../global.h"
#include <vector>
#include <iostream>
#include "../json/json_object.h"


TOOSKA_BEGIN_NAMESPACE(serialization)

class serializer_base;

/*
struct serialize_rule_base;
struct serialize_rule_base
{
    serialize_rule_base *next;
    const std::string &name;
    constexpr serialize_rule_base(const std::string &name) : next(nullptr), name(name)
    {
//        std::cout << "ctor " << name << std::endl;
    }
    virtual ~serialize_rule_base() {
        std::cout << "~ctor " << name << std::endl;
    }

    virtual void write (const std::string &val)
    {
        std::cout << "writing " << val << std::endl;
    }
};

template<typename T>
struct serialize_rule : public serialize_rule_base
{
    T &data;

    constexpr serialize_rule(const std::string &name, T &data) : serialize_rule_base(name), data(data)
    {
//        std::cout << "*" <<name <<"*" << std::endl;
    }

    template<typename _T>
    void write (std::string &val)
    {

    }
};

template<typename T1, typename T2>
constexpr serialize_rule<T2> operator &(serialize_rule<T1> &&l, serialize_rule<T2> &&r)
{
    r.next = &l;
    std::cout << "operator & : " << l.name << " & " << r.name << std::endl;
    return r;
}
*/

//TOOSKA_BEGIN_NAMESPACE(serialization)
//template<class T>
//class serializer;
//TOOSKA_END_NAMESPACE

#define SERIALIZATION_BLOCK void serialize(tooska::serialization::serializer_base *t)
#define FIELD(name)    t->set(#name, name);
//#define BEGIN_SERIALIZATION_BLOCK template<class T> void serialize(T *t) {
//#define END_SERIALIZATION_BLOCK }

class serializable
{
public:
    serializable();
    virtual ~serializable() = default;

//    virtual const serialize_rule_base rule() = 0;
    virtual void serialize(serializer_base *t) = 0;
};

TOOSKA_END_NAMESPACE

#endif // SERIALIZABLE_H
