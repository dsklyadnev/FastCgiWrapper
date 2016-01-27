#include "FcgiServer.h"

#include <thread>

#include <fcgi_config.h>
#include <fcgiapp.h>

#include "FcgiRequest.h"
#include "FcgiResponse.h"

std::mutex FcgiServer::acceptMutex;

FcgiServer::FcgiServer(const std::string & host, uint16_t port)
  : host(host),
    port(port),
    threadCount(std::thread::hardware_concurrency())
{
}

bool FcgiServer::start()
{
  std::string socketPath = host + ":" + std::to_string(port);
  FCGX_Init();
  socketId = FCGX_OpenSocket(socketPath.c_str(), 20);
  if(socketId < 0)
  {
    //ошибка при открытии сокета
    return false;
  }
  printf("Socket is opened\n");

  //создаём рабочие потоки
  for(auto i = 0; i < threadCount; i++)
  {
    pthread_t id = 0;
    pthread_create(&id, NULL, thread_func, this);
    threads.push_back(id);
  }
  return true;
}

void FcgiServer::setRequestHandler(const RequestHandler & requestHandler)
{
  this->requestHandler = requestHandler;
}

void *FcgiServer::thread_func(void *a)
{
    int rc;
    FCGX_Request request;
    FcgiServer * server = (FcgiServer*)a;

    if(FCGX_InitRequest(&request, server->socketId, 0) != 0)
    {
      //ошибка при инициализации структуры запроса
        printf("Can not init request\n");
      return NULL;
    }
    printf("Request is inited\n");

    for(;;)
    {
//        static pthread_mutex_t accept_mutex = PTHREAD_MUTEX_INITIALIZER;

        //попробовать получить новый запрос
        printf("Try to accept new request\n");
        //
//        pthread_mutex_lock(&accept_mutex);
      {
        std::unique_lock <std::mutex> lock(acceptMutex);
        rc = FCGX_Accept_r(&request);
//        pthread_mutex_unlock(&accept_mutex);
      }
        if(rc < 0)
        {
          //ошибка при получении запроса
            printf("Can not accept new request\n");
            break;
        }
        printf("request is accepted\n");

        FcgiRequest  fcgiRequest(request);
        FcgiResponse fcgiResponse;

        server->requestHandler(fcgiRequest, fcgiResponse);

        FCGX_PutS(fcgiResponse.httpResponse().c_str(), request.out);

        //закрыть текущее соединение
        FCGX_Finish_r(&request);

        //завершающие действия - запись статистики, логгирование ошибок и т.п.
    }
    return NULL;
}
