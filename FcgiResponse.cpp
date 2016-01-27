#include "FcgiResponse.h"

void FcgiResponse::addHeader(const std::string & name, const std::string & value)
{
  headers[name] = value;
}

std::string FcgiResponse::getHeader(const std::string & name) const
{
  auto it = headers.find(name);
  if (it != headers.end())
  {
    return it->second;
  }
  return std::string();
}

bool FcgiResponse::hasHeader(const std::string & name) const
{
  auto it = headers.find(name);
  return (it != headers.end());
}

void FcgiResponse::setBody(const std::string & body)
{
  this->body = body;
}

std::string FcgiResponse::getBody() const
{
  return body;
}

std::string FcgiResponse::httpResponse() const
{
  std::string resp;
  for(auto it = headers.begin(); it != headers.end(); ++it)
  {
    resp += it->first + ":" + it->second + "\r\n";
  }
  resp += "\r\n" + body;
  return resp;
}
