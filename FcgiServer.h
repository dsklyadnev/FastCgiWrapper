#pragma once

#include <mutex>
#include <vector>

class FcgiRequest;
class FcgiResponse;

class FcgiServer
{
public:
  typedef std::function<void(const FcgiRequest&, FcgiResponse&)> RequestHandler;

  FcgiServer(const std::string & host, uint16_t port);
  bool start();
  void setRequestHandler(const RequestHandler & requestHandler);
private:
  std::string host;
  uint16_t port = 0;
  int socketId = 0;
  uint8_t threadCount = 0;
  std::vector <pthread_t> threads;
  static std::mutex acceptMutex;
  RequestHandler requestHandler;
  static void *thread_func(void *a);  
};
