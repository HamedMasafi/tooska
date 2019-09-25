#ifndef JSON_SERIALIZER_H
#define JSON_SERIALIZER_H

#include <vector>
#include "../global.h"
#include "serializable.h"
#include "json_token_serializer.h"
#include "../json/json_document.h"
#include "../json/json_array.h"

TOOSKA_BEGIN_NAMESPACE(json)
class document;
TOOSKA_END_NAMESPACE

TOOSKA_BEGIN_NAMESPACE(serialization)

class serializable;
class json_serializer
{
public:
    json_serializer();


    tooska::json::document *serialize(serializable* obj) const
    {
//        json_token_serializer w;
//        obj->serialize(&w);
        return new tooska::json::document();//w.obj());
    }

    void deserialize(tooska::json::document &doc, serializable *obj) const
    {
//        json_token_serializer w(doc.to_object());
//        obj->serialize(&w);
    }

    tooska::json::document *serialize(std::vector<serializable*> obj) const
    {
//        token_serializer w;
//        obj->serialize(&w);
        return new tooska::json::document();//w.obj());
    }

    template<class T>
    void deserialize(tooska::json::array *arr, std::vector<T*> &obj) const
    {
        arr->for_each([&](tooska::json::value *v){
            token_serializer w(v->to_object());
            T *o = new T;
            o->serialize(&w);
            obj.push_back(o);
        });
    }
};

TOOSKA_END_NAMESPACE

#endif // JSON_SERIALIZER_H
