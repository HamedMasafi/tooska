#ifndef SOAP_CLIENT_H
#define SOAP_CLIENT_H

#include "../global.h"
#include <thread>
#include <functional>

namespace httplib {
class Client;
}

TOOSKA_BEGIN_NAMESPACE(serialization)
class serializable;
TOOSKA_END_NAMESPACE

TOOSKA_BEGIN_NAMESPACE(soap)

class client;

template<class T>
class response
{
    httplib::Client *_client;
    friend class client;
    typedef std::function<void(T*)> &callback;

    callback _callback;
    void send() {
        std::thread th([]{
//            _client.send
        });
    }
public:
    response(httplib::Client *client);
    void then(callback &cb) {
        _callback = cb;
    }
};

class client
{
    httplib::Client *_client;
public:
    client(const char* host, int port = 80);
    void invoke(const std::string &method_name, tooska::serialization::serializable *param);
};

TOOSKA_END_NAMESPACE

#endif // SOAP_CLIENT_H
