#include "token_serializer.h"
#include "../json/json_document.h"

TOOSKA_BEGIN_NAMESPACE(serialization)

token_serializer::token_serializer() : mode(mode_t::write), _obj(new json::json_object)
{

}
token_serializer::token_serializer(json::json_object *obj) : mode(mode_t::read),  _obj(obj)
{
    json::json_document d(obj);

    std::cout << d.to_string(tooska::print_type::compact)<<std::endl;
}

TOOSKA_END_NAMESPACE


