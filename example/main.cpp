//#include <pthread.h>
//#include <sys/types.h>
#include <stdio.h>

//#include <string>

#include "FcgiServer.h"
#include "FcgiResponse.h"
#include "FcgiRequest.h"

void fcgiRequestHandler(const FcgiRequest & request, FcgiResponse & response)
{
  response.addHeader("Content-Type", "text/html");
  response.setBody("test");
}

int main(void)
{
  FcgiServer server("127.0.0.1", 9000);

  server.setRequestHandler(fcgiRequestHandler);

  if (server.start())
  {
    printf("Server started\n");
  }

  for(;;);

  return 0;
}

