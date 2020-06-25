#ifndef FILE_TOKENIZER_H
#define FILE_TOKENIZER_H

#include "tokenizer_base.h"
#include <fstream>
#include <iostream>

TOOSKA_BEGIN_NAMESPACE(core)

class file_tokenizer : public tokenizer_base
{
                                  std::ifstream file;

public:
    file_tokenizer(const std::string &file_path);
    bool readchar(char *ch) override;
    bool atend() override;
};

TOOSKA_END_NAMESPACE

#endif // FILE_TOKENIZER_H
