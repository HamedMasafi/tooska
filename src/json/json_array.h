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
class json_array_data;
class json_array : public json_value
{
    json_array(json_array_data *data);

public:
    json_array();
    json_array(const json_array &other);
    json_array(json_array &&other);

    json_array &operator =(const json_array &other);

    virtual ~json_array() override;
    void add(json_value v);
    json_value at(const size_t &pos) const;

    const json_value operator[](const size_t &i) const;
    json_value operator[](const size_t &i);

    void for_each(const std::function<void(json_value)> &callback);
private:
    void render(core::string_renderer &r) const override;
    json_array_data *_array_data;

    friend class json_value;
};

TOOSKA_END_NAMESPACE

#endif // JSON_ARRAY_H
