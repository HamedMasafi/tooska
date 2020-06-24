#ifndef TEST_TOKENIZER_H
#define TEST_TOKENIZER_H

#include "test.h"
#include <core/string_tokenizer.h>
#include <iostream>

using namespace tooska::core;

int token(int n)
{
    return isalnum(n) || isdigit(n) || n == '-';
}

void test_tokenizer() {
    string_tokenizer t;
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

    t._literals.push_back(new tokenizer_base::literal_t{">",  "<",  "",     true,  true});
    t._literals.push_back(new tokenizer_base::literal_t{"\"", "\"", "\\\"", false, true, true});
    t._literals.push_back(new tokenizer_base::literal_t{"'",  "'",  "\\'",  false, true, true});
    t._literals.push_back(new tokenizer_base::literal_t{"<!--",  "-->",  "",     false,  false});
    t._literals.push_back(new tokenizer_base::literal_t{"<!",  ">",  "",     false,  false});
    t._check_fns.push_back(token);

    t.set_data(html_text);
    t.parse_tokens();
    auto tokens = t.tokens();

    std::cout << "====TOKENS====" << std::endl;
    std::for_each(tokens.begin(), tokens.end(), [&](std::string token){
        std::cout << token << "<<<" << std::endl;
    });
    std::cout << "==============: count=" << tokens.size() << std::endl;
}


#endif // TEST_TOKENIZER_H
