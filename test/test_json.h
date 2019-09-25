#ifndef TEST_JSON_H
#define TEST_JSON_H

#include <json/json_value.h>
#include <json/json_document.h>
#include "test.h"

void test_json() {
    tooska::json::document _json;

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
    ASSERT(v != nullptr);
    ASSERT(v->type() == tooska::json::value::type_t::int_t);
    auto v2 = _json.find("invalid_path");
    ASSERT(v2 == nullptr);

}
#endif // TEST_JSON_H
