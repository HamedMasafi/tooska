#include <algorithm>

#include "query_parser.h"
#include "html_node.h"
#include "html_tag_vector.h"

TOOSKA_BEGIN_NAMESPACE(html)

html_tag_vector::html_tag_vector() : tooska::core::nodes_vector<html_tag>()
{

}

void html_tag_vector::add_class(const std::string &cls)
{
    std::for_each(begin(), end(), [&cls](html_tag *tag){
        tag->add_class(cls);
    });
}

void html_tag_vector::remove_class(const std::string &cls)
{
    std::for_each(begin(), end(), [&cls](html_tag *tag){
        tag->remove_class(cls);
    });
}

//void html_tag_vector::remove_all()
//{
//    std::for_each(begin(), end(), [&](html_tag *tag){
//        delete tag;
//    });
//    clear();
//}

html_tag_vector html_tag_vector::find(const std::string &query)
{
    html_tag_vector vec;
    query_parser qp;
    qp.set_text(query);
    std::for_each(begin(), end(), [&qp, &vec](html_node *node){
        auto tag = node->to_tag();
        if (tag) {
            qp.tag = tag;
            auto results = qp.search();
            if (results.size())
                vec.insert(vec.end(), results.begin(), results.end());
        }
    });
    return vec;
}

html_tag_vector html_tag_vector::tags() const
{
    html_tag_vector vec;
    std::for_each(begin(), end(), [&vec](html_node *node){
        auto tag = node->to_tag();
        if (tag)
            vec.push_back(tag);
    });
    return vec;
}

//html_tag *html_tag_vector::first()
//{
//    return size() ? at(0) : nullptr;
//}

//html_tag *html_tag_vector::last()
//{
//    return size() ? at(size() - 1) : nullptr;
//}

//void html_tag_vector::for_each(const std::function<void (html_tag *)> &callback)
//{
//    std::for_each(begin(), end(), callback);
//}

TOOSKA_END_NAMESPACE
