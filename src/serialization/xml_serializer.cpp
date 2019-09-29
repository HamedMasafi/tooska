#include "xml_serializer.h"
#include "../xml/xml_node.h"
#include "../xml/xml_document.h"
#include "../core/variant.h"
#include <iostream>


TOOSKA_BEGIN_NAMESPACE(serialization)
using namespace tooska;

xml_serializer::xml_serializer() : serializer_base(Serialize)
      , _node(new tooska::xml::node)
{

}

xml_serializer::xml_serializer(tooska::xml::node *node) : serializer_base(Deserialize)
      , _node(node)
{

}

bool xml_serializer::has_key(const std::string &key) const
{
    return _node->has_attr(key) || _node->find(key).size();
}

void xml_serializer::serialize_value(const std::string &name, const tooska::core::variant &value)
{
    _node->set_attr(name, value.to_string());
}

void xml_serializer::deserialize_value(const std::string &name, tooska::core::variant &value)
{
    value = _node->attr(name);
}

serializer_base *xml_serializer::create_serializer(serializable *child) const
{
    auto t = new xml_serializer;
    t->mode = mode;
    return t;
}

tooska::xml::node *xml_serializer::node() const
{
    return _node;
}

void xml_serializer::serialize_object(const std::string &name, serializable *object)
{
    xml_serializer t;
    object->__tokenize(&t);
    tooska::xml::node *node = t.node();
    node->set_name(object->__class_name());
    _node->add_child(node);
}

void xml_serializer::deserialize_object(const std::string &name, serializable *object)
{
    auto node_name = object->__class_name();
//    if (!has_key(node_name)) {
//        std::cout << node_name << " is not present in json!" << std::endl;
//        return;
//    }

    auto o = _node->find(node_name).first();
    if (!o) {
        std::cout << node_name << " is not valid json xml node!" << std::endl;
        return;
    }
    xml_serializer s(o);
    object->__tokenize(&s);
}

void xml_serializer::serialize_vector(const std::string &name, const tooska::core::variant_vector &vec)
{
    auto parent = new tooska::xml::node(name);
    auto arr = new core::nodes_vector<xml::node>;
    std::for_each(vec.begin(), vec.end(), [parent, &vec, arr](core::variant v){
        auto n = new xml::node("item");
        n->set_inner_text(v.to_string());
        parent->add_child(n);
    });
    _node->add_child(parent);
}

void xml_serializer::deserialize_vector(const std::string &name, tooska::core::variant_vector &vec)
{
    if (!has_key(name)) {
        std::cout << name << " is not present in json!" << std::endl;
        return;
    }

    auto a = _node->find(name + "/item");
    if (!a.size()) {
        std::cout << name << " is not valid json array!" << std::endl;
        return;
    }

    a.for_each([&vec](tooska::xml::node *val){
        tooska::core::variant v(val->inner_text());
        vec.push_back(v);
    });
}


void xml_serializer::before_serialize(serializable *object)
{
    _node->set_name(object->__class_name());
}

TOOSKA_END_NAMESPACE
