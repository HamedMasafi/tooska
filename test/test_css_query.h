#ifndef TEST_CSS_QUERY_H
#define TEST_CSS_QUERY_H

#include "test.h"
#include <html/query_parser.h>

using namespace std;
using namespace tooska::html;

void print(const query_parser::rules_group_list &rules) {
    int i = 0;
    for_each(rules.begin(), rules.end(), [&i](vector<query_parser::query_rule_t*> rl){
        cout << "RULE: " << (++i) << endl;
        int n = 0;
        for_each(rl.begin(), rl.end(), [&n](query_parser::query_rule_t *r){
            cout << (n++);

            if (r->id.size())
                cout << " id:" << r->id;

            if (r->tag_name.size())
                cout << " tag:" << r->tag_name;

            if (r->is_child)
                cout << boolalpha << " child:" << r->is_child;

            if (r->attr_name.size())
                cout << " " << r->attr_name << "=" << r->attr_value;

            if (r->classes.size()) {
                cout << " classes:";
                int n {0};
                for_each(r->classes.begin(), r->classes.end(), [&n](string cls){
                    if (n++)
                    cout << ", ";
                    cout << cls;
                });
            }
            cout << endl;
        });
    });
}

void test1() {
    query_parser qp;
    qp.set_text("div.sample.cls3 .inner b #my_elem > input[type=text] a");
    qp.parse();

    auto rules = qp.rules();

    print(rules);

    ASSERT(rules.size() == 1);
    auto rl = rules[0];
    ASSERT(rl.size() == 6);
    ASSERT(rl[0]->tag_name == "div");
    ASSERT(rl[2]->tag_name == "b");
    ASSERT(rl[5]->tag_name == "a");
}

void test2() {
    query_parser qp;
    qp.set_text("div, a");
    qp.parse();

    auto rules = qp.rules();

    print(rules);

    ASSERT(rules.size() == 2);
    ASSERT(rules[0][0]->tag_name == "div");
    ASSERT(rules[1][0]->tag_name == "a");
}

void test_css_query() {
    test1();
    test2();
}

#endif // TEST_CSS_QUERY_H
