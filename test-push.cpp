#include <iostream>

#include <nghttp2/asio_http2_client.h>


using boost::asio::ip::tcp;

using namespace nghttp2::asio_http2::client;

int main(int argc, char *argv[])
{
  boost::system::error_code ec;
  boost::asio::io_service io_service;

  session sess(io_service, "localhost", "4444");


  sess.on_connect([&sess](tcp::resolver::iterator endpoint_it) {
    
    boost::system::error_code ec;
    auto req_push = sess.submit(ec, "GET", "http://localhost:4444/push.html");

    req_push->on_response([](const response &res) {
      res.on_data([](const uint8_t *data, std::size_t len) {
      });
    });

    req_push->on_push([](const request &push) {
      push.on_response([](const response &res) {
        res.on_data([](const uint8_t *data, std::size_t len) {
        });
      });
    });

    req_push->on_close([&sess](uint32_t error_code) {
      sess.shutdown();
    });
    

  });

  sess.on_error([](const boost::system::error_code &ec) {
    std::cerr << "error: " << ec.message() << std::endl;
  });

  auto wcts = std::chrono::system_clock::now();
  io_service.run();
  std::chrono::duration<double> wctduration = (std::chrono::system_clock::now() - wcts);
  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(wctduration).count() << std::endl;
  
}