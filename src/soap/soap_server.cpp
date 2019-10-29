#include "soap_server.h"
#include "../core/httplib.h"

TOOSKA_BEGIN_NAMESPACE(soap)

server::server()
{
    _server = new httplib::Server;
    _server->listen("localhost", 80);
}

}}
