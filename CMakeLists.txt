cmake_minimum_required(VERSION 3.10)

project(MyMessenger)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ICU_ROOT "/opt/homebrew/Cellar/icu4c@77/77.1")
include_directories(${ICU_ROOT}/include)
link_directories(${ICU_ROOT}/lib)

include_directories(src)
include_directories(dependencies)



# connect boost
add_subdirectory(dependencies/boost)
# /opt/homebrew/Cellar/icu4c@77/77.1/include/unicode/ucnv.h
# include_directories(/opt/homebrew/Cellar/icu4c@77/77.1/include/unicode/)

include_directories(${CMAKE_SOURCE_DIR}/dependencies/boost)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/boost/libs/align/include)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/boost/libs/mpl/include)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/boost/libs/asio/include)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/boost/libs/logic/include)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/boost/libs/beast/include)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/boost/libs/static_string/include)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/boost/libs/smart_ptr/include)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/boost/libs/static_assert/include)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/boost/libs/numeric/conversion/include)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/boost/libs/preprocessor/include)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/boost/libs/type_traits/include)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/boost/libs/core/include)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/boost/libs/utility/include)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/boost/libs/date_time/include)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/boost/libs/process/include)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/boost/libs/config/include)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/boost/libs/assert/include)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/boost/libs/throw_exception/include)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/boost/libs/system/include)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/boost/libs/uuid/include)
include_directories(${CMAKE_SOURCE_DIR}/dependencies/boost/libs/endian/include)
include_directories(${BOOST_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/dependencies/boost/libs/locale/src/icu)


add_subdirectory(dependencies)
#add_subdirectory(dependencies/boost)!!!
add_subdirectory(src/db)
add_subdirectory(src/http)
add_subdirectory(src/models)
add_subdirectory(tests)




add_custom_target(run_tests
    COMMAND MessengerTests
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/tests
    DEPENDS MessengerTests
    COMMENT "Running tests..."
)