#include "string_tokenizer.h"

TOOSKA_BEGIN_NAMESPACE(core)

string_tokenizer::string_tokenizer()
{

}

std::string string_tokenizer::data() const
{
    return _data;
}

void string_tokenizer::set_data(const std::string &data)
{
    _data = data;
    _index = _data.begin();
}

bool string_tokenizer::readchar(char *ch)
{
    if (_index == _data.end())
        return false;
    *ch = *_index;
    _index++;
    return true;
}

bool string_tokenizer::atend()
{
    return _index == _data.end();
}

TOOSKA_END_NAMESPACE
