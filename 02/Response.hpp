#ifndef HTTPRESPONSE_HPP
#define HTTPRESPONSE_HPP

class Response {
 public:
  Response();
  virtual ~Response();
  Response(Response const &other);
  Response &operator=(Response const &other);

 private:
};

#endif
