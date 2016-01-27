#pragma once

#include <map>

class FcgiResponse
{
public:
  void addHeader(const std::string & name, const std::string & value);
  std::string getHeader(const std::string & name) const;
  bool hasHeader(const std::string & name) const;
  void setBody(const std::string & body);
  std::string getBody() const;
  std::string httpResponse() const;
private:
  std::map<std::string, std::string> headers;
  std::string body;
};
