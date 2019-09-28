#ifndef TEST_VARIANT_H
#define TEST_VARIANT_H

#include "test.h"
#include <core/variant.h>

using namespace tooska::core;

void test_variant() {
    variant v1(4);
    ASSERT(v1.value<int>() == 4);
    ASSERT(v1.value<long long>() == 4);
    ASSERT(v1.value<float>() == 4);
    ASSERT(v1.value<double>() == 4);
    ASSERT(v1.value<std::string>() == "4");

    variant v2("5.6");
    ASSERT(v2.value<int>() == 5);
    ASSERT(v2.value<float>() == 5.6f);
    ASSERT(v2.value<std::string>() == "5.6");

    variant v3('n');
    ASSERT(v3.to_int() == 'n');

    variant v4(true);
    ASSERT(v4.type() == variant::bool_t);
    ASSERT(v4.to_string() == "true");
    ASSERT(v4.to_bool());
}

#endif // TEST_VARIANT_H
