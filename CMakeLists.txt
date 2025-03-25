cmake_minimum_required(VERSION 3.15)
project(Messenger)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем SQLite
find_package(SQLite3 REQUIRED)

# Компилируем Boost из подмодуля
add_subdirectory(dependencies/boost)

# Добавляем остальные твои подмодули
add_subdirectory(db)
add_subdirectory(http)
add_subdirectory(models)
add_subdirectory(dependencies)

# Исполняемый файл
add_executable(Messenger
    main.cpp
    core.cpp
)

# Подключаем заголовочные файлы Boost
# Предполагается, что у тебя заголовки Boost по пути dependencies/boost
# Если путь отличается, поправь соответственно

target_include_directories(Messenger PRIVATE
    dependencies/boost
)

# Линкуем собранные вручную библиотеки Boost
# Убедись, что имена целей именно такие (boost_system и boost_filesystem)
target_link_libraries(Messenger PRIVATE
    db
    http
    models
    coredependencies
    SQLite::SQLite3
    boost_system
    boost_filesystem
)

# Линкуем фреймворк для macOS
if(APPLE)
    target_link_libraries(Messenger PRIVATE "-framework Foundation")
endif()
