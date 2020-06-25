# file(GLOB SOURCES "*.cpp")
set(SOURCES
   ${SOURCES}
   ${CMAKE_CURRENT_SOURCE_DIR}/command_line_parser.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/converter.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/doc_node_base.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/nodes_vector.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/string_helper.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/string_renderer.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/token_parser.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/tree.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/variant.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/tokenizer_base.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/string_tokenizer.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/file_tokenizer.cpp
#   ${CMAKE_CURRENT_SOURCE_DIR}/shared_data.cpp
   PARENT_SCOPE
)

set(HEADERS
   ${HEADERS}
   ${CMAKE_CURRENT_SOURCE_DIR}/command_line_parser.h
   ${CMAKE_CURRENT_SOURCE_DIR}/converter.h
   ${CMAKE_CURRENT_SOURCE_DIR}/doc_node_base.h
   ${CMAKE_CURRENT_SOURCE_DIR}/nodes_vector.h
   ${CMAKE_CURRENT_SOURCE_DIR}/string_helper.h
   ${CMAKE_CURRENT_SOURCE_DIR}/string_renderer.h
   ${CMAKE_CURRENT_SOURCE_DIR}/token_parser.h
   ${CMAKE_CURRENT_SOURCE_DIR}/tree.h
   ${CMAKE_CURRENT_SOURCE_DIR}/variant.h
   PARENT_SCOPE
)

