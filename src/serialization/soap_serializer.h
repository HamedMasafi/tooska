#ifndef SOAP_SERIALIZER_H
#define SOAP_SERIALIZER_H

#include "../global.h"
#include "serializer_base.h"

TOOSKA_BEGIN_NAMESPACE(xml)
class node;
TOOSKA_END_NAMESPACE
TOOSKA_BEGIN_NAMESPACE(serialization)

class soap_serializer : public serializer_base
{
    tooska::xml::node *_root;
    tooska::xml::node *_node;
    bool _fields_in_attributes;
    bool _wrap_vectors;
    void wrap_node();

public:
    soap_serializer();
    soap_serializer(tooska::xml::node *node);

public:
    bool has_key(const std::string &key) const override;
    void serialize_value(const std::string &name, const tooska::core::variant &value) override;
    void deserialize_value(const std::string &name, tooska::core::variant &value) override;

    void serialize_vector(const std::string &name, const tooska::core::variant_vector &vec) override;
    void deserialize_vector(const std::string &name, tooska::core::variant_vector &vec) override;

    void serialize_object(const std::string &name, serializable *object) override;
    void deserialize_object(const std::string &name, serializable *object) override;
    serializer_base *create_serializer(serializable *child) const override;
    tooska::xml::node *node() const;
    void before_serialize(serializable *object);
};

TOOSKA_END_NAMESPACE

#endif // SOAP_SERIALIZER_H
