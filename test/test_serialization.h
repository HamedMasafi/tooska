#ifndef TEST_SERIALIZATION_H
#define TEST_SERIALIZATION_H

#include <assert.h>

#include "test.h"
#include "json/json_object.h"
#include "json/json_document.h"
#include "xml/xml_document.h"
#include "xml/xml_node.h"
#include "serialization/json_serializer.h"
#include "serialization/serializable.h"
#include "serialization/serializer_base.h"
#include "serialization/xml_serializer.h"

using namespace tooska::serialization;
class serializable_test_child : public tooska::serialization::serializable
{
public:
    std::string name;
    std::string last_name;
    int age;

    SERIALIZATION_BLOCK(serializable_test_child) {
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
    std::vector<int> int_vector;
    serializable_test_child *child;

    serializable_test() : child(nullptr)
    {}

    SERIALIZATION_BLOCK(serializable_test) {
        FIELD(s)
        FIELD(n)
        FIELD(f)
        FIELD(child)
        FIELD(int_vector)
    }
};


void test_xml_serialization(serializable_test original_object) {
    xml_serializer serializer;
    serializer.serialize(&original_object);
    auto node = serializer.node();

    auto deserializer = new xml_serializer(node);
    auto deserialized_object = deserializer->deserialize<serializable_test>();
    std::cout << node->to_string(tooska::print_type::formatted) << std::endl;

    ASSERT(original_object.n == deserialized_object->n);

    assert(deserialized_object->child);
    assert(original_object.n == deserialized_object->n);
    assert(original_object.child->age == deserialized_object->child->age);
    assert(original_object.child->name == deserialized_object->child->name);
    assert(original_object.child->last_name == deserialized_object->child->last_name);
    assert(original_object.int_vector.size() == deserialized_object->int_vector.size());

    for (int i = 0; i < original_object.int_vector.size(); ++i)
        assert(original_object.int_vector.at(i) == deserialized_object->int_vector.at(i));
}
void test_json_serialization(serializable_test &original_object) {
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

    json_serializer serializer;//(j.to_object());

    serializer.serialize(&original_object);

    json_serializer dserializer(serializer.object());
    auto deserialized_object = dserializer.deserialize<serializable_test>();

    tooska::json::document doc(serializer.object());
    std::cout << "Json=" << doc.to_string() << std::endl;

    assert(deserialized_object->child);
    assert(original_object.n == deserialized_object->n);
    assert(original_object.child->age == deserialized_object->child->age);
    assert(original_object.child->name == deserialized_object->child->name);
    assert(original_object.child->last_name == deserialized_object->child->last_name);
    assert(original_object.int_vector.size() == deserialized_object->int_vector.size());

    for (int i = 0; i < original_object.int_vector.size(); ++i)
        assert(original_object.int_vector.at(i) == deserialized_object->int_vector.at(i));
}

void test_serialization() {
    serializable_test original_object;
    original_object.n = 7;
    original_object.f = 3.14;
    original_object.s = "Hi";
    original_object.int_vector.push_back(1);
    original_object.int_vector.push_back(2);
    original_object.int_vector.push_back(3);

    serializable_test_child child;
    child.age = 36;
    child.name = "hamed";
    child.last_name = "masafi";

    original_object.child = &child;
//    test_json_serialization(original_object);
    test_xml_serialization(original_object);
}

#endif // TEST_SERIALIZATION_H

