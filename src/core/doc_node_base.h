#ifndef DOC_NODE_BASE_H
#define DOC_NODE_BASE_H

#include "global.h"
#include <vector>
#include <map>

TOOSKA_BEGIN_NAMESPACE(core)

class doc_node_base
{
protected:
    std::string _name;
    std::map<std::string, std::string> _attributes;

public:
    doc_node_base(std::string name);

    std::string attr(const std::string &name);
    void set_attr(const std::string &name, const std::string &value);
    bool has_attr(const std::string &name);
    std::string name() const;
    virtual void set_name(const std::string &name);
};

TOOSKA_END_NAMESPACE

#endif // DOC_NODE_BASE_H
