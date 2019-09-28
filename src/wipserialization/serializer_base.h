#ifndef SERIALIZER_BASE_H
#define SERIALIZER_BASE_H

#include "../global.h"
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include "../core/variant.h"

TOOSKA_BEGIN_NAMESPACE(serialization)

class serializable;
class serializer_base
{
public:
    enum mode_t {
        Unset,
        Deserialize,
        Serialize
    } mode;

    serializer_base();
    template<typename T>
    void set(const std::string &name, T &t)
    {
        if (mode == Deserialize) {
            if (has_key(name)) {
                std::string v;
                get_value(name, v);
            }
        } else if (mode == Serialize) {
            set_value(name, std::to_string(t));
        }
    }
    template<typename T>
    void set(const std::string &name, std::vector<T> &vec)
    {
        if (mode == Deserialize) {
            std::for_each(vec.begin(), vec.end(), [&name, this](T t) {
                if (has_key(name)) {
                    std::string v;
                    get_value(name, v);
                }
            });
        } else if (mode == Serialize) {
            tooska::core::variant_vector v =
                tooska::core::variant_vector::from_vector(vec);
            vec.clear();
//            set_value(name, std::to_string(t));
        }
    }
    template<typename T>
    void set(const std::string &name, T* &object)
    {
        if (!std::is_base_of<serializable, T>::value) {
            std::cerr << "The child for key " << name
                      << " is not derived from tooska::serialization::serializable"
                      << std::endl;
            return;
        }

        auto s = create_serializer();
        object->serialize(s);
        delete s;
    }

    virtual serializer_base *create_serializer() const = 0;
    virtual bool has_key(const std::string &key) const = 0;
    virtual void set_value(const std::string &name, const std::string &value) = 0;
    virtual void get_value(const std::string &name, std::string &value) = 0;
};

TOOSKA_END_NAMESPACE

#endif // SERIALIZER_BASE_H
