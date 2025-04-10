cmake_minimum_required(VERSION 3.10)

project(CoreDependencies)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# set(BOOST_ROOT "${CMAKE_SOURCE_DIR}/dependencies/boost")
# set(Boost_NO_SYSTEM_PATHS TRUE)
# set(Boost_NO_BOOST_CMAKE TRUE)


# find_package(Boost REQUIRED)
# if (Boost_FOUND)
#     message(STATUS "Boost found: ${Boost_INCLUDE_DIRS}")
# else()
#     message(FATAL_ERROR "Boost not found in ${BOOST_ROOT}!")
# endif()

add_library(CoreDependencies STATIC
    CoreDependencies.cpp
    CoreDependencies.h
)

target_include_directories(CoreDependencies PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/src/db
    ${CMAKE_SOURCE_DIR}/src/http
)