# Set names
set(LIB_NAME "lexer")

# Set includes
set(LIB_INCLUDE_DIR ${PROJECT_INCLUDE_DIR}/lexer)
set(HEADER_FILES
        "${LIB_INCLUDE_DIR}/Lexer.h")

# Set sources
set(SOURCE_FILES
        Lexer.cpp)

# Set libraries
set(PROJECT_LIBRARIES symbol util)
set(THIRD_PARTY_LIBRARIES spdlog)

# Creating Binary for main application
add_library(${LIB_NAME} STATIC ${HEADER_FILES} ${SOURCE_FILES})

target_include_directories(${LIB_NAME} PUBLIC
        "$<BUILD_INTERFACE:${LIB_INCLUDE_DIR}>"
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

target_link_libraries(${LIB_NAME} PRIVATE
        ${PROJECT_LIBRARIES}
        ${THIRD_PARTY_LIBRARIES})

# Enable a reasonable set of warnings (no, -Wextra is not reasonable)
target_compile_options(${LIB_NAME} PRIVATE
        "$<$<C_COMPILER_ID:AppleClang>:-Wall>"
        "$<$<C_COMPILER_ID:Clang>:-Wall>"
        "$<$<C_COMPILER_ID:GNU>:-Wall>")

# Disable msvc unsafe warnings
if (MSVC)
    target_compile_definitions(${LIB_NAME} PRIVATE
            _CRT_SECURE_NO_WARNINGS
            _CRT_NONSTDC_NO_WARNINGS)
endif ()