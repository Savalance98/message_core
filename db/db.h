#ifndef DB_H
#define DB_H

#include <iostream>
#include <string>
#include <sqlite3.h>
#include <filesystem>

class DB {
public:
    // Конструктор: dbname_ (название БД), ip_ (опционально, если хотите как-то различать инстансы)
    DB(const std::string& dbname_, const std::string& ip_);
    ~DB();

    // Метод для добавления сообщения: fromUser, toUser, message
    void add_message(const std::string& from, 
                     const std::string& to,
                     const std::string& message);

    // Метод для вывода/запроса истории сообщений (отправитель == peer ИЛИ получатель == peer)
    void get_history(const std::string& peer);

private:
    // Создание таблиц
    void create_tables();

private:
    std::string dbname;
    std::string db_path;
    std::string ip_address;
    sqlite3* db;
};

#endif
