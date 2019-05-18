#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

#include <map>
#include "../global.h"

TOOSKA_BEGIN_NAMESPACE(serialization)

class serializer
{
public:
    template<typename T>
     void operator &(T &&other)
    {

    }
};

template<typename T>
class serializable_token
{
    std::string _name;
    T &_ref;
public:
    serializable_token(const std::string &name, T &data)
        : _name(name), _ref(data)
    {}
};

class serializable_token_list
{
    std::map<std::string, void*> _map;
public:
    template<typename T>
    constexpr serializable_token_list(serializable_token<T> &&token)
    {}
};

template<typename _T1, typename _T2>
serializable_token_list operator&&(serializable_token<_T1> &&t1, serializable_token<_T2> &&t2)
{
}

class serializable
{
protected:
    template<typename T>
    serializable_token<T> token(const std::string &name, T &data)
    {
        return serializable_token<T>(name, data);
    }

public:
    serializable();
    virtual ~serializable() = default;
    virtual serializable_token_list serialize() = 0;
};

TOOSKA_END_NAMESPACE

#endif // SERIALIZABLE_H
