#include <iostream>

#include <nghttp2/asio_http2_client.h>


using boost::asio::ip::tcp;

using namespace nghttp2::asio_http2::client;

int main(int argc, char *argv[])
{
  auto wcts = std::chrono::system_clock::now();

  for(int conns = 0; conns < 2; conns++)
  {
    boost::system::error_code ec;
    boost::asio::io_service io_service;

    session sess(io_service, "localhost", "4444");

    int num_connections = 10;
    std::shared_ptr<int> count = std::make_shared<int>(num_connections);

    sess.on_connect([&sess, &count, &num_connections](tcp::resolver::iterator endpoint_it) {
      boost::system::error_code ec;

      for(auto i = 0; i < num_connections; i++)
      {
        auto req_norm = sess.submit(ec, "GET", "http://localhost:4444/normal.html");
        req_norm->on_response([](const response &res) {
          res.on_data([](const uint8_t *data, std::size_t len) {
          });
        });

        req_norm->on_close([&sess, &count](uint32_t error_code) {
          if(--*count == 0)
          {
            
            sess.shutdown();
          }
        });


      } // end for
      

    });

    sess.on_error([](const boost::system::error_code &ec) {
      std::cerr << "error: " << ec.message() << std::endl;
    });

    io_service.run();
  }

  
  std::chrono::duration<double> wctduration = (std::chrono::system_clock::now() - wcts);
  std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(wctduration).count() << std::endl;
}