#include "HTTPResponse.hpp"

HTTPResponse::HTTPResponse(HTTPServer *sv) { sv_ = sv; }

HTTPResponse::~HTTPResponse() {}

int HTTPResponse::createResponseMessage() {
  unsigned int no_body_len;
  unsigned int body_len;
  response_message_[0] = '\0';
  if (sv_->get_status_() == 200) {
    sprintf(response_message_, "HTTP/1.1 200 OK\r\n%s\r\n",
            sv_->get_header_field_());

    no_body_len = strlen(response_message_);
    body_len = sv_->get_file_size_();

    memcpy(&response_message_[no_body_len], sv_->get_body_(), body_len);
  } else if (sv_->get_status_() == 404) {
    sprintf(response_message_, "HTTP/1.1 404 Not Found\r\n%s\r\n",
            sv_->get_header_field_());

    no_body_len = strlen(response_message_);
    body_len = 0;
  } else {
    // statusが200 404以外の時
    printf("Not support status(%d)\n", sv_->get_status_());
    return -1;
  }
  sv_->set_response_message_(response_message_);

  return no_body_len + body_len;
}

HTTPResponse::HTTPResponse(HTTPResponse const &other) { *this = other; }

HTTPResponse &HTTPResponse::operator=(HTTPResponse const &other) {
  if (this != &other) {
  }
  return *this;
}
