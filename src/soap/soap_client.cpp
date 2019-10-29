#include "soap_client.h"

#include "../core/httplib.h"
#include "../serialization/soap_serializer.h"
#include "../serialization/serializable.h"
#include "../xml/xml_node.h"

TOOSKA_BEGIN_NAMESPACE(soap)

client::client(const char *host, int port)
{
    _client = new httplib::Client(host, port);
}

void client::invoke(const std::string &method_name, tooska::serialization::serializable *param)
{
    serialization::soap_serializer s;
    s.serialize(param);
    httplib::Headers headers;
//    headers["Content-Type"] = "text/xml; charset=utf-8";
//    headers["SOAPAction"] = "http://tempuri.org/Add";
    std::string body = s.node()->to_string(tooska::print_type::formatted);

    _client->Post(method_name.c_str(),
                  headers,
                  body,
                  "text/xml; charset=utf-8");
}

}}
