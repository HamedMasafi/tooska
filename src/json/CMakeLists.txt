# file(GLOB SOURCES "*.cpp")
set(SOURCES
   ${SOURCES}
   ${CMAKE_CURRENT_SOURCE_DIR}/json_array.cpp  
   ${CMAKE_CURRENT_SOURCE_DIR}/json_document.cpp  
   ${CMAKE_CURRENT_SOURCE_DIR}/json_object.cpp  
   ${CMAKE_CURRENT_SOURCE_DIR}/json_value.cpp

   PARENT_SCOPE
)

set(HEADERS
   ${HEADERS}
   ${CMAKE_CURRENT_SOURCE_DIR}/*.h
   PARENT_SCOPE
)

