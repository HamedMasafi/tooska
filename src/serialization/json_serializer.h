#ifndef JSON_SERIALIZER_H
#define JSON_SERIALIZER_H

#include <vector>
#include "../global.h"
#include "serializable.h"
#include "token_serializer.h"
#include "../json/json_document.h"
#include "../json/json_array.h"

TOOSKA_BEGIN_NAMESPACE(json)
class json_document;
TOOSKA_END_NAMESPACE

TOOSKA_BEGIN_NAMESPACE(serialization)

class serializable;
class json_serializer
{
public:
    json_serializer();


    tooska::json::json_document *serialize(serializable* obj) const
    {
        token_serializer w;
        obj->serialize(&w);
        return new tooska::json::json_document(w._obj);
    }

    void deserialize(tooska::json::json_document &doc, serializable *obj) const
    {
        token_serializer w(doc.to_object());
        obj->serialize(&w);
    }

    tooska::json::json_document *serialize(std::vector<serializable*> obj) const
    {
        token_serializer w;
        //    obj->serialize(&w);
        return new tooska::json::json_document(w._obj);
    }

    template<class T>
    void deserialize(tooska::json::json_array *arr, std::vector<T*> &obj) const
    {
        arr->for_each([&](tooska::json::json_value *v){
            token_serializer w(v->to_object());
            T *o = new T;
            o->serialize(&w);
            obj.push_back(o);
        });
    }
};

TOOSKA_END_NAMESPACE

#endif // JSON_SERIALIZER_H
