#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include "core.h"
#include "db/db.h"
#include "http/http.h"
#include "History.h"  // Для работы с классом History
#include "Message.h"  // Для работы с классом Message

TEST_CASE("Messenger: Send and Receive Messages", "[messenger]") {
    // Создаем два экземпляра базы данных и HTTP-серверов для Alice и Bob
    auto db1 = std::make_shared<DB>("messenger_test1", "127.0.0.1:8081");
    auto db2 = std::make_shared<DB>("messenger_test2", "127.0.0.1:8082");
    auto http1 = std::make_shared<http_server>("8081");
    auto http2 = std::make_shared<http_server>("8082");

    // Создаем два экземпляра Core
    auto core1 = std::make_unique<Core>(db1, http1); // Alice
    auto core2 = std::make_unique<Core>(db2, http2); // Bob

    SECTION("Alice sends a message to Bob") {
        // Alice отправляет сообщение Bob'у
        core1->get_messages_manager()->send_message(
            "Привет, Bob! Это Alice.",
            "127.0.0.1:8082"
        );

        // Даем время HTTP-серверу обработать сообщение
        std::this_thread::sleep_for(std::chrono::milliseconds(100));

        // Получаем историю у Alice для переписки с Bob'ом
        auto history_alice = core1->get_messages_manager()->get_history("127.0.0.1:8082");
        auto messages_alice = history_alice->get_messages();

        // Проверяем, что в истории Alice есть отправленное сообщение
        REQUIRE(messages_alice.size() == 1);
        REQUIRE(messages_alice[0] == "Привет, Bob! Это Alice.");

        // Получаем историю у Bob'а для переписки с Alice
        auto history_bob = core2->get_messages_manager()->get_history("127.0.0.1:8081");
        auto messages_bob = history_bob->get_messages();

        // Проверяем, что в истории Bob'а есть полученное сообщение
        REQUIRE(messages_bob.size() == 1);
        REQUIRE(messages_bob[0] == "Привет, Bob! Это Alice.");
    }

    // Останавливаем серверы перед завершением теста
    http1->stop();
    http2->stop();
}