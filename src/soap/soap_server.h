#ifndef SOAP_SERVER_H
#define SOAP_SERVER_H

#include "../global.h"

namespace httplib {
class Server;
}
TOOSKA_BEGIN_NAMESPACE(soap)

class server
{
    httplib::Server *_server;
public:
    server();
};

TOOSKA_END_NAMESPACE

#endif // SOAP_SERVER_H
