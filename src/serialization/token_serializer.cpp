#include "token_serializer.h"
#include "../json/json_document.h"

TOOSKA_BEGIN_NAMESPACE(serialization)

token_serializer::token_serializer() : mode(serialize)
{ }

token_serializer::token_serializer(json::json_object obj) : mode(deserialize),  _obj(obj)
{ }

TOOSKA_END_NAMESPACE


