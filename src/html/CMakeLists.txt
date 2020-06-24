# file(GLOB SOURCES "*.cpp")
set(SOURCES
   ${SOURCES}
   ${CMAKE_CURRENT_SOURCE_DIR}/css_document.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/css_node.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/html_document.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/html_node.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/html_tag_vector.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/html_writer.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/query_parser.cpp
   PARENT_SCOPE
)

set(HEADERS
   ${HEADERS}
   ${CMAKE_CURRENT_SOURCE_DIR}/*.h
   PARENT_SCOPE
)

