#include "FcgiRequest.h"

FcgiRequest::FcgiRequest(const FCGX_Request & request)
  : request(request)
{
}

std::string FcgiRequest::getParameter(const std::string & paramName)
{
  return FCGX_GetParam(paramName.c_str(), request.envp);
}
