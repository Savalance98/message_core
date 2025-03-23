#include "db.h"

DB::DB(const std::string& dbname_, const std::string& ip_)
    : dbname(dbname_)
    , ip_address(ip_)
    , db_path(dbname_ + "_" + ip_ + ".db")
    , db(nullptr)
{
    bool dbExists = std::filesystem::exists(db_path);
    if (sqlite3_open(db_path.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Ошибка открытия базы данных: " << sqlite3_errmsg(db) << std::endl;
    }
    if (!dbExists) {
        create_tables();
    }
}

void DB::create_tables()
{
    // Создаём только таблицу messages
    const char* createMessagesTable =
        "CREATE TABLE IF NOT EXISTS messages ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "fromUser TEXT NOT NULL, "
        "toUser TEXT NOT NULL, "
        "message TEXT NOT NULL, "
        "status INTEGER NOT NULL DEFAULT 0"
        ");";

    char* errMsg = nullptr;
    if (sqlite3_exec(db, createMessagesTable, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Ошибка создания таблицы messages: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

void DB::add_message(const std::string& from, 
                     const std::string& to,
                     const std::string& message)
{
    // std::cout << from << " " << to << " " << message << std::endl;
    const char* insertMessageSql =
        "INSERT INTO messages (fromUser, toUser, message, status) "
        "VALUES (?, ?, ?, 0);";
    
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, insertMessageSql, -1, &stmt, nullptr) == SQLITE_OK) {
        // Привязываем параметры
        sqlite3_bind_text(stmt, 1, from.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, to.c_str(),   -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, message.c_str(), -1, SQLITE_TRANSIENT);

        if (sqlite3_step(stmt) != SQLITE_DONE) {
            std::cerr << "Ошибка при добавлении сообщения: " << sqlite3_errmsg(db) << std::endl;
        }
    } else {
        std::cerr << "Ошибка sqlite3_prepare_v2: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
}

void DB::get_history(const std::string& peer)
{
    // Выбираем все сообщения, где отправитель = peer ИЛИ получатель = peer
    const char* selectMessagesSql =
        "SELECT fromUser, toUser, message "
        "FROM messages "
        "WHERE fromUser = ? OR toUser = ?;";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(db, selectMessagesSql, -1, &stmt, nullptr) == SQLITE_OK) {
        // Привязываем peer к обоим параметрам
        sqlite3_bind_text(stmt, 1, peer.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, peer.c_str(), -1, SQLITE_TRANSIENT);

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            //выводим в консоль
            std::cout << sqlite3_column_text(stmt, 0) << " -> "
                      << sqlite3_column_text(stmt, 1) << ": "
                      << sqlite3_column_text(stmt, 2) << "\n";
        }
    } else {
        std::cerr << "Ошибка sqlite3_prepare_v2: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
}

DB::~DB()
{
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}
