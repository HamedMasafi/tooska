#ifndef TEST_JSON_H
#define TEST_JSON_H

#include <json/json_value.h>
#include <json/json_document.h>
#include "test.h"
#include <iostream>

using namespace tooska::json;

std::ostream & operator << (std::ostream &out, const json_value::type_t &t)
{
    out << static_cast<int>(t);
    return out;
}

void test_values() {
    ASSERT2(json_value(true).type(),    json_value::type_t::bool_t);
    ASSERT2(json_value(1).type(),       json_value::type_t::int_t);
//    ASSERT2(json_value(1l).type(),      json_value::type_t::int_t);
//    ASSERT2(json_value(1ll).type(),     json_value::type_t::int_t);
//    ASSERT2(json_value(1u).type(),      json_value::type_t::int_t);
//    ASSERT2(json_value(1ul).type(),     json_value::type_t::int_t);
//    ASSERT2(json_value(1ull).type(),    json_value::type_t::int_t);
//    ASSERT2(json_value(4.2).type(),     json_value::type_t::float_t);
    ASSERT2(json_value(4.2f).type(),    json_value::type_t::float_t);
    ASSERT2(json_value("test").type(),  json_value::type_t::string_t);
    ASSERT2(json_value::null().type(),  json_value::type_t::null_t);
}

void test_json() {
    test_values();

    tooska::json::json_document _json;

    auto json_text = R"~(
                     {
                        name: "hamed",
                        last_name: "masafi",
                        unescaped: "the'string",
                        unescaped2: 'the"string',
                        unescaped3: "the'one\"string",
                        array: [1, 2, 3, 4, 5],
                        other: 4,
                        nl: null,
                        pi : 3.14,
                        n : 10 ,
                        b: true,
                        bs: 'false',
                        n: null,
                        ia: [
                                {a : 2}, {b: 23},
                                [1,2,5,7]
                            ]
                    }
                     )~";

    _json.set_text(json_text);
    auto v = _json.find("ia.1.b");
    ASSERT(v.is_valid());
    ASSERT(v.type() == tooska::json::json_value::type_t::int_t);
    auto v2 = _json.find("invalid_path");
    ASSERT(!v2.is_valid());

}
#endif // TEST_JSON_H
