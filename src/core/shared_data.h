#ifndef SHARED_DATA_H
#define SHARED_DATA_H

#include "../global.h"
#include <atomic>

TOOSKA_BEGIN_NAMESPACE(core)

class shared_data
{
public:
    mutable std::atomic_uint ref;
    inline shared_data() noexcept : ref(0) { }
    inline shared_data(const shared_data &) noexcept : ref(0) { }

    shared_data &operator=(const shared_data &) = delete;
    ~shared_data() = default;
};

template <class T>
class shared_data_pointer
{
public:
    typedef T Type;
    typedef T *pointer;

    inline T &operator*() const { return *d; }
    inline T *operator->() { return d; }
    inline T *operator->() const { return d; }
    inline T *data() const { return d; }
    inline const T *constData() const { return d; }
    inline T *take() { T *x = d; d = nullptr; return x; }

    inline void detach() {
        if (d && d->ref.load() != 1)
            detach_helper();
    }
    inline void reset()
    {
        if(d && !d->ref.fetch_sub(1))
            delete d;
        d = nullptr;
    }

protected:
    T *clone();

private:
    void detach_helper();
    shared_data *d;
};

template <class T>
T *shared_data_pointer<T>::clone()
{
    return new T(*d);
}

template <class T>
void shared_data_pointer<T>::detach_helper()
{
    T *x = clone();
    x->ref.ref();
    if (!d->ref.deref())
        delete d;
    d = x;
}

TOOSKA_END_NAMESPACE

#endif // SHARED_DATA_H
