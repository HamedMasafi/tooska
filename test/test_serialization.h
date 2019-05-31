#ifndef TEST_SERIALIZATION_H
#define TEST_SERIALIZATION_H

#include "test.h"
#include "json/json_object.h"
#include "serialization/token_serializer.h"
#include "serialization/serializable.h"
#include "serialization/json_serializer.h"

using namespace tooska::json;
using namespace tooska::serialization;

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
    tooska::json::json_document sample_json;

    sample_json.set_text(R"({
               n:4,
               f:3.14,
               s:'test',
               child: {
                    name: 'hamed',
                    last_name: 'masafi',
                    age: 35
               }
               }\n)");

    serializable_test test_object;
    tooska::serialization::json_serializer serializer;
    serializer.deserialize(sample_json.to_object(), &test_object);
    ASSERT(test_object.n == 4);
    ASSERT(test_object.s == "test");
    ASSERT(test_object.child->name == "hamed");
    ASSERT(test_object.child->last_name == "masafi");
    ASSERT(test_object.child->age == 35);
    auto deserialized_json = serializer.serialize(&test_object);
    ASSERT(test_object.n == 4);
std::cout << json_document(deserialized_json).to_string() << std::endl;
std::cout << json_document(sample_json).to_string() << std::endl;
//    ASSERT(doc->to_string() == j.to_string());
}

#endif // TEST_SERIALIZATION_H
