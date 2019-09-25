#ifndef JSON_ARRAY_H
#define JSON_ARRAY_H

#include "../global.h"
#include "json_value.h"
#include <vector>
#include <functional>

TOOSKA_BEGIN_NAMESPACE(core)
class string_renderer;
TOOSKA_END_NAMESPACE

TOOSKA_BEGIN_NAMESPACE(json)
class array : public value
{
    std::vector<value*> _values;

public:
    array();
    virtual ~array();
    void add(value *v);
    value *at(const size_t &pos) const;

    const value *operator[](const size_t &i) const;
    value *operator[](const size_t &i);

    void for_each(const std::function<void(value*)> &callback);
private:
    void render(core::string_renderer &r) override;
};

TOOSKA_END_NAMESPACE

#endif // JSON_ARRAY_H
