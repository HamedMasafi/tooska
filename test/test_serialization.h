#ifndef TEST_SERIALIZATION_H
#define TEST_SERIALIZATION_H

#include "test.h"
#include "json/json_object.h"
#include "serialization/token_serializer.h"
#include "serialization/serializable.h"
#include "serialization/json_serializer.h"

class serializable_test_child : public tooska::serialization::serializable
{
public:
    std::string name;
    std::string last_name;
    int age;

    void serialize(tooska::serialization::token_serializer *t) {
        t->set("name", name);
        t->set("last_name", last_name);
        t->set("age", age);
    }
};

class serializable_test : public tooska::serialization::serializable
{
public:
    int n;
    float f;
    std::string s;
    serializable_test_child *child;

    serializable_test() : child(nullptr)
    {}

    void serialize(tooska::serialization::token_serializer *t) {
        t->set("s", s);
        t->set("n", n);
        t->set("f", f);
        t->set("child", child);
    }
};

void test_serialization() {
    tooska::json::json_document j;

    j.set_text(R"({
               n:4,
               f:3.14,
               s:'test',
               child: {
                    name: 'hamed',
                    last_name: 'masafi',
                    age: 35
               }
               }\n)");

    serializable_test t;
    tooska::serialization::json_serializer ser;
    ser.deserialize(j, &t);
    ASSERT(t.n == 4);
    ASSERT(t.s == "test");
    ASSERT(t.child->name == "hamed");
    ASSERT(t.child->last_name == "masafi");
    ASSERT(t.child->age == 35);
    auto doc = ser.serialize(&t);
    ASSERT(t.n == 4);

    ASSERT(doc->to_string() == j.to_string());
}

#endif // TEST_SERIALIZATION_H
