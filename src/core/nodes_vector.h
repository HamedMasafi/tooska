#ifndef NODES_VECTOR_H
#define NODES_VECTOR_H

#include "global.h"

#include <vector>
#include <functional>
#include <algorithm>

TOOSKA_BEGIN_NAMESPACE(core)

template <class T>
class nodes_vector : public std::vector<T *>
{
public:
    nodes_vector()
    {}

    T *first_or_null()
    {
        return this->size() ? this->at(0) : nullptr;
    }

    T *last_or_null()
    {
        return this->size() ? this->at(this->size() - 1) : nullptr;
    }

    void for_each(std::function<void(T*)> &callback) {
        std::for_each(this->begin(), this->end(), callback);
    }
};

TOOSKA_END_NAMESPACE

#endif // NODES_VECTOR_H
