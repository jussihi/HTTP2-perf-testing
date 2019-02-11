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
    auto req_norm = sess.submit(ec, "GET", "http://localhost:4444/normal.html");

    req_norm->on_response([&sess](const response &res) {
      res.on_data([&sess](const uint8_t *data, std::size_t len) {

        // got data from first req, request the needed css file too!
        boost::system::error_code ec;
        auto req_another = sess.submit(ec, "GET", "http://localhost:4444/push-style.css");

        req_another->on_response([](const response &res) {
          res.on_data([](const uint8_t *data, std::size_t len) {

          });
        });

        req_another->on_close([&sess](uint32_t error_code) {
          sess.shutdown();
        });

      });
    });

    req_norm->on_close([&sess](uint32_t error_code) {
      
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