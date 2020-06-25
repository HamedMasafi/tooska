#include <iostream>
#include <algorithm>
#include <chrono>

#include "test.h"
#include "test_html.h"
#include "test_xml.h"
#include "test_css.h"
#include "test_json.h"
#include "test_serialization.h"
#include "test_soap.h"
#include "test_temp.h"
#include "test_variant.h"
#include "test_tokenizer.h"
#include "test_css_query.h"

int main() {
    START();

//    RUN_TEST(temp);
    RUN_TEST(html);
//    RUN_TEST(xml);
    RUN_TEST(css);
//    RUN_TEST(variant);
//    RUN_TEST(json);
//    RUN_TEST(serialization);
//    RUN_TEST(soap);
//    RUN_TEST(tokenizer);
    RUN_TEST(css_query);

    PASSED();
}

