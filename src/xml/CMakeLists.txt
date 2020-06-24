# file(GLOB SOURCES "*.cpp")
set(SOURCES
   ${SOURCES}
   ${CMAKE_CURRENT_SOURCE_DIR}/node_finder.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/xml_document.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/xml_node.cpp
   PARENT_SCOPE
)

set(HEADERS
   ${HEADERS}
   ${CMAKE_CURRENT_SOURCE_DIR}/*.h
   PARENT_SCOPE
)

