#ifndef TEST_HTML_H
#define TEST_HTML_H

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
                     <p style=" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;">dfg</p>
                     <img src="image.png" />
                     <p id="p1" class="par">
                     <b>Sample</b> paragraph
                     <img src="image.png" />
                     </p>
                     </body>
                     </html>)~";

    _html.set_text(html_text);
    auto tags = _html.query("p.par>b");
    std::for_each(tags.begin(), tags.end(), [](tooska::html::html_node *tag){
        tag->to_tag()->add_class("new-class");
    });
    ASSERT(1 == tags.size());


}
#endif // TEST_HTML_H
