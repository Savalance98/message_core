cmake_minimum_required(VERSION 3.15)
project(Messenger)

# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пути для поиска Boost (для macOS)
set(BOOST_ROOT $ENV{HOMEBREW_PREFIX}/opt/boost)
set(BOOST_LIBRARY_DIR $ENV{HOMEBREW_PREFIX}/opt/boost/lib)
set(BOOST_INCLUDEDIR $ENV{HOMEBREW_PREFIX}/opt/boost/include)


find_package(Boost 1.72.0 REQUIRED COMPONENTS system filesystem)


find_package(SQLite3 REQUIRED)


include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/dependencies
    ${CMAKE_SOURCE_DIR}/http
    ${CMAKE_SOURCE_DIR}/db
    ${CMAKE_SOURCE_DIR}/models
    ${Boost_INCLUDE_DIRS}
    ${SQLite3_INCLUDE_DIRS}
)


add_executable(Messenger
    main.cpp
    core.cpp
    dependencies/CoreDependencies.cpp
    http/http.cpp
    http/HTTPManager.cpp
    db/db.cpp
    db/DBManager.cpp
    models/MessagesManager.cpp
)

# Линкуем зависимости
target_link_libraries(Messenger
    PRIVATE
    Boost::system
    Boost::filesystem
    ${SQLite3_LIBRARIES}
)


if(APPLE)
    target_link_libraries(Messenger PRIVATE "-framework Foundation")
endif()