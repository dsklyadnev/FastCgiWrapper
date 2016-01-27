#pragma once

#include <fcgi_config.h>
#include <fcgiapp.h>

#include <string>

class FcgiRequest
{
public:
  FcgiRequest(const FCGX_Request & request);
  std::string getParameter(const std::string & paramName);
private:
  FCGX_Request request;
};
