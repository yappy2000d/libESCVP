cmake_minimum_required(VERSION 3.14)
project(libESCVP LANGUAGES CXX)

option(libESCVP_BUILD_SHARED "Build shared library" ON)

add_library(libESCVP INTERFACE)
target_include_directories(libESCVP INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")

if(WIN32)
    set(libESCVP_LIB "${CMAKE_CURRENT_SOURCE_DIR}/lib/libESCVP.dll")
elseif(UNIX)
    set(libESCVP_LIB "${CMAKE_CURRENT_SOURCE_DIR}/lib/libESCVP.so")
endif()

target_link_libraries(libESCVP INTERFACE "${libESCVP_LIB}")

# 安裝規則
install(TARGETS libESCVP EXPORT libESCVPConfig)
install(FILES include/libESCVP.h DESTINATION include)
install(FILES "${libESCVP_LIB}" DESTINATION lib)