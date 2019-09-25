#include "token_serializer.h"
#include "../json/json_document.h"

TOOSKA_BEGIN_NAMESPACE(serialization)

token_serializer::token_serializer() : mode(serialize), _obj(new json::object)
{ }

token_serializer::token_serializer(json::object *obj) : mode(deserialize),  _obj(obj)
{ }

TOOSKA_END_NAMESPACE


