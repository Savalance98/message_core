cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SQLite3 REQUIRED)
if (SQLite3_FOUND)
    include_directories(${SQLite3_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "SQLite3 not found!")
endif()


add_library(DB STATIC
    db.cpp
    db.h
    MessageRecord.h
    MessageRecord.cpp
)


target_link_libraries(DB PRIVATE ${SQLite3_LIBRARIES})


target_include_directories(DB PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)


# add_library(DBManager STATIC
#     DBManager.cpp
#     DBManager.h
# )


# target_link_libraries(DBManager PUBLIC DB)


# target_include_directories(DBManager PUBLIC
#     ${CMAKE_CURRENT_SOURCE_DIR}
# )