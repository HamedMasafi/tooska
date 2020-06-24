# file(GLOB SOURCES "*.cpp")
set(SOURCES
   ${SOURCES}
   ${CMAKE_CURRENT_SOURCE_DIR}/class_generator.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/soap_client.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/soap_http_parser.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/soap_server.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/wsdl.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/wsdl_parser.cpp
   PARENT_SCOPE
)

set(HEADERS
   ${HEADERS}
   ${CMAKE_CURRENT_SOURCE_DIR}/class_generator.h
   ${CMAKE_CURRENT_SOURCE_DIR}/soap_client.h
   ${CMAKE_CURRENT_SOURCE_DIR}/soap_http_parser.h
   ${CMAKE_CURRENT_SOURCE_DIR}/soap_server.h
   ${CMAKE_CURRENT_SOURCE_DIR}/wsdl.h
   ${CMAKE_CURRENT_SOURCE_DIR}/wsdl_parser.h
   PARENT_SCOPE
)

