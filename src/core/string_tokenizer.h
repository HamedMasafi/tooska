#ifndef STRING_TOKENIZER_H
#define STRING_TOKENIZER_H

#include "tokenizer_base.h"

TOOSKA_BEGIN_NAMESPACE(core)

class string_tokenizer : public tokenizer_base
{
                                    std::string _data;
    std::string::iterator _index;
public:
    string_tokenizer();

    std::string data() const;
    void set_data(const std::string &data);

    bool readchar(char *ch) override;
    bool atend() override;
};

TOOSKA_END_NAMESPACE

#endif // STRING_TOKENIZER_H
