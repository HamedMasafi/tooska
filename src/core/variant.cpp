#include "variant.h"

TOOSKA_BEGIN_NAMESPACE(core)

variant::variant()
{
}

#define x(type) variant::variant(const type &val) {}
FOR_EACH_TYPES(x,)
#undef x

TOOSKA_END_NAMESPACE
