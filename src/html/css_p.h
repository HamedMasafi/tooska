#ifndef CSS_P_H
#define CSS_P_H

#include "../global.h"
#include <map>
#include <vector>
#include <string>

TOOSKA_BEGIN_NAMESPACE(html)

struct css_node_data
{
    std::vector<std::string> selectors;
    std::map<std::string, std::string> rules;
};

TOOSKA_END_NAMESPACE

#endif // CSS_P_H
