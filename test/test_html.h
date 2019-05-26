#ifndef TEST_HTML_H
#define TEST_HTML_H

#include "test.h"
#include <algorithm>
#include <html/html_document.h>
#include <html/html_node.h>

void test_html() {

    tooska::html::html_document _html;
    auto html_text = R"~(<!DOCTYPE HTML>
    <html>
        <head>
            <meta name="qrichtext" content="1" />
            <style type="text/css">
                p, li { white-space: pre-wrap; }
                b { color: "red" }
            </style>
        </head>
        <body style=" font-family:'Noto Sans'; font-size:10pt; font-weight:400; font-style:normal;">
            <p style=" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;">
                dfg
            </p>
            <img src="image.png" />
            <p id="p1" class="par">
                <b>Sample</b> paragraph
                <img src="image.png" />
            </p>
            <b>Other</b>
        </body>
    </html>)~";

    _html.set_text(html_text);
    auto tags = _html.query("p.par>b");
    ASSERT(1 == tags.size());

    auto b = _html.query("b");
    std::for_each(b.begin(), b.end(), [](tooska::html::html_tag *tag){
        tag->add_class("new-class");
    });

    auto new_classes = _html.query(".new-class");
    ASSERT(b.size() == new_classes.size());

    b.add_class("new-class2");
    auto new_classes2 = _html.query(".new-class2");
    ASSERT(b.size() == new_classes2.size());
}

#endif // TEST_HTML_H
