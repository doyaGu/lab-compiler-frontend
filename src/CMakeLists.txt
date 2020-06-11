# Set project include dir
set(PROJECT_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
#include_directories("${PROJECT_INCLUDE_DIR}")

# Project libraries
add_subdirectory(util)
add_subdirectory(symbol)
add_subdirectory(grammar)
add_subdirectory(inter)
add_subdirectory(lexer)
add_subdirectory(parser)

# Project applications
add_subdirectory(app)