file(GLOB SOURCES "core/*.cpp" "html/*.cpp" "json/*.cpp" "serialization/*.cpp" "soap/*.cpp" "xml/*.cpp")
#add_subdirectory(core)
#add_subdirectory(html)
#add_subdirectory(json)
#add_subdirectory(serialization)


add_library(tooska SHARED ${SOURCES})
#include_directories("src")
target_include_directories (tooska PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

