file(GLOB SOURCES "core/*.cpp" "html/*.cpp" "json/*.cpp" "soap/*.cpp" "xml/*.cpp" "serialization/*.cpp")
#add_subdirectory(core)
#add_subdirectory(html)
#add_subdirectory(json)
#add_subdirectory(serialization)


add_library(tooska SHARED ${SOURCES})
#include_directories("src")
find_package (Threads)

target_include_directories (tooska PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries (tooska ${CMAKE_THREAD_LIBS_INIT})

