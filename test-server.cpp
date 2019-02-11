#include <nghttp2/asio_http2_server.h>
#include <iostream>
#include <fstream>
#include <random>
#include <boost/chrono.hpp>
#include <boost/thread/thread.hpp> 

using namespace nghttp2::asio_http2::server;



int main(int argc, char *argv[])
{
  boost::system::error_code ec;
  http2 server;
  server.num_threads(6);


  server.handle("/normal.html", [](const request &req, const response &res) {
    res.write_head(200);
    res.end(nghttp2::asio_http2::file_generator("html-files/normal.html"));
  });

  server.handle("/push.html", [](const request &req, const response &res) {
    boost::system::error_code ec;
    auto push = res.push(ec, "GET", "/push-style.css");
    push->write_head(200);
    push->end(nghttp2::asio_http2::file_generator("html-files/push-style.css"));

    res.write_head(200);
    res.end(nghttp2::asio_http2::file_generator("html-files/push_body.html"));
  });

  // The push does this:
  
  server.handle("/push-style.css", [](const request &req, const response &res) {
    res.write_head(200);
    res.end(nghttp2::asio_http2::file_generator("html-files/push-style.css"));
  });


  //
  // Start up the server
  //
  server.listen_and_serve(ec, "localhost", "4444");

  server.join();
}