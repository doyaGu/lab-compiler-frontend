# Set names
set(LIB_NAME "inter")

# Set includes
set(LIB_INCLUDE_DIR ${PROJECT_INCLUDE_DIR}/inter)
set(HEADER_FILES
        "${LIB_INCLUDE_DIR}/Storage.h"
        "${LIB_INCLUDE_DIR}/Quaternion.h"
        "${LIB_INCLUDE_DIR}/Variable.h"
        "${LIB_INCLUDE_DIR}/Constant.h"
        "${LIB_INCLUDE_DIR}/Temp.h"
        "${LIB_INCLUDE_DIR}/Operand.h"
        "${LIB_INCLUDE_DIR}/Operator.h"
        "${LIB_INCLUDE_DIR}/Identifier.h"
        "${LIB_INCLUDE_DIR}/Expression.h"
        "${LIB_INCLUDE_DIR}/Node.h")

# Set sources
set(SOURCE_FILES
        Storage.cpp
        Quaternion.cpp
        Variable.cpp
        Constant.cpp
        Temp.cpp
        Operand.cpp
        Operator.cpp
        Identifier.cpp
        Expression.cpp
        Node.cpp)

# Set libraries
set(PROJECT_LIBRARIES symbol)
set(THIRD_PARTY_LIBRARIES)

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