#include <iostream>
#include <algorithm>
#include <chrono>

#include "test.h"
#include "test_html.h"
#include "test_css.h"
#include "test_json.h"
#include "test_serialization.h"

int main() {
    START();

    RUN_TEST(html);
    RUN_TEST(css);
    RUN_TEST(json);
    RUN_TEST(serialization);

    PASSED();
}

