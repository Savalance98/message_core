#pragma once
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <functional>
#include <string>
#include <memory>

namespace asio = boost::asio;
namespace beast = boost::beast;
namespace http = beast::http;

class http_server final {
public:
    using RequestHandler = std::function<void(const std::string&, const std::string&)>;
    
    explicit http_server(const std::string& port);
    ~http_server();
    
    void set_request_handler(RequestHandler handler);
    void send_message(const std::string& message, const std::string& ip, const std::string& port);
    void stop();

private:
    void start_accept();
    void handle_accept(const boost::system::error_code& ec);
    void read_request();
    void handle_read(const boost::system::error_code& ec, size_t bytes);
    void process_request();

    asio::io_context io_context_;
    asio::ip::tcp::acceptor acceptor_;
    asio::ip::tcp::socket socket_;
    beast::flat_buffer buffer_;
    http::request<http::string_body> request_;
    
    std::string port_;
    RequestHandler request_handler_;
    std::thread io_thread_;
    
    void run_io_context();
};