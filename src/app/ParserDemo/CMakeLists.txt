# Set names
set(APP_NAME "ParserDemo")

# Set includes
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
set(HEADER_FILES)

# Set sources
set(SOURCE_FILES ParserDemo.cpp)

# Set libraries
set(PROJECT_LIBRARIES parser lexer grammar symbol util)
set(THIRD_PARTY_LIBRARIES)

# Creating Binary for main application
add_executable(${APP_NAME} ${HEADER_FILES} ${SOURCE_FILES})
target_link_libraries(${APP_NAME} PRIVATE
        ${PROJECT_LIBRARIES}
        ${THIRD_PARTY_LIBRARIES})

# Enable a reasonable set of warnings (no, -Wextra is not reasonable)
target_compile_options(${APP_NAME} PRIVATE
        "$<$<C_COMPILER_ID:AppleClang>:-Wall>"
        "$<$<C_COMPILER_ID:Clang>:-Wall>"
        "$<$<C_COMPILER_ID:GNU>:-Wall>")

# Disable msvc unsafe warnings
if (MSVC)
    target_compile_definitions(${APP_NAME} PRIVATE
            _CRT_SECURE_NO_WARNINGS
            _CRT_NONSTDC_NO_WARNINGS)
endif ()