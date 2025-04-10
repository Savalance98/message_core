// #include <iostream>
// #include <memory>

// #include "core.h"
// #include "db/db.h"
// #include "http/http.h"

// int main()
// {
//     auto db1 = std::make_shared<DB>("messenger_test1", "127.0.0.1:8081");
//     auto db2 = std::make_shared<DB>("messenger_test2", "127.0.0.1:8082");
//     auto http1 = std::make_shared<http_server>("8081");
//     auto http2 = std::make_shared<http_server>("8082");

//     auto core1 = std::make_unique<Core>(db1, http1);
//     auto core2 = std::make_unique<Core>(db2, http2);

//     core1->messagesManager->send_message(
//         "Привет, Bob! Это Alice.",
//         "127.0.0.1:8082"
//     );
//     // std::cout << "\n=== История у Bob c (127.0.0.1:8081) ===\n";
//     // core2->dbManager->history("127.0.0.1:8081");

//     core2->messagesManager->send_message(
//         "Привет, Alice! Сообщение получил.",
//         "127.0.0.1:8081"
//     );

//     std::cout << "\n=== История у Alice c (127.0.0.1:8082) ===\n";
//     core1->dbManager->history("127.0.0.1:8082");

//     std::cout << "\n=== История у Bob c (127.0.0.1:8081) ===\n";
//     core2->dbManager->history("127.0.0.1:8081");

//     std::cout << "\n[TEST] Тест завершён.\n";
//     return 0;
// }
#include <iostream>
#include <string>
#include "core.h"
#include "db/db.h"
#include "http/http.h"
#include "dependencies/CoreDependencies.h"

int main() {
    std::cout << "=== Welcome to MyMessenger! ===\n";

    // Инициализация компонентов
    std::string ip_port;
    std::cout << "Enter your IP:Port (e.g., 127.0.0.1:8080): ";
    std::getline(std::cin, ip_port);

    // Извлекаем порт из ip_port
    size_t colon_pos = ip_port.find(':');
    if (colon_pos == std::string::npos) {
        std::cerr << "Invalid IP:Port format. Expected 'IP:PORT'.\n";
        return 1;
    }
    std::string port = ip_port.substr(colon_pos + 1);

    // Создаем объекты
    auto db = std::make_shared<DB>("messenger_db", ip_port);
    auto http = std::make_shared<http_server>(port);
    auto core = std::make_unique<Core>(db, http);

    std::cout << "Messenger started on " << ip_port << "\n";
    std::cout << "Commands:\n";
    std::cout << "  send <IP:Port> <message> - Send a message to another user\n";
    std::cout << "  history <IP:Port>        - View message history with a user\n";
    std::cout << "  exit                     - Exit the application\n";

    // Основной цикл приложения
    std::string command;
    while (true) {
        std::cout << "\n> ";
        std::getline(std::cin, command);

        // Разбиваем команду на части
        std::string action, target, message;
        size_t first_space = command.find(' ');
        if (first_space == std::string::npos) {
            action = command;
        } else {
            action = command.substr(0, first_space);
            std::string rest = command.substr(first_space + 1);
            size_t second_space = rest.find(' ');
            if (second_space == std::string::npos) {
                target = rest;
            } else {
                target = rest.substr(0, second_space);
                message = rest.substr(second_space + 1);
            }
        }

        // Обработка команд
        if (action == "exit") {
            std::cout << "Shutting down...\n";
            http->stop(); // Останавливаем HTTP-сервер перед выходом
            break;
        } else if (action == "send" && !target.empty() && !message.empty()) {
            try {
                core->get_messages_manager()->send_message(message, target);
                std::cout << "Message sent to " << target << ": " << message << "\n";
            } catch (const std::exception& e) {
                std::cerr << "Error sending message: " << e.what() << "\n";
            }
        } else if (action == "history" && !target.empty()) {
            std::cout << "=== History with " << target << " ===\n";
            core->get_db_manager()->history(target);
        } else {
            std::cout << "Invalid command. Available commands:\n";
            std::cout << "  send <IP:Port> <message>\n";
            std::cout << "  history <IP:Port>\n";
            std::cout << "  exit\n";
        }
    }

    return 0;
}