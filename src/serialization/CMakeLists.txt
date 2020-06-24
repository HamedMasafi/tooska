# file(GLOB SOURCES "*.cpp")
set(SOURCES
   ${SOURCES}
   ${CMAKE_CURRENT_SOURCE_DIR}/json_serializer.cpp  
   ${CMAKE_CURRENT_SOURCE_DIR}/serializable.cpp  
   ${CMAKE_CURRENT_SOURCE_DIR}/serializer_base.cpp  
   ${CMAKE_CURRENT_SOURCE_DIR}/soap_serializer.cpp  
   ${CMAKE_CURRENT_SOURCE_DIR}/xml_serializer.cpp

   PARENT_SCOPE
)

set(HEADERS
   ${HEADERS}
   ${CMAKE_CURRENT_SOURCE_DIR}/*.h
   PARENT_SCOPE
)

