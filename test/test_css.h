#ifndef CSS_H
#define CSS_H

#include "test.h"
#include <html/css_document.h>

void test_css() {
    tooska::html::css_document _css;
    auto css_text = R"~(
                    body{
                    color: red;
                    background-color: green;
                    }
                    body div{
                    display: block;
                    }
                    /*comment outside - /*/
                    .p{ coloe: green; }
                    .p,div{
                    background-image: url('image.png');
                    padding: 2px;
                    border: 1px solid green;
                    padding-top: 3px;
                    /*comment: none*/color:red;
                    }

                    )~";
    _css.set_text(css_text);
    ASSERT(4 == _css.nodes().size());
    ASSERT(1 == _css.find_match_selector("body").size());
    ASSERT(2 == _css.find_contains_selector(".p").size());
}
#endif // CSS_H
