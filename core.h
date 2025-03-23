// core.h

#ifndef CORE_H
#define CORE_H

#include <memory>
#include <string>
// #include "models/User.h"
#include "db/db.h"
#include "http/http.h"
#include "models/MessagesManager.h"
// #include "models/UsersManager.h"
#include "db/DBManager.h"
#include "http/HTTPManager.h"
#include "dependencies/CoreDependencies.h"

class Core {
public:
    Core(std::shared_ptr<DB> db_,
         std::shared_ptr<http_server> http_);

    // Временно делаем поля публичными, чтобы в тесте писать core->messagesManager->...
    // (В рабочем коде обычно лучше использовать геттеры или методы-обёртки.)
public:
    std::unique_ptr<Message_manager> messagesManager;
    // std::unique_ptr<Users_manager>   usersManager;
    std::unique_ptr<DB_manager>      dbManager;
    std::unique_ptr<HTTP_manager>    httpManager;
    std::shared_ptr<CoreDependencies> dependencies;
};

#endif
