// core.cpp
#include "core.h"

Core::Core(std::shared_ptr<DB>   db_,
           std::shared_ptr<http_server> http_)
{
    // Создаём зависимости
    this->dependencies = std::make_shared<CoreDependencies>(db_, http_);

    // Инициализируем менеджеры
    httpManager     = std::make_unique<HTTP_manager>(http_);
    dbManager       = std::make_unique<DB_manager>(db_);
    messagesManager = std::make_unique<Message_manager>(this->dependencies);
    // usersManager    = std::make_unique<Users_manager>(user_);

}
