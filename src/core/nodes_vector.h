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

    T *first()
    {
        return this->size() ? this->at(0) : nullptr;
    }

    T *last()
    {
        return this->size() ? this->at(this->size() - 1) : nullptr;
    }

    void for_each(const std::function<void(T*)> &callback) {
        std::for_each(this->begin(), this->end(), callback);
    }
    void delete_all() {
        std::for_each(this->begin(), this->end(), [&](T *node){
            delete node;
        });
        this->clear();
    }
};

TOOSKA_END_NAMESPACE

#endif // NODES_VECTOR_H
