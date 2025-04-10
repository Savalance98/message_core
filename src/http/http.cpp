#include "http.h"
#include <iostream>

http_server::http_server(const std::string& port)
    : port_(port),
      acceptor_(io_context_),
      socket_(io_context_) {
    
    asio::ip::tcp::resolver resolver(io_context_);
    asio::ip::tcp::endpoint endpoint = *resolver.resolve("0.0.0.0", port_).begin();
    
    acceptor_.open(endpoint.protocol());
    acceptor_.set_option(asio::ip::tcp::acceptor::reuse_address(true));
    acceptor_.bind(endpoint);
    acceptor_.listen();
    
    start_accept();
    io_thread_ = std::thread(&http_server::run_io_context, this);
}

http_server::~http_server() {
    io_context_.stop();
    if(io_thread_.joinable()) io_thread_.join();
    
    if(acceptor_.is_open()) acceptor_.close();
    if(socket_.is_open()) socket_.close();
}

void http_server::set_request_handler(RequestHandler handler) {
    request_handler_ = std::move(handler);
}

void http_server::run_io_context() {
    io_context_.run();
}

// Остальные методы (start_accept, handle_accept, read_request, 
// handle_read, process_request) остаются без изменений из предыдущей реализации

void http_server::send_message(const std::string& message, const std::string& ip, const std::string& port) {
    try {

        asio::ip::tcp::resolver resolver(io_context_);
        asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(ip, port);
        
        asio::ip::tcp::socket socket(io_context_);
        asio::connect(socket, endpoints);

        // Добавляем порт сервера в тело сообщения
        std::string full_msg = "SERVER_PORT:" + port_ + "|" + message;

        http::request<http::string_body> req{http::verb::post, "/", 11};
        req.set(http::field::host, ip);
        req.body() = full_msg;
        req.prepare_payload();

        http::write(socket, req);
        
        beast::flat_buffer buffer;
        http::response<http::string_body> res;
        http::read(socket, buffer, res);

    } catch (const std::exception& e) {
        std::cerr << "Send error: " << e.what() << std::endl;
    }
}

void http_server::start_accept() {
    acceptor_.async_accept(
        socket_,
        [this](const boost::system::error_code& ec) {
            handle_accept(ec);
        });
}

void http_server::handle_accept(const boost::system::error_code& ec) {
    if(!ec) {
        read_request();
    }
    start_accept();
}

void http_server::read_request() {
    http::async_read(
        socket_,
        buffer_,
        request_,
        [this](const boost::system::error_code& ec, size_t bytes) {
            handle_read(ec, bytes);
        });
}

void http_server::handle_read(const boost::system::error_code& ec, size_t) {
    if(!ec) {
        process_request();
    }
}

void http_server::process_request() {
    std::string remote_ip = socket_.remote_endpoint().address().to_string();
    std::string msg = request_.body();

    // Парсим SERVER_PORT из тела сообщения
    size_t port_pos = msg.find("SERVER_PORT:");
    std::string sender_port = port_;
    
    if (port_pos != std::string::npos) {
        size_t delimiter = msg.find("|", port_pos);
        sender_port = msg.substr(port_pos + 12, delimiter - (port_pos + 12));
        msg = msg.substr(delimiter + 1);
    }

    std::string sender = remote_ip + ":" + sender_port;

    if (request_handler_) {
        request_handler_(msg, sender);
    }

    http::response<http::string_body> res{http::status::ok, request_.version()};
    res.body() = "OK";
    res.prepare_payload();
    http::write(socket_, res);
    socket_.shutdown(asio::ip::tcp::socket::shutdown_send);
}



void http_server::stop() {
    io_context_.stop();
    if(io_thread_.joinable()) io_thread_.join();
}