cmake_minimum_required(VERSION 3.10)

project(MessagesManager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_library(model STATIC
    core.h
    core.cpp
    MessagesManager.cpp
    MessagesManager.h
    TextMessage.h
    TextMessage.cpp
    Message.h
    History.cpp
    History.h
)

# Линкуем зависимости: CoreDependencies, DB, HTTP
target_link_libraries(model PUBLIC
    CoreDependencies
    DB
    HTTP
)


target_include_directories(model PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}           # Наша 
    ${CMAKE_SOURCE_DIR}/dependencies      
    ${CMAKE_SOURCE_DIR}/src/db            
    ${CMAKE_SOURCE_DIR}/src/http          
)