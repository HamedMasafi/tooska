#ifndef TEST_SERIALIZATION_H
#define TEST_SERIALIZATION_H

#include "test.h"
#include "json/json_object.h"
#include "serialization/json_serializer.h"
#include "serialization/serializable.h"
#include "serialization/json_token_serializer.h"
#include "serialization/serializer_base.h"

class serializable_test_child : public tooska::serialization::serializable
{
public:
    std::string name;
    std::string last_name;
    int age;

//    void serialize(tooska::serialization::serializer_base *t) {
//        t->set("name", name);
//        t->set("last_name", last_name);
//        t->set("age", age);
//    }
    SERIALIZATION_BLOCK {
        FIELD(name)
        FIELD(last_name)
        FIELD(age)
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

    SERIALIZATION_BLOCK {
        FIELD(s)
        FIELD(n)
//        FIELD(f)
        FIELD(child)
    }

//    void serialize(tooska::serialization::serializer_base *t) {
//        t->set("s", s);
//        t->set("n", n);
//        t->set("f", f);
//        t->set("child", child);
//    }
};

void test_serialization() {
    tooska::json::document j;

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

//    tooska::serialization::json_token_serializer tt;
//    int n;
//    tt.set<int>("s", n);

    serializable_test t;
    tooska::serialization::json_serializer ser;
    ser.deserialize(j.to_object(), &t);
    ASSERT(t.n == 4);
    ASSERT(t.s == "test");
    ASSERT(t.child->name == "hamed");
    ASSERT(t.child->last_name == "masafi");
    ASSERT(t.child->age == 35);
    auto doc = ser.serialize(&t);
    ASSERT(t.n == 4);

//    ASSERT(doc->to_string() == j.to_string());
}

#endif // TEST_SERIALIZATION_H
