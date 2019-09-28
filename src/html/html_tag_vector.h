#ifndef HTML_TAG_VECTOR_H
#define HTML_TAG_VECTOR_H

#include "../core/nodes_vector.h"
#include <string>
#include "../global.h"

TOOSKA_BEGIN_NAMESPACE(html)

class html_tag;
class html_tag_vector : public tooska::core::nodes_vector<html_tag>
{
public:
    html_tag_vector();

    void add_class(const std::string &cls);
    void remove_class(const std::string &cls);

//    void remove_all();

    html_tag_vector find(const std::string &query);

    html_tag_vector tags() const;

//    html_tag *first();
//    html_tag *last();

//    void for_each(const std::function<void(html_tag*)> &callback);
};

TOOSKA_END_NAMESPACE

#endif // HTML_TAG_VECTOR_H
