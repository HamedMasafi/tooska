# JSON

## Parsing json

```cpp
using namespace parser;

auto json_text = R"~(
                     {
                        name: hamed,
                        last_name: masafi,
                        array: [1, 2, 3, 4, 5],
                        other: 4,
                        f: 3.14,
                        n: 10,
                        ia: [
                                {a : 2}, {b: 23},
                                [1,2,5,7]
                            ]
                    }
                     )~";

json_document json;
json.set_text(json_text);

auto v = json.find("ia.1.b");
ASSERT(v->type() == json_value::json_value_t::int_t);
auto v2 = json.find("invalid_path");
ASSERT(v2 == nullptr);
```

## Convert json to string

```cpp
auto formatted_json = json.to_string(print_type::formatted));
auto compaqt_json = json.to_string(print_type::compact));
```

## Types

The <i>json_document</i> type contain a root value that can be <i>json_array</i> or <i>json_object</i>.

## json_object

