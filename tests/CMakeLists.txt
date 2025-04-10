cmake_minimum_required(VERSION 3.10)
project(MessengerTests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.4.0  # Укажем конкретную версию Catch2
)
FetchContent_MakeAvailable(Catch2)

add_executable(MessengerTests
    tests_main.cpp
)

target_link_libraries(MessengerTests PUBLIC
    Catch2::Catch2WithMain
    model
)

# target_link_libraries(MessengerTests PUBLIC
#     Boost
#     Catch2::Catch2WithMain  # Catch2 с предоставленным main()
#     CoreDependencies
#     DB
#     DBManager
#     HTTP
#     MessagesManager
# )


# target_include_directories(MessengerTests PRIVATE
#     ${CMAKE_SOURCE_DIR}/dependencies
#     ${CMAKE_SOURCE_DIR}/src/db
#     ${CMAKE_SOURCE_DIR}/src/http
#     ${CMAKE_SOURCE_DIR}/src/models
#     ${Boost_INCLUDE_DIRS}
#     ${CMAKE_SOURCE_DIR}/../dependencies/boost/libs/config/include
#     ${CMAKE_SOURCE_DIR}/../dependencies/boost/libs/system/include
#     ${CMAKE_SOURCE_DIR}/../dependencies/boost/libs/asio/include
#     ${CMAKE_SOURCE_DIR}/../dependencies/boost/libs/beast/include
# )