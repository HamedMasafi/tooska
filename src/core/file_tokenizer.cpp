#include "file_tokenizer.h"

TOOSKA_BEGIN_NAMESPACE(core)

file_tokenizer::file_tokenizer(const std::string &file_path)
    : file(std::ifstream(file_path, std::fstream::in))
{
}

bool file_tokenizer::readchar(char *ch)
{
    char c;

    if (file >> std::noskipws >> c) {
        *ch = c;
        return true;
    }

    return false;
}

bool file_tokenizer::atend()
{
    return file.eof();
}

TOOSKA_END_NAMESPACE
