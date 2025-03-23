#include <iostream>
#include <memory>

#include "core.h"
#include "db/db.h"
#include "http/http.h"

int main()
{
    auto db1 = std::make_shared<DB>("messenger_test1", "127.0.0.1:8081");
    auto db2 = std::make_shared<DB>("messenger_test2", "127.0.0.1:8082");
    auto http1 = std::make_shared<http_server>("8081");
    auto http2 = std::make_shared<http_server>("8082");

    auto core1 = std::make_unique<Core>(db1, http1);
    auto core2 = std::make_unique<Core>(db2, http2);

    core1->messagesManager->send_message(
        "Привет, Bob! Это Alice.",
        "127.0.0.1:8082"
    );

    // std::cout << "\n=== История у Bob c (127.0.0.1:8081) ===\n";
    // core2->dbManager->history("127.0.0.1:8081");

    core2->messagesManager->send_message(
        "Привет, Alice! Сообщение получил.",
        "127.0.0.1:8081"
    );

    std::cout << "\n=== История у Alice c (127.0.0.1:8082) ===\n";
    core1->dbManager->history("127.0.0.1:8082");

    std::cout << "\n=== История у Bob c (127.0.0.1:8081) ===\n";
    core2->dbManager->history("127.0.0.1:8081");

    std::cout << "\n[TEST] Тест завершён.\n";
    return 0;
}
