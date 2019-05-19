#include "json_serializer.h"
#include "serializable.h"
#include "token_serializer.h"
#include "../json/json_document.h"

TOOSKA_BEGIN_NAMESPACE(serialization)

json_serializer::json_serializer()
{

}

tooska::json::json_document *json_serializer::serialize(serializable *obj) const
{
    token_serializer w;
    obj->serialize(&w);
    return new tooska::json::json_document(w._obj);
}

void json_serializer::deserialize(tooska::json::json_document &doc, serializable *obj) const
{
    token_serializer w(doc.to_object());
    obj->serialize(&w);
}

TOOSKA_END_NAMESPACE
