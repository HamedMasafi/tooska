#include "soap_serializer.h"
#include "../xml/xml_node.h"
#include "../xml/xml_document.h"
#include "../core/variant.h"
#include <iostream>


TOOSKA_BEGIN_NAMESPACE(serialization)
using namespace tooska;

soap_serializer::soap_serializer()
    : serializer_base(Serialize)
    , _node(new tooska::xml::node)
{
    wrap_node();
}

soap_serializer::soap_serializer(tooska::xml::node *node)
    : serializer_base(Deserialize)
    , _node(node)
{
    wrap_node();
}

bool soap_serializer::has_key(const std::string &key) const
{
    return _node->has_attr(key) || _node->find(key).size();
}

void soap_serializer::serialize_value(const std::string &name, const tooska::core::variant &value)
{
    auto vnode = new tooska::xml::node(value.type_str());
    vnode->set_inner_text(value.to_string());
    _node->add_child(vnode);
}

void soap_serializer::deserialize_value(const std::string &name, tooska::core::variant &value)
{
    value = _node->attr(name);
}

serializer_base *soap_serializer::create_serializer(serializable *child) const
{
    auto t = new soap_serializer;
    t->mode = mode;
    return t;
}

tooska::xml::node *soap_serializer::node() const
{
    return _root;
}

void soap_serializer::serialize_object(const std::string &name, serializable *object)
{
    soap_serializer t;
    object->__tokenize(&t);
    tooska::xml::node *node = t.node();
    node->set_name(object->__class_name());
    _node->add_child(node);
}

void soap_serializer::deserialize_object(const std::string &name, serializable *object)
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
    soap_serializer s(o);
    object->__tokenize(&s);
}

void soap_serializer::serialize_vector(const std::string &name,
                                       const tooska::core::variant_vector &vec)
{
    auto parent = new tooska::xml::node(name);
    auto arr = new core::nodes_vector<xml::node>;
    std::for_each(vec.begin(), vec.end(), [parent, &vec, arr](core::variant v) {
        auto n = new xml::node("item");
        n->set_inner_text(v.to_string());
        parent->add_child(n);
    });
    _node->add_child(parent);
}

void soap_serializer::deserialize_vector(const std::string &name, tooska::core::variant_vector &vec)
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

    a.for_each([&vec](tooska::xml::node *val) {
        tooska::core::variant v(val->inner_text());
        vec.push_back(v);
    });
}

void soap_serializer::before_serialize(serializable *object)
{
    _node->set_name(object->__class_name());
}

void soap_serializer::wrap_node()
{
    _root = new tooska::xml::node("soap:Envelope");
    _root->set_attr("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance");
    _root->set_attr("xmlns:xsd", "http://www.w3.org/2001/XMLSchema");
    _root->set_attr("xmlns:soap", "http://schemas.xmlsoap.org/soap/envelope/");

    auto body = new tooska::xml::node("soap:Body", _root);
    body->set_attr("xmlns", "http://tempuri.org/");

    body->add_child(_node);
}

TOOSKA_END_NAMESPACE
